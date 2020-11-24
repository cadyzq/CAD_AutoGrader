//#include <iostream>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/core.hpp>
////#include <opencv2/ximgproc.hpp>
//
//using namespace cv;
//using namespace std;
//
//Mat src, src2, dst, grey, inv, bin, cropped, cropped2;
//int angle_line = 20;
//
//void find_hatched(){
//    vector<Vec4i> linesP; // will hold the results of the detection
//    HoughLinesP(grey, linesP, 1, CV_PI / 180, 10, 2, 5); // runs the actual detection
//    // Draw the lines
//    for (size_t i = 0; i < linesP.size(); i++)
//    {
//        Vec4i l = linesP[i];
//        if (abs(l[0] - l[2]) == abs(l[1] - l[3])) {
//            line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
//            hatched_contour[0].push_back(Point(l[0], l[1]));
//            hatched_contour[0].push_back(Point(l[2], l[3]));
//            //circle(dst, Point(l[0], l[1]), 1, Scalar(255, 0, 0), 3);
//            //circle(dst, Point(l[2], l[3]), 1, Scalar(255, 0, 0), 3);
//        }
//    }
//}
//
//void rs() {
//    resize(cropped, dst, cropped2.size());
//    //dst += cropped2;
//}
//
//void compare() {
//    if (cropped.size() != cropped2.size()) {
//        cout << "Incorrect size" << endl;
//        cout << "Size 1: " << cropped.size() << endl;
//        cout << "Size 2: " << cropped2.size() << endl;
//        return;
//    }
//    Mat dst = cropped - cropped2;
//}
//
//Mat crop(Mat* img)
//{
//    cvtColor(*img, grey, COLOR_RGB2GRAY);
//    inv = Scalar::all(255) - grey;
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
//    
//    return Mat(grey, boundRect[0]);
//}
//
//int main(int argc, char** argv)
//{
//	const char* input_file_1 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\5_SlideBlock.png";
//	const char* input_file_2 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\5_SlideBlock_cat.png";
//
//	const char* filename = input_file_1;
//    const char* filename2 = input_file_2;
//	const char* result_window_name = "Result";
//
//    src = imread(samples::findFile(filename), IMREAD_COLOR);
//    src2 = imread(samples::findFile(filename2), IMREAD_COLOR);
//    Canny(src, grey, 20, 200, 3);
//    //cvtColor(src, grey, COLOR_RGB2GRAY);
//    inv = Scalar::all(255) - grey;
//    //inv = threshold(src, dst, 100, 255, THRESH_BINARY_INV);
//    threshold(grey, bin, 100, 255, THRESH_BINARY);
//    src.copyTo(dst);
//
//    //Mat skel(src.size(), CV_8UC1, Scalar(0));
//    //Mat temp, eroded;
//    //Mat element = getStructuringElement(MORPH_CROSS, cv::Size(3, 3));
//
//    //bool done;
//    //do
//    //{
//    //    cv::erode(bin, eroded, element);
//    //    cv::dilate(eroded, temp, element); // temp = open(img)
//    //    cv::subtract(bin, temp, temp);
//    //    cv::bitwise_or(skel, temp, skel);
//    //    eroded.copyTo(bin);
//
//    //    done = (cv::countNonZero(bin) == 0);
//    //} while (!done);
//
//    
//    // Hough Line
//    //cvtColor(grey, dst, COLOR_GRAY2BGR);
//    //dst.setTo(Scalar(0, 0, 0));
//    //find_hatched();
//    //drawContours(dst, hatched_contour, 0, Scalar(255, 0, 0));
//
//    cropped = crop(&src);
//    cropped2 = crop(&src2);
//    compare();
//    rs();
//
//    //cvtColor(dst, dst, COLOR_BGR2GRAY);
//    //vector<vector<Point> > contours;
//    //vector<Vec4i> hierarchy;
//    //findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//
//    //Mat drawing = Mat::zeros(grey.size(), CV_8UC3);
//    //for (size_t i = 0; i < contours.size(); i++)
//    //{
//    //    drawContours(drawing, contours, (int)i, Scalar(255, 0, 0), 1, LINE_8, hierarchy, 0);
//    //}
//    //imshow("Contours", drawing);
//
//
//	// image display
//	imshow(result_window_name, dst);
//	imshow("src", cropped);
//    imshow("src2", cropped2);
//	waitKey(0);
//	return 0;
//}