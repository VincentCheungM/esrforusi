#ifndef esr_h
#define esr_h
#include <cstdio>
#include <cmath>
#include <cstdint>
#include <vector>

#include "./driver/controlcan.h"
#include "./msg/SensorMsg.h"

#define NUMOFGFRAME 64
// bytes to sign
#define B2SIGN(x) ((x)==1?-1:1)
// bytes to complement
#define B2COMP(x) ((512)-(x)) 

namespace ESR{

class EsrCanFrame{
protected:
    std::int16_t id_;
    std::vector<uint8_t> bytes_;
public:
    virtual bool set_bytes(int16_t id, std::vector<uint8_t> bytes, int size)=0;
    virtual void set_frames()=0;
    virtual void* to_msg() = 0;
    virtual void print_frame() = 0;
};

class EsrTrackFrame:public EsrCanFrame{
private:
    std::int16_t track_ID_;//from [0x500, 0x53F]
    bool is_on_coming_;//bit 0
    bool is_grouped_changed_;//bit 1
    double lat_rate_;//bit [2, 8); scale 0.25
    int status_;//bit 8, 11 
    double angle_;//bit 11, 21; scale 0.1
    double range_;//bit 21, 32; scale 0.1
    double width_;//bit 32, 36; scale 0.5
    int rolling_count_;//bit 36
    bool is_bridge_object_;//bit 37
    double range_accel_;//bit 38, 48; scale 0.05
    int med_range_mode_;//bit 48, 50;
    double range_rate_;//bit 50, 64; scale 0.01
public:
    //implement
    bool set_bytes(int16_t id, std::vector<uint8_t> bytes, int size);
    void set_frames();
    void* to_msg();
    void print_frame();
    // normal get function
    std::int16_t get_track_id(){return track_ID_;}
    bool get_is_on_coming(){return is_on_coming_;}
    bool get_is_grouped_changed(){return is_grouped_changed_;}
    double get_lat_rate(){return lat_rate_;}
    int get_status(){return status_;}
    double get_angle(){return angle_;}
    double get_range(){return range_;}
    double get_width(){return width_;}
    int get_rolling_count(){return rolling_count_;}
    bool get_is_bridge_object(){return is_bridge_object_;};
    double get_range_accel(){return range_accel_;}
    int get_med_range_mode(){return med_range_mode_;}
    double get_range_rate(){return range_rate_;}

    //void set_Frame(VCI_CAN_OBJ vco_receive);
    //void print_Frame();
    bool is_Worked();


};

//TODO: global instance
extern EsrTrackFrame g_esr_track_frames[NUMOFGFRAME];

void print_g_esr_track_frames();
}

#endif
