#include "Image.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;

// Default constructor - creates an empty image with no data
Image::Image() : m_data(nullptr), m_width(0), m_height(0) {}

// Constructor that creates an image of specified dimensions
// All pixels are initialized to 0 (black)
Image::Image(unsigned int w, unsigned int h) : m_width(w), m_height(h) {
    if (w == 0 || h == 0) {
        m_data = nullptr;
        return;
    }
    // Allocate 2D array for image data
    // First dimension is height (rows)
    // Second dimension is width (columns)
    m_data = new unsigned char*[h];
    for (unsigned int i = 0; i < h; ++i) {
        m_data[i] = new unsigned char[w];
        std::fill(m_data[i], m_data[i] + w, 0);  // Initialize to black
    }
}

// Copy constructor - creates a deep copy of another image
// Ensures that each image has its own copy of the data
Image::Image(const Image &other) : m_width(other.m_width), m_height(other.m_height) {
    if (m_width == 0 || m_height == 0) {
        m_data = nullptr;
        return;
    }
    // Create new 2D array and copy all pixel data
    m_data = new unsigned char*[m_height];
    for (unsigned int i = 0; i < m_height; ++i) {
        m_data[i] = new unsigned char[m_width];
        std::copy(other.m_data[i], other.m_data[i] + m_width, m_data[i]);
    }
}

// Destructor - clean up allocated memory
// Called automatically when image goes out of scope
Image::~Image() {
    release();
}

// Release all allocated memory and reset dimensions
// This is called by destructor and when loading new images
void Image::release() {
    if (m_data) {
        // Delete each row of pixels
        for (unsigned int i = 0; i < m_height; ++i) {
            delete[] m_data[i];
        }
        // Delete the array of row pointers
        delete[] m_data;
        m_data = nullptr;
    }
    m_width = m_height = 0;
}

// Load a PGM (Portable Gray Map) image file
// Format:
//   P5\n                    - Magicnumber for binary PGM
//   width height\n          - Image dimensions
//   255\n                   - Maximum pixel value
//   [binary pixel data]     - Raw pixel values
bool Image::load(const std::string& imagePath) {
    release();
    std::ifstream file(imagePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file: " << imagePath << std::endl;
        return false;
    }

    // Read and verify magic number (must be P5 for binary PGM)
    std::string magic;
    std::getline(file, magic);
    std::cout << "[DEBUG] Magic: '" << magic << "'" << std::endl;
    if (magic != "P5") {
        std::cerr << "Error: Invalid magic number. Expected P5, got " << magic << std::endl;
        return false;
    }

    // Read image dimensions
    std::string dimensions;
    std::getline(file, dimensions);
    std::cout << "[DEBUG] Dimensions line: '" << dimensions << "'" << std::endl;
    std::istringstream dim_stream(dimensions);
    dim_stream >> m_width >> m_height;
    std::cout << "[DEBUG] Parsed width: " << m_width << ", height: " << m_height << std::endl;
    if (m_width == 0 || m_height == 0) {
        std::cerr << "Error: Invalid dimensions: " << m_width << "x" << m_height << std::endl;
        return false;
    }

    // Read and verify max value (must be 255 for 8-bit grayscale)
    std::string max_value;
    std::getline(file, max_value);
    std::cout << "[DEBUG] Max value line: '" << max_value << "'" << std::endl;
    int max_val = std::stoi(max_value);
    if (max_val != 255) {
        std::cerr << "Error: Unsupported max value: " << max_val << std::endl;
        return false;
    }

    // Allocate memory for image data
    m_data = new unsigned char*[m_height];
    for (unsigned int i = 0; i < m_height; ++i) {
        m_data[i] = new unsigned char[m_width];
    }

    // Read binary image data row by row
    for (unsigned int i = 0; i < m_height; ++i) {
        file.read(reinterpret_cast<char*>(m_data[i]), m_width);
        if (!file) {
            std::cerr << "Error: Failed to read image data" << std::endl;
            release();
            return false;
        }
    }

    return true;
}

