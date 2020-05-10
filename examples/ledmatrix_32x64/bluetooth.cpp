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

void Bluetooth::run(P3RGB64x32MatrixPanel* matrix)
{
  buffser.process(matrix, &ledpannel, &SerialBT);
  command_excute(1);
}

void Bluetooth::led_setup(P3RGB64x32MatrixPanel* matrix)
{
	ledpannel.setup(matrix);
}


void Bluetooth::command_excute(uint8_t mode)
{
  #define MODE_LOOP 1
  #define MODE_SINGLE 2

  if(mode == MODE_LOOP)
    ledpannel.command_excute();
  else if(mode == MODE_SINGLE)
  {
    ledpannel.command_excute();
  }

}