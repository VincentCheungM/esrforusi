#ifndef sensormsg_h
#define sensormsg_h


#include <vector>
#include <cstdint>
#include "./lcm/sensormsglcm/senseRangeFrame.hpp"
namespace SensorMsg{

class sensorRangeEle{
private:
    double x_pos_;
    double y_pos_;
    double width_;
    std::int16_t id_;
    std::int16_t status_;
public:
    void set_range(double x_pos, double y_pos, double width, std::int16_t id, std::int16_t status);
    double get_xpos();
    double get_ypos();
    double get_width();
    std::int16_t get_id();
    std::int16_t get_status();
};

class sensorRangeFrame{
private:
    std::int16_t nele_;
    std::vector<SensorMsg::sensorRangeEle> sensor_range_ele_;
public:
    void add_ele(SensorMsg::sensorRangeEle ele);
    void set_frame(std::vector<SensorMsg::sensorRangeEle> v_frame);
    void clear_frame();
    std::int16_t get_size();
    std::vector<SensorMsg::sensorRangeEle> get_frame();
};

class sensorMsgAdapter{
public:
    virtual void* msg2pub(sensorRangeFrame& vframe) = 0;
    virtual sensorRangeFrame pub2msg(const void*) = 0;
};

class lcmMsgAdapter:public sensorMsgAdapter{
public:
    void* msg2pub(sensorRangeFrame& vframe);
    sensorRangeFrame pub2msg(const void*);
};

extern sensorRangeFrame g_sensor_msgs;
}
#endif
