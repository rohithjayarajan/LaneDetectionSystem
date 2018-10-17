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
 *  @date 10/15/2018
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

#include "LaneInfo.hpp"
  /**
   *   @brief Default constructor for LaneDetection
   *
   *   @param nothing
   *   @return nothing
   */
LaneInfo::LaneInfo() {
}
  /**
   *   @brief Default destructor for LaneDetection
   *
   *   @param nothing
   *   @return nothing
   */
LaneInfo::~LaneInfo() {
}
/**
 *   @brief Function to set lanePoints
 *
 *   @param set of lane pixels of type std::vector<cv::Point>
 *   @return nothing
 */
void LaneInfo::setLanePoints(std::vector<cv::Point> lanePoints) {
}
/**
 *   @brief Function to set laneCoeffs
 *
 *   @param lane coefficients of type cv::Mat
 *   @return nothing
 */
void LaneInfo::setLaneCoeffs(cv::Mat laneCoeffs) {
}
/**
 *   @brief Function to set laneColor
 *
 *   @param lane color of type cv::Vec3b
 *   @return nothing
 */
void LaneInfo::setLaneColor(cv::Vec3b laneColor) {
}
/**
 *   @brief Function to get lanePoints
 *
 *   @param nothing
 *   @return set of lane pixels of type std::vector<cv::Point>
 */
std::vector<cv::Point> LaneInfo::getLanePoints(void) {
std::vector<cv::Point> a;
return a;
}
/**
 *   @brief Function to get laneCoeffs
 *
 *   @param nothing
 *   @return lane coefficients of type cv::Mat
 */
cv::Mat LaneInfo::getLaneCoeffs(void) {
cv::Mat a;
return a;
}
/**
 *   @brief Function to get laneColor
 *
 *   @param nothing
 *   @return lane color of type cv::Vec3b
 */
cv::Vec3b LaneInfo::getLaneColor(void) {
  cv::Vec3b a;
return a;
}
