#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <sstream>
#include <OCR/OCR.h>
#include <iostream>

BOOST_AUTO_TEST_CASE(ocr_rec)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();
	std::string currentPath = sst.str();
	currentPath.erase(currentPath.begin());
	currentPath.erase(currentPath.end()-1);

	currentPath += "/Tests/";
	
	
}