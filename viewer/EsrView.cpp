#include <cmath>

#include "EsrView.h"

#include "../driver/controlcan.h"
#include "Esr.h"





#define H 512  
#define W 512 

//extern EsrTrackFrame g_esr_track_frames[NUMOFGFRAME];

void update(cv::Mat img, int s = 1){
	img = cv::Mat::zeros(512,512,CV_8UC3);
	
	cv::line(img, cv::Point(10, 0), cv::Point(H / 2 - 5, W), cv::Scalar(100, 255, 255));
	cv::line(img, cv::Point(W - 10, 0), cv::Point(H / 2 + 5, W), cv::Scalar(100, 255, 255));
    
    double track_range, track_angle,rad;
    int x_pos, y_pos;
	double width;
    //cv::CvFont font;
    //cv::cvInitFont(&font,CV_FONT_HERSHEY_COMPLEX,1.0,1.0,0,2,8);
	for (int id = 0; id < 64; id++){

		if (ESR::g_esr_track_frames[id].is_Worked()){
            track_range = ESR::g_esr_track_frames[id].get_range();//
			track_angle = ESR::g_esr_track_frames[id].get_angle();
			rad = track_angle*CV_PI/180;
			width = ESR::g_esr_track_frames[id].get_width();
			
            x_pos = sin(rad)*track_range*4;
            y_pos = cos(rad)*track_range*4;
			
            cv::circle(img, cv::Point(W / 2 + int(x_pos), H / 2 - int(y_pos) - 10), width*5+5, cv::Scalar(255, 255, 255));

		}
	}
	cv::namedWindow("radar");
	cv::imshow("radar", img);
	cv::waitKey(s);
}
