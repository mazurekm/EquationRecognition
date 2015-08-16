#include "ImageProcessing.h"

CImageProcessing::CImageProcessing(const std::string &path)
{
	m_originalImg = cv::imread(path.c_str(), CV_LOAD_IMAGE_COLOR);
	m_processedImg = m_originalImg.clone();
}

CImageProcessing::CImageProcessing()
{

}

cv::Mat CImageProcessing::process(const cv::Mat &img)
{
	return img;	
}

void CImageProcessing::markTextBox(const cv::Rect &rect)
{
	cv::rectangle(m_processedImg, rect, cv::Scalar(255,0,0), 2);
}

std::vector<cv::Mat> CImageProcessing::detectLetters()
{
	std::vector<cv::Rect> boundRect;
    cv::Mat imgAsGray, imgBySobel, imgThreshold;
    
    cv::cvtColor(m_originalImg, imgAsGray, CV_BGR2GRAY);
    cv::Sobel(imgAsGray, imgBySobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::threshold(imgBySobel, imgThreshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
    
    cv::Mat strElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(17, 3) );
    cv::morphologyEx(imgThreshold, imgThreshold, CV_MOP_CLOSE, strElement);
    
    std::vector< std::vector< cv::Point> > contours;
    cv::findContours(imgThreshold, contours, 0, 1); 
    
    std::vector<std::vector<cv::Point> > contoursPoly( contours.size() );
    
    for(size_t i = 0; i < contours.size(); ++i)
    {
    	if (contours[i].size() > 100)
        { 
            cv::approxPolyDP( cv::Mat(contours[i]), contoursPoly[i], 3, true );
            cv::Rect appRect( boundingRect( cv::Mat(contoursPoly[i]) ) );

            if (appRect.width>appRect.height)
            { 
            	boundRect.push_back(appRect);
            }
        }
    }

    m_processedImg = m_originalImg.clone();

    std::vector<cv::Mat> croppedImgs;
    for(auto &rect : boundRect)
    {
    	cv::Mat tmpImg = m_originalImg.clone();
		markTextBox(rect);
    	croppedImgs.push_back( tmpImg(rect) );
    }

    
    return croppedImgs;
}

void CImageProcessing::showImg(const cv::Mat &img, int time)
{
	std::string win = "Display window"; 
	cv::namedWindow( win, cv::WINDOW_AUTOSIZE );
	cv::imshow(win, img);
	cv::waitKey(time);
	cv::destroyWindow(win);
}