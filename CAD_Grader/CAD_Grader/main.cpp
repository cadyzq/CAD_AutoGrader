#include <string>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#include "hatching.h"
#include "zhangsuen.h"
#include "compare.h"
#include "feature_extraction.h"
#include "fields.h"


void find_hatching(const cv::Mat& src, const cv::Mat& thin, cv::Mat& hatched, cv::Mat& contour, bool do_graph, std::string name) {
    cv::Mat hatching_lines_mat;
    thin.copyTo(hatching_lines_mat);
    std::queue<cv::Point>* mid_points = new std::queue<cv::Point>();
    // find all hatching lines, store mid-points of those lines in mid_points
    hatching::find_hatching_lines(hatching_lines_mat, mid_points, do_graph);

    // hatched_area is white on a black background
    cv::Mat hatched_area = hatching::detect_hatched_area(thin, mid_points);
    hatching::remove_hatching_lines(hatched_area, false);
    delete mid_points;

    // flip back. Now black hatching area on white background. 
    hatched = cv::Scalar::all(255) - hatched_area;
    // get contour (get rid of hatched area)
    cv::bitwise_or(thin, hatched_area, contour);

    if (do_graph) {
         //image display, only if needed 
        cv::imshow(name + ", Original", src);
        //cv::imshow(name + ", Hatching Lines", hatching_lines_mat);
        //cv::imshow(name + ", Thin", thin);
        cv::imshow(name + ", Hatched Area", hatched);
        //cv::imshow(name + ", Contour", contour);
    }
}

void pre_process(cv::Mat& img, cv::Mat& thin, std::vector<std::vector<cv::Point>>& contours) {
    printf("Processing Image...\n");
    // Turn img into a binary image
    cvtColor(img, thin, cv::COLOR_BGR2GRAY);
    threshold(thin, thin, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    
    // Thin and crop to the smallest bounding box
    zs::thin(thin, false, false, false);
    compare::crop(img, thin);
}

std::string find_name(const char* file_dir) {
    std::string s(file_dir);
    std::size_t idx = s.find_last_of("/\\");
    return s.substr(idx + 1);
}

int main(int argc, char** argv)
{
    // Variables Definition
    cv::Mat src1, thin1, hatched1, contour1, dilated_contour1, outer1;
    cv::Mat src2, thin2, hatched2, contour2, dilated_contour2, outer2;
    std::vector<std::vector<cv::Point>> c1, c2;

    const char* input_file_0 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\2_Flange.png";
    const char* input_file_1 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\2_Flange_cat.png";
    const char* input_file_2 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\2_Flange_2_cat.png";
    const char* input_file_3 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\4_Flange_2_cat.png";
    const char* input_file_4 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\5_SlideBlock.png";
    const char* input_file_5 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\5_SlideBlock_cat.png";
    const char* input_file_6 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\5_TeeSlide.png";
    const char* input_file_7 = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\5_TeeSlide_cat.png";
    const char* color = "C:\\Users\\Candy\\Documents\\CADGrader\\resources\\pictures\\color.png";

    const char* filename1 = input_file_0;
    const char* filename2 = input_file_1;

    // Image Input
    src1 = cv::imread(cv::samples::findFile(filename1), cv::IMREAD_COLOR);
    src2 = cv::imread(cv::samples::findFile(filename2), cv::IMREAD_COLOR);

    // Thin and Cut 
    pre_process(src1, thin1, c1);
    pre_process(src2, thin2, c2);

    // Cut thin1 to the size of thin2
    bool dimension_is_same = false;
    dimension_is_same = compare::resize(thin1, thin2);

    if (dimension_is_same) {
        bool continue_run = true;

        printf("Two images have the same dimension!\n");
        printf("Comparing hatching area...\n");
        find_hatching(src1, thin1, hatched1, contour1, true, find_name(filename1));
        find_hatching(src2, thin2, hatched2, contour2, true, find_name(filename2));
        double hatched_diff = compare::get_percentage_diff(hatched1, hatched2, true, "Hatched Area", false);
        printf("Hatched Area Percentage Difference: %f", hatched_diff);
        if (hatched_diff > kHatchedThreshold) {
            printf("\nHatched areas don't match. Begin feature extraction.\n");
            continue_run = false;
        }
        else {
            printf(", SAME\n");
        }

        // check outer contour 
        if (continue_run) {
            // dilate contour so that we can set the threshold for same/different contour 
            contour1.copyTo(dilated_contour1);
            contour2.copyTo(dilated_contour2);
            hatching::dilate_image(dilated_contour1);
            hatching::dilate_image(dilated_contour2);
            double contour_diff = compare::get_percentage_diff(dilated_contour1, dilated_contour2, true, "Contour", true);
            printf("Contour Percentage Difference: %f", contour_diff);
            if (contour_diff < kContourThreshold) {
                printf(", SAME\nThe answer is correct!\n");
                cv::waitKey(0);
                return 0;
            }
            else {
                printf("\nContours don't match. Begin feature extraction.\n");
            }
        }
    }


    // Check outer contour 
    if (!dimension_is_same) {
        printf("Outer contour check skipped since dimension doesn't agree.\n");
    } else {
        outer1 = cv::Mat(src1.size(), CV_8UC1, cv::Scalar(kWhiteColor));
        outer2 = cv::Mat(src2.size(), CV_8UC1, cv::Scalar(kWhiteColor));

        features::findContour(thin1, outer1, c1);
        features::findContour(thin2, outer2, c2);
        imshow("Outer1", outer1);
        imshow("Outer2", outer2);

        double contour_diff = compare::get_percentage_diff(outer1, outer2, true, "Outer Contour", true);
        printf("Outer Contour Percentage Difference: %f\n", contour_diff);
    }


    // Display circles in the picture 
    features::hough_circle(src1, src1, find_name(filename1));
    features::hough_circle(src2, src2, find_name(filename2));
    imshow("Circles, " + find_name(filename1), src1);
    imshow("Circles, " + find_name(filename2), src2);

    cv::waitKey(0);
    return 0;
}