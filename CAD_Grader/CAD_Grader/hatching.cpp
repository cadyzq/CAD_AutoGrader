#include "hatching.h"

cv::RNG rng(12345);
namespace hatching {

    /**
        Hatching Lines Detection 
    */

    float get_m(cv::Vec4i line) {
        return ((float)line[3] - line[1]) / (line[2] - line[0]);
    }

    float get_b(cv::Vec4i line) {
        float m = get_m(line);
        return line[1] - m * line[0];
    }

    void combineLines(std::vector<cv::Vec4i>* linesP) {
        bool flag = true;
        // write the line as y=mx+b
        float berror = 5;
        float distance_error = 10;

        while (flag) {
            flag = false;
            for (std::vector<cv::Vec4i>::iterator it1 = linesP->begin(); it1 != linesP->end(); ++it1) {
                cv::Vec4i l = *it1;
                int m = get_m(l);
                int b = get_b(l);
                for (std::vector<cv::Vec4i>::iterator it = it1 + 1; it != linesP->end(); ) {
                    cv::Vec4i checker = *it;
           
                    if (abs(b - get_b(checker)) < berror) { // two lines have the same function
                        if ((l[0] - checker[2] < distance_error && checker[2] - l[2] < distance_error)
                            || (checker[0] - l[2] < distance_error && l[0] - checker[0] < distance_error)) { // two lines close enough 
                            flag = true;

                            // Combining lines
                            if (l[0] < checker[0]) {
                                (*it1)[0] = l[0];
                                (*it1)[1] = l[1];
                            }
                            else {
                                (*it1)[0] = checker[0];
                                (*it1)[1] = checker[1];
                            }

                            if (l[2] > checker[2]) {
                                (*it1)[2] = l[2];
                                (*it1)[3] = l[3];
                            }
                            else {
                                (*it1)[2] = checker[2];
                                (*it1)[3] = checker[3];
                            }
                            it = linesP->erase(it);
                            continue;
                        }
                    }
                    it++;
                }
            }
        }
    }

    /*
        
    */
    void find_hatching_lines(cv::Mat& img, std::queue<cv::Point>* mid_points, bool show_draw) {
        float errorm = 0.1;

        std::vector<cv::Vec4i> linesP; // will hold the results of the hough line detection
        cv::Mat bw = cv::Scalar::all(255) - img;
        cv::HoughLinesP(bw, linesP, 0.3, CV_PI / (180 * 16), 6, 0, 5);

        // Write a 2D line in the form of y=mx+b, dashed lines are 45 degree, meaning m = -1 (+-) errorm
        // Keep only dashed lines
        for (std::vector<cv::Vec4i>::iterator it = linesP.begin(); it != linesP.end();)
        {
            if (abs(get_m(*it) + 1) < errorm) {
                ++it;
                continue;
            }
            it = linesP.erase(it);
        }
        // HoughLinesP gives only line segments (shown in OpenCV doc), combine those short lines
        combineLines(&linesP);

        int min_length = 15;
        // So drawings are in color 
        cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);

