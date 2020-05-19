/* Derived from Adafruit RGB_matrix_Panel library */
#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>
#include "bluetooth.h"
#include "ledpannel.h"


// constructor with default pin wiring

Bluetooth bluetooth;
P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 16, 17, 4);
//P3RGB64x32MatrixPanel matrix;


void setup() {
  
  Serial.begin(115200);
  bluetooth.setup();
  Serial.println("The device started, now you can pair it with bluetooth!");

  while(1)
  {
    if(bluetooth.check())
    {
      bluetooth.led_setup((P3RGB64x32MatrixPanel*)&matrix);
      break;
    }
    delay(500);
  }
   
}

void loop() 
{
  bluetooth.run((P3RGB64x32MatrixPanel*)&matrix);
}