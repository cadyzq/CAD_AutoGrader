# CAD AutoGrader
This is an autograder for CAD drawings based on image processing.

## Quick Start Guide
1. Clone this repo. This project is a Visual Studio Solution:
- If you use Visual Studio, click `CAD_Grader->CAD_Grader.sln` opens the solution
- Otherwise, all codes files are in `CAD_Grader->CAD_Grader`. Testing pictures are in `resources/pictures` Import them to the editor you are comfortable with. 

2. Install the latest version of OpenCV C++. Link it to your project if need to. 

3. Change image directories in `main.cpp`.


## Project Structure 
- Main: `main.cpp`  
- Header files for constants:
    - color.h: lower and upper bound of colors in HSV for color detection
    - fields.h: all other constants
- There are four modules, each with a cpp file and its corresponding header file:
    - COMPARE: crop, resize, get percentage difference of two images
    - HATCHING: detect hatcing lines and hatched areas of an image
    - ZHANGSUEN: zhang-suen thinning algorithm from [yati-sagade](https://github.com/yati-sagade/zhang-suen-thinning)
    - FEATURE_EXTRACTION: perform feature extractions if two images are not the same

## Miscellanous
Since some functions I wrote have the same name as OpenCV built-in functions, it is not recommended to do `using namespace` in main.


## Known Bugs / Unfinished Work
See Issues




