#ifndef IMAGE_PROCESSING
#define IMAGE_PROCESSING

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>

class CImageProcessing
{
public:
	CImageProcessing(const std::string &path);
	CImageProcessing();

	cv::Mat process(const cv::Mat & img);

	cv::Mat getOriginalImg() const
	{
		return m_originalImg;
	}

	cv::Mat getProcessedImg() const
	{
		return m_processedImg;
	}

	void markTextBox(const cv::Rect &rect);

	static void showImg(const cv::Mat &img, int time);
	std::vector<cv::Mat> detectLetters();

private:
	cv::Mat m_originalImg;
	cv::Mat m_processedImg;
		
};

#endif
