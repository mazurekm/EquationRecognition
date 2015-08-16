#include <boost/test/unit_test.hpp>

#include <sstream>
#include <vector>
#include <OCR/OCR.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <memory>

struct Fixture
{
	std::string currentPath;
	std::string tessData;

	Fixture()
	{
		std::stringstream sst;
		sst << boost::filesystem::current_path();
		
		currentPath = sst.str();
		currentPath.erase(currentPath.begin());
		currentPath.erase(currentPath.end()-1);
		
		tessData = currentPath;
		currentPath += "/Tests/";	
	}
};

BOOST_FIXTURE_TEST_SUITE( s, Fixture )

BOOST_AUTO_TEST_CASE(ocr_rec)
{
	std::unique_ptr<COCR> ptr; 

	ptr.reset(new COCR (currentPath+"1.png"));
	ptr->init(tessData, "eng");
	auto res = ptr->perform();
	CImageProcessing::showImg( ptr->getProcessedImg(), 5000 );

	ptr.reset(new COCR (currentPath+"2.png"));
	ptr->init(tessData, "eng");
	res = ptr->perform();	
	CImageProcessing::showImg( ptr->getProcessedImg(), 5000 );

	ptr.reset(new COCR (currentPath+"3.png"));
	ptr->init(tessData, "eng");
	res = ptr->perform();
	CImageProcessing::showImg( ptr->getProcessedImg(), 5000 );
}

BOOST_AUTO_TEST_CASE(img_test)
{
	CImageProcessing proc(currentPath+"3.png");
	proc.detectLetters();
	proc.showImg(proc.getProcessedImg(), 5000);	
}


BOOST_AUTO_TEST_SUITE_END()