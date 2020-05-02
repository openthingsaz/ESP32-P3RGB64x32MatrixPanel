#include "Arduino.h"
#include "ledpannel.h"
#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>


// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(P3RGB64x32MatrixPanel* matrix, byte WheelPos) {
  if(WheelPos < 8) {
   return matrix->color444(15 - WheelPos*2, WheelPos*2, 0);
  } else if(WheelPos < 16) {
   WheelPos -= 8;
   return matrix->color444(0, 15-WheelPos*2, WheelPos*2);
  } else {
   WheelPos -= 16;
   return matrix->color444(0, WheelPos*2, 7 - WheelPos*2);
  }
}

void LedPannel::setup(P3RGB64x32MatrixPanel* mat)
{
    matrix = mat;
    matrix->begin();
    // fill the screen with 'black'
    matrix->fillScreen(matrix->color444(0, 0, 0));    
}

void LedPannel::scoll_text(char* data, uint8_t ser_recev_len)
{
  uint8_t w = 0;
  int pos = 0;
  int tmp;
  // fill the screen with 'black'
  matrix->fillScreen(0);
  matrix->setTextSize(2);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves

  tmp = -((ser_recev_len * 8)*2);
  Serial.println(tmp);
 
  for(pos=64; pos >= -((ser_recev_len * 6)*2); pos--) 
  {
    matrix->fillScreen(0);
    matrix->setCursor(pos, 10);    // start at top left, with 8 pixel of spacing
    for(int i=0; i<ser_recev_len; i++)
    {
      matrix->print(data[i]);
      matrix->setTextColor(Wheel(matrix, i));
      //matrix->setTextColor(20);
    }
    delay(80); 
  }
}
void LedPannel::print_exam_1(void)
{
  uint8_t w = 0;
  int len;
  char str[] = "Baby On Board";
  
  // fill the screen with 'black'
  matrix->fillScreen(matrix->color444(0, 0, 0));
  // draw some text!
  matrix->setTextSize(2);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix->setCursor(8, 2);    // start at top left, with 8 pixel of spacing
  
  len = strlen(str);
  for (w=0; w<len; w++) 
  {
    if(w == 5) {
      matrix->println();
      matrix->setTextSize(1);     // size 1 == 8 pixels high
      matrix->setCursor(8, 17);    // start at top left, with 8 pixel of spacing
    }
    matrix->setTextColor(Wheel(matrix, w));
    delay(500);
    
    matrix->print(str[w]);  
  }
  matrix->println();

  ////print_phone_num();
}

void LedPannel::print_exam_2(void)
{
  // fill the screen with 'black'
  //matrix->fillScreen(matrix->color444(0, 0, 0));
  matrix->fillScreen(0);
  // draw some text!
  matrix->setTextSize(2);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  
  matrix->setCursor(0, 2);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  int len1;
  char str[] = "STUDIO GOoooD";
  len1 = strlen(str);
  for (w=0; w<len1; w++) 
  {
    if(w == 7) {
      matrix->println();
      matrix->setTextSize(1);     // size 1 == 8 pixels high
      matrix->setCursor(8, 17);    // start at top left, with 8 pixel of spacing
    }
    matrix->setTextColor(Wheel(matrix, w));
    delay(500);
    matrix->print(str[w]);  
  }
  
  delay(3000);
  matrix->println();
  matrix->fillScreen(0);
  ////print_phone_num_gooood();
}

void LedPannel::print_exam_3(void)
{
  for (int i=0; i<10; i++) 
  {
    matrix->fillScreen(0);
    // draw some text!
    matrix->setTextSize(2);     // size 1 == 8 pixels high
    matrix->setCursor(5, 9);    // start at top left, with 8 pixel of spacing
    uint8_t w = 0;
    int len1;
    char str[] = ">>>>>";
    len1 = strlen(str);
    for (w=0; w<len1; w++) 
    {
      //matrix->setTextColor(Wheel(w));
      matrix->setTextColor(matrix->color444(15,0,0));
      delay(200);
      matrix->print(str[w]);  
    }
  }
}


void LedPannel::print_exam_4(void)
{
  // draw an 'X' in red
  matrix->drawLine(0, 0, matrix->width()-1, matrix->height()-1, matrix->color444(7, 0, 0));
  matrix->drawLine(matrix->width()-1, 0, 0, matrix->height()-1, matrix->color444(7, 0, 0));
  delay(500);  
}

