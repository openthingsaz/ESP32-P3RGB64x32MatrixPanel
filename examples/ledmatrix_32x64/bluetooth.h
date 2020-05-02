#ifndef _BLUETOOTH_
#define _BLUETOOTH_
#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>
#include "BluetoothSerial.h"

class Bluetooth {
private:
	BluetoothSerial SerialBT;
	uint8_t ser_recev_len;
	char temp[100];
	int cmd;
	int init_setup = 0;
public:
	void setup();
	int check();
	void run();
    void led_setup(P3RGB64x32MatrixPanel* matrix);
};

#endif
