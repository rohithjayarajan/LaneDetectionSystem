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
 *  @file    LaneDetection.hpp
 *  @author  rohithjayarajan, Akash Guha
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
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

class LaneDetection {
 private:
  int windowBuffer;
  std::vector<int> avgRightCenter;
  cv::Mat leftLaneCoeffs;
  cv::Mat rightLaneCoeffs;

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
  void generateHist(cv::Mat& src, std::vector<double>& hist);
  /**
   *   @brief Function to get average of window center
   *
   *   @param histogram containing lane pixels of type cv::Mat
   *   @param pixel locations of left or right lane, type std::vector<cv::Point_<int>>
   *   @param lane to be extracted - left or right of type string
   *   @return nothing
   */
  int averageWindowCenter(int& xVal);
  /**
   *   @brief Function to extract left or right lane
   *
   *   @param histogram containing lane pixels of type cv::Mat
   *   @param pixel locations of left or right lane, type std::vector<cv::Point_<int>>
   *   @param lane to be extracted - left or right of type string
   *   @return nothing
   */
  void extractLane(cv::Mat& perspectiveImg, std::vector<double>& hist,
                   std::vector<cv::Point>& dstLane,
                   std::string laneType,
                   cv::Mat& drawWindow);
  /**
   *   @brief Function to fit a polynomial on the received lane pixel data
   *
   *   @param left or right lane pixel locations, type std::vector<cv::Point_<int>>
   *   @param pixel locations fitted to a particular polynomial, type std::vector<cv::Point_<int>>
   *   @return nothing
   */
  void fitPoly(std::vector<cv::Point>& laneLR, cv::Mat& dstLaneParameters,
               int order);
  /**
   *   @brief Function to extract central line
   *
   *   @param left lane pixel locations, type std::vector<cv::Point_<int>>
   *   @param right lane pixel locations, type std::vector<cv::Point_<int>>
   *   @param central line pixel locations, type std::vector<cv::Point_<int>>
   *   @return nothing
   */
  void extractCentralLine(std::vector<cv::Point>& leftLanePoints,
          std::vector<cv::Point>& centralLine);
  /**
   *   @brief Function to compute turn angle for the lane
   *
   *   @param left line pixel locations, type std::vector<cv::Point_<int>>
   *   @return turn angle, type double
   */
  double computeTurnAngle(std::vector<cv::Point>& leftLine);
  /**
   *   @brief Function to implement the entire system pipeline
   *
   *   @param nothing
   *   @return nothing
   */
  void detectLanes(void);
};

#endif  // INCLUDE_LANEDETECTION_HPP_
