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
  // initialize camera intrinsics
  intrinsic =
      (cv::Mat_<double>(3, 3) << 1154.22732, 0.0, 671.627794, 0.0, 1148.18221, 386.046312, 0.0, 0.0, 1.0);
  // initialize camera distortion
  distortionCoeffs =
      (cv::Mat_<double>(1, 5) << -0.242565104, -0.0477893070, -0.00131388084, -0.0000879107779, 0.0220573263);
  gaussianSigmaX = 0.04;  // set S.D. in X for Gaussian blur
  gaussianSigmaY = 0.06;  // set S.D. in Y for Gaussian blur
  minThreshHLS = cv::Scalar(18, 97, 97);  // set lower bounds for HLS mask
  maxThreshHLS = cv::Scalar(32, 255, 255);  // set lower bounds for HLS mask
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
  cv::Mat undistortedImg, densoisedImg;  // declare variable holders
                                         // for undistorted and denoised images
  // undistort frame using camera intrinsics
  cv::undistort(src, undistortedImg, intrinsic, distortionCoeffs);
  // smoothen or denoise the image using Gaussian blur
  cv::GaussianBlur(undistortedImg, densoisedImg, cv::Size(5, 5), gaussianSigmaX,
                   gaussianSigmaY);
  // create and fill ROImask with zeros of same image size and type as src
  cv::Mat ROImask = cv::Mat::zeros(src.size(), src.type());
  // create rectangle mask to ignore areas not of interest for lane detection
  cv::rectangle(ROImask, cv::Point(0, 429), cv::Point(1280, 672),
                cv::Scalar(255, 255, 255), -1, 8, 0);
  // mask the smoothened image with the rectangular mask
  densoisedImg.copyTo(dst, ROImask);
}
/**
 *   @brief Function to get a binary image after color thresholding and edge
 *   detection
 *
 *   @param masked image of type cv::Mat
 *   @param binary image of type cv::Mat
 *   @return nothing
 */
void ImageProcessing::getBinaryImg(cv::Mat& src, cv::Mat& dst) {
  cv::Mat HLSimg, thresholdImg;  // declare variable holders for HLS image and
                                 // thresholded image
  // convert image to HLS colorspace
  cv::cvtColor(src, HLSimg, cv::COLOR_BGR2HLS);
  // threshold in HLS colorspace
  cv::inRange(HLSimg, minThreshHLS, maxThreshHLS, thresholdImg);
  std::vector<cv::Point> lanePoints;  // declare variable holder for points
                                      // of polygon in which lanes appear
  // create laneMaskROI with zeros image size of src and binary type
  cv::Mat laneMaskROI(src.size(), CV_8U, cv::Scalar(0));
  lanePoints.push_back(cv::Point(560, 429));  // points of vertex 1 of polygon
  lanePoints.push_back(cv::Point(690, 429));  // points of vertex 2 of polygon
  lanePoints.push_back(cv::Point(1155, 672));  // points of vertex 3 of polygon
  lanePoints.push_back(cv::Point(225, 672));  // points of vertex 4 of polygon
  // fill convex polygon having vertices described by lanePoints with value 255
  cv::fillConvexPoly(laneMaskROI, lanePoints, 255);
  // mask the thresholded image using bitwise AND to only display the lane ROI
  cv::bitwise_and(thresholdImg, laneMaskROI, dst);
}
/**
 *   @brief Function to perform prospective transform
 *
 *   @param binary image of type cv::Mat
 *   @param bird's view image of type cv::Mat
 *   @return nothing
 */
