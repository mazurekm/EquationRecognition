#include<iostream>
#include "OCR.h"
#include <memory>
#include <cstdlib>

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
	m_process.process();
	cv::Mat img = m_process.getProcessedImg();

	if(false == img.empty())
	{
		std::vector<std::pair<std::string,int> > results;
		m_tess.SetImage((uchar*)img.data, img.cols, img.rows, 1, img.cols);
		Boxa* boxes = m_tess.GetComponentImages(tesseract::RIL_TEXTLINE, true, NULL, NULL);
		
		for (int i = 0; i < boxes->n; i++) 
		{
			std::unique_ptr<BOX> box( boxaGetBox(boxes, i, L_CLONE) );
			m_tess.SetRectangle(box->x, box->y, box->w, box->h);
			std::string ocrResult = m_tess.GetUTF8Text();
		
			verifyConfidence(ocrResult, NULL);

			if(false == ocrResult.empty())
			{
				std::clog << ocrResult << " with confidence " <<m_tess.MeanTextConf() << std::endl;
				results.push_back(std::make_pair(m_evaluator(ocrResult), m_tess.MeanTextConf()));
			}
			
		}

		return results;
	}
	
	return std::vector<std::pair<std::string, int> >();	
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
