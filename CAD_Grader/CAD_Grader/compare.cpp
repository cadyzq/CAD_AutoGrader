#include "compare.h"

namespace compare {

	/*
		Find the smallest bounding rectangle of thin, cut both img and thin to that size 
		@param img  The original image
		@param thih The thinned image
	*/
	void crop(cv::Mat& img, cv::Mat& thin)
	{
		cv::Mat inv = cv::Scalar::all(255) - thin;
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(inv, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		std::vector<std::vector<cv::Point>> contours_poly(contours.size());
		std::vector<cv::Rect> boundRect(contours.size());

		if (contours.size() != 1) {
			printf("Warning: %d countours found!\n", contours.size());
		}
		for (size_t i = 0; i < contours.size(); i++)
		{
			cv::approxPolyDP(contours[i], contours_poly[i], 3, true);
			boundRect[i] = cv::boundingRect(contours_poly[i]);
		}

		thin = cv::Mat(thin, boundRect[boundRect.size() - 1]);
		img = cv::Mat(img, boundRect[boundRect.size() - 1]);
	}

	/*
		resize img1 to the size of img2
		@return false if img1 cannot be resized to img2's size, true otherwise
	*/
	bool resize(cv::Mat& img1, cv::Mat& img2) {

		double prop1 = (double) img1.rows / img1.cols;
		double prop2 = (double) img2.rows / img2.cols;

		printf("Height/Width of image 1: %f\n", prop1);
		printf("Height/Width of image 2: %f\n", prop2);
		printf("Dimension difference: %f\n", abs(prop1 - prop2));
		
		if (abs(prop1 - prop2) > kDimThreshold) {
			
			printf("Image dimensions don't agree.\n");
			return false;
		}

		cv::resize(img1, img1, img2.size());
		threshold(img1, img1, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
		zs::thin(img1, false, false, false);
		return true;
	}
	
	/*
		Check the number of black pixels in two images 
	*/
	double get_percentage_diff(const cv::Mat& img1, const cv::Mat& img2, bool make_graph, std::string name, bool is_contour) {
		if (img1.size() != img2.size()) {
			printf("Warning: Image dimension don't agree when comparing hatched area. Quit...\n");
			return -1;
		}

		int diff_count = 0;
		int contour_count = 0;
		cv::Mat diff;


		if (make_graph) 
			diff = cv::Mat(img1.size(), CV_8UC1, cv::Scalar(kWhiteColor));

		for (int x = 0; x < img1.cols; x++) {
			for (int y = 0; y < img1.rows; y++) {
				if (is_contour && img1.at<uchar>(cv::Point(x, y)) == kBlackColor) contour_count++;
				if (img1.at<uchar>(cv::Point(x, y)) != img2.at<uchar>(cv::Point(x, y))) {
					diff_count++;
					if (make_graph) {	
						diff.at<uchar>(cv::Point(x, y)) = kBlackColor;
					}
				}
			}
		}

		if (make_graph) {
			imshow(name + " Diff", diff);
		}

		if (is_contour) {
			return ((double) diff_count) / ((double) contour_count);
		}
		return ((double) diff_count) / ((double) img1.rows * img1.cols);
	}



}	