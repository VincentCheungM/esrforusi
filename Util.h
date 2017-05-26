#ifndef UTIL_H_
#define UTIL_H_ 

#define BYTE unsigned char
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>

class Util {
public:
	static BYTE string2BYTE(std::string steering_angle_speed_str);
	static BYTE short2BYTE(short input);
};

#endif