#include<iostream>
#include "OCR.h"
#include <memory>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <cctype>
#include <algorithm>

COCR::COCR(const std::string &path) : m_path(path), m_process(path)
{
	char *env =  getenv("TESSDATA_PREFIX");
	
	if(nullptr != env)
	{
		m_tessDataPath = env;
	}
}

void COCR::init(const std::string &data, const std::string &lang)
{
	setenv("TESSDATA_PREFIX", data.c_str(), 1);
	m_tess.Init(NULL, lang.c_str());
	m_tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
	m_tess.SetVariable("save_blob_choices", "T");
}

std::vector<std::pair<std::string,int> > COCR::perform()
{
	cv::Mat img;
	cv::cvtColor(m_process.getOriginalImg(), img, CV_BGR2GRAY);

	if(false == img.empty())
	{
		std::vector<std::pair<std::string,int> > results;
		m_tess.SetImage((uchar*)img.data, img.cols, img.rows, 1, img.cols);
		std::unique_ptr<Boxa> boxes( m_tess.GetComponentImages(
									tesseract::RIL_TEXTLINE, 
									true, NULL, NULL) );
		
		for (int i = 0; i < boxes->n; i++) 
		{
			std::unique_ptr<BOX> box( boxaGetBox(boxes.get(), i, L_CLONE) );
			m_tess.SetRectangle(box->x, box->y, box->w, box->h);
			m_process.markTextBox( cv::Rect(box->x, box->y, box->w, box->h) );

			std::string ocrResult = m_tess.GetUTF8Text();
			
			//verifyConfidence(ocrResult, NULL);
			if(false == ocrResult.empty())
			{
				postProcess(ocrResult);
				std::clog << ocrResult << " with confidence " <<m_tess.MeanTextConf() << std::endl;
				results.push_back(std::make_pair(ocrResult, m_tess.MeanTextConf()));
			}
			
		}

		return results;
	}
	
	return std::vector<std::pair<std::string, int> >();	
}

void COCR::postProcess(std::string &exp)
{
	boost::replace_all(exp, "\"", "^");
	boost::replace_all(exp, "\n", "");
	boost::to_lower(exp);
}

void COCR::verifyConfidence(std::string &str, int *tab)
{
	tesseract::ResultIterator *iter = m_tess.GetIterator();
	do
	{
		std::cout << iter->GetUTF8Text(tesseract::RIL_SYMBOL) << " " << iter->Confidence(tesseract::RIL_SYMBOL) << std::endl;
	}
	while(iter->Next(tesseract::RIL_SYMBOL) );
}


COCR::~COCR()
{
	m_tess.End();
	setenv("TESSDATA_PREFIX", m_tessDataPath.c_str(), 1);
}
