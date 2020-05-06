#include "Arduino.h"
#include "BluetoothSerial.h"
#include "bluetooth.h"
#include "ledpannel.h"
#include "uart.h"

LedPannel ledpannel;
BufferSerial buffser = BufferSerial();

void Bluetooth::setup() 
{
  SerialBT.begin("LedMatrix"); //Bluetooth device name
}

int Bluetooth::check()
{
	return SerialBT.available();
}

void Bluetooth::run()
{
  buffser.process(&SerialBT);
}

void Bluetooth::led_setup(P3RGB64x32MatrixPanel* matrix)
{
	ledpannel.setup(matrix);
}