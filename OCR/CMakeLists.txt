cmake_minimum_required (VERSION 2.8)

project (OCR)

set(SOURCE OCR.cpp Evaluator.cpp ImageProcessing.cpp)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(${PROJECT_NAME} ${SOURCE})

