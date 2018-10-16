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
 *  @file    LaneDetection.cpp
 *  @author  rohithjayarajan, Akash Guha
 *  @date 10/13/2018
 *  @version 1.1
 *
 *  @brief Lane Detection Class file
 *
 *  @section DESCRIPTION
 *
 *  Class for lane detection. This
 *  includes definitions all functionalities to
 *  implement a lane detection system and to predict
 *  steering information for the vehicle.
 *
 */

#include "LaneDetection.hpp"
#include "ImageProcessing.cpp"

/**
 *   @brief Default constructor for LaneDetection
 *
 *   @param nothing
 *   @return nothing
 */
LaneDetection::LaneDetection() {
  windowBuffer = 15;
  }
/**
 *   @brief Default destructor for LaneDetection
 *
 *   @param nothing
 *   @return nothing
 */
LaneDetection::~LaneDetection() {
}
/**
 *   @brief Function to undistort the input image
 *
 *   @param input image of type cv::Mat
 *   @return undistorted input image of type cv::Mat
 */
/**
 *   @brief Function to generate lane pixel histogram
 *
 *   @param projective transform of binary image of type cv::Mat
 *   @param histogram containing lane pixels of type cv::Mat
 *   @return nothing
 */
void LaneDetection::generateHist(cv::Mat& src, std::vector<double>& hist) {
//  hist = cv::Mat::zeros(1, src.cols, CV_64FC1);
  cv::Rect bottomHalfROI(0, src.rows / 2, src.cols, src.rows / 2);
  cv::Mat bottomHalfImage = src(bottomHalfROI);
  cv::reduce(bottomHalfImage, hist, 0, CV_REDUCE_SUM, CV_64FC1);
}
/**
 *   @brief Function to get average of window center
 *
 *   @param histogram containing lane pixels of type cv::Mat
 *   @param pixel locations of left or right lane, type std::vector<cv::Point_<int>>
 *   @param lane to be extracted - left or right of type string
 *   @return nothing
 */
int LaneDetection::averageWindowCenter(int& xVal_) {
  int new_xVal = 0;
  if (avgRightCenter.size() < windowBuffer) {
    avgRightCenter.push_back(xVal_);
  }
  else {
    avgRightCenter.erase(avgRightCenter.begin(), avgRightCenter.begin() + 3);
    avgRightCenter.push_back(xVal_);
  }
  for (int& n : avgRightCenter) {
    new_xVal += n;
  }
  new_xVal = new_xVal / avgRightCenter.size();
  return new_xVal;
}
/**
 *   @brief Function to extract left or right lane
 *
 *   @param histogram containing lane pixels of type cv::Mat
 *   @param pixel locations of left or right lane, type std::vector<cv::Point_<int>>
 *   @param lane to be extracted - left or right of type string
 *   @return nothing
 */