void ImageProcessing::prespectiveTransform(cv::Mat& src, cv::Mat& dst,
                                           cv::Mat& T_perspective_inv) {
  cv::Point2f inputQuadrilateral[4];  // declare variable holder for vertices of
                                      // input polygon for perspective transform
  cv::Point2f outputQuadrilateral[4];  // declare variable holder for vertices
                                       // of output for perspective transform
  // initialize variable T_perspective
  cv::Mat T_perspective = cv::Mat::zeros(src.size(), src.type());
  // set variable T_perspective_inv to zeros
  T_perspective_inv = cv::Mat::zeros(src.size(), src.type());
  // set vertices of input polygon for perspective transform
  cv::Point2f inQuadrilateral[4] = { cv::Point(544, 462), cv::Point(731, 462),
      cv::Point(1268, 708), cv::Point(0, 708) };
  // set vertices of output polygon for perspective transform
  cv::Point2f outQuadrilateral[4] = { cv::Point(0, 0), cv::Point(src.cols, 0),
      cv::Point(src.cols, src.rows), cv::Point(0, src.rows) };
  // get perspective transform using inQuadrilateral and outQuadrilateral
  T_perspective = cv::getPerspectiveTransform(inQuadrilateral,
                                              outQuadrilateral);
  // get inverse of perspective transform using inQuadrilateral
  // and outQuadrilateral
  T_perspective_inv = cv::getPerspectiveTransform(outQuadrilateral,
                                                  inQuadrilateral);
  // transform image points using the perspective transform obtained
  cv::warpPerspective(src, dst, T_perspective, src.size());
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
                                   double cy_) {
  // set intrinsic matrix
  intrinsic =
      (cv::Mat_<double>(3, 3) << fx_, 0.0, cx_, 0.0, fy_, cy_, 0.0, 0.0, 1.0);
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
                                    double p2_, double k3_) {
  // set distortion coefficients
  distortionCoeffs =
      (cv::Mat_<double>(1, 5) << k1_, k2_, p1_, p2_, k3_);
}
/**
 *   @brief Function to set standard deviation in X for gaussian blur
 *
 *   @param standard deviation in X for gaussian blur
 *   @return nothing
 */
void ImageProcessing::setgaussianSigmaX(double gaussianSigmaX_) {
  gaussianSigmaX = gaussianSigmaX_;
}
/**
 *   @brief Function to set standard deviation in Y for gaussian blur
 *
 *   @param standard deviation in Y for gaussian blur
 *   @return nothing
 */
void ImageProcessing::setgaussianSigmaY(double gaussianSigmaY_) {
  gaussianSigmaY = gaussianSigmaY_;
}
/**
 *   @brief Function to set HSL color space minimum threshold value
 *
 *   @param minimum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 *   @return nothing
 */
void ImageProcessing::setMinThreshHLS(cv::Scalar minThreshHLS_) {
  minThreshHLS = minThreshHLS_;
}
/**
 *   @brief Function to set HSL color space maximum threshold value
 *
 *   @param maximum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 *   @return nothing
 */
void ImageProcessing::setMaxThreshHLS(cv::Scalar maxThreshHLS_) {
  maxThreshHLS = maxThreshHLS_;
}
/**
 *   @brief Function to set RGB color space minimum threshold value
 *
 *   @param minimum threshold values for red,green and blue, type cv::Vec<double, 3>
 *   @return nothing
 */
void ImageProcessing::setMinThreshBGR(cv::Scalar minThreshBGR_) {
  minThreshBGR = minThreshBGR_;
}
/**
 *   @brief Function to set RGB color space maximum threshold value
 *
 *   @param maximum threshold values for red,green and blue, type cv::Vec<double, 3>
 *   @return nothing
 */
void ImageProcessing::setMaxThreshBGR(cv::Scalar maxThreshBGR_) {
  maxThreshBGR = maxThreshBGR_;
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
  return intrinsic;
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
cv::Mat ImageProcessing::getDistCoeffs(void) {
  return distortionCoeffs;
}
/**
 *   @brief Function to get standard deviation in X for gaussian blur
 *
 *   @param nothing
 *   @return standard deviation in X for gaussian blur
 */
double ImageProcessing::getgaussianSigmaX(void) {
  return gaussianSigmaX;
}
/**
 *   @brief Function to get standard deviation in Y for gaussian blur
 *
 *   @param nothing
 *   @return standard deviation in Y for gaussian blur
 */
double ImageProcessing::getgaussianSigmaY(void) {
  return gaussianSigmaY;
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
cv::Scalar ImageProcessing::getMinThreshHLS(void) {
  return minThreshHLS;
}
/**
 *   @brief Function to get HSL color space maximum threshold value
 *
 *   @param nothing
 *   @return maximum threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 */
cv::Scalar ImageProcessing::getMaxThreshHLS(void) {
  return maxThreshHLS;
}
/**
 *   @brief Function to get RGB color space minimum threshold value
 *
 *   @param nothing
 *   @return minimum threshold values for red,green and blue, type cv::Vec<double, 3>
 */
cv::Scalar ImageProcessing::getMinThreshBGR(void) {
  return minThreshBGR;
}
/**
 *   @brief Function to get RGB color space maximum threshold value
 *
 *   @param nothing
 *   @return maximum threshold values for red,green and blue, type cv::Vec<double, 3>
 */
cv::Scalar ImageProcessing::getMaxThreshBGR(void) {
  return maxThreshBGR;
}
