#include "cvviewer.h"
#include "../msg/SensorMsg.h"

opencvViewer::opencvViewer(){
    w_ = 512;
    h_ = 512;
};

opencvViewer::opencvViewer(int w, int h){
    w_ = w;
    h_ = h;
};

void opencvViewer::init_display(){
    img_ = cv::Mat::zeros(w_,h_,CV_8UC3);
};

void opencvViewer::update(std::int64_t time){
    cv::line(img_, cv::Point(10, 0), cv::Point(h_ / 2 - 5, w_), cv::Scalar(100, 255, 255));
	cv::line(img_, cv::Point(w_ - 10, 0), cv::Point(h_ / 2 + 5, w_), cv::Scalar(100, 255, 255));
    
    //cv::CvFont font;
    //cv::cvInitFont(&font,CV_FONT_HERSHEY_COMPLEX,1.0,1.0,0,2,8);
    std::vector<SensorMsg::sensorRangeEle> data = SensorMsg::g_sensor_msgs.get_frame();
    for (int id = 0; id < data.size(); id++){
        
        if (data[id].get_status()!=0){
            double x_pos = data[id].get_xpos();
            double y_pos = data[id].get_ypos();
            double width = data[id].get_width();
            cv::circle(img_, cv::Point(w_ / 2 + int(x_pos), w_ / 2 - int(y_pos) - 10), width*5+5, cv::Scalar(255, 255, 255));

		}
	}
	cv::namedWindow("radar");
    cv::imshow("radar", img_);
	cv::waitKey(time);
};
