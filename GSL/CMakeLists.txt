cmake_minimum_required (VERSION 2.8)

project (GSL)

file(GLOB binaries ${CMAKE_CURRENT_SOURCE_DIR}/libs/*.so)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)

add_library(${PROJECT_NAME} link.cpp)

target_link_libraries(${PROJECT_NAME} ${binaries})
