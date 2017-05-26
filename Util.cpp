#include "Util.h"

/**
 * @fn Util::string2BYTE(int i)
 * @brief convert int to string
 * @param i int type
 * @return string result
 */
BYTE Util::string2BYTE(std::string steering_angle_speed_str) {
	short temp_speed = atoi(steering_angle_speed_str.c_str());
	temp_speed = temp_speed / 4;
	temp_speed += 10;

	if (temp_speed <= 255 && temp_speed >= 0) {
		if (temp_speed < 10) {
			return 0x22;
		}

		std::string s = "";
		if (temp_speed == 0)
			s = "0";

		while (temp_speed != 0) {
			if (temp_speed % 16 >9)
				s += temp_speed % 16 - 10 + 'A';
			else
				s += temp_speed % 16 + '0';
			temp_speed = temp_speed / 16;
		}
		reverse(s.begin(), s.end());

		BYTE tem, tem1, tem2;

		if (s.length() >= 2) {
			switch (s[0]) {
			case '0': {tem1 = 0x00; break; }
			case '1': {tem1 = 0x10; break; }
			case '2': {tem1 = 0x20; break; }
			case '3': {tem1 = 0x30; break; }
			case '4': {tem1 = 0x40; break; }
			case '5': {tem1 = 0x50; break; }
			case '6': {tem1 = 0x60; break; }
			case '7': {tem1 = 0x70; break; }
			case '8': {tem1 = 0x80; break; }
			case '9': {tem1 = 0x90; break; }
			case 'A': {tem1 = 0xA0; break; }
			case 'B': {tem1 = 0xB0; break; }
			case 'C': {tem1 = 0xC0; break; }
			case 'D': {tem1 = 0xD0; break; }
			case 'E': {tem1 = 0xE0; break; }
			case 'F': {tem1 = 0xF0; break; }
			}
			switch (s[1]) {
			case '0': {tem2 = 0x00; break; }
			case '1': {tem2 = 0x01; break; }
			case '2': {tem2 = 0x02; break; }
			case '3': {tem2 = 0x03; break; }
			case '4': {tem2 = 0x04; break; }
			case '5': {tem2 = 0x05; break; }
			case '6': {tem2 = 0x06; break; }
			case '7': {tem2 = 0x07; break; }
			case '8': {tem2 = 0x08; break; }
			case '9': {tem2 = 0x09; break; }
			case 'A': {tem2 = 0x0A; break; }
			case 'B': {tem2 = 0x0B; break; }
			case 'C': {tem2 = 0x0C; break; }
			case 'D': {tem2 = 0x0D; break; }
			case 'E': {tem2 = 0x0E; break; }
			case 'F': {tem2 = 0x0F; break; }
			}
		}
		else if (s.length() == 1) {
			tem1 = 0x00;
			switch (s[0]) {
			case '0': {tem2 = 0x00; break; }
			case '1': {tem2 = 0x01; break; }
			case '2': {tem2 = 0x02; break; }
			case '3': {tem2 = 0x03; break; }
			case '4': {tem2 = 0x04; break; }
			case '5': {tem2 = 0x05; break; }
			case '6': {tem2 = 0x06; break; }
			case '7': {tem2 = 0x07; break; }
			case '8': {tem2 = 0x08; break; }
			case '9': {tem2 = 0x09; break; }
			case 'A': {tem2 = 0x0A; break; }
			case 'B': {tem2 = 0x0B; break; }
			case 'C': {tem2 = 0x0C; break; }
			case 'D': {tem2 = 0x0D; break; }
			case 'E': {tem2 = 0x0E; break; }
			case 'F': {tem2 = 0x0F; break; }
			}
		}
		else {
			printf("string to byte error!!!\n");
		}
		return  tem1^tem2;
	}
	else
		return  0x11;
}


BYTE Util::short2BYTE(short input) {
	BYTE output = (input << 8) >> 8;
	return output;
}