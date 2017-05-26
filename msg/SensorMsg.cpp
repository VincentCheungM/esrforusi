#include "SensorMsg.h"
#include "./lcm/sensormsglcm/senseRangeFrame.hpp"

namespace SensorMsg{
sensorRangeFrame g_sensor_msgs;

/* sensor range element */
void sensorRangeEle::set_range(double x_pos, double y_pos, double width, std::int16_t id, std::int16_t status){
    x_pos_ = x_pos;
    y_pos_ = y_pos;
    width_ = width;
    id_ = id;
    status_ = status;
}

double sensorRangeEle::get_xpos(){
    return x_pos_;
}

double sensorRangeEle::get_ypos(){
    return y_pos_;
}

double sensorRangeEle::get_width(){
    return width_;
}

std::int16_t sensorRangeEle::get_id(){
    return id_;
}

std::int16_t sensorRangeEle::get_status(){
    return status_;
}

/* sensor range frame */
void sensorRangeFrame::add_ele(SensorMsg::sensorRangeEle ele){
    sensor_range_ele_.push_back(ele);
    nele_ = sensor_range_ele_.size();
}

void sensorRangeFrame::set_frame(std::vector<SensorMsg::sensorRangeEle> v_frame){
    sensor_range_ele_ = v_frame;
    nele_ = sensor_range_ele_.size();
}

void sensorRangeFrame::clear_frame(){
    sensor_range_ele_.clear();
    nele_ = sensor_range_ele_.size();
}

std::int16_t sensorRangeFrame::get_size(){
    return nele_;
}

std::vector<SensorMsg::sensorRangeEle> sensorRangeFrame::get_frame(){
    return sensor_range_ele_;
}

/* adpater interface */
void* lcmMsgAdapter::msg2pub(sensorRangeFrame& vframe){
    sensormsglcm::senseRangeFrame* pubmsg = new sensormsglcm::senseRangeFrame();
    sensormsglcm::sense_range_t ele;
    pubmsg->nele = vframe.get_size();
    std::vector<SensorMsg::sensorRangeEle> v = vframe.get_frame();
    
    for(int i =0;i<v.size();i++){
        ele.x_pos = v[i].get_xpos();
        ele.y_pos = v[i].get_ypos();
        ele.width = v[i].get_width();
        ele.id = v[i].get_id();
        ele.status = v[i].get_status();
        pubmsg->sense_range.push_back(ele);
    }
    return (pubmsg);
}

sensorRangeFrame lcmMsgAdapter::pub2msg(const void* pub){
    sensormsglcm::senseRangeFrame* pubmsg = (sensormsglcm::senseRangeFrame*)pub;
    std::vector< sensormsglcm::sense_range_t > v = pubmsg->sense_range;
    sensorRangeFrame msg;
    SensorMsg::sensorRangeEle ele;
    for(int i =0;i<v.size();i++){
        ele.set_range(v[i].x_pos, v[i].y_pos, v[i].width, v[i].id, v[i].status);
        msg.add_ele(ele);
    }
    return msg;
}

}
