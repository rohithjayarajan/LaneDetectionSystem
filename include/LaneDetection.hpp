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
 *  Copyright 2018 Akash Guha, rohithjayarajan
 *  @file    LaneDetection.hpp
 *  @author  Akash Guha, rohithjayarajan
 *  @date 10/13/2018
 *  @version 1.1
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
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class LaneDetection {
 private:
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
  ~LaneDetection();
  /**
   *   @brief Function to generate lane pixel histogram
   *
   *   @param projective transform of binary image of type cv::Mat
   *   @param histogram containing lane pixels of type cv::Mat
   *   @return nothing
   */
  void generateHist(cv::Mat& src, cv::Mat& hist);
  /**
   *   @brief Function to extract left or right lane
   *
   *   @param histogram containing lane pixels of type cv::Mat
   *   @param pixel locations of left or right lane, type std::vector<cv::Point_<int>>
   *   @param lane to be extracted - left or right of type string
   *   @return nothing
   */
  void extractLane(cv::Mat& hist, std::vector<cv::Point_<int>>& dstLane,
                   std::string& laneType);
  /**
   *   @brief Function to fit a polynomial on the received lane pixel data
   *
   *   @param left or right lane pixel locations, type std::vector<cv::Point_<int>>
   *   @param pixel locations fitted to a particular polynomial, type std::vector<cv::Point_<int>>
   *   @return nothing
   */
  void fitPoly(std::vector<cv::Point_<int>> laneLR,
               std::vector<cv::Point_<int>> dstPixelPoly);
  /**
   *   @brief Function to extract central line
   *
   *   @param left lane pixel locations, type std::vector<cv::Point_<int>>
   *   @param right lane pixel locations, type std::vector<cv::Point_<int>>
   *   @param central line pixel locations, type std::vector<cv::Point_<int>>
   *   @return nothing
   */
  void extractCentralLine(
      std::vector<cv::Point_<int>> leftLane,
                          std::vector<cv::Point_<int>> rightLane,
                          std::vector<cv::Point_<int>> centralLine);
  /**
   *   @brief Function to compute slope of the central line
   *
   *   @param central line pixel location, type std::vector<cv::Point_<int>>
   *   @param string, indicating left or right turn
   *   @return nothing
   */
  void computeGradient(std::vector<cv::Point_<int>> centralLine,
                       std::string steerDirection);
  /**
   *   @brief Function to compute radius of curvature of the lane
   *
   *   @param central line pixel locations, type std::vector<cv::Point_<int>>
   *   @return radius of curvature, type double
   */
  double computeRadiusOfCurve(std::vector<cv::Point_<int>> centralLine);
};

#endif  // INCLUDE_LANEDETECTION_HPP_
