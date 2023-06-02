cmake_minimum_required(VERSION 3.25)
project(Optical_Flow)

set(OpenCV_DIR C:/Users/manny/Desktop/WORK/OpenCV-Project/Libraries/opencv/build)
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 14)

include_directories(main)

add_executable(Optical_Flow
        main/_FileHandler.cpp
        main/_init.cpp
        main/analysis.cpp
        main/_FileHandler.h
        main/_init.h
        main/analysis.h
        main/main.cpp
        main/OpticalFlowCalc.cpp main/OpticalFlowCalc.h)

target_link_libraries(Optical_Flow ${OpenCV_LIBS} )