void LaneDetection::extractLane(cv::Mat& perspectiveImg,
                                std::vector<double>& hist,
                                std::vector<cv::Point>& dstLane,
                                std::string laneType) {
  cv::Mat debug;
  perspectiveImg.copyTo(debug);
  cv::Mat drawWindow;
  cv::cvtColor(debug, drawWindow, cv::COLOR_GRAY2BGR);
  std::size_t const histMidPoint = hist.size() / 2;
  std::vector<double> histLeft(hist.begin(), hist.begin() + histMidPoint);
  std::vector<double> histRight(hist.begin() + histMidPoint, hist.end());
  int idxPeak;
  if (laneType == "Left") {
    idxPeak = std::max_element(histLeft.begin(), histLeft.end())
        - histLeft.begin();
    int xVal = idxPeak;
    int numWindows = 8;
    int linespace = 0;
    int linespaceBound = 100;
    int heightWindow = perspectiveImg.rows / numWindows;
    int widthWindow = 2 * heightWindow;
    int temp_xVal;
    int var_heightWindow = perspectiveImg.rows;
    std::vector<int> updated_xVal_list;
    for (int windows = 0; windows < numWindows; windows++) {
      cv::Point windowTopLeft(xVal - widthWindow / 2,
                              var_heightWindow - heightWindow);
      cv::Point windowBottomRight(xVal + widthWindow / 2, var_heightWindow);
      cv::rectangle(drawWindow, windowTopLeft, windowBottomRight,
                    cv::Scalar(0, 0, 255), 1);
      for (int x_iter = windowTopLeft.x; x_iter <= windowBottomRight.x;
          x_iter++) {
        for (int y_iter = windowTopLeft.y; y_iter <= windowBottomRight.y;
            y_iter++) {
          if (perspectiveImg.at<uchar>(y_iter, x_iter) > 0) {
            if (linespace % linespaceBound == 0) {
              dstLane.push_back(cv::Point(y_iter, x_iter));
            }
            linespace++;
            drawWindow.at<cv::Vec3b>(cv::Point(x_iter, y_iter)) = cv::Vec3b(255,
                                                                        128,
                                                                        14);
            updated_xVal_list.push_back(x_iter);
          }
        }
      }
      if (!updated_xVal_list.empty()) {
        temp_xVal = 0;
        for (int& n : updated_xVal_list) {
          temp_xVal += n;
        }
        xVal = temp_xVal / updated_xVal_list.size();
      }
      var_heightWindow = var_heightWindow - heightWindow - 1;
      updated_xVal_list.clear();
    }
    std::cout << dstLane.size();
    this->fitPoly(dstLane, leftLaneCoeffs, 2);
    cv::imshow("Undistorted Frame", drawWindow);
    cv::waitKey(0);
  } else if (laneType == "Right") {
    idxPeak = std::max_element(histRight.begin(), histRight.end())
        - histRight.begin()
        + histMidPoint;
    int xVal = averageWindowCenter(idxPeak);
    int numWindows = 8;
    int linespace = 0;
    int linespaceBound = 100;
    int heightWindow = perspectiveImg.rows / numWindows;
    int widthWindow = 2 * heightWindow;
    int temp_xVal;
    int var_heightWindow = perspectiveImg.rows;
    std::vector<int> updated_xVal_list;
    for (int windows = 0; windows < numWindows; windows++) {
      cv::Point windowTopLeft(xVal - widthWindow / 2,
                              var_heightWindow - heightWindow);
      cv::Point windowBottomRight(xVal + widthWindow / 2, var_heightWindow);
      cv::rectangle(drawWindow, windowTopLeft, windowBottomRight,
                    cv::Scalar(0, 0, 255), 1);
      for (int x_iter = windowTopLeft.x; x_iter <= windowBottomRight.x;
          x_iter++) {
        for (int y_iter = windowTopLeft.y; y_iter <= windowBottomRight.y;
            y_iter++) {
          if (perspectiveImg.at<uchar>(y_iter, x_iter) > 0) {
            if (linespace % linespaceBound == 0) {
              dstLane.push_back(cv::Point(y_iter, x_iter));
            }
            linespace++;
            drawWindow.at<cv::Vec3b>(cv::Point(x_iter, y_iter)) = cv::Vec3b(255,
                                                                        128,
                                                                        14);
            updated_xVal_list.push_back(x_iter);
          }
        }
      }
      if (!updated_xVal_list.empty()) {
        temp_xVal = 0;
        for (int& n : updated_xVal_list) {
          temp_xVal += n;
        }
        xVal = temp_xVal / updated_xVal_list.size();
      }
      var_heightWindow = var_heightWindow - heightWindow - 1;
//      updated_xVal_list.clear();
    }
    std::cout << dstLane.size();
    this->fitPoly(dstLane, rightLaneCoeffs, 2);
    cv::imshow("Undistorted Frame", drawWindow);
    cv::waitKey(0);
  } else {
    throw std::invalid_argument("received unknown lane type value");
  }
}
/**
 *   @brief Function to fit a polynomial on the received lane pixel data
 *
 *   @param left or right lane pixel locations, type std::vector<cv::Point_<int>>
 *   @param pixel locations fitted to a particular polynomial, type std::vector<cv::Point_<int>>
 *   @return nothing
 */
