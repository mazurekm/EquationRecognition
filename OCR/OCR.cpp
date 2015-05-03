#include<iostream>
#include "OCR.h"

COCR::COCR(const std::string &path) : m_path(path), m_process(path)
{
	init();
}

void COCR::init()
{
	m_tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
	m_tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
}

std::string COCR::perform()
{
	m_process.process();
	cv::Mat img = m_process.getProcessedImg();

	if(false == img.empty())
	{
		m_tess.SetImage((uchar*)img.data, img.cols, img.rows, 1, img.cols);
		char* out = m_tess.GetUTF8Text();	
		return std::string(out);
	}
	
	return "";	
}
	
