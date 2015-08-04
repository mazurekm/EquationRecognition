cmake_minimum_required (VERSION 2.6)

project(Equation)

option(BOOST "BOOST_LIBRARY" OFF)
option(CPP11 "CPP11 SUPPORT" ON)

set(DEST ${CMAKE_CURRENT_BINARY_DIR}/tessdata)
set(OCR_TEST ocr_test)
set(TEST_DIR ${PROJECT_BINARY_DIR}/Tests)

if(CPP11)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/OpenCV/include)

find_package(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})	

add_subdirectory(OpenCV)
add_subdirectory(Tesseract)
add_subdirectory(GSL)
add_subdirectory(OCR)
add_subdirectory(GUI)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} OpenCV)
target_link_libraries(${PROJECT_NAME} Tesseract)
target_link_libraries(${PROJECT_NAME} GUI)

enable_testing()

add_test(${OCR_TEST} ${TEST_DIR}/${OCR_TEST})
