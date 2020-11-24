#include "thin.h"


namespace thin {
    void hilditch_thin(cv::Mat& dst) {
        int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
        int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
        std::map<std::pair<int, int>, int>* apmap = new std::map<std::pair<int, int>, int>();
        std::map<std::pair<int, int>, int>* bpmap = new std::map<std::pair<int, int>, int>();

        // first insert function version (single parameter):

        for (int x = 1; x < dst.cols - 1; x++) {
            for (int y = 1; y < dst.rows - 1; y++) {
                cv::Scalar inten = dst.at<uchar>(cv::Point(x, y));
                if (inten[0] == kWhiteColor) {
                    apmap->insert(std::pair<std::pair<int, int>, int>(std::pair<int, int>(x, y), 0));
                    continue;
                }

                int ap = 0, bp = 0;
                for (int i = 0; i < 8; i++) {
                    cv::Point current = cv::Point(x + dx[i], y + dy[i]);
                    cv::Scalar intensity = dst.at<uchar>(current);
                    if (intensity[0] == kBlackColor)
                    {
                        bp++;
                        cv::Point next = cv::Point(x + dx[(i + 1) % 8], y + dy[(i + 1) % 8]);
                        cv::Scalar next_inten = dst.at<uchar>(next);
                        if (next_inten[0] == kWhiteColor) ap++;
                    }
                }

                apmap->insert(std::pair<std::pair<int, int>, int>(std::pair<int, int>(x, y), ap));
                bpmap->insert(std::pair<std::pair<int, int>, int>(std::pair<int, int>(x, y), bp));
            }
        }

        for (int x = 2; x < dst.cols - 2; x++) {
            for (int y = 2; y < dst.rows - 2; y++) {
                if (apmap->find(std::pair<int, int>(x, y))->second == 1) {
                    int bp = bpmap->find(std::pair<int, int>(x, y))->second;

                    if (bp >= 2 && bp <= 6) {
                        int ap2 = apmap->find(std::pair<int, int>(x, y - 1))->second;
                        cv::Scalar inten2, inten4;
                        if (ap2 == 1) {
                            inten2 = dst.at<uchar>(cv::Point(x, y - 1));
                            inten4 = dst.at<uchar>(cv::Point(x + 1, y));
                            cv::Scalar inten8 = dst.at<uchar>(cv::Point(x - 1, y));

                            if (inten2[0] == kBlackColor || inten4[0] == kBlackColor || inten8[0] == kBlackColor)
                                continue;
                        }

                        int ap4 = apmap->find(std::pair<int, int>(x + 1, y))->second;
                        if (ap4 == 1) {
                            cv::Scalar inten6 = dst.at<uchar>(cv::Point(x, y + 1));

                            if (inten2[0] == kBlackColor || inten4[0] == kBlackColor || inten6[0] == kBlackColor)
                                continue;
                        }

                        dst.at<uchar>(cv::Point(x, y)) = kWhiteColor;
                    }

                }
            }
        }
    }
}