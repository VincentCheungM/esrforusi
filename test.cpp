#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "./driver/controlcan.h"
#include "Esr.h"
#include "./msg/SensorMsg.h"
#include "./publisher/Publisher.h"
#include "./msg/lcm/lcmbase.h"
#include "./handler/Handler.h"
#include "./viewer/cvviewer.h"


using namespace std;
using namespace ESR;
using namespace cv;

int main(){
    /* step1: set up trackframe */
    EsrTrackFrame testFrame;
    // set up id
    int16_t id = 0x500;
    // set up bytes vector
    vector<uint8_t> v;
    v.push_back(0x0);
    v.push_back(0x7F);
    v.push_back(0x58);
    v.push_back(0xB0);
    v.push_back(0x40);
    v.push_back(0x11);
    v.push_back(0xc1);
    v.push_back(0xe8);
    // set up frame size
    int size = 8;
    testFrame.set_bytes(id, v, size);
    testFrame.set_frames();
    cout<<"finish step 1"<<endl;

    /* step2: trackframe to msg */
    SensorMsg::sensorRangeEle* ele = (SensorMsg::sensorRangeEle*)testFrame.to_msg();
    // return new ptr need delete
    cout<<"setup ele"<<endl;
    SensorMsg::sensorRangeFrame msg_frame;
    msg_frame.add_ele(*ele);
    delete ele;
    ele = NULL;
    cout<<"finish step 2"<<endl;



    /* step3: msg to publish */
//    Publisher::lcmPublisher publisher;
//    publisher.publish_msg(&msg_frame);
//    cout<<"finish step 3"<<endl;

    /* step4: publish to msg */
    SensorMsgLcmHandler<sensormsglcm::senseRangeFrame> lcmhandler;
    LcmBase* lcmbase = LcmBase::get_instance();//get lcm instance
    //lcm handler will save the lcm msg to g_sensor_msgs
    lcmbase->get_lcm().subscribe("channel",&SensorMsgLcmHandler<sensormsglcm::senseRangeFrame>::handleMessage, &lcmhandler);
    cout<<"finish step 4"<<endl;

    /* step4.1: simulate handl msg */
    SensorMsg::g_sensor_msgs = msg_frame;

    /* step5: msg display */
    opencvViewer cvViewer(512, 512);
    cvViewer.init_display();
    cvViewer.update(0);
    cout<<"finish step5"<<endl;


    return 0;
}
