/**
 *  Copyright [2018] Akash Guha
 *  @file    ImageProcessingTest.cpp
 *  @author  Akash Guha
 *
 *  @brief Image Processing Class Test
 *
 *  @section DESCRIPTION
 *
 *  This module tests the functionality of
 *  the image processing class.
 *
 */

#include <gtest/gtest.h>
#include "ImageProcessing.hpp"

/**
 * @brief  Class to test ImageProcessing.
 */
class ImageProcessingTest : public ::testing::Test {
 protected:
  ImageProcessing testObject;
//  cv::Mat srcImg;
//  cv::Mat preProcessedImg;
//  cv::Mat binaryImg;
//  cv::Mat birdViewImg;
};
/**
 *@brief Test to ensure intrinsic parameters are set
 */
TEST_F(ImageProcessingTest, isIntrinsicSet) {
  testObject.setIntrinsic(1.0, 2.0, 3.0, 4.0);
  cv::Mat gotIntrinsic = testObject.getIntrinsic();
  EXPECT_EQ(6.0, gotIntrinsic.at<double>(0, 0));
  EXPECT_EQ(2.0, gotIntrinsic.at<double>(0, 1));
  EXPECT_EQ(3.0, gotIntrinsic.at<double>(1, 1));
  EXPECT_EQ(4.0, gotIntrinsic.at<double>(1, 2));
}
/**
 *@brief Test to ensure distortion coefficients are set
 */
TEST_F(ImageProcessingTest, isDistortionCoefficientsSet) {
  testObject.setDistCoeffs(1.0, 2.0, 3.0, 4.0, 5.0);
  cv::Mat gotDistCoeffs = testObject.getDistCoeffs();
  EXPECT_EQ(1.0, gotDistCoeffs.at<double>(0, 0));
  EXPECT_EQ(2.0, gotDistCoeffs.at<double>(0, 1));
  EXPECT_EQ(3.0, gotDistCoeffs.at<double>(0, 2));
  EXPECT_EQ(4.0, gotDistCoeffs.at<double>(0, 3));
  EXPECT_EQ(5.0, gotDistCoeffs.at<double>(0, 4));
}
/**
 *@brief Test to ensure standard deviation in X for gaussian blur is set
 */
TEST_F(ImageProcessingTest, isGaussianSigmaXSet) {
  testObject.setgaussianSigmaX(1.0);
  EXPECT_EQ(1.0, testObject.getgaussianSigmaX());
}
/**
 *@brief Test to ensure standard deviation in Y for gaussian blur is set
 */
TEST_F(ImageProcessingTest, isGaussianSigmaYSet) {
  testObject.setgaussianSigmaY(5.0);
  EXPECT_EQ(5.0, testObject.getgaussianSigmaY());
}
/**
 *@brief Test to ensure minimum threshold values of hue,saturation and luminousness
 *       are set
 */
TEST_F(ImageProcessingTest, isHSLMinThresholdSet) {
  cv::Scalar tempHSLMin(1.0, 2.0, 3.0);
  testObject.setMinThreshHLS(tempHSLMin);
  EXPECT_EQ(tempHSLMin, testObject.getMinThreshHLS());
}
/**
 *@brief Test to ensure maximum threshold values of hue,saturation and luminousness
 *       are set
 */
TEST_F(ImageProcessingTest, isHSLMaxThresholdSet) {
  cv::Scalar tempHSLMax(1.0, 2.0, 3.0);
  testObject.setMaxThreshHLS(tempHSLMax);
  EXPECT_EQ(tempHSLMax, testObject.getMaxThreshHLS());
}
/**
 *@brief Test to ensure minimum threshold values of red, green and blue are set
 */
TEST_F(ImageProcessingTest, isBGRMinThresholdSet) {
  cv::Scalar tempBGRMin(1.0, 2.0, 3.0);
  testObject.setMinThreshBGR(tempBGRMin);
  EXPECT_EQ(tempBGRMin, testObject.getMinThreshBGR());
}
/**
 *@brief Test to ensure maximum threshold values of red, green and blue are set
 */
TEST_F(ImageProcessingTest, isBGRMaxThresholdSet) {
  cv::Scalar tempBGRMax(1.0, 2.0, 3.0);
  testObject.setMaxThreshBGR(tempBGRMax);
  EXPECT_EQ(tempBGRMax, testObject.getMaxThreshBGR());
}
