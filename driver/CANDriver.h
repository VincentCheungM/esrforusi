#ifndef candriver_h
#define candriver_h

#include <cstdio>
#include <string>
#include <cstdlib>

#include "controlcan.h"
#include "../Util.h"
#include "../Esr.h"
#include "driver.h"

//using namespace std;

class CANDriver: public Driver {

/*****************************parameter***********************************/

private:
	/* can structure */
	VCI_CAN_OBJ vco_receive[64];
	VCI_CAN_OBJ vco_send[8];
	VCI_INIT_CONFIG vic_1;
	int nDeviceType;
	int nDeviceInd;
	int nCANInd_1;
	int nCANInd_2;


/*****************************method************************************/
public:
    CANDriver();
    ~CANDriver();
	/* can device */
    int init();
    int close();
    int start();
    int recv();
    int send();


};

#endif
