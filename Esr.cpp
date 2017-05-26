#include "Esr.h"

namespace ESR{

bool EsrTrackFrame::set_bytes(int16_t id, std::vector<uint8_t> bytes, int size){
    id_ = id;
    bytes_ = bytes;
    return bytes_.size()==size;
}

void EsrTrackFrame::set_frames(){
    // complement
    // big endian
    track_ID_ = id_ - 0x500;//from [0x500, 0x53F]
    is_on_coming_ = (bytes_[0]&0x01);
    is_grouped_changed_ = (bytes_[0] & 0x02)>>1;

    //sign value
    if(B2SIGN((bytes_[0]&0x80)>>7)==-1){
        lat_rate_ = -B2COMP((bytes_[0]&0x7C)>>2);
    }else{
        lat_rate_ = (bytes_[0]&0x7C)>>2;
    }
    
    status_ = (bytes_[1]&0xE0)>>5;

    //sign value
    if(B2SIGN((bytes_[1]&0x10)>>4)==-1){
        angle_ = -B2COMP((((bytes_[1]&0x0F)<<5)|(bytes_[2]>>3)))*0.1;
    }else{
        angle_ = (((bytes_[1]&0x0F)<<5)|(bytes_[2]>>3))*0.1;
    }

    range_ = (((bytes_[2]&0x07)<<8)+bytes_[3])*0.1;
    is_bridge_object_ = (bytes_[4]&0x80)>>7;
    rolling_count_ = (bytes_[4]&0x40)>>6;
    width_ = (bytes_[4]&0x3C)>>2; 

    //sign value
    if(B2SIGN((bytes_[4]&0b00000010)>>1)==-1){
        range_accel_ = -B2COMP((((bytes_[4]&0x01)<<8)+bytes_[5]))*0.05;
    }else{
        range_accel_ = (((bytes_[4]&0x01)<<8)+bytes_[5])*0.05;
    }    

    med_range_mode_ = ((bytes_[6]&0xC0)>>6);

    //sign value
    if(B2SIGN((bytes_[6]&0b00100000)>>5)==-1){
        range_rate_ = -B2COMP((((bytes_[6]&0x1F)<<8)+bytes_[7]))*0.01;
    }else{
        range_rate_ = (((bytes_[6]&0x1F)<<8)+bytes_[7])*0.01;//sign
    }
}

void* EsrTrackFrame::to_msg(){
    SensorMsg::sensorRangeEle *ele = new SensorMsg::sensorRangeEle();
    double track_range = get_range();
    double track_angle = get_angle();
    double rad = track_angle*3.1415926/180;
    double x_pos = sin(rad)*track_range*4;
    double y_pos = cos(rad)*track_range*4;
    
    ele->set_range(x_pos,y_pos,get_width(),track_ID_,status_);
    return (void*)ele;
}

void EsrTrackFrame::print_frame(){
    printf("=============\n");
    printf("track_id: %x\n",track_ID_);
    printf("is_on_coming: %x\n", is_on_coming_);
    printf("is_grouped_changed: %x\n", is_grouped_changed_);
    printf("lat_rate: %lf\n", lat_rate_);
    printf("status: %d\n", status_);
    printf("angle: %lf\n", angle_);
    printf("range: %lf\n",range_);
    printf("width: %lf\n",width_);
    printf("rolling_count: %d\n",rolling_count_);
    printf("is_bridge_object: %d\n",is_bridge_object_);
    printf("range_accel: %lf\n",range_accel_);
    printf("med_range_mode: %d\n",med_range_mode_);
    printf("range_rate: %lf m/s\n",range_rate_);
    printf("=================\n");
}

bool EsrTrackFrame::is_Worked(){
    return status_!=0&&track_ID_<=63&&track_ID_>=0;
}

//TODO: global instance
EsrTrackFrame g_esr_track_frames[NUMOFGFRAME];

void print_g_esr_track_frames(){
    printf("**********************\n");
    for(int i=0;i<NUMOFGFRAME;i++){
        if(g_esr_track_frames[i].is_Worked()){
            g_esr_track_frames[i].print_frame();
        }
    }
    printf("**********************\n");
}



}
