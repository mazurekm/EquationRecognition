cmake_minimum_required (VERSION 2.8)

project (OCR)

set(SOURCE 
	OCR.cpp 
	Evaluator.cpp 
	ImageProcessing.cpp 
	EqualSolver.cpp 
	ArthmeticSolver.cpp
	SolverFactory.cpp)

find_package (Boost COMPONENTS system regex REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(${PROJECT_NAME} ${SOURCE})

file(GLOB Data ${CMAKE_CURRENT_SOURCE_DIR}/bin/*.traineddata)

file(COPY ${Data} DESTINATION ${DEST})

target_link_libraries (${PROJECT_NAME}
		GSL
		OpenCV
		Tesseract
		${Boost_SYSTEM_LIBRARY}
		${Boost_REGEX_LIBRARY})


add_subdirectory(unittests)