        for (size_t i = 0; i < linesP.size(); i++)
        {
            cv::Vec4i l = linesP[i];
            // Keep only longer lines to omit lines near, for example, a cirlce. 
            // This avoids mis-detection in hatching area finding.
            if (l[2] - l[0] > min_length) {  
                // Draw lines and mid-points
                if (show_draw) {
                    cv::Scalar color = cv::Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
                    cv::line(img, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), color, 2, cv::LINE_AA);
                    cv::circle(img, cv::Point((l[0] + l[2] + 1) / 2, (l[1] + l[3] + 1) / 2), 5, color);
                }
                // Save mid-points and pixels around it for better hatching area detection 
                mid_points->push(cv::Point((l[0] + l[2] + 1) / 2, (l[1] + l[3] + 1) / 2));
                mid_points->push(cv::Point((l[0] + l[2] - 1) / 2, (l[1] + l[3] - 1) / 2));
                mid_points->push(cv::Point((l[0] + l[2]) / 2, (l[1] + l[3]) / 2));
            }
        }
    }

    /**
        Hatched Area Detection 
    */
    bool in_range(int x, int y, const cv::Mat& img) {
        return (x >= 0) && (y >= 0) && (x < img.cols) && (y < img.rows);
    }

    bool has_black_line(cv::Mat img, int nx1, int ny1, int nx2, int ny2) {
        if (in_range(nx1, ny1, img) &&
            in_range(nx2, ny2, img) &&
            img.at<uchar>(cv::Point(nx1, ny1)) == kBlackColor &&
            img.at<uchar>(cv::Point(nx2, ny2)) == kBlackColor) {
            return true;
        }

        return false;
    }

    /*
        Find hatched areas based on hatching lines 
    */
    cv::Mat detect_hatched_area(const cv::Mat& img, std::queue<cv::Point>* mid_points) {
        // output img, white hatched area of black background
        cv::Mat black = cv::Mat(img.size(), img.type(), cv::Scalar(0));
        std::set<std::pair<int, int>>* visited = new std::set<std::pair<int, int>>();

        while (mid_points->size() > 0) {
            cv::Point p = mid_points->front();
            mid_points->pop();
            visited->insert(std::make_pair(p.x, p.y));
            // change point to white 
            black.at<uchar>(p) = kWhiteColor;

            // check points around that point to find another hatched area pixel 
            // (if that point is not a boundary (meaning it's not black on img))
            for (int i = 0; i < 4; ++i) {
                int nx = p.x + xse[i];
                int ny = p.y + yse[i];

                if (!in_range(nx, ny, img)) continue;
                if (visited->count(std::make_pair(nx, ny)) > 0) continue;
            
                cv::Point next = cv::Point(nx, ny);
                cv::Scalar intensity = img.at<uchar>(next);
                // image is binary 
                if (!(intensity[0] == 0 || intensity[0] == 255)) {
                    printf("Error Intensity %d at (x: %d, y: %d)", intensity[0], nx, ny);
                    continue;
                }

                visited->insert(std::make_pair(next.x, next.y));
                // even if the pixel is white, it stil might be a bondary if pixels around it are black.
                // push only hatched area pixels into mid_points
                if (intensity[0] == kWhiteColor) {
                    // allow gaps 
                    bool flag = false;
                    for (int i = 1; i <= kContourGap; i++) {
                        for (int j = 1; j <= kContourGap; j++) {
                            if (has_black_line(img, nx - i, ny, nx + j, ny) ||
                                has_black_line(img, nx, ny - i, nx, ny + j) ||
                                //has_black_line(img, nx + i, ny - i, nx - j + 1, ny + j) ||
                                //has_black_line(img, nx + i, ny - i, nx - j, ny + j - 1) ||
                                has_black_line(img, nx + i, ny - i, nx - j, ny + j) ||
                                //has_black_line(img, nx + i - 1, ny - i, nx - j, ny + j) ||
                                //has_black_line(img, nx + i, ny - i - 1, nx - j, ny + j) ||
                                has_black_line(img, nx + i, ny + i, nx - j, ny - j)
                                //has_black_line(img, nx + i, ny + i, nx - j + 1, ny - j) ||
                                //has_black_line(img, nx + i, ny + i, nx - j, ny - j + 1) ||
                                //has_black_line(img, nx + i + 1, ny + i, nx - j, ny - j) ||
                                //has_black_line(img, nx + i, ny + i - 1, nx - j, ny - j)
                            ){
                                flag = true;
                                break;
                            }
                        }
                        if (flag) break;
                    }
                    if (flag) break;
                    mid_points->push(next);
                }
             
            }

        }
        delete visited;
        return black;
    }

    /*
        Remove hatchling lines. If a pixel is balck but pixels around it are white, 
        then it's a hatching line pixel. 
    */
    void remove_hatching_lines(cv::Mat& hatched_area, bool show_pre_process) {
        if (show_pre_process) {
            cv::imshow("With Hatched Lines", cv::Scalar::all(255) - hatched_area);
        }

        for (int row = 0; row < hatched_area.rows; ++row) {
            for (int col = 0; col < hatched_area.cols; ++col) {
                bool found_one_point[] = { false, false, false, false };
                
                for (int i = 0; i < 4; i++) {
                    for (int j = 1; j <= kMaxLineWidth; j++) {
                        int nx = col + xsf[i] * j;
                        int ny = row + ysf[i] * j;

                        if (in_range(nx, ny, hatched_area)) {
                            cv::Point p = cv::Point(nx, ny);
                            if (hatched_area.at<uchar>(p) == kWhiteColor) {
                                found_one_point[i] = true;
                                break;
                            }

                        }
                    }
                }

                if (found_one_point[0] && found_one_point[1] &&
                    found_one_point[2] && found_one_point[3])
                {
                    hatched_area.at<uchar>(cv::Point(col, row)) = kWhiteColor;
                }
            }
        }
     
    }

    void dilate_image(cv::Mat img) {
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,
        cv::Size(2 * kContourDilationSize + 1, 2 * kContourDilationSize + 1),
        cv::Point(kContourDilationSize, kContourDilationSize));
        cv::erode(img, img, element);
    }
}