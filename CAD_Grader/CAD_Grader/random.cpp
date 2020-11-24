#include <string>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

bool in_range(Mat& img, int r, int c) {
    return (r >= 0) && (r < img.cols) && (c >= 0) && (c < img.rows);
}

void draw_shape(Mat& img, int row, int col, int width, int height) {
    for (int x = col; x < col + width; x++) {
        for (int y = row; y < row + height; y++) {
            if (!in_range(img, x, y)) continue;
            Point b = Point(x, y);
            img.at<Vec3b>(b) = Vec3b(0, 0, 0);
        }
    }
}

Mat sobel(Mat& src) {
    Mat gray, grad;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imshow("gray", gray);


    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    int ddepth = CV_16S;
    int ksize = 1;
    int scale = 1;
    int delta = 0;

    Sobel(gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
    Sobel(gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);

    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    return grad;
    
}

int main(int argc, char** argv)
{
    cv::Mat src; 

    const char* input_file_0 = "C:\\Users\\Candy\\Documents\\Code588\\images\\none.jpg";

    const char* filename1 = input_file_0;

    src = cv::imread(cv::samples::findFile(filename1), cv::IMREAD_COLOR);
/*    Point top_left = Point(95, 61);
    Point bottom_right = Point(405, 370);
    Rect roi = Rect(top_left, bottom_right);

    for (int r = 0; r < 300; r = r + 10) {
        for (int c = 80; c < 400; c = c + 10) {
            Mat n;
            src.copyTo(n);
            draw_shape(n, r, c, 300, 300);
           
            string name = "C:\\Users\\Candy\\Documents\\Code588\\blocked_images_300s\\" + to_string(r) + " " + to_string(c) + ".jpg";
            imwrite(name, n(roi));
        }
    }  */  
    
        //for (int c = 80; c < 400; c = c + 20) {
        //    Mat n;
        //    src.copyTo(n);
        //    draw_shape(n, 0, c, 80, n.rows);
        //    string name = "C:\\Users\\Candy\\Documents\\Code588\\blocked_images\\" + to_string(0) + " " + to_string(c) + ".jpg";
        //    imwrite(name, n);
        //}

    //Mat dst;
    //src.copyTo(dst);
    //for (int x = 1; x < src.cols; x += 2) {
    //    for (int y = 0; y < src.rows; y++) {
    //        Point b = Point(x, y);
    //        Vec3b v = dst.at<Vec3b>(b);

    //        Point a = Point(x - 1, y);
    //        dst.at<Vec3b>(b) = dst.at<Vec3b>(a);
    //        dst.at<Vec3b>(a) = v;
    //    }
    //}

    //imshow("c", dst);
    //string name = "C:\\Users\\Candy\\Documents\\Code588\\noisy_images\\neighbor_shuffle.jpg";
    //imwrite(name, dst);

    //bool flag = true;
    //Mat grad;

    //int th_MIN = 150;
    //int th_MAX = 255;
    //int blurk = 2;
    //int blur_kernel_size = 11;
    //int iter = 50;
    //int n = 0;

    //while (flag && n < iter) {
    //    n++;
    //    printf("%d\n", n);
    //    flag = false;

    //    Mat src_gray;
    //    cvtColor(src, src_gray, COLOR_RGB2GRAY);
    //    //GaussianBlur(src, src, Size(21, 21), 0, 0, BORDER_DEFAULT);

    //    Mat grad_x, grad_y;
    //    Mat abs_grad_x, abs_grad_y;
    //    int ddepth = CV_16S;
    //    int ksize = 3;
    //    Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, BORDER_DEFAULT);
    //    Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, BORDER_DEFAULT);
    //    convertScaleAbs(grad_x, abs_grad_x);
    //    convertScaleAbs(grad_y, abs_grad_y);
    //    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    //    for (int x = 0; x < grad.cols; x += blurk) {
    //        for (int y = 0; y < grad.rows; y += blurk) {
    //            int inten = grad.at<uchar>(Point(x, y));
    //            if (inten > th_MIN && inten < th_MAX) {
    //                //printf("%d, %d\n", x, y);
    //                flag = true;
    //                Point top_left = Point(x - blurk + 1, y - blurk + 1);
    //                Point bottom_right = Point(x + blurk, y + blurk);
    //                if (top_left.x > 0 && top_left.y > 0 && bottom_right.x < grad.cols && bottom_right.y < grad.rows) {
    //                    Rect roi = Rect(top_left, bottom_right);
    //                    //medianBlur(src(roi), src(roi), blur_kernel_size);
    //                    blur(src(roi), src(roi), Size(blur_kernel_size, blur_kernel_size));
    //                }

    //            }
    //        }
    //    }
    //}


    /*GaussianBlur(src, dst, Size(41, 41), 0, 0);
    dst = sobel(dst);*/


    //bool flag = true;
    //Mat grad;

    //int th_MIN = 200;
    //int th_MAX = 255;
    //int blurk = 1;
    //int blur_kernel_size = 11;
    //int iter = 5;
    //int n = 0;
    //GaussianBlur(src, src, Size(3, 3), 0);

    //while (flag && n < iter) {
    //    n++;
    //    printf("%d\n", n);
    //    flag = false;

    //    Mat src_gray;
    //    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    //    Mat grad_x, grad_y;
    //    Mat abs_grad_x, abs_grad_y;
    //    int ddepth = CV_16S;
    //    int ksize = 3;
    //    Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, BORDER_DEFAULT);
    //    Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, BORDER_DEFAULT);
    //    convertScaleAbs(grad_x, abs_grad_x);
    //    convertScaleAbs(grad_y, abs_grad_y);
    //    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    //    grad = abs_grad_x;

    //    for (int x = 0; x < grad.cols; x += blurk) {
    //        for (int y = 1; y < grad.rows; y += blurk) {
    //            int inten = grad.at<uchar>(Point(x, y));
    //            if (inten > th_MIN && inten <= th_MAX) {
   
    //                flag = true;
    //                if (grad.at<uchar>(Point(x , y -1)) > th_MIN) continue;
    //                float reg = (float) grad.at<uchar>(Point(x, y - 1)) / grad.at<uchar>(Point(x, y));
    //                //cout <<"reg" <<  reg << endl; 
    //                Vec3b intensity = src.at<Vec3b>(Point(x, y));
    //           
    //                //cout << (int) intensity.val[0] << " " << (int)intensity.val[1] << " " << (int)intensity.val[2] << endl;
    //                int b = intensity.val[0] / reg;
    //                int r = intensity.val[1] / reg;
    //                int g = intensity.val[2] / reg;
    //                src.at<Vec3b>(Point(x, y)) = Vec3b(255, 255, 255);
    //                //cout << b << " " << r << " " << g << endl;

    //            }
    //        }
    //    }
    //}

    //
    //imshow("g", grad);
    //string name = "C:\\Users\\Candy\\Documents\\Code588\\noisy_images\\color_mod.jpg";
    //imwrite(name, src);

int blurk = 50;
int sz = 40;
    for (int x = 0; x < src.cols; x += blurk) {
        for (int y = 0; y < src.rows; y += blurk) {
            Point left_top = Point(x, y);
            Point right_bottom = Point(x + sz, y + sz);
            if (x + blurk >= src.cols || y + blurk >= src.rows) continue;
            Rect roi = Rect(left_top, right_bottom);
            normalize(src(roi), src(roi), 100, 200, NORM_MINMAX);
        }
    }

    string name = "C:\\Users\\Candy\\Documents\\Code588\\noisy_images\\norm.jpg";
    imwrite(name, src);

     Mat src_gray, grad;
     cvtColor(src, src_gray, COLOR_BGR2GRAY);

     Mat grad_x, grad_y;
     Mat abs_grad_x, abs_grad_y;
     int ddepth = CV_16S;
     int ksize = 3;
     Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, BORDER_DEFAULT);
     Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, BORDER_DEFAULT);
     convertScaleAbs(grad_x, abs_grad_x);
     convertScaleAbs(grad_y, abs_grad_y);
     addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
     grad = abs_grad_x;

     imshow("g", grad);
     

    //for (int i = 101; i < 401; i += 2) {
    //    Mat src_gray;
    //    GaussianBlur(src, src_gray, Size(i, i), 0, 0, BORDER_DEFAULT);
    //    string name = "C:\\Users\\Candy\\Documents\\Code588\\blurring_images\\blurring_" + to_string(i) + ".jpg";
    //    imwrite(name, src_gray);
    //}

    cv::waitKey(0);
    return 0;
}