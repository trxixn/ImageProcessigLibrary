cmake_minimum_required(VERSION 3.10)
project(ImageProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/main.cpp
    src/Point.cpp
    src/Rectangle.cpp
    src/Image.cpp
    src/BrightnessContrast.cpp
    src/GammaCorrection.cpp
    src/Convolution.cpp
    src/Drawing.cpp
)

# Add executable
add_executable(image_processor ${SOURCES})

# Include directories
target_include_directories(image_processor PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
) 