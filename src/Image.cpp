#include "Image.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace std;

// Default constructor - creates an empty image with no data
Image::Image() : m_width(0), m_height(0), m_data(nullptr) {}

// Constructor that creates an image of specified dimensions
// All pixels are initialized to 0 (black)
Image::Image(unsigned int width, unsigned int height) : m_width(width), m_height(height) {
    m_data = new unsigned char[width * height];
    memset(m_data, 0, width * height);
}

// Copy constructor - creates a deep copy of another image
// Ensures that each image has its own copy of the data
Image::Image(const Image &other) : m_width(other.m_width), m_height(other.m_height) {
    m_data = new unsigned char[m_width * m_height];
    memcpy(m_data, other.m_data, m_width * m_height);
}

// Destructor - clean up allocated memory
// Called automatically when image goes out of scope
Image::~Image() {
    delete[] m_data;
}

// Load a PGM (Portable Gray Map) image file
// Format:
//   P5\n                    - Magicnumber for binary PGM
//   width height\n          - Image dimensions
//   255\n                   - Maximum pixel value
//   [binary pixel data]     - Raw pixel values
bool Image::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    char magic[3];
    file.read(magic, 2);
    magic[2] = '\0';

    if (strcmp(magic, "P5") != 0) {
        std::cerr << "Not a PGM file" << std::endl;
        return false;
    }

    file >> m_width >> m_height;
    int maxVal;
    file >> maxVal;
    file.ignore();

    delete[] m_data;
    m_data = new unsigned char[m_width * m_height];
    file.read(reinterpret_cast<char*>(m_data), m_width * m_height);

    return true;
}

// Save image as PGM file
// Uses the same format as load()
bool Image::save(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return false;
    }

    file << "P5\n" << m_width << " " << m_height << "\n255\n";
    file.write(reinterpret_cast<const char*>(m_data), m_width * m_height);

    return true;
}

// Assignment operator - deep copy of another image
// Handles self-assignment and memory management
Image& Image::operator=(const Image &other) {
    if (this != &other) {
        delete[] m_data;
        m_width = other.m_width;
        m_height = other.m_height;
        m_data = new unsigned char[m_width * m_height];
        memcpy(m_data, other.m_data, m_width * m_height);
    }
    return *this;
}

// Image addition - pixel by pixel addition with clamping to 255
// Used for combining images or adding brightness
Image Image::operator+(const Image &i) {
    if (m_width != i.m_width || m_height != i.m_height)
        throw std::runtime_error("Image dimensions must match");

    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y * m_width + x] = std::min(255, 
                static_cast<int>(m_data[y * m_width + x]) + static_cast<int>(i.m_data[y * m_width + x]));
        }
    }
    return result;
}

// Image subtraction - pixel by pixel subtraction with clamping to 0
// Used for difference images or subtracting brightness
Image Image::operator-(const Image &i) {
    if (m_width != i.m_width || m_height != i.m_height)
        throw std::runtime_error("Image dimensions must match");

    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y * m_width + x] = std::max(0, 
                static_cast<int>(m_data[y * m_width + x]) - static_cast<int>(i.m_data[y * m_width + x]));
        }
    }
    return result;
}

// Image multiplication - pixel by pixel multiplication with scaling
// Used for blending images or applying masks
Image Image::operator*(const Image &i) {
    if (m_width != i.m_width || m_height != i.m_height)
        throw std::runtime_error("Image dimensions must match");

    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y * m_width + x] = std::min(255, 
                static_cast<int>(m_data[y * m_width + x]) * static_cast<int>(i.m_data[y * m_width + x]) / 255);
        }
    }
    return result;
}

// Scalar addition - add constant value to all pixels
// Used for uniform brightness adjustment
Image Image::operator+(unsigned char scalar) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y * m_width + x] = std::min(255, 
                static_cast<int>(m_data[y * m_width + x]) + static_cast<int>(scalar));
        }
    }
    return result;
}

// Scalar subtraction - subtract constant value from all pixels
// Used for uniform darkness adjustment
Image Image::operator-(unsigned char scalar) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y * m_width + x] = std::max(0, 
                static_cast<int>(m_data[y * m_width + x]) - static_cast<int>(scalar));
        }
    }
    return result;
}