// Save image as PGM file
// Uses the same format as load()
bool Image::save(const std::string& imagePath) {
    if (m_width == 0 || m_height == 0 || m_data == nullptr) {
        std::cerr << "Error: Invalid image data" << std::endl;
        return false;
    }

    std::ofstream file(imagePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << imagePath << std::endl;
        return false;
    }

    // Write PGM header
    file << "P5\n" << m_width << " " << m_height << "\n255\n";
    if (file.fail()) {
        std::cerr << "Error: Failed to write header" << std::endl;
        return false;
    }
    
    // Write binary image data row by row
    for (unsigned int i = 0; i < m_height; ++i) {
        file.write(reinterpret_cast<const char*>(m_data[i]), m_width);
        if (file.fail()) {
            std::cerr << "Error: Failed to write data" << std::endl;
            return false;
        }
    }

    file.close();
    return true;
}

// Assignment operator - deep copy of another image
// Handles self-assignment and memory management
Image& Image::operator=(const Image &other) {
    if (this != &other) {  // Prevent self-assignment
        release();
        m_width = other.m_width;
        m_height = other.m_height;
        m_data = new unsigned char*[m_height];
        for (unsigned int i = 0; i < m_height; ++i) {
            m_data[i] = new unsigned char[m_width];
            std::copy(other.m_data[i], other.m_data[i] + m_width, m_data[i]);
        }
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
            result.m_data[y][x] = std::min(255, 
                static_cast<int>(m_data[y][x]) + static_cast<int>(i.m_data[y][x]));
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
            result.m_data[y][x] = std::max(0, 
                static_cast<int>(m_data[y][x]) - static_cast<int>(i.m_data[y][x]));
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
            result.m_data[y][x] = std::min(255, 
                static_cast<int>(m_data[y][x]) * static_cast<int>(i.m_data[y][x]) / 255);
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
            result.m_data[y][x] = std::min(255, 
                static_cast<int>(m_data[y][x]) + static_cast<int>(scalar));
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
            result.m_data[y][x] = std::max(0, 
                static_cast<int>(m_data[y][x]) - static_cast<int>(scalar));
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
            result.m_data[y][x] = std::min(255, 
                static_cast<int>(m_data[y][x] * scalar));
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
    roiImg.m_data = new unsigned char*[height];
    
    // Copy ROI data
    for (unsigned int i = 0; i < height; ++i) {
        roiImg.m_data[i] = new unsigned char[width];
        std::copy(m_data[y + i] + x, m_data[y + i] + x + width, roiImg.m_data[i]);
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
    return m_data[y][x];
}

// Get reference to pixel at Point with bounds checking
// Convenience wrapper for at(x,y)
unsigned char& Image::at(Point pt) {
    return at(pt.x, pt.y);
}

// Get pixel value at (x,y) with bounds checking (const version)
// This is for reading pixel values only
unsigned char Image::at(unsigned int x, unsigned int y) const {
    if (x >= m_width || y >= m_height)
        throw std::out_of_range("Index out of bounds");
    return m_data[y][x];
}

// Get pixel value at Point with bounds checking (const version)
// Convenience wrapper for at(x,y)
unsigned char Image::at(Point pt) const {
    return at(pt.x, pt.y);
}

// Get pointer to start of row y
// Useful for efficient row-by-row processing
unsigned char* Image::row(int y) {
    if (y < 0 || static_cast<unsigned int>(y) >= m_height)
        throw std::out_of_range("Row index out of bounds");
    return m_data[y];
}

// Output operator - print image as ASCII values
// Useful for debugging small images
std::ostream& operator<<(std::ostream& os, const Image& img) {
    for (unsigned int y = 0; y < img.m_height; ++y) {
        for (unsigned int x = 0; x < img.m_width; ++x) {
            os << static_cast<int>(img.m_data[y][x]) << " ";
        }
        os << "\n";
    }
    return os;
}

// Create black image (all pixels = 0)
// Useful for creating masks or blank images
Image Image::zeros(unsigned int width, unsigned int height) {
    Image result(width, height);
    for (unsigned int y = 0; y < height; ++y) {
        std::fill(result.m_data[y], result.m_data[y] + width, 0);
    }
    return result;
}

// Create white image (all pixels = 255)
// Useful for creating masks or blank images
Image Image::ones(unsigned int width, unsigned int height) {
    Image result(width, height);
    for (unsigned int y = 0; y < height; ++y) {
        std::fill(result.m_data[y], result.m_data[y] + width, 255);
    }
    return result;
} 