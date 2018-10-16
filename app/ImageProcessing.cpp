/************************************************************************
 MIT License

 Copyright (c) 2018 Rohith Jayarajan, Akash Guha

 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 *************************************************************************/
/**
 *  Copyright [2018] rohithjayarajan, Akash Guha
 *  @file    ImageProcessing.cpp
 *  @author  rohithjayarajan, Akash Guha
 *  @date 10/13/2018
 *  @version 1.1
 *
 *  @brief Image Processing Class File
 *
 *  @section DESCRIPTION
 *
 *  Includes all operations for image processing and pre
 *  processing tasks to be performed on the frames in the
 *  lane detection pipeline.
 *
 */

#include "ImageProcessing.hpp"
/**
 *   @brief Default constructor for ImgProcessing
 *
 *   @param nothing
 *   @return nothing
 */
ImageProcessing::ImageProcessing() {
}
/**
 *   @brief Default destructor for ImageProcessing
 *
 *   @param nothing
 *   @return nothing
 */
ImageProcessing::~ImageProcessing() {
}
/**
 *   @brief Function to pre-process the input image
 *
 *   @param input image of type cv::Mat
 *   @param processed image of type cv::Mat
 *   @return nothing
 */
void ImageProcessing::preProcessing(cv::Mat& src, cv::Mat& dst) {
}
/**
 *   @brief Function to get a binary image after color thresholding and edge
 *   detection
 *
 *   @param masked image of type cv::Mat
 *   @param binary image of type cv::Mat
 *   @return nothing
 */
void ImageProcessing::getBinaryImg(cv::Mat& srcImg, cv::Mat& dstImg) {
}
/**
 *   @brief Function to perform prospective transform
 *
 *   @param binary image of type cv::Mat
 *   @param bird's view image of type cv::Mat
 *   @return nothing
 */
void ImageProcessing::prespectiveTransform(cv::Mat& srcImg, cv::Mat& dstImg) {
}
/**
 *   @brief Function to set camera matrix
 *
 *   @param fx, the x component of focal length of type double
 *   @param fy, the y component of focal length of type double
 *   @param cx, the x coordinate of camera center of type double
 *   @param cy, the y coordinate of camera center of type double
 *   @return nothing
 */
void ImageProcessing::setIntrinsic(double fx_, double fy_, double cx_,
                                   double cy) {
}
/**
 *   @brief Function to set camera distortion
 *
 *   @param distortion parameter k1 of type double
 *   @param distortion parameter k2 of type double
 *   @param distortion parameter p1 of type double
 *   @param distortion parameter p2 of type double
 *   @param distortion parameter k3 of type double
 *   @return nothing
 */
void ImageProcessing::setDistCoeffs(double k1_, double k2_, double p1_,
                                    double p2_, double k3) {
}
/**
 *   @brief Function to set standard deviation in X for gaussian blur
 *
 *   @param standard deviation in X for gaussian blur
 *   @return nothing
 */
void ImageProcessing::setgaussianSigmaX(double gaussianSigmaX) {
}
/**
 *   @brief Function to set standard deviation in Y for gaussian blur
 *
 *   @param standard deviation in Y for gaussian blur
 *   @return nothing
 */
void ImageProcessing::setgaussianSigmaY(double gaussianSigmaY) {
}
/**
 *   @brief Function to set HSL color space minimum threshold value
 *
 *   @param minimum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 *   @return nothing
 */
void ImageProcessing::setMinThreshHLS(cv::Vec<double, 3> minThreshHSL) {
}
/**
 *   @brief Function to set HSL color space maximum threshold value
 *
 *   @param maximum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 *   @return nothing
 */
void ImageProcessing::setMaxThreshHLS(cv::Vec<double, 3> maxThreshHSL) {
}
/**
 *   @brief Function to set RGB color space minimum threshold value
 *
 *   @param minimum threshold values for red,green and blue, type cv::Vec<double, 3>
 *   @return nothing
 */
void ImageProcessing::setMinThreshBGR(cv::Vec<double, 3> minThreshBGR) {
}
/**
 *   @brief Function to set RGB color space maximum threshold value
 *
 *   @param maximum threshold values for red,green and blue, type cv::Vec<double, 3>
 *   @return nothing
 */
void ImageProcessing::setMaxThreshBGR(cv::Vec<double, 3> maxThreshBGR) {
}
/**
 *   @brief Function to get camera matrix
 *
 *   @param nothing
 *   @return fx, the x component of focal length of type double
 *           fy, the y component of focal length of type double
 *           cx, the x coordinate of camera center of type double
 *           cy, the y coordinate of camera center of type double
 */
cv::Mat ImageProcessing::getIntrinsic(void) {
  cv::Mat a;
  return a;
}
/**
 *   @brief Function to get camera distortion
 *
 *   @param nothing
 *   @return distortion parameter k1 of type double
 *           distortion parameter k2 of type double
 *           distortion parameter p1 of type double
 *           distortion parameter p2 of type double
 *           distortion parameter k3 of type double
 */
cv::Mat<double> ImageProcessing::getDistCoeffs(void) {
  cv::Mat a;
  return a;
}
/**
 *   @brief Function to get standard deviation in X for gaussian blur
 *
 *   @param nothing
 *   @return standard deviation in X for gaussian blur
 */
double ImageProcessing::getgaussianSigmaX(void) {
  return 0.0;
}
/**
 *   @brief Function to get standard deviation in Y for gaussian blur
 *
 *   @param nothing
 *   @return standard deviation in Y for gaussian blur
 */
double ImageProcessing::getgaussianSigmaY(void) {
  return 0.0;
}
/**
 *   @brief Function to get HSL color space minimum threshold value
 *
 *   @param nothing
 *   @return minimum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 */
/**
 *   @brief Function to get HSL color space minimum threshold value
 *
 *   @param nothing
 *   @return minimum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 */
cv::Vec<double, 3> ImageProcessing::getMinThreshHLS(void) {
  cv::Vec<double, 3> a;
  return a;
}
/**
 *   @brief Function to get HSL color space maximum threshold value
 *
 *   @param nothing
 *   @return maximum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 */
cv::Vec<double, 3> ImageProcessing::getMaxThreshHLS(void) {
  cv::Vec<double, 3> a;
  return a;
}
/**
 *   @brief Function to get RGB color space minimum threshold value
 *
 *   @param nothing
 *   @return minimum threshold values for red,green and blue, type cv::Vec<double, 3>
 */
cv::Vec<double, 3> ImageProcessing::getMinThreshBGR(void) {
  cv::Vec<double, 3> a;
  return a;
}
/**
 *   @brief Function to get RGB color space maximum threshold value
 *
 *   @param nothing
 *   @return maximum threshold values for red,green and blue, type cv::Vec<double, 3>
 */
cv::Vec<double, 3> ImageProcessing::getMaxThreshBGR(void) {
  cv::Vec<double, 3> a;
  return a;
}
