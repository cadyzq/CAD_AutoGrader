#ifndef FIELDS_H
#define FIELDS_H

#include <opencv2/core.hpp>

const int xsf[4] = { 0, -1, 0, 1 };
const int ysf[4] = { -1, 0, 1, 0 };

const int xse[8] = { 0, -1, 0, 1, 1, 1, -1, -1 };
const int yse[8] = { -1, 0, 1, 0, 1, -1, 1, -1 };

const int xdia_pos[2] = { 1, -1 };
const int ydia_pos[2] = { 1, -1 };

const int kBlackColor = 0;
const int kWhiteColor = 255;

const int kMaxLineWidth = 2;
const int kContourGap = 2;
const int kContourDilationSize = 3;

const double kHatchedThreshold = 0.1;
const double kContourThreshold = 0.35;
const double kDimThreshold = 0.01;

#endif // !FIELDS_H
