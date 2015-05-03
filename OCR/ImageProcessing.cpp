#include "ImageProcessing.h"

CImageProcessing::CImageProcessing(const std::string &path)
{
	m_originalImg = cv::imread(path.c_str(), CV_LOAD_IMAGE_COLOR);
}

void CImageProcessing::process()
{
	if(0 == m_originalImg.data || 0 != m_processedImg.data)
	{
		return;
	}

	cv::cvtColor(m_originalImg, m_processedImg, CV_BGR2GRAY);	
}


