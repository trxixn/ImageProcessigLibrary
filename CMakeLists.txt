cmake_minimum_required(VERSION 3.10)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/main.cpp
    src/Image.cpp
    src/BrightnessContrast.cpp
    src/GammaCorrection.cpp
    src/Convolution.cpp
    src/Drawing.cpp
    src/SobelFilter.cpp
)

# Add header files
set(HEADERS
    src/Image.h
    src/ImageProcessing.h
    src/BrightnessContrast.h
    src/GammaCorrection.h
    src/Convolution.h
    src/Drawing.h
    src/SobelFilter.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src) 