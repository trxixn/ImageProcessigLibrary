#pragma once

#include <string>
#include <iostream>
#include "Point.h"
#include "Size.h"
#include "Rectangle.h"

using namespace std;

class Image {
public:
    /**
     * @brief Default constructor
     */
    Image();

    /**
     * @brief Constructor with specified dimensions
     * @param w Width of the image
     * @param h Height of the image
     */
    Image(unsigned int w, unsigned int h);

    /**
     * @brief Copy constructor
     * @param other Image to copy from
     */
    Image(const Image &other);

    /**
     * @brief Destructor
     */
    ~Image();

    /**
     * @brief Load image from file
     * @param imagePath Path to the image file
     * @return true if loading was successful, false otherwise
     */
    bool load(const std::string& imagePath);

    /**
     * @brief Save image to file
     * @param imagePath Path where to save the image
     * @return true if saving was successful, false otherwise
     */
    bool save(const std::string& imagePath);

    /**
     * @brief Assignment operator
     * @param other Image to assign from
     * @return Reference to this image
     */
    Image& operator=(const Image &other);

    /**
     * @brief Addition operator for two images
     * @param i Image to add
     * @return Resulting image
     */
    Image operator+(const Image &i);

    /**
     * @brief Subtraction operator for two images
     * @param i Image to subtract
     * @return Resulting image
     */
    Image operator-(const Image &i);

    /**
     * @brief Multiplication operator for two images
     * @param i Image to multiply with
     * @return Resulting image
     */
    Image operator*(const Image &i);

    /**
     * @brief Addition operator for image and scalar
     * @param scalar Value to add
     * @return Resulting image
     */
    Image operator+(unsigned char scalar);

    /**
     * @brief Subtraction operator for image and scalar
     * @param scalar Value to subtract
     * @return Resulting image
     */
    Image operator-(unsigned char scalar);

    /**
     * @brief Multiplication operator for image and scalar
     * @param scalar Value to multiply with
     * @return Resulting image
     */
    Image operator*(float scalar);

    /**
     * @brief Get region of interest from image
     * @param roiImg Output image to store ROI
     * @param roiRect Rectangle defining the region of interest
     * @return true if ROI extraction was successful, false otherwise
     */
    bool getROI(Image &roiImg, Rectangle roiRect);

    /**
     * @brief Get region of interest from image
     * @param roiImg Output image to store ROI
     * @param x X coordinate of ROI
     * @param y Y coordinate of ROI
     * @param width Width of ROI
     * @param height Height of ROI
     * @return true if ROI extraction was successful, false otherwise
     */
    bool getROI(Image &roiImg, unsigned int x, unsigned int y, 
                unsigned int width, unsigned int height);

    /**
     * @brief Check if image is empty
     * @return true if image is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Get image size
     * @return Size object containing width and height
     */
    Size size() const;

    /**
     * @brief Get image width
     * @return Width of the image
     */
    unsigned int width() const;

    /**
     * @brief Get image height
     * @return Height of the image
     */
    unsigned int height() const;

    /**
     * @brief Access pixel value at specified coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @return Reference to pixel value
     */
    unsigned char& at(unsigned int x, unsigned int y);

    /**
     * @brief Access pixel value at specified point
     * @param pt Point containing coordinates
     * @return Reference to pixel value
     */
    unsigned char& at(Point pt);

    /**
     * @brief Get pixel value at specified coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @return Pixel value
     */
    unsigned char at(unsigned int x, unsigned int y) const;

    /**
     * @brief Get pixel value at specified point
     * @param pt Point containing coordinates
     * @return Pixel value
     */
    unsigned char at(Point pt) const;

    /**
     * @brief Get pointer to row data
     * @param y Row index
     * @return Pointer to row data
     */
    unsigned char* row(int y);

    /**
     * @brief Release image data
     */
    void release();

    /**
     * @brief Stream output operator
     * @param os Output stream
     * @param dt Image to output
     * @return Output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Image& dt);

    /**
     * @brief Create image filled with zeros
     * @param width Width of the image
     * @param height Height of the image
     * @return New image filled with zeros
     */
    static Image zeros(unsigned int width, unsigned int height);

    /**
     * @brief Create image filled with ones
     * @param width Width of the image
     * @param height Height of the image
     * @return New image filled with ones
     */
    static Image ones(unsigned int width, unsigned int height);

private:
    unsigned char** m_data;
    unsigned int m_width;
    unsigned int m_height;
}; 