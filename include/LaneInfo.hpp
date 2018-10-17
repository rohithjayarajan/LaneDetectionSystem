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
 *  @date 10/15/2018
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

#ifndef INCLUDE_LANEINFO_HPP_
#define INCLUDE_LANEINFO_HPP_
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

class LaneInfo {
 private:
  std::vector<cv::Point> lanePoints;
  cv::Mat laneCoeffs;
  cv::Vec3b laneColor;
 public:
  /**
   *   @brief Default constructor for LaneDetection
   *
   *   @param nothing
   *   @return nothing
   */
  LaneInfo();
  /**
   *   @brief Default destructor for LaneDetection
   *
   *   @param nothing
   *   @return nothing
   */
  ~LaneInfo();
  /**
   *   @brief Function to set lanePoints
   *
   *   @param set of lane pixels of type std::vector<cv::Point>
   *   @return nothing
   */
  void setLanePoints(std::vector<cv::Point> lanePoints);
  /**
   *   @brief Function to set laneCoeffs
   *
   *   @param lane coefficients of type cv::Mat
   *   @return nothing
   */
  void setLaneCoeffs(cv::Mat laneCoeffs);
  /**
   *   @brief Function to set laneColor
   *
   *   @param lane color of type cv::Vec3b
   *   @return nothing
   */
  void setLaneColor(cv::Vec3b laneColor);
  /**
   *   @brief Function to get lanePoints
   *
   *   @param nothing
   *   @return set of lane pixels of type std::vector<cv::Point>
   */
  std::vector<cv::Point> getLanePoints(void);
  /**
   *   @brief Function to get laneCoeffs
   *
   *   @param nothing
   *   @return lane coefficients of type cv::Mat
   */
  cv::Mat getLaneCoeffs(void);
  /**
   *   @brief Function to get laneColor
   *
   *   @param nothing
   *   @return lane color of type cv::Vec3b
   */
  cv::Vec3b getLaneColor(void);
};

#endif /* INCLUDE_LANEINFO_HPP_ */
