#ifndef OCR_H
#define OCR_H

#include<string>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<tesseract/baseapi.h>
#include<leptonica/allheaders.h>
#include <utility>


#include "Evaluator.h"
#include "ImageProcessing.h"

class COCR
{
public:
	COCR(const std::string &path);
	void init(const std::string &data, const std::string &lang = "eng");
	std::vector<std::pair<std::string, int> > perform();
	
	cv::Mat getProcessedImg() const
	{
		return m_process.getProcessedImg();
	}

	~COCR();

private:

	void verifyConfidence(std::string &str, int *tab);
	void postProcess(std::string &exp);

	std::string m_path;
	CEvaluator m_evaluator;
	CImageProcessing m_process;
	tesseract::TessBaseAPI m_tess;
	std::string m_tessDataPath;	

};

#endif
