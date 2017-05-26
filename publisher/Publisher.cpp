#include "Publisher.h"
#include "../msg/SensorMsg.h"
#include "../msg/lcm/lcmbase.h"
#include "../msg/lcm/sensormsglcm/senseRangeFrame.hpp"

namespace Publisher{

void lcmPublisher::publish_msg(void* msg){
    SensorMsg::lcmMsgAdapter adp;
    sensormsglcm::senseRangeFrame *data;//pub range frame
    //msg 2 range frame
    SensorMsg::sensorRangeFrame* msg_frame = (SensorMsg::sensorRangeFrame*) msg;
    data = (sensormsglcm::senseRangeFrame*)adp.msg2pub(*msg_frame);
    LcmBase* lcmbase = LcmBase::get_instance();
    lcmbase->get_lcm().publish("channel", data);

}

void* lcmPublisher::serialize_msg(void* msg){
    //TODO: not implemented
    return NULL;
}

}