// Scalar multiplication - multiply all pixels by constant
// Used for uniform contrast adjustment
Image Image::operator*(float scalar) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y * m_width + x] = std::min(255, 
                static_cast<int>(m_data[y * m_width + x] * scalar));
        }
    }
    return result;
}

// Get Region of Interest (ROI) using Rectangle
bool Image::getROI(Image &roiImg, Rectangle roiRect) {
    return getROI(roiImg, roiRect.x, roiRect.y, roiRect.width, roiRect.height);
}

// Get Region of Interest (ROI) using coordinates and dimensions
// Extracts a rectangular portion of the image
// Parameters:
//   roiImg: Output image that will contain the ROI
//   x, y: Top-left corner of the ROI
//   width, height: Dimensions of the ROI
// Returns:
//   true if ROI is valid and was extracted
//   false if ROI is outside image bounds
bool Image::getROI(Image &roiImg, unsigned int x, unsigned int y, 
                  unsigned int width, unsigned int height) {
    // Check if ROI is within image bounds
    if (x + width > m_width || y + height > m_height)
        return false;

    // Create new image for ROI
    roiImg.release();
    roiImg.m_width = width;
    roiImg.m_height = height;
    roiImg.m_data = new unsigned char[width * height];
    
    // Copy ROI data
    for (unsigned int i = 0; i < height; ++i) {
        std::copy(m_data + (y + i) * m_width + x, m_data + (y + i) * m_width + x + width, roiImg.m_data + i * width);
    }
    
    return true;
}

// Check if image is empty (no data or zero dimensions)
bool Image::isEmpty() const {
    return m_data == nullptr || m_width == 0 || m_height == 0;
}

// Get image size as a Size object
Size Image::size() const {
    return Size(m_width, m_height);
}

// Get image width
unsigned int Image::width() const {
    return m_width;
}

// Get image height
unsigned int Image::height() const {
    return m_height;
}

// Get reference to pixel at (x,y) with bounds checking
// Allows modifying the pixel value
unsigned char& Image::at(unsigned int x, unsigned int y) {
    if (x >= m_width || y >= m_height)
        throw std::out_of_range("Index out of bounds");
    return m_data[y * m_width + x];
}

// Get reference to pixel at Point with bounds checking
// Convenience wrapper for at(x,y)
unsigned char& Image::at(Point pt) {
    return at(pt.x, pt.y);
}

// Get pixel value at (x,y) with bounds checking (const version)
// This is for reading pixel values only
const unsigned char& Image::at(unsigned int x, unsigned int y) const {
    if (x >= m_width || y >= m_height)
        throw std::out_of_range("Index out of bounds");
    return m_data[y * m_width + x];
}

// Get pixel value at Point with bounds checking (const version)
// Convenience wrapper for at(x,y)
const unsigned char& Image::at(Point pt) const {
    return at(pt.x, pt.y);
}

// Get pointer to start of row y
// Useful for efficient row-by-row processing
unsigned char* Image::row(int y) {
    if (y < 0 || static_cast<unsigned int>(y) >= m_height)
        throw std::out_of_range("Row index out of bounds");
    return m_data + y * m_width;
}

// Output operator - print image as ASCII values
// Useful for debugging small images
std::ostream& operator<<(std::ostream& os, const Image& img) {
    for (unsigned int y = 0; y < img.m_height; ++y) {
        for (unsigned int x = 0; x < img.m_width; ++x) {
            os << static_cast<int>(img.m_data[y * img.m_width + x]) << " ";
        }
        os << "\n";
    }
    return os;
}

// Create black image (all pixels = 0)
// Useful for creating masks or blank images
Image Image::zeros(unsigned int width, unsigned int height) {
    Image result(width, height);
    memset(result.m_data, 0, width * height);
    return result;
}

// Create white image (all pixels = 255)
// Useful for creating masks or blank images
Image Image::ones(unsigned int width, unsigned int height) {
    Image result(width, height);
    memset(result.m_data, 255, width * height);
    return result;
}

void Image::release() {
    delete[] m_data;
    m_data = nullptr;
    m_width = 0;
    m_height = 0;
} 