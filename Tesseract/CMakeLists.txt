cmake_minimum_required (VERSION 2.8)

project (Tesseract)

file(GLOB binaries ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.so)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(Tesseract link.cpp)

target_link_libraries(Tesseract ${binaries})
