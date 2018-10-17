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
#include "LaneInfo.hpp"
/**
 * @brief  Class to test LaneInfo.
 */
class LaneInfoTest : public ::testing::Test {
 protected:
  LaneInfo testObject;
};
/**
 *@brief Test to ensure lane coefficients are set
 */
TEST_F(LaneInfoTest, isLaneCoefficientSet) {
  cv::Mat input;  // variable to store lane coefficients
  // assigning lane coefficients values
  input.at<double>(0, 0) = 1.0;
  input.at<double>(0, 1) = 2.0;
  input.at<double>(0, 2) = 3.0;
  testObject.setLaneCoeffs(input);  // setting coefficients through setLaneCoeffs
  cv::Mat gotLaneCoefficients = testObject.getLaneCoeffs();  // getting lane coefficients
  // applyinig the check conditions
  EXPECT_EQ(1.0, gotLaneCoefficients.at<double>(0, 0));
  EXPECT_EQ(2.0, gotLaneCoefficients.at<double>(0, 1));
  EXPECT_EQ(3.0, gotLaneCoefficients.at<double>(0, 2));
}
/**
 *@brief Test to ensure lane color is set
 */
TEST_F(LaneInfoTest, isLaneColorSet) {
  cv::Vec3b input(50, 60, 70);  // declaring and assigning values to a variable
  testObject.setLaneColor(input);  // setting color value through setLaneColor
  cv::Vec3b gotLaneColors = testObject.getLaneColor();  // getting color value
  // applying the check conditions
  EXPECT_EQ(50, gotLaneColors[0]);
  EXPECT_EQ(60, gotLaneColors[1]);
  EXPECT_EQ(70, gotLaneColors[2]);
}
