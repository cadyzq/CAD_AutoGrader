#include "feature_extraction.h"

namespace features {
	void hough_circle(cv::Mat& img, cv::Mat& canvas, std::string name)
	{

		cv::Mat gray;
		cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);
		cv::GaussianBlur(gray, gray, cv::Size(3, 3), -1, -1);

		std::vector<cv::Vec3f> circles;
		cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1,
			gray.rows / 16,  // change this value to detect circles with different distances to each other
			950, 55, 0, 0 // change the last two parameters
			// (min_radius & max_radius) to detect larger circles
		);

		// 500, 78 works for file0
		// 950, 55 works for file1

		printf("%s: %d circles found\n", name.c_str(), circles.size());
		for (size_t i = 0; i < circles.size(); i++)
		{
			cv::Vec3i c = circles[i];
			cv::Point center = cv::Point(c[0], c[1]);
			// circle center
			cv::circle(canvas, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
			// circle outline
			int radius = c[2];
			cv::circle(canvas, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
			printf("Circle %d: centered at (%d, %d), radius=%d\n", i, c[0], c[1], radius);
		}
	}


	void findContour(const cv::Mat & img, cv::Mat & canvas, std::vector<std::vector<cv::Point>>& contours) {
		cv::Mat inv = cv::Scalar::all(255) - img;
		cv::findContours(inv, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		cv::drawContours(canvas, contours, 0, cv::Scalar(0, 255, 0), 3);
	}

	void detectColor(const cv::Mat& img, cv::Mat& out) {
		cv::cvtColor(img, out, cv::COLOR_BGR2HSV);
		cv::inRange(out, RED_LOWER, RED_HIGHER, out);
	}
}