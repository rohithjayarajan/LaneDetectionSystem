/**
 *  Copyright [2018] Akash Guha
 *  @file    main.cpp
 *  @author  Akash Guha, rohithjayarajan
 *
 *  @brief Lane Detection Main file
 *
 *  @section DESCRIPTION
 *
 *  This program is used to implement lane detection system and
 *  curvature prediction on a video sequence or image snesor data.
 *
 */
#include <iostream>
#include "LaneDetection.cpp"

int main() {
  LaneDetection lanes;
  lanes.detectLanes();
  return 0;
}