void LedPannel::print_exam_5(void)
{
  // fill the screen with 'black'
  matrix->fillScreen(matrix->color444(0, 0, 0));
  // draw some text!
  matrix->setTextSize(1);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  
  matrix->setCursor(8, 0);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  char str[] = "TrueSolutionGoods";
  for (w=0; w<8; w++) {
    matrix->setTextColor(Wheel(matrix, w));
    matrix->print(str[w]);
  }
  matrix->setCursor(2, 8);    // next line
  for (w=8; w<18; w++) {
    matrix->setTextColor(Wheel(matrix, w));
    matrix->print(str[w]);
  }
  matrix->println();
  
  matrix->setTextColor(matrix->color444(7,7,7));
  matrix->println("LED MATRIX!");
  
  // print each letter with a rainbow color
  matrix->setTextColor(matrix->color444(7,0,0));
  matrix->print('0');
  matrix->setTextColor(matrix->color444(0,7,0));
  matrix->print('1');
  matrix->setTextColor(matrix->color444(0,0,7));
  matrix->print('0');
  matrix->setTextColor(matrix->color444(7,7,7));
  matrix->print('4');
  matrix->setTextColor(matrix->color444(0,7,0));
  matrix->print('4');
  //matrix->setCursor(34, 24);
  matrix->setTextColor(matrix->color444(0,7,7));
  matrix->print('1');
  matrix->setTextColor(matrix->color444(0,4,7));
  matrix->print('8');
  matrix->setTextColor(matrix->color444(0,0,7));
  matrix->print('4');
  matrix->setTextColor(matrix->color444(4,0,7));
  matrix->print('4');
  matrix->setTextColor(matrix->color444(7,0,4));
  matrix->print('5');
  matrix->setTextColor(matrix->color444(7,0,4));
  matrix->print('1');
}

void LedPannel::print_exam_6(void)
{
  // fill the screen with 'black'
  matrix->fillScreen(matrix->color444(0, 0, 0));
  // draw some text!
  matrix->setTextSize(1);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  
  matrix->setCursor(8, 0);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  char str[] = "http://www.k-amd.com/";
  for (w=0; w<8; w++) {
    matrix->setTextColor(Wheel(matrix, w));
    matrix->print(str[w]);
  }
  matrix->setCursor(2, 8);    // next line
  for (w=8; w<18; w++) {
    matrix->setTextColor(Wheel(matrix, w));
    matrix->print(str[w]);
  }
  matrix->println();
  
  //matrix->setTextColor(matrix->color444(7,7,7));
  //matrix->println("LED MATRIX!");
}

void LedPannel::print_exam_7(void)
{
  // fill the screen with 'black'
  matrix->fillScreen(matrix->color444(0, 0, 0));
  // draw some text!
  matrix->setTextSize(1);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  
  matrix->setCursor(5, 0);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  int len1;
  char str[] = "WelcometoOurCompany";
  len1 = strlen(str);
  for (w=0; w<len1; w++) 
  {
    if(w == 9) matrix->println();
    matrix->setTextColor(Wheel(matrix, w));
    matrix->print(str[w]);  
  }
  matrix->println();
  matrix->setTextColor(matrix->color444(7,7,7));
  matrix->println("Lunch Time");
  //matrix->println("Call me");
  
  //print_phone_num();  
}

void LedPannel::print_exam_8(void)
{
  // fill the screen with 'black'
  matrix->fillScreen(matrix->color444(0, 0, 0));
  // draw some text!
  matrix->setTextSize(1);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  
  matrix->setCursor(3, 5);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  int len1;
  char str[] = "Lunch Time";
  len1 = strlen(str);
  for (w=0; w<len1; w++) 
  {
    matrix->setTextColor(Wheel(matrix, w));
    matrix->print(str[w]);  
  }
  matrix->println();
  matrix->println();
  //print_phone_num();  
}

void LedPannel::print_exam_9(void)
{
  // fill the screen with 'black'
  //matrix->fillScreen(matrix->color444(0, 0, 0));
  matrix->fillScreen(0);
  // draw some text!
  matrix->setTextSize(2);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  
  matrix->setCursor(8, 2);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  int len1;
  char str[] = "Baby On Board";
  len1 = strlen(str);
  for (w=0; w<len1; w++) 
  {
    if(w == 5) {
      matrix->println();
      matrix->setTextSize(1);     // size 1 == 8 pixels high
      matrix->setCursor(8, 17);    // start at top left, with 8 pixel of spacing
      delay(1000);
    }
    matrix->setTextColor(Wheel(matrix, w));
    matrix->print(str[w]);  
  }
  matrix->println();
  matrix->println();
  ////print_phone_num();
}

