#ifndef cvviewer_h
#define cvviewer_h

#include <opencv2/core/utility.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include "EsrView.h"

#include "../msg/SensorMsg.h"

class opencvViewer:public viewer{
public:
    opencvViewer();
    opencvViewer(int w, int h);
    void init_display();
    void update(std::int64_t time);
private:
    cv::Mat img_;
    int w_, h_;
};


#endif
