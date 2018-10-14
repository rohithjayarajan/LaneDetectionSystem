/**
 *  Copyright [2018] Akash Guha
 *  @file    LaneDetection.cpp
 *  @author  Akash Guha
 *
 *  @brief Lane Detection Class file
 *
 *  @section DESCRIPTION
 *
 *  Class for lane detection. This
 *  includes definations all functionalities to
 *  implement a lane detection system and to predict
 *  steering information for the vehicle.
 *
 */

#include "LaneDetection.hpp"

/**
 *   @brief Default constructor for LaneDetection
 *
 *   @param nothing
 *   @return nothing
 */
LaneDetection::LaneDetection() {
  }
/**
 *   @brief Default destructor for LaneDetection
 *
 *   @param nothing
 *   @return nothing
 */
virtual LaneDetection::~LaneDetection() {
}
/**
 *   @brief Function to undistort the input image
 *
 *   @param input image of type cv::Mat
 *   @return undistorted input image of type cv::Mat
 */
cv::Mat LaneDetection::unDistort(cv::Mat inputImg) {
  return cv::Mat;
}
/**
 *   @brief Function to denoise undistorted input image
 *
 *   @param undistorted image of type cv::Mat
 *   @return denoised image of type cv::Mat
 */
cv::Mat LaneDetection::deNoise(cv::Mat undistortedImg) {
  return cv::Mat;
}
/**
 *   @brief Function to denoise image
 *
 *   @param denoised image of type cv::Mat
 *   @return masked image of type cv::Mat
 */
cv::Mat LaneDetection::ROI(cv::Mat denoisedImg) {
  return cv::Mat;
}
/**
 *   @brief Function to get a binary image based on the color thresholding
 *
 *   @param masked image of type cv::Mat
 *   @param thresholding color space of type string
 *   @return binary image of type cv::Mat
 */
cv::Mat LaneDetection::colorThreshold(cv::Mat maskedImg,
                                      std::string colorSpace) {
  return cv::Mat;
}
/**
 *   @brief Function to generate lane pixel histogram
 *
 *   @param projective transform of binary image of type cv::Mat
 *   @return histogram containing lane pixels of type cv::Mat
 */
cv::Mat LaneDetection::generateHist(cv::Mat birdView) {
  return cv::Mat;
}
/**
 *   @brief Function to extract left or right lane
 *
 *   @param histogram containing lane pixels of type cv::Mat
 *   @param lane to be extracted - left or right of type string
 *   @return pixel locations of left or right lane, type std::vector<cv::Point_<int>>
 */
std::vector<cv::Point_<int>> LaneDetection::extractLane(cv::Mat hist,
                                                        std::string lane) {
  return std::vector<cv::Point_<int>>;
}
/**
 *   @brief Function to fit a polynomial on the received lane pixel data
 *
 *   @param left or right lane pixel locations, type std::vector<cv::Point_<int>>
 *   @return pixel locations fitted to a particular polynomial, type std::vector<cv::Point_<int>>
 */
std::vector<cv::Point_<int>> LaneDetection::fitPoly(
    std::vector<cv::Point_<int>> laneLR) {
  return std::vector<cv::Point_<int>>;
}
/**
 *   @brief Function to extract central line
 *
 *   @param left lane pixel locations, type std::vector<cv::Point_<int>>
 *   @param right lane pixel locations, type std::vector<cv::Point_<int>>
 *   @return central line pixel locations, type std::vector<cv::Point_<int>>
 */
std::vector<cv::Point_<int>> LaneDetection::extractCentralLine(
    std::vector<cv::Point_<int>> leftLane,
    std::vector<cv::Point_<int>> rightLane) {
  return std::vector<cv::Point_<int>>;
}
/**
 *   @brief Function to compute slope of the central line
 *
 *   @param central line pixel location, type std::vector<cv::Point_<int>>
 *   @return string, indicating left or right turn
 */
