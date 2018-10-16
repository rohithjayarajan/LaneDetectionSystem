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
 *  Copyright 2018 rohithjayarajan, Akash Guha
 *  @file    ImageProcessing.hpp
 *  @author  rohithjayarajan, Akash Guha
 *  @date 10/13/2018
 *  @version 1.1
 *
 *  @brief Image Processing Class Header
 *
 *  @section DESCRIPTION
 *
 *  Class header which includes declarations of all
 *  image pre-processing functionalities in lane
 *  detection and steering system.
 *
 */

#ifndef INCLUDE_IMAGEPROCESSING_HPP_
#define INCLUDE_IMAGEPROCESSING_HPP_
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ImageProcessing {
 private:
  cv::Mat intrinsic;  // Camera's intrinsic parameters
  cv::Mat distortionCoeffs;  // Distortion coefficients
  double gaussianSigmaX;  // standard deviation in X for gaussian blur
  double gaussianSigmaY;  // standard deviation in Y for gaussian blur
  cv::Vec<double, 3> minThreshHSL;  // HSL color space threshold values
  cv::Vec<double, 3> maxThreshHSL;  // HSL color space threshold values
  cv::Vec<double, 3> minThreshBGR;  // RGB color space threshold values
  cv::Vec<double, 3> maxThreshBGR;  // RGB color space threshold values

 public:
  /**
   *   @brief Default constructor for ImgProcessing
   *
   *   @param nothing
   *   @return nothing
   */
  ImageProcessing();
  /**
   *   @brief Default destructor for ImgProcessing
   *
   *   @param nothing
   *   @return nothing
   */
  ~ImageProcessing();
  /**
   *   @brief Function to pre-process the input image
   *
   *   @param input image of type cv::Mat
   *   @param processed image of type cv::Mat
   *   @return nothing
   */
  void preProcessing(cv::Mat& srcImg, cv::Mat& dstImg);
  /**
   *   @brief Function to get a binary image after color thresholding and edge
   *   detection
   *
   *   @param masked image of type cv::Mat
   *   @param binary image of type cv::Mat
   *   @return nothing
   */
  void getBinaryImg(cv::Mat& srcImg, cv::Mat& dstImg);
  /**
   *   @brief Function to perform prospective transform
   *
   *   @param binary image of type cv::Mat
   *   @param bird's view image of type cv::Mat
   *   @return nothing
   */
  void prespectiveTransform(cv::Mat& srcImg, cv::Mat& dstImg);
  /**
   *   @brief Function to set camera matrix
   *
   *   @param fx, the x component of focal length of type double
   *   @param fy, the y component of focal length of type double
   *   @param cx, the x coordinate of camera center of type double
   *   @param cy, the y coordinate of camera center of type double
   *   @return nothing
   */
  void setIntrinsic(double fx_, double fy_, double cx_, double cy);
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
  void setDistCoeffs(double k1_, double k2_, double p1_, double p2_, double k3);
  /**
   *   @brief Function to set standard deviation in X for gaussian blur
   *
   *   @param standard deviation in X for gaussian blur
   *   @return nothing
   */
  void setgaussianSigmaX(double gaussianSigmaX);
  /**
   *   @brief Function to set standard deviation in Y for gaussian blur
   *
   *   @param standard deviation in Y for gaussian blur
   *   @return nothing
   */
  void setgaussianSigmaY(double gaussianSigmaY);
  /**
   *   @brief Function to set HSL color space minimum threshold value
   *
   *   @param minimum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
   *   @return nothing
   */
  void setMinThreshHLS(cv::Vec<double, 3> minThreshHSL);
  /**
   *   @brief Function to set HSL color space maximum threshold value
   *
   *   @param maximum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
   *   @return nothing
   */
  void setMaxThreshHLS(cv::Vec<double, 3> maxThreshHSL);
  /**
   *   @brief Function to set RGB color space minimum threshold value
   *
   *   @param minimum threshold values for red,green and blue, type cv::Vec<double, 3>
   *   @return nothing
   */
  void setMinThreshBGR(cv::Vec<double, 3> minThreshBGR);
  /**
   *   @brief Function to set RGB color space maximum threshold value
   *
   *   @param maximum threshold values for red,green and blue, type cv::Vec<double, 3>
   *   @return nothing
   */
  void setMaxThreshBGR(cv::Vec<double, 3> maxThreshBGR);
  /**
   *   @brief Function to get camera matrix
   *
   *   @param nothing
   *   @return fx, the x component of focal length of type double
   *           fy, the y component of focal length of type double
   *           cx, the x coordinate of camera center of type double
   *           cy, the y coordinate of camera center of type double
   */
  cv::Mat getIntrinsic(void);
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
  cv::Mat getDistCoeffs(void);
  /**
   *   @brief Function to get standard deviation in X for gaussian blur
   *
   *   @param nothing
   *   @return standard deviation in X for gaussian blur
   */
  double getgaussianSigmaX(void);
  /**
   *   @brief Function to get standard deviation in Y for gaussian blur
   *
   *   @param nothing
   *   @return standard deviation in Y for gaussian blur
   */
  double getgaussianSigmaY(void);
  /**
   *   @brief Function to get HSL color space minimum threshold value
   *
   *   @param nothing
   *   @return minimum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
   */
  cv::Vec<double, 3> getMinThreshHLS(void);
  /**
   *   @brief Function to get HSL color space maximum threshold value
   *
   *   @param nothing
   *   @return maximum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
   */
  cv::Vec<double, 3> getMaxThreshHLS(void);
  /**
   *   @brief Function to get RGB color space minimum threshold value
   *
   *   @param nothing
   *   @return minimum threshold values for red,green and blue, type cv::Vec<double, 3>
   */
  cv::Vec<double, 3> getMinThreshBGR(void);
  /**
   *   @brief Function to get RGB color space maximum threshold value
   *
   *   @param nothing
   *   @return maximum threshold values for red,green and blue, type cv::Vec<double, 3>
   */
  cv::Vec<double, 3> getMaxThreshBGR(void);
};

#endif  // INCLUDE_IMAGEPROCESSING_HPP_
