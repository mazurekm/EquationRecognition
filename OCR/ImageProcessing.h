#ifndef IMAGE_PROCESSING
#define IMAGE_PROCESSING

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class CImageProcessing
{
public:
	CImageProcessing(const std::string &path);
	void process();

	cv::Mat getOriginalImg() const
	{
		return m_originalImg;
	}

	cv::Mat getProcessedImg() const
	{
		return m_processedImg;
	}

private:
	cv::Mat m_originalImg;
	cv::Mat m_processedImg;
		
};

#endif