std::string LaneDetection::computeGradient(
    std::vector<cv::Point_<int>> centralLine) {
  return std::string;
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
 *   @brief Function to set size of the input image
 *
 *   @param input image size of type cv::Size_<int>
 *   @return nothing
 */
void LaneDetection::setImgSize(cv::Size_<int>& imgSize) {
}
/**
 *   @brief Function to set input image
 *
 *   @param input image of type cv::Mat
 *   @return nothing
 */
void LaneDetection::setInputImg(cv::Mat& inputImg) {
}
/**
 *   @brief Function to set undistorted image
 *
 *   @param undistorted image of type cv::Mat
 *   @return nothing
 */
void LaneDetection::setUndistortedImg(cv::Mat& undistortedImg) {
}
/**
 *   @brief Function to set denoised image
 *
 *   @param denoised image of type cv::Mat
 *   @return nothing
 */
void LaneDetection::setDenoisedImg(cv::Mat& denoisedImg) {
}
/**
 *   @brief Function to set masked image
 *
 *   @param masked image of type cv::Mat
 *   @return nothing
 */
void LaneDetection::setMaskedImg(cv::Mat& maskedImg) {
}
/**
 *   @brief Function to set binary image
 *
 *   @param binary image of type cv::Mat
 *   @return nothing
 */
void LaneDetection::setBinaryImg(cv::Mat& binaryImg) {
}
/**
 *   @brief Function to set right lane pixel location
 *
 *   @param set of pixels consisting of right lane, type std::vector<cv::Point_<int>>
 *   @return nothing
 */
void LaneDetection::setRightLane(std::vector<cv::Point_<int>>& rightLane) {
}
/**
 *   @brief Function to set left lane pixel location
 *
 *   @param set of pixels consisting of left lane, type std::vector<cv::Point_<int>>
 *   @return nothing
 */
void LaneDetection::setLeftLane(std::vector<cv::Point_<int>>& leftLane) {
}
/**
 *   @brief Function to set central line pixel location
 *
 *   @param set of pixels consisting of central line, type std::vector<cv::Point_<int>>
 *   @return nothing
 */
void LaneDetection::setCentralLine(std::vector<cv::Point_<int>>& centralLine) {
}
/**
 *   @brief Function to set HSL color space threshold
 *
 *   @param threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 *   @return nothing
 */
void LaneDetection::setThreshHSL(cv::Vec<double, 3>& threshHSL) {
}
/**
 *   @brief Function to set RGB color space threshold
 *
 *   @param threshold values for red,green and blue, type cv::Vec<double, 3>
 *   @return nothing
 */
void LaneDetection::setThreshBGR(cv::Vec<double, 3>& threshBGR) {
}
/**
 *   @brief Function to set lane pixel histogram
 *
 *   @param histogram representing the lane pixels along y-direction
 *   @return nothing
 */
void LaneDetection::setHist(cv::Mat& hist) {
}
/**
 *   @brief Function to get size of the input image
 *
 *   @param nothing
 *   @return input image size of type cv::Size_<int>
 */
cv::Size_<int> LaneDetection::getImgSize(void) {
  return cv::Size_<int>;
}
/**
 *   @brief Function to get input image
 *
 *   @param nothing
 *   @return input image of type cv::Mat
 */
cv::Mat LaneDetection::getInputImg(void) {
  return cv::Mat;
}
/**
 *   @brief Function to get undistorted image
 *
 *   @param nothing
 *   @return undistorted image of type cv::Mat
 */
cv::Mat LaneDetection::getUndistortedImg(void) {
  return cv::Mat;
}
/**
 *   @brief Function to get denoised image
 *
 *   @param nothing
 *   @return denoised image of type cv::Mat
 */
cv::Mat LaneDetection::getDenoisedImg(void) {
  return cv::Mat;
}
/**
 *   @brief Function to get masked image
 *
 *   @param nothing
 *   @return masked image of type cv::Mat
 */
cv::Mat LaneDetection::getMaskedImg(void) {
  return cv::Mat;
}
/**
 *   @brief Function to get binary image
 *
 *   @param nothing
 *   @return binary image of type cv::Mat
 */
cv::Mat LaneDetection::getBinaryImg(void) {
  return cv::Mat;
}
/**
 *   @brief Function to get right lane pixel location
 *
 *   @param nothing
 *   @return set of pixels consisting of right lane, type std::vector<cv::Point_<int>>
 */
std::vector<cv::Point_<int>> LaneDetection::getRightLane(void) {
  return std::vector<cv::Point_<int>>;
}
/**
 *   @brief Function to get left lane pixel location
 *
 *   @param nothing
 *   @return set of pixels consisting of left lane, type std::vector<cv::Point_<int>>
 */
std::vector<cv::Point_<int>> LaneDetection::getLeftLane(void) {
  return std::vector<cv::Point_<int>>;
}
/**
 *   @brief Function to get central line pixel location
 *
 *   @param nothing
 *   @return set of pixels consisting of central line, type std::vector<cv::Point_<int>>
 */
std::vector<cv::Point_<int>> LaneDetection::getCentralLine(void) {
  return std::vector<cv::Point_<int>>;
}
/**
 *   @brief Function to get HSL color space threshold
 *
 *   @param nothing
 *   @return threshold values for hue,saturation and luminousness, type cv::Vec<double, 3>
 */
cv::Vec<double, 3> LaneDetection::getThreshHSL(void) {
  return cv::Vec<double, 3>;
}
/**
 *   @brief Function to get RGB color space threshold
 *
 *   @param nothing
 *   @return threshold values for red,green and blue, type cv::Vec<double, 3>
 */
cv::Vec<double, 3> LaneDetection::getThreshBGR(void) {
  return cv::Vec<double, 3>;
}
/**
 *   @brief Function to get lane pixel histogram
 *
 *   @param nothing
 *   @return histogram representing the lane pixels along y-direction
 */
cv::Mat LaneDetection::getHist(void) {
  return cv::Mat;
}
