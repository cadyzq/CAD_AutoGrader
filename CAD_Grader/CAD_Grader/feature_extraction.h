#ifndef FEATURE_EXTRACTION_H
#define FEATURE_EXTRACTION_H

#include <vector>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "color.h"

namespace features {
	void hough_circle(cv::Mat& img, cv::Mat& canvas, std::string name);
	void findContour(const cv::Mat & img, cv::Mat & canvas, std::vector<std::vector<cv::Point>>& contours);
	void detectColor(const cv::Mat& img, cv::Mat& out);
}

#endif // !FEATURE_EXTRACTION_H
