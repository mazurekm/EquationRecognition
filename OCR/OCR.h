#ifndef OCR_H
#define OCR_H

#include<string>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<tesseract/baseapi.h>
#include<leptonica/allheaders.h>

#include "Evaluator.h"
#include "ImageProcessing.h"

class COCR
{
public:
	COCR(const std::string &path);
	void init();
	std::string perform();

private:
	std::string m_path;
	CEvaluator m_evaluator;
	CImageProcessing m_process;
	tesseract::TessBaseAPI m_tess;	

};

#endif
