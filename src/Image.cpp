#include "Image.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;

Image::Image() : m_data(nullptr), m_width(0), m_height(0) {}

Image::Image(unsigned int w, unsigned int h) : m_width(w), m_height(h) {
    if (w == 0 || h == 0) {
        m_data = nullptr;
        return;
    }
    m_data = new unsigned char*[h];
    for (unsigned int i = 0; i < h; ++i) {
        m_data[i] = new unsigned char[w];
        std::fill(m_data[i], m_data[i] + w, 0);
    }
}

Image::Image(const Image &other) : m_width(other.m_width), m_height(other.m_height) {
    if (m_width == 0 || m_height == 0) {
        m_data = nullptr;
        return;
    }
    m_data = new unsigned char*[m_height];
    for (unsigned int i = 0; i < m_height; ++i) {
        m_data[i] = new unsigned char[m_width];
        std::copy(other.m_data[i], other.m_data[i] + m_width, m_data[i]);
    }
}

Image::~Image() {
    release();
}

void Image::release() {
    if (m_data) {
        for (unsigned int i = 0; i < m_height; ++i) {
            delete[] m_data[i];
        }
        delete[] m_data;
        m_data = nullptr;
    }
    m_width = m_height = 0;
}

bool Image::load(const std::string& imagePath) {
    release();
    std::ifstream file(imagePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file: " << imagePath << std::endl;
        return false;
    }

    // Read magic number
    std::string magic;
    std::getline(file, magic);
    std::cout << "[DEBUG] Magic: '" << magic << "'" << std::endl;
    if (magic != "P5") {
        std::cerr << "Error: Invalid magic number. Expected P5, got " << magic << std::endl;
        return false;
    }

    // Read dimensions
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

    // Read max value
    std::string max_value;
    std::getline(file, max_value);
    std::cout << "[DEBUG] Max value line: '" << max_value << "'" << std::endl;
    int max_val = std::stoi(max_value);
    if (max_val != 255) {
        std::cerr << "Error: Unsupported max value: " << max_val << std::endl;
        return false;
    }

    // Allocate 2D array
    m_data = new unsigned char*[m_height];
    for (unsigned int i = 0; i < m_height; ++i) {
        m_data[i] = new unsigned char[m_width];
    }

    // Read image data row by row
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

    // Write header
    file << "P5\n" << m_width << " " << m_height << "\n255\n";
    if (file.fail()) {
        std::cerr << "Error: Failed to write header" << std::endl;
        return false;
    }
    
    // Write binary data
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

Image& Image::operator=(const Image &other) {
    if (this != &other) {
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

bool Image::getROI(Image &roiImg, Rectangle roiRect) {
    return getROI(roiImg, roiRect.x, roiRect.y, roiRect.width, roiRect.height);
}

bool Image::getROI(Image &roiImg, unsigned int x, unsigned int y, 
                  unsigned int width, unsigned int height) {
    if (x + width > m_width || y + height > m_height)
        return false;

    roiImg.release();
    roiImg.m_width = width;
    roiImg.m_height = height;
    roiImg.m_data = new unsigned char*[height];
    
    for (unsigned int i = 0; i < height; ++i) {
        roiImg.m_data[i] = new unsigned char[width];
        std::copy(m_data[y + i] + x, m_data[y + i] + x + width, roiImg.m_data[i]);
    }
    
    return true;
}

bool Image::isEmpty() const {
    return m_data == nullptr || m_width == 0 || m_height == 0;
}

Size Image::size() const {
    return Size(m_width, m_height);
}

unsigned int Image::width() const {
    return m_width;
}

unsigned int Image::height() const {
    return m_height;
}

unsigned char& Image::at(unsigned int x, unsigned int y) {
    if (x >= m_width || y >= m_height)
        throw std::out_of_range("Index out of bounds");
    return m_data[y][x];
}

unsigned char& Image::at(Point pt) {
    return at(pt.x, pt.y);
}

unsigned char Image::at(unsigned int x, unsigned int y) const {
    if (x >= m_width || y >= m_height)
        throw std::out_of_range("Index out of bounds");
    return m_data[y][x];
}

unsigned char Image::at(Point pt) const {
    return at(pt.x, pt.y);
}

unsigned char* Image::row(int y) {
    if (y < 0 || static_cast<unsigned int>(y) >= m_height)
        throw std::out_of_range("Row index out of bounds");
    return m_data[y];
}

std::ostream& operator<<(std::ostream& os, const Image& img) {
    for (unsigned int y = 0; y < img.m_height; ++y) {
        for (unsigned int x = 0; x < img.m_width; ++x) {
            os << static_cast<int>(img.m_data[y][x]) << " ";
        }
        os << "\n";
    }
    return os;
}

Image Image::zeros(unsigned int width, unsigned int height) {
    Image result(width, height);
    for (unsigned int y = 0; y < height; ++y) {
        std::fill(result.m_data[y], result.m_data[y] + width, 0);
    }
    return result;
}

Image Image::ones(unsigned int width, unsigned int height) {
    Image result(width, height);
    for (unsigned int y = 0; y < height; ++y) {
        std::fill(result.m_data[y], result.m_data[y] + width, 255);
    }
    return result;
} 