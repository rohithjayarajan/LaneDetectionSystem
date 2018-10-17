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
#include "ImageProcessing.hpp"

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
 *   @param
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
  // select ROI as bottom half of the image
  cv::Rect bottomHalfROI(0, src.rows / 2, src.cols, src.rows / 2);
  // crop image according to ROI
  cv::Mat bottomHalfImage = src(bottomHalfROI);
  // reduce the image to a row vector of sum of rows
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
  int new_xVal = 0;  // initialize variable for new histogram center
  //  condition to push elements in vector to compute average center of
  //  histogram
  if (avgRightCenter.size() < windowBuffer) {
    // push element in the container
    avgRightCenter.push_back(xVal_);
  } else {
    // erase first four values of container
    avgRightCenter.erase(avgRightCenter.begin(), avgRightCenter.begin() + 3);
    avgRightCenter.push_back(xVal_);
  }
  // compute sum of the histogram center
  for (int& n : avgRightCenter) {
    new_xVal += n;
  }
  // compute average of the histogram center
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
                                std::string laneType, cv::Mat& drawWindow) {
  cv::Mat debug;  // create image container called debug
  // copy contents of perspectiveImg to debug
  perspectiveImg.copyTo(debug);
  // convert debug to color space BGR and save it in drawWindow
  cv::cvtColor(debug, drawWindow, cv::COLOR_GRAY2BGR);
  // initialize midpoint of histogram
  std::size_t const histMidPoint = hist.size() / 2;
  // get left half of histogram
  std::vector<double> histLeft(hist.begin(), hist.begin() + histMidPoint);
  // get right half of histogram
  std::vector<double> histRight(hist.begin() + histMidPoint, hist.end());
  int idxPeakL, idxPeakR;  // declare peaks of histogram
  // get left peak of histogram
  idxPeakL = std::max_element(histLeft.begin(), histLeft.end())
      - histLeft.begin();
  int xValL = idxPeakL;  // initialize xValL to left histograms  peak
  int numWindowsL = 8;  // set the number of left lane sliding windows
  // set the height of sliding window for left lane
  int heightWindowL = perspectiveImg.rows / numWindowsL;
  // set the width of sliding window for left lane
  int widthWindowL = 2 * heightWindowL;
  int temp_xValL;  // temporary variable to hold new peak
  // variable to update the height of sliding window from bottom of image
  int var_heightWindowL = perspectiveImg.rows;
  std::vector<int> updated_xVal_listL;  // initialize list of updated peaks
  // algorithm to find the lane pixels using sliding window approach
  for (int windowsL = 0; windowsL < numWindowsL; windowsL++) {
    // initialize the top left corner coordinates of sliding window
    cv::Point windowTopLeft(xValL - widthWindowL / 2,
                            var_heightWindowL - heightWindowL);
    // initialize the bottom right corner coordinates of sliding window
    cv::Point windowBottomRight(xValL + widthWindowL / 2, var_heightWindowL);
    for (int x_iterL = windowTopLeft.x; x_iterL <= windowBottomRight.x;
        x_iterL++) {
      for (int y_iterL = windowTopLeft.y; y_iterL <= windowBottomRight.y;
          y_iterL++) {
        // if image consists lane pixel, push it to container
        if (perspectiveImg.at<uchar>(y_iterL, x_iterL) > 0) {
          dstLane.push_back(cv::Point(y_iterL, x_iterL));
          // mark the lane pixels to a distinct color
          drawWindow.at<cv::Vec3b>(cv::Point(x_iterL, y_iterL)) = cv::Vec3b(0,
                                                                            255,
                                                                            0);
          // container to update the new x coordinate value for
          // further processing
          updated_xVal_listL.push_back(x_iterL);
          }
        }
      }
    // calculate the average value of the new x position of sliding window
    if (!updated_xVal_listL.empty()) {
      temp_xValL = 0;
      for (int& n : updated_xVal_listL) {
        temp_xValL += n;
        }
      xValL = temp_xValL / updated_xVal_listL.size();
      }
    // update the height of window
    var_heightWindowL = var_heightWindowL - heightWindowL - 1;
    // clear the list
    updated_xVal_listL.clear();
    }
  // get right peak of histogram
  idxPeakR = std::max_element(histRight.begin(), histRight.end())
        - histRight.begin()
        + histMidPoint;
  // initialize xValL to right histograms  peak
  int xValR = averageWindowCenter(idxPeakR);
  // set the number of left lane sliding windows
  int numWindowsR = 8;
  // set the height of sliding window for left lane
  int heightWindowR = perspectiveImg.rows / numWindowsR;
  // set the width of sliding window for left lane
  int widthWindowR = 2 * heightWindowR;
  int temp_xValR;  // temporary variable to hold new peak
  // variable to update the height of sliding window from bottom of image
  int var_heightWindowR = perspectiveImg.rows;
  std::vector<int> updated_xVal_listR;  // initialize list of updated peaks
  // algorithm to find the lane pixels using sliding window approach
  for (int windowsR = 0; windowsR < numWindowsR; windowsR++) {
    // initialize the top left corner coordinates of sliding window
    cv::Point windowTopLeft(xValR - widthWindowR / 2,
                            var_heightWindowR - heightWindowR);
    // initialize the bottom right corner coordinates of sliding window
    cv::Point windowBottomRight(xValR + widthWindowR / 2, var_heightWindowR);
    for (int x_iterR = windowTopLeft.x; x_iterR <= windowBottomRight.x;
        x_iterR++) {
      // if image consists lane pixel, push it to container
      for (int y_iterR = windowTopLeft.y; y_iterR <= windowBottomRight.y;
          y_iterR++) {
        if (perspectiveImg.at<uchar>(y_iterR, x_iterR) > 0) {
          dstLane.push_back(cv::Point(y_iterR, x_iterR));
          // mark the lane pixels to a distinct color
          drawWindow.at<cv::Vec3b>(cv::Point(x_iterR, y_iterR)) = cv::Vec3b(
                0, 0, 255);
          // container to update the new x coordinate value for
          // further processing
          updated_xVal_listR.push_back(x_iterR);
          }
        }
      }
    // calculate the average value of the new x position
    // of sliding window
    if (!updated_xVal_listR.empty()) {
      temp_xValR = 0;
      for (int& n : updated_xVal_listR) {
        temp_xValR += n;
        }
      xValR = temp_xValR / updated_xVal_listR.size();
      }
    // update the height of window
    var_heightWindowR = var_heightWindowR - heightWindowR - 1;
  }
  }
