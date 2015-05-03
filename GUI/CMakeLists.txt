cmake_minimum_required (VERSION 2.6)

project(GUI)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})	
QT4_WRAP_UI(UISrcs cgui.ui)
QT4_WRAP_CPP(MOCSrcs cgui.h)


add_library(${PROJECT_NAME} cgui.cpp ${MOCSrcs} ${UISrcs})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
target_link_libraries(${PROJECT_NAME} OCR)