void LedPannel::print_exam_10(void)
{
  
  // print each letter with a rainbow color
  matrix->setTextColor(matrix->color444(7,0,0));
  matrix->print('0');
  matrix->setTextColor(matrix->color444(7,4,0));
  matrix->print('1');
  matrix->setTextColor(matrix->color444(7,7,0));
  matrix->print('0');

  matrix->setTextColor(matrix->color444(4,7,0));
  matrix->print('4');
  matrix->setTextColor(matrix->color444(0,7,0));
  matrix->print('4');
  matrix->setTextColor(matrix->color444(0,7,7));
  matrix->print('1');
  matrix->setTextColor(matrix->color444(0,4,7));
  matrix->print('8');
  
  matrix->setTextColor(matrix->color444(0,0,7));
  matrix->print('4');
  matrix->setTextColor(matrix->color444(4,0,7));
  matrix->print('4');
  matrix->setTextColor(matrix->color444(7,0,4));
  matrix->print('5');
  matrix->setTextColor(matrix->color444(7,0,4));
  matrix->print('1');  
}

void LedPannel::print_exam_11(void)
{
  for (int i=0; i<3; i++) {
    matrix->setTextSize(2);  
    matrix->setCursor(5, 5);
    
    // print each letter with a rainbow color
    matrix->setTextColor(matrix->color444(7,0,0));
    matrix->print('0');
    matrix->setTextColor(matrix->color444(7,4,0));
    matrix->print('1');
    matrix->setTextColor(matrix->color444(7,7,0));
    matrix->print('0');
    delay(2000);      
    matrix->fillScreen(0);
  
    matrix->setCursor(5, 5);
    matrix->setTextColor(matrix->color444(4,7,0));
    matrix->print('3');
    matrix->setTextColor(matrix->color444(0,7,0));
    matrix->print('2');
    matrix->setTextColor(matrix->color444(0,7,7));
    matrix->print('4');
    matrix->setTextColor(matrix->color444(0,4,7));
    matrix->print('7');
    delay(2000); 
    matrix->fillScreen(0);
  
    matrix->setCursor(5, 5);
    matrix->setTextColor(matrix->color444(0,0,7));
    matrix->print('2');
    matrix->setTextColor(matrix->color444(4,0,7));
    matrix->print('7');
    matrix->setTextColor(matrix->color444(7,0,4));
    matrix->print('3');
    matrix->setTextColor(matrix->color444(7,0,4));
    matrix->print('4');  
    delay(2000);      
    matrix->fillScreen(0);
  }
}

void LedPannel::print_exam_12(void)
{

  
  // fill the screen with 'black'
  matrix->fillScreen(matrix->color444(0, 0, 0));
  
  // draw some text!
  matrix->setTextSize(1);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves

  matrix->setCursor(8, 0);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  char str[] = "P3indoorSMDDisplay";
  for (w=0; w<8; w++) {
    matrix->setTextColor(Wheel(matrix, w));
    matrix->print(str[w]);
  }
  matrix->setCursor(2, 8);    // next line
  for (w=8; w<18; w++) {
    matrix->setTextColor(Wheel(matrix, w));
    matrix->print(str[w]);
  }
  matrix->println();
  //matrix->setTextColor(matrix->color444(4,4,4));
  //matrix->println("Industries");
  matrix->setTextColor(matrix->color444(5,5,5));
  matrix->println("LED MATRIX!");
  
  // print each letter with a rainbow color
  matrix->setTextColor(matrix->color444(5,0,0));
  matrix->print('3');
  matrix->setTextColor(matrix->color444(5,4,0)); 
  matrix->print('2');
  matrix->setTextColor(matrix->color444(5,5,0));
  matrix->print('x');
  matrix->setTextColor(matrix->color444(8,5,0)); 
  matrix->print('6');
  matrix->setTextColor(matrix->color444(0,5,0));  
  matrix->print('4');
  matrix->setCursor(34, 24);  
  matrix->setTextColor(matrix->color444(0,5,5)); 
  matrix->print("*");
  matrix->setTextColor(matrix->color444(0,8,5)); 
  matrix->print('R');
  matrix->setTextColor(matrix->color444(0,0,5));
  matrix->print('G');
  matrix->setTextColor(matrix->color444(8,0,5)); 
  matrix->print("B");
  matrix->setTextColor(matrix->color444(5,0,8)); 
  matrix->println("*");
}
