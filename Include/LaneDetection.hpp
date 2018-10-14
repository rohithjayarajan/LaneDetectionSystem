/**
 *  Copyright 2018 Akash Guha
 *  @file    LaneDetection.hpp
 *  @author  Akash Guha
 *
 *  @brief Lane Detection Class Header
 *
 *  @section DESCRIPTION
 *
 *  Class for lane detection module. This
 *  includes declarations of all functionalities to
 *  implement a lane detection system and to predict
 *  steering information for the vehicle.
 *
 */

#ifndef INCLUDE_LANEDETECTION_HPP_
#define INCLUDE_LANEDETECTION_HPP_
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/core/core.hpp"

class LaneDetection {
 private:
  cv::Size_<int> imgSize;  // size of the input image
  cv::Mat inputImg;  // variable to hold the input image
  cv::Mat undistortedImg;  // variable to hold undistorted image
  cv::Mat denoisedImg;  // variable to hold denoised image
  cv::Mat maskedImg;  // variable to hold masked image
  cv::Mat binaryImg;  // variable to hold binary image
  std::vector<cv::Point_<int>> rightLane;  // right lane pixels
  std::vector<cv::Point_<int>> leftLane;  // left lane pixels
  std::vector<cv::Point_<int>> centralLine;  // central line pixels
  cv::Vec<double, 3> threshHSL;  // HSL color space threshold values
  cv::Vec<double, 3> threshBGR;  // RGB color space threshold values
  cv::Mat hist;  // lane pixel histogram

