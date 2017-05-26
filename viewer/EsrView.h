#ifndef esrview_h
#define esrview_h

#include <opencv2/core/utility.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include "../driver/controlcan.h"


class viewer{
public:
    virtual void init_display() = 0;
    virtual void update(std::int64_t time) = 0;
};


void update(cv::Mat img, int s);

#endif