/**
 *   @brief Function to fit a polynomial on the received lane pixel data
 *
 *   @param left or right lane pixel locations, type std::vector<cv::Point_<int>>
 *   @param pixel locations fitted to a particular polynomial, type std::vector<cv::Point_<int>>
 *   @return nothing
 */
void LaneDetection::fitPoly(std::vector<cv::Point>& laneLR,
                            cv::Mat& dstLaneParameters, int order) {
  cv::Mat src_x = cv::Mat(laneLR.size(), 1, CV_32F);
  cv::Mat src_y = cv::Mat(laneLR.size(), 1, CV_32F);
  for (int iter = 0; iter < laneLR.size(); iter++) {
    src_x.at<float>(iter, 0) = static_cast<float>(laneLR[iter].x);
    src_y.at<float>(iter, 0) = static_cast<float>(laneLR[iter].y);
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
void LaneDetection::extractCentralLine(std::vector<cv::Point>& leftLanePoints,
                                       std::vector<cv::Point>& centralLine) {
  int offset = 333;  // offset for central line
  // update central line information
  for (auto& n : leftLanePoints) {
    centralLine.push_back(cv::Point(n.y, n.x + offset));
  }
}
/**
 *   @brief Function to compute turn angle for the lane
 *
 *   @param central line pixel locations, type std::vector<cv::Point_<int>>
 *   @return radius of curvature, type double
 */
double LaneDetection::computeTurnAngle(
    std::vector<cv::Point>& leftLine) {
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
  // declare the images to be used or processed
  cv::Mat frame, processedFrame, binaryFrame, perspectiveImg, T_perspective_inv,
      drawWindow, ouputFrame, unWarp_drawWindow;
  ImageProcessing processImage;
  // declare the containers to be used
  std::vector<double> histogram;
  std::vector<cv::Point> leftLanePts, rightLanePts;
  while (true) {
    cap >> frame;  // process video frame by frame
    // if frame is empty, break
    if (frame.empty()) {
      break;
    }
    // pre process image
    processImage.preProcessing(frame, processedFrame);
    // get binary thresholded image
    processImage.getBinaryImg(processedFrame, binaryFrame);
    // get perspective image
    processImage.prespectiveTransform(binaryFrame, perspectiveImg,
                                      T_perspective_inv);
    // generate histogram of image pixels
    generateHist(perspectiveImg, histogram);
    // extract lanes
    extractLane(perspectiveImg, histogram, leftLanePts, "Left", drawWindow);
    cv::Mat outImage, colorOutImage;
    // undo perspective transformation
    cv::warpPerspective(drawWindow, outImage, T_perspective_inv,
                        drawWindow.size());

    outImage.copyTo(colorOutImage);
    int width = frame.cols;
    int height = frame.rows;
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        if ((colorOutImage.at<cv::Vec3b>(j, i)[0] == 0)
            && (colorOutImage.at<cv::Vec3b>(j, i)[1] == 0)
            && (colorOutImage.at<cv::Vec3b>(j, i)[2] == 0)) {
          colorOutImage.at<cv::Vec3b>(j, i)[0] = frame.at<cv::Vec3b>(j, i)[0];
          colorOutImage.at<cv::Vec3b>(j, i)[1] = frame.at<cv::Vec3b>(j, i)[1];
          colorOutImage.at<cv::Vec3b>(j, i)[2] = frame.at<cv::Vec3b>(j, i)[2];
        }
      }
    }

    cv::imshow("Undistorted Frame", colorOutImage);
//    cv::waitKey(0);
//    //    press ESC
//    //    to exit
//    char c = (char) cv::waitKey(25);
//    if (c == 27)
//      break;
    if (cv::waitKey(30) >= 0)
      break;
  }
  cap.release();  // release video capture object
  cv::destroyAllWindows();  // destroy/close all frames
}
