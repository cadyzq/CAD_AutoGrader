//#include <iostream>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/core.hpp>
//
//using namespace cv;
//using namespace std;
//
//int tshold = 200;
//const int max_threshold = 500;
//const int kernel_size = 3;
//RNG rng(12345);
//Mat src, dst, grey, inv;
//Mat templ , mask;
//

//
//void canny_op()
//{
//	Canny(grey, dst, tshold, tshold * 3, kernel_size);
//}
//
//void bounding_box()
//{
//	//Mat canny_output;
//	//Canny(gray, canny_output, tshold, tshold * 3, kernel_size);
//	vector<vector<Point>> contours;
//	findContours(inv, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//	vector<vector<Point> > contours_poly(contours.size());
//	vector<Rect> boundRect(contours.size());
//	cout << contours.size() << " countours found!" << endl;
//	for (size_t i = 0; i < contours.size(); i++)
//	{
//		approxPolyDP(contours[i], contours_poly[i], 3, true);
//		boundRect[i] = boundingRect(contours_poly[i]);
//	}
//	for (size_t i = 0; i < contours.size(); i++)
//	{
//		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
//		drawContours(dst, contours_poly, (int)i, color);
//		rectangle(dst, boundRect[i].tl(), boundRect[i].br(), color, 2);
//	}
//}
//
//void matching(int match_method) {
//
//	int result_cols = src.cols - templ.cols + 1;
//	int result_rows = src.rows - templ.rows + 1;
//
//	dst.create(result_rows, result_cols, CV_32FC1);
//	bool method_accepts_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);
//	if (method_accepts_mask) {
//		matchTemplate(grey, templ, dst, match_method, mask);
//	} else {
//		matchTemplate(grey, templ, dst, match_method);
//	}
//	normalize(dst, dst, 0, 1, NORM_MINMAX, -1, Mat());
//
//	double minVal; double maxVal; Point minLoc; Point maxLoc;
//	Point matchLoc;
//	minMaxLoc(dst, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
//		matchLoc = minLoc;
//		cout << "Min value is " << minVal << endl;
//	} else {
//		matchLoc = maxLoc;
//		cout << "Max value is " << maxVal << endl;
//	}
//	cout << "Matched at (" << matchLoc.x << ", " << matchLoc.y << ") " << endl;
//	rectangle(dst, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
//}
//
//
//double percentage_diff(const Mat& a, const Mat& b)
//{
//	if ((a.rows != b.rows) || (a.cols != b.cols))
//		cout << "Dimension not agreed." << endl;
//		return 1;
//
//	Scalar s = sum(a - b);
//	return s[0] + s[1]  + s[2];
//}
//
//int main(int argc, char** argv)
//{
//	// image read
//	const char* input_file_1 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\2_Flange.png";
//	const char* input_file_2 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\5_SlideBlock.png";
//	const char* filename = argc >= 2 ? argv[1] : input_file_1;
//	const char* window_name = "Result";
//
//	src = imread(samples::findFile(filename), IMREAD_COLOR);  
//	templ = imread(samples::findFile(input_file_2), IMREAD_GRAYSCALE);
//	if (src.empty()) {
//		printf(" Error opening image\n");
//		printf(" Program Arguments: [image_name -- default %s] \n", filename);
//		return -1;
//	}
//	cvtColor(src, grey, COLOR_BGR2GRAY);
//	src.copyTo(dst);
//	inv = Scalar::all(255) - grey;
//
//	// Hough Circle 
//	//hough_circle();
//
//	// Canny
//	//canny_op();
//
//	// Bounding Box
//	//bounding_box();
//	
//	// Matching
//	//templ = grey;
//	matching(TM_CCOEFF);
//
//
//	// image display
//	imshow(window_name, dst);
//	imshow("Original Image", src);
//	waitKey(0);
//	return 0;
//
//}