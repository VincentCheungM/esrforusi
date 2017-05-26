#include "CANDriver.h"
#include "../Esr.h"

/**
 * @func Control::Control()
 * @brief Default constructor of class Control
 * @details Set the can sturcture information such as can index.
 */
CANDriver::CANDriver() {
	/* CANalyst-II设备为4 */
	nDeviceType = 4;
	/* 设备索引，如果插一个USB设备则为0 */
	nDeviceInd = 0;
	/* CAN通道索引，CAN1为0，CAN2为1 */
	nCANInd_1 = 0;
	nCANInd_2 = 1;
}

int CANDriver::init() {
    /* CANalyst-II设备为4 */
    nDeviceType = 4;
    /* 设备索引，如果插一个USB设备则为0 */
    nDeviceInd = 0;
    /* CAN通道索引，CAN1为0，CAN2为1 */
    nCANInd_1 = 0;
    nCANInd_2 = 1;
}


/**
 * @func Control::~Control()
 * @brief Default destructor of class Control
 * @details Close can device.
 */
CANDriver::~CANDriver() {
    close();
}



int CANDriver::start() {
	int dwRelOpenDevice;
	int dwRelVCI_InitCAN;

	dwRelOpenDevice = VCI_OpenDevice(nDeviceType, nDeviceInd, 0);
	if (dwRelOpenDevice != 1) {
		printf("VCI_OpenDevice fail!\n");
        return -1;
	}

	/*初始 CAN*/
	vic_1.AccCode = 0x80000008;
	vic_1.AccMask = 0xFFFFFFFF;
	vic_1.Filter = 1;		//接受所有帧
	vic_1.Timing0 = 0x00;
	vic_1.Timing1 = 0x1C;//波特率500Kbps
	vic_1.Mode = 0;		//正常模式
	dwRelVCI_InitCAN = VCI_InitCAN(nDeviceType, nDeviceInd, nCANInd_1, &vic_1);
	if (dwRelVCI_InitCAN != 1) {
		printf("dwRelVCI_InitCAN fail!\n");
        return -1;
	}
	if (VCI_StartCAN(nDeviceType, nDeviceInd, nCANInd_1) != 1) {
		printf("VCI_StartCAN 1 fail!\n");
        return -1;
	}
	
	VCI_ClearBuffer(nDeviceType, nDeviceInd, nCANInd_1);
    return 1;
}


int CANDriver::close() {
	int dwRel;
	dwRel = VCI_CloseDevice(nDeviceType, nDeviceInd);
	if (dwRel != 1) {
		printf("Can Close Errors!\n");
        return -1;
	}
    return 1;
}


/**
 * @func Control::RecvInfo(int print)
 * @brief receive information from can.
 * @details return value return -1 if receive failed, otherwise return 0, receive information from can periodiclly, run it in a thread.
 */
int CANDriver::recv() {
	int dwRel;
	dwRel = VCI_Receive(nDeviceType, nDeviceInd, nCANInd_1, vco_receive, 1024, 0);

    if(dwRel>0){
        //TODO: add a factory class to get instance according to CAN ID
        ESR::EsrTrackFrame *esr_Frame = new ESR::EsrTrackFrame();
        std::vector<uint8_t> v;
        for(int i =0;i<vco_receive[0].DataLen;i++){
            v.push_back(vco_receive[0].Data[i]);
        }
        //set can frame
        esr_Frame->set_bytes(vco_receive[0].ID, v, vco_receive[0].DataLen);
        esr_Frame->set_frames();
        SensorMsg::sensorRangeEle* ele = (SensorMsg::sensorRangeEle*)esr_Frame->to_msg();
        //return new ptr need delete

        SensorMsg::g_sensor_msgs.add_ele(*ele);
        delete ele;
        ele = NULL;
    }else
        return -1;

    return 1;
}


/**
 * @func Control::sendCAP1Command()
 * @brief send CAP_1 command.
 * @details This is only an example, you should modify it according to your can api and can it periodiclly in a thread.
 */
int CANDriver::send() {
	int dwRel;
	/* you should set your own id according to api. */
	vco_send[0].ID = (UINT)(0x00000098);
	vco_send[0].RemoteFlag = 0;
	vco_send[0].ExternFlag = 1; //扩展帧
	vco_send[0].DataLen = 8;
	/* you should set  according to control matrix, and put data */
    vco_send[0].Data[0] = 0x00;
    vco_send[0].Data[1] = 0x00;
	vco_send[0].Data[2] = 0x00;
	vco_send[0].Data[3] = 0x00;
	vco_send[0].Data[4] = 0x00;
	vco_send[0].Data[5] = 0x00;
	vco_send[0].Data[6] = 0x00;
	vco_send[0].Data[7] = 0x00;
	dwRel = VCI_Transmit(nDeviceType, nDeviceInd, nCANInd_1, vco_send, 1);
	if (dwRel <= 0) {
        return -1;
	}
    return 1;
}


