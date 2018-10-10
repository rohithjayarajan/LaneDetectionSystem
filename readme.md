# Lane Detection System
[![Build Status](https://travis-ci.org/rohithjayarajan/LaneDetectionSystem.svg?branch=master)](https://travis-ci.org/rohithjayarajan/LaneDetectionSystem)
[![Coverage Status](https://coveralls.io/repos/github/rohithjayarajan/LaneDetectionSystem/badge.svg?branch=master)](https://coveralls.io/github/rohithjayarajan/LaneDetectionSystem?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

---

## Overview

Project to design a system for lane departure warning system for self-driving cars which include lane detection and steer prediction. In this project, a monocular camera installed on the self driving vehicle serves as the input for the lane detecton system pipeline. After preprocessing of image frame, the segmented two lanes are used to fit curves describing the traffic lanes. Also this information is used to predict the steering angle of the vehicle. 
A C++ project with:

- cmake
- googletest
- OpenCV

## License
```
MIT License

Copyright (c) 2018 Rohith Jayarajan, Akash Guha

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
```

## Dependencies

- [OpenCV][reference-id-for-OpenCV]: An Open Source Computer Vision Library released under a BSD license.
A complete installation guide for OpenCV can be found [here][reference-id-for-here].

[reference-id-for-OpenCV]: https://opencv.org/
[reference-id-for-here]: https://docs.opencv.org/3.3.1/d7/d9f/tutorial_linux_install.html

## Solo Iterative Process

SIP is a software process that single programmers use while working on a software project. The solo programmer who is the hero of this process is named “Sol”. Sol receives the requirements from the users and records them in the product backlog. From the iteration backlog, Sol selects a specific change request and implements the corresponding software changes. Product Backlog, Work Log and Iteration Backlog for this project can be found [here][reference-id-for-here1].

[reference-id-for-here1]: https://docs.google.com/spreadsheets/d/1b254fKUI1N3dCOtlsByfg0JyH0NWnpPUUpDtdTfVFeI/edit?usp=sharing

## Standard install via command-line
```
git clone --recursive https://github.com/rohithjayarajan/LaneDetectionSystem
cd <path to repository>
mkdir build
cd build
cmake ..
make
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```

## Building for code coverage
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```
This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.

## Working with Eclipse IDE ##

## Installation

In your Eclipse workspace directory (or create a new one), checkout the repo (and submodules)
```
mkdir -p ~/workspace
cd ~/workspace
git clone --recursive https://github.com/rohithjayarajan/LaneDetectionSystem
```

In your work directory, use cmake to create an Eclipse project for an [out-of-source build] of LaneDetectionSystem

```
cd ~/workspace
mkdir -p LaneDetectionSystem-eclipse
cd LaneDetectionSystem-eclipse
cmake -G "Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D CMAKE_ECLIPSE_VERSION=4.7.0 -D CMAKE_CXX_COMPILER_ARG1=-std=c++14 ../LaneDetectionSystem/
```

## Import

Open Eclipse, go to File -> Import -> General -> Existing Projects into Workspace -> 
Select "LaneDetectionSystem-eclipse" directory created previously as root directory -> Finish

# Edit

Source files may be edited under the "[Source Directory]" label in the Project Explorer.


## Build

To build the project, in Eclipse, unfold LaneDetectionSystem-eclipse project in Project Explorer,unfold Build Targets, double click on "all" to build all projects.

## Run

1. In Eclipse, right click on the LaneDetectionSystem-eclipse in Project Explorer,
select Run As -> Local C/C++ Application

2. Choose the binaries to run (e.g. shell-app, cpp-test for unit testing)


## Debug


1. Set breakpoint in source file (i.e. double click in the left margin on the line you want 
the program to break).

2. In Eclipse, right click on the LaneDetectionSystem-eclipse in Project Explorer, select Debug As -> 
Local C/C++ Application, choose the binaries to run (e.g. shell-app).

3. If prompt to "Confirm Perspective Switch", select yes.

4. Program will break at the breakpoint you set.

5. Press Step Into (F5), Step Over (F6), Step Return (F7) to step/debug your program.

6. Right click on the variable in editor to add watch expression to watch the variable in 
debugger window.

7. Press Terminate icon to terminate debugging and press C/C++ icon to switch back to C/C++ 
perspetive view (or Windows->Perspective->Open Perspective->C/C++).


## Plugins

- CppChEclipse

    To install and run cppcheck in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> cppcheclipse.
    Set cppcheck binary path to "/usr/bin/cppcheck".

    2. To run CPPCheck on a project, right click on the project name in the Project Explorer 
    and choose cppcheck -> Run cppcheck.


- Google C++ Sytle

    To include and use Google C++ Style formatter in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> Code Style -> Formatter. 
    Import [eclipse-cpp-google-style][reference-id-for-eclipse-cpp-google-style] and apply.

    2. To use Google C++ style formatter, right click on the source code or folder in 
    Project Explorer and choose Source -> Format

[reference-id-for-eclipse-cpp-google-style]: https://raw.githubusercontent.com/google/styleguide/gh-pages/eclipse-cpp-google-style.xml

- Git

    It is possible to manage version control through Eclipse and the git plugin, but it typically requires creating another project. If you're interested in this, try it out yourself and contact me on Canvas.
