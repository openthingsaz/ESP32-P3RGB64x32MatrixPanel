#include "Arduino.h"
#include "bluetooth.h"
#include "BluetoothSerial.h"
#include "ledpannel.h"

LedPannel ledpannel;
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
  if (SerialBT.available()) 
  { 
    ser_recev_len = SerialBT.readBytes(temp, 100);
    Serial.print("read data Lenght : ");
    Serial.println(ser_recev_len);
    
    for(int i=0; i<ser_recev_len; i++)
      Serial.print(temp[i]);

    if(ser_recev_len <= 1) 
    {
      Serial.println("cmd start");
      cmd = temp[0] - 48;
      if(cmd == 1)
      {
		ledpannel.print_exam_12();
      }
      else if(cmd == 2)
      {
         ledpannel.print_exam_2();
      }
      else if(cmd == 3)
      {
         ledpannel.print_exam_3();;
      }
      else if(cmd == 4)
      {
        ledpannel.print_exam_4();
      }
      else if(cmd == 5)
      {
        ledpannel.print_exam_5();
      }
      else if(cmd == 6)
      {
        ledpannel.print_exam_6();
      }
      else if(cmd == 7)
      {
        ledpannel.print_exam_7();
      }
      else if(cmd == 8)
      {
         ledpannel.print_exam_8();
      }
      else if(cmd == 9)
      {
        ledpannel.print_exam_9();
      }
      Serial.println("cmd end");
    }    
    else 
    {
       ledpannel.scoll_text(temp, ser_recev_len);
    }
  }
  
  if (Serial.available())
  {
    ser_recev_len = Serial.readBytes(temp, 100);
    for(int i=0; i<ser_recev_len; i++)
      SerialBT.print(temp[i]);
    SerialBT.println();
  }
}

void Bluetooth::led_setup(P3RGB64x32MatrixPanel* matrix)
{
	ledpannel.setup(matrix);
}