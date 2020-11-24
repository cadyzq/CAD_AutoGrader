#ifndef COMPARE_H
#define COMPARE_H

#include <vector>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "zhangsuen.h"
#include "fields.h"

namespace compare {
	void crop(cv::Mat& img, cv::Mat& thin);
	bool resize(cv::Mat& img1, cv::Mat& img2);
	double get_percentage_diff(const cv::Mat& img1, const cv::Mat& img2, bool make_graph, std::string name, bool is_contour);
}

#endif // !COMPARE_H