 public:
  /**
   *   @brief Default constructor for LaneDetection
   *
   *   @param nothing
   *   @return nothing
   */
  LaneDetection();
  /**
   *   @brief Default destructor for LaneDetection
   *
   *   @param nothing
   *   @return nothing
   */
  virtual ~LaneDetection();
  /**
   *   @brief Function to undistort the input image
   *
   *   @param input image of type cv::Mat
   *   @return undistorted input image of type cv::Mat
   */
  cv::Mat unDistort(cv::Mat inputImg);
  /**
   *   @brief Function to denoise undistorted input image
   *
   *   @param undistorted image of type cv::Mat
   *   @return denoised image of type cv::Mat
   */
  cv::Mat deNoise(cv::Mat undistortedImg);
  /**
   *   @brief Function to denoise image
   *
   *   @param denoised image of type cv::Mat
   *   @return masked image of type cv::Mat
   */
  cv::Mat ROI(cv::Mat denoisedImg);
  /**
   *   @brief Function to get a binary image based on the color thresholding
   *
   *   @param masked image of type cv::Mat
   *   @param thresholding color space of type string
   *   @return binary image of type cv::Mat
   */
  cv::Mat colorThreshold(cv::Mat maskedImg, std::string colorSpace);
  /**
   *   @brief Function to generate lane pixel histogram
   *
   *   @param projective transform of binary image of type cv::Mat
   *   @return histogram containing lane pixels of type cv::Mat
   */
  cv::Mat generateHist(cv::Mat birdView);
  /**
   *   @brief Function to extract left or right lane
   *
   *   @param histogram containing lane pixels of type cv::Mat
   *   @param lane to be extracted - left or right of type string
   *   @return pixel locations of left or right lane, type std::vector<cv::Point_<int>>
   */
  std::vector<cv::Point_<int>> extractLane(cv::Mat hist, std::string lane);
  /**
   *   @brief Function to fit a polynomial on the received lane pixel data
   *
   *   @param left or right lane pixel locations, type std::vector<cv::Point_<int>>
   *   @return pixel locations fitted to a particular polynomial, type std::vector<cv::Point_<int>>
   */
  std::vector<cv::Point_<int>> fitPoly(std::vector<cv::Point_<int>> laneLR);
  /**
   *   @brief Function to extract central line
   *
   *   @param left lane pixel locations, type std::vector<cv::Point_<int>>
   *   @param right lane pixel locations, type std::vector<cv::Point_<int>>
   *   @return central line pixel locations, type std::vector<cv::Point_<int>>
   */
  std::vector<cv::Point_<int>> extractCentralLine(
      std::vector<cv::Point_<int>> leftLane,
      std::vector<cv::Point_<int>> rightLane);
  /**
   *   @brief Function to compute slope of the central line
   *
   *   @param central line pixel location, type std::vector<cv::Point_<int>>
   *   @return string, indicating left or right turn
   */
  std::string computeGradient(std::vector<cv::Point_<int>> centralLine);
  /**
   *   @brief Function to compute radius of curvature of the lane
   *
   *   @param central line pixel locations, type std::vector<cv::Point_<int>>
   *   @return radius of curvature, type double
   */
  double computeRadiusOfCurve(std::vector<cv::Point_<int>> centralLine);
  /**
   *   @brief Function to set size of the input image
   *
   *   @param input image size of type cv::Size_<int>
   *   @return nothing
   */
  void setImgSize(cv::Size_<int>& imgSize);
  /**
   *   @brief Function to set input image
   *
   *   @param input image of type cv::Mat
   *   @return nothing
   */
  void setInputImg(cv::Mat& inputImg);
  /**
   *   @brief Function to set undistorted image
   *
   *   @param undistorted image of type cv::Mat
   *   @return nothing
   */
  void setUndistortedImg(cv::Mat& undistortedImg);
  /**
   *   @brief Function to set denoised image
   *
   *   @param denoised image of type cv::Mat
   *   @return nothing
   */
  void setDenoisedImg(cv::Mat& denoisedImg);
  /**
   *   @brief Function to set masked image
   *
   *   @param masked image of type cv::Mat
   *   @return nothing
   */
  void setMaskedImg(cv::Mat& maskedImg);
  /**
   *   @brief Function to set binary image
   *
   *   @param binary image of type cv::Mat
   *   @return nothing
   */
  void setBinaryImg(cv::Mat& binaryImg);
  /**
   *   @brief Function to set right lane pixel location
   *
   *   @param set of pixels consisting of right lane, type std::vector<cv::Point_<int>>
   *   @return nothing
   */
  void setRightLane(std::vector<cv::Point_<int>>& rightLane);
  /**
   *   @brief Function to set left lane pixel location
   *
   *   @param set of pixels consisting of left lane, type std::vector<cv::Point_<int>>
   *   @return nothing
   */
  void setLeftLane(std::vector<cv::Point_<int>>& leftLane);
  /**
   *   @brief Function to set central line pixel location
   *
   *   @param set of pixels consisting of central line, type std::vector<cv::Point_<int>>
   *   @return nothing
   */
  void setCentralLine(std::vector<cv::Point_<int>>& centralLine);
  /**
   *   @brief Function to set HSL color space threshold
   *
   *   @param threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
   *   @return nothing
   */
  void setThreshHSL(cv::Vec<double, 3>& threshHSL);
  /**
   *   @brief Function to set RGB color space threshold
   *
   *   @param threshold values for red,green and blue, type cv::Vec<double, 3>
   *   @return nothing
   */
  void setThreshBGR(cv::Vec<double, 3>& threshBGR);
  /**
   *   @brief Function to set lane pixel histogram
   *
   *   @param histogram representing the lane pixels along y-direction
   *   @return nothing
   */
  void setHist(cv::Mat& hist);
  /**
   *   @brief Function to get size of the input image
   *
   *   @param nothing
   *   @return input image size of type cv::Size_<int>
   */
  cv::Size_<int> getImgSize(void);
  /**
   *   @brief Function to get input image
   *
   *   @param nothing
   *   @return input image of type cv::Mat
   */
  cv::Mat getInputImg(void);
  /**
   *   @brief Function to get undistorted image
   *
   *   @param nothing
   *   @return undistorted image of type cv::Mat
   */
  cv::Mat getUndistortedImg(void);
  /**
   *   @brief Function to get denoised image
   *
   *   @param nothing
   *   @return denoised image of type cv::Mat
   */
  cv::Mat getDenoisedImg(void);
  /**
   *   @brief Function to get masked image
   *
   *   @param nothing
   *   @return masked image of type cv::Mat
   */
  cv::Mat getMaskedImg(void);
  /**
   *   @brief Function to get binary image
   *
   *   @param nothing
   *   @return binary image of type cv::Mat
   */
  cv::Mat getBinaryImg(void);
  /**
   *   @brief Function to get right lane pixel location
   *
   *   @param nothing
   *   @return set of pixels consisting of right lane, type std::vector<cv::Point_<int>>
   */
  std::vector<cv::Point_<int>> getRightLane(void);
  /**
   *   @brief Function to get left lane pixel location
   *
   *   @param nothing
   *   @return set of pixels consisting of left lane, type std::vector<cv::Point_<int>>
   */
  std::vector<cv::Point_<int>> getLeftLane(void);
  /**
   *   @brief Function to get central line pixel location
   *
   *   @param nothing
   *   @return set of pixels consisting of central line, type std::vector<cv::Point_<int>>
   */
  std::vector<cv::Point_<int>> getCentralLine(void);
  /**
   *   @brief Function to get HSL color space threshold
   *
   *   @param nothing
   *   @return threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
   */
  cv::Vec<double, 3> getThreshHSL(void);
  /**
   *   @brief Function to get RGB color space threshold
   *
   *   @param nothing
   *   @return threshold values for red,green and blue, type cv::Vec<double, 3>
   */
  cv::Vec<double, 3> getThreshBGR(void);
  /**
   *   @brief Function to get lane pixel histogram
   *
   *   @param nothing
   *   @return histogram representing the lane pixels along y-direction
   */
  cv::Mat getHist(void);
};




#endif  // INCLUDE_LANEDETECTION_HPP_
