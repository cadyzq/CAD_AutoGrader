#ifndef HATCHING_H
#define HATCHING_H

#include <queue>
#include <vector>
#include <set>
#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include"fields.h"

namespace hatching {
	void find_hatching_lines(cv::Mat& img, std::queue<cv::Point>* mid_points, bool show_draw);
	cv::Mat detect_hatched_area(const cv::Mat& img, std::queue<cv::Point>* mid_points);
	void remove_hatching_lines(cv::Mat& hatched_area, bool show_pre_process);
	void dilate_image(cv::Mat img);
}

#endif // !HATCHING_H
