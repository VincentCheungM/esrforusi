#ifndef handler_h
#define handler_h

#include <lcm/lcm_coretypes.h>
#include "../msg/lcm/lcmbase.h"
#include "../msg/SensorMsg.h"

template <class T>
class LcmHandler{
public:
    virtual void handleMessage(const lcm::ReceiveBuffer* rbuf,
    const std::string& chan, const T* msg) = 0;
};

template <class T>
class SensorMsgLcmHandler:public LcmHandler<T>{
public:
    void handleMessage(const lcm::ReceiveBuffer* rbuf,
    const std::string& chan, const T* msg);
};
template <class T>
void SensorMsgLcmHandler<T>::handleMessage(const lcm::ReceiveBuffer* rbuf,
    const std::string& chan, const T* msg){
    SensorMsg::lcmMsgAdapter adp;
    SensorMsg::g_sensor_msgs = adp.pub2msg(msg);
};
#endif
