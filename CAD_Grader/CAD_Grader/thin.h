#ifndef THIN_H
#define THIN_H

#include <map>

#include <opencv2/core.hpp>

#include "fields.h"

namespace thin {
	void hilditch_thin(cv::Mat& dst);
}

#endif // !THIN_H


