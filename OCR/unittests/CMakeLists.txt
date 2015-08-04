cmake_minimum_required(VERSION 2.8)

project(ocr_unittest)

set( EXECUTABLE_OUTPUT_PATH ${TEST_DIR} )

find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (${OCR_TEST} ocr_unittests.cpp)

target_link_libraries (${OCR_TEST}
		OCR
		${Boost_FILESYSTEM_LIBRARY}
		${Boost_SYSTEM_LIBRARY}
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