void LaneDetection::fitPoly(std::vector<cv::Point> laneLR,
                            cv::Mat dstLaneParameters, int order) {
  cv::Mat src_x = cv::Mat(laneLR.size(), 1, CV_32F);
  cv::Mat src_y = cv::Mat(laneLR.size(), 1, CV_32F);
  for (int iter = 0; iter < laneLR.size(); iter++) {
    src_x.at<float>(iter, 0) = (float) laneLR[iter].x;
    src_y.at<float>(iter, 0) = (float) laneLR[iter].y;
  }
  int npoints = src_x.checkVector(1);
  int nypoints = src_y.checkVector(1);
  CV_Assert(npoints == nypoints && npoints >= order + 1);
  cv::Mat_<double> srcX(src_x), srcY(src_y);
  cv::Mat_<double> A = cv::Mat_<double>::ones(npoints, order + 1);
  // build A matrix
  for (int y = 0; y < npoints; ++y) {
    for (int x = 1; x < A.cols; ++x)
      A.at<double>(y, x) = srcX.at<double>(y) * A.at<double>(y, x - 1);
  }
  cv::Mat w;
  cv::solve(A, srcY, w, cv::DECOMP_SVD);
  w.convertTo(
      dstLaneParameters,
      ((src_x.depth() == CV_64F || src_y.depth() == CV_64F) ? CV_64F : CV_32F));
}
/**
 *   @brief Function to extract central line
 *
 *   @param left lane pixel locations, type std::vector<cv::Point_<int>>
 *   @param right lane pixel locations, type std::vector<cv::Point_<int>>
 *   @param central line pixel locations, type std::vector<cv::Point_<int>>
 *   @return nothing
 */
void LaneDetection::extractCentralLine(
    std::vector<cv::Point_<int>> leftLane,
                        std::vector<cv::Point_<int>> rightLane,
    std::vector<cv::Point_<int>> centralLine) {
}
/**
 *   @brief Function to compute slope of the central line
 *
 *   @param central line pixel location, type std::vector<cv::Point_<int>>
 *   @param string, indicating left or right turn
 *   @return nothing
 */
void LaneDetection::computeGradient(std::vector<cv::Point_<int>> centralLine,
                                    std::string steerDirection) {
}
/**
 *   @brief Function to compute radius of curvature of the lane
 *
 *   @param central line pixel locations, type std::vector<cv::Point_<int>>
 *   @return radius of curvature, type double
 */
double LaneDetection::computeRadiusOfCurve(
    std::vector<cv::Point_<int>> centralLine) {
  return 0.0;
}
/**
 *   @brief Function to implement the entire system pipeline
 *
 *   @param nothing
 *   @return nothing
 */
void LaneDetection::detectLanes(void) {
  // uncomment this block to use input from image sensor
  //  cv::VideoCapture cap(0);  // open default camera
  //  if (!cap.isOpened()) {  // check if camera not opened
  //    std::cout << "No video device detected!!!" << std::endl;
  //  }
  //  else {
  //    cv::VideoCapture cap(
  //        "..\\data\\test_video.mp4");  // open video file
  //  }
  cv::VideoCapture cap("test_video.mp4");  // open video file
  if (!cap.isOpened()) {  // check if file is opened
    std::cout << "No video file detected!!!" << std::endl;
  }
  cv::Mat frame;
  ImageProcessing processImage;
  cv::Mat processedFrame, binaryFrame, perspectiveImg, T_perspective_inv;
  std::vector<double> histogram;
  std::vector<cv::Point> leftLane;
  std::vector<cv::Point> rightLane;
  while (true) {
    cap >> frame;  // process video frame by frame
    // if frame is empty, break
    if (frame.empty()) {
      break;
    }
    processImage.preProcessing(frame, processedFrame);
    processImage.getBinaryImg(processedFrame, binaryFrame);
    processImage.prespectiveTransform(binaryFrame, perspectiveImg,
                                      T_perspective_inv);
    generateHist(perspectiveImg, histogram);
    extractLane(perspectiveImg, histogram, leftLane, "Left");
    extractLane(perspectiveImg, histogram, rightLane, "Right");
//    cv::imshow("Undistorted Frame", perspectiveImg);
//    cv::imshow("Undistorted Frame", perspectiveImg);
//    cv::waitKey(0);
    // press ESC to exit
//    char c = (char) cv::waitKey(25);
//    if (c == 27)
//      break;
  }
  cap.release();  // release video capture object
  cv::destroyAllWindows();  // destroy/close all frames
}
