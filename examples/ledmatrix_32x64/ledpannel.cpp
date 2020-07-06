#include "Arduino.h"
#include "ledpannel.h"
#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>
#include <Fonts/GodoM6pt8b.h>
#include "command.h"

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
void LedPannel::setupFont(uint8_t sel)
{
  if(sel == 0)
  {
    matrix->setFont(NULL);
    matrix->setTextSize(1);     // size 1 == 8 pixels high
    matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix->setAttribute(UTF8_ENABLE , false);
  }
  else if(sel == 1)
  {
    matrix->setFont(&GodoM6pt8b);  
    matrix->setTextSize(1);     // size 1 == 8 pixels high
    matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves

    matrix->setAttribute(UTF8_ENABLE , true);
  }
}
void LedPannel::setup(P3RGB64x32MatrixPanel* mat)
{
    matrix = mat;
    matrix->begin();
    // fill the screen with 'black'
    
}

uint16_t LedPannel::get_disp_width(void)
{
    return 64;
}

uint16_t LedPannel::get_disp_height(void)
{
    return 32;
}


void LedPannel::command_excute(void)
{
  if(scrollText.length() != 0)
    scroll_text(scrollText, displayTextSize, displayFontColor, displayColor, displayStartX, displayStartY, scrollCmd, displayTime);
  
  if(blinkText.length() != 0) {
    blink_text(blinkText, displayTextSize, displayFontColor, displayColor, displayStartX, displayStartY, scrollCmd, displayTime);
    Serial.print("blink text :"); Serial.println(blinkText);
  }

  //Serial.print("blink text :"); Serial.println(blinkText);

}


void LedPannel::set_blink_text(String text, uint8_t textSize, int fontColor, int scrColor, uint8_t startX, uint8_t startY, uint8_t cmd, uint16_t time)
{
    blinkText = text;
    displayTextSize = textSize;
    displayFontColor = fontColor;
    displayColor = scrColor;
    displayStartX = startX;
    displayStartY = startY;
    scrollCmd = cmd;
    displayTime = time;
}


void LedPannel::blink_text(String text, uint8_t textSize, int fontColor, int scrColor, uint8_t startX, uint8_t startY, uint8_t cmd, uint16_t time)
{
  uint8_t w = 0;
  int pos = 0;
  int tmp;
  uint8_t red;
  uint8_t green;
  uint8_t blue;

  red = (uint8_t)(scrColor >> 16);
  green = (uint8_t)(scrColor >> 8);
  blue = (uint8_t)(scrColor >> 0);
  matrix->fillScreen(matrix->color555(red, green, blue));
  Serial.print("Screen Color :"); Serial.print(red, HEX); Serial.print(" "); Serial.print(green, HEX); Serial.print(" "); Serial.print(blue, HEX); Serial.println(" ");
  matrix->setTextSize(textSize);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  
  Serial.print("Text Color :"); Serial.print(red, HEX); Serial.print(" "); Serial.print(green, HEX); Serial.print(" "); Serial.print(blue, HEX); Serial.println(" ");
  
  Serial.println("blink"); 
  for(int i=0; i<2; i++) 
  {
    red = (uint8_t)(scrColor >> 16);
    green = (uint8_t)(scrColor >> 8);
    blue = (uint8_t)(scrColor >> 0);
    matrix->fillScreen(matrix->color555(red, green, blue));
    matrix->setCursor(startX, startY);    // start at top left, with 8 pixel of spacing
    if(i == 0)
    {
      red = (uint8_t)(fontColor >> 16);
      green = (uint8_t)(fontColor >> 8);
      blue = (uint8_t)(fontColor >> 0);
      matrix->setTextColor(matrix->color555(red, green, blue));
      matrix->print(text);
    }
    else
    {
      red = 0;
      green = 0;
      blue = 0;
      matrix->setTextColor(matrix->color555(red, green, blue));
      matrix->print(text);
    }
    delay(time); 
  }
  
}


void LedPannel::set_scroll_text(String text, uint8_t textSize, int fontColor, int scrColor, uint8_t startX, uint8_t startY, uint8_t cmd, uint16_t time)
{
    scrollText = text;
    displayTextSize = textSize;
    displayFontColor = fontColor;
    displayColor = scrColor;
    displayStartX = startX;
    displayStartY = startY;
    scrollCmd = cmd;
    displayTime = time;
}
void LedPannel::set_action_off(void)
{
  scrollText = "";
  blinkText = "";
}

void LedPannel::scroll_text(String text, uint8_t textSize, int fontColor, int scrColor, uint8_t startX, uint8_t startY, uint8_t cmd, uint16_t time)
{
  uint8_t w = 0;
  int pos = 0;
  int tmp;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t textLen;

  textLen = text.length();
  red = (uint8_t)(scrColor >> 16);
  green = (uint8_t)(scrColor >> 8);
  blue = (uint8_t)(scrColor >> 0);
  matrix->fillScreen(matrix->color555(red, green, blue));
  Serial.print("Screen Color :"); Serial.print(red, HEX); Serial.print(" "); Serial.print(green, HEX); Serial.print(" "); Serial.print(blue, HEX); Serial.println(" ");
  matrix->setTextSize(textSize);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  red = (uint8_t)(fontColor >> 16);
  green = (uint8_t)(fontColor >> 8);
  blue = (uint8_t)(fontColor >> 0);
  matrix->setTextColor(matrix->color555(red, green, blue));
  Serial.print("Text Color :"); Serial.print(red, HEX); Serial.print(" "); Serial.print(green, HEX); Serial.print(" "); Serial.print(blue, HEX); Serial.println(" ");
 if(cmd == CMD_ACT_RIGHT_LEFT)
 {
    for(pos=startX; pos >= -((textLen * 4)*textSize); pos--) 
    {
      red = (uint8_t)(scrColor >> 16);
      green = (uint8_t)(scrColor >> 8);
      blue = (uint8_t)(scrColor >> 0);
      matrix->fillScreen(matrix->color555(red, green, blue));
      matrix->setCursor(pos, startY);    // start at top left, with 8 pixel of spacing
      for(int i=0; i<textLen; i++)
      {
        matrix->print(text[i]);
      }
      delay(time); 
    }
 }
 else if(cmd == CMD_ACT_LEFT_RIGHT)
 {
   for(pos=-((textLen * 4)*textSize); pos <= startX; pos++) 
   {
      red = (uint8_t)(scrColor >> 16);
      green = (uint8_t)(scrColor >> 8);
      blue = (uint8_t)(scrColor >> 0);
      matrix->fillScreen(matrix->color555(red, green, blue));
      matrix->setCursor(pos, startY);    // start at top left, with 8 pixel of spacing
      for(int i=0; i<textLen; i++)
      {
        matrix->print(text[i]);
      }
      delay(time); 
   }
 }
 else if(cmd == CMD_ACT_TOP_DOWN)
 {
    for(pos=startY; pos <= (32 + (textSize * 8)); ++pos) 
    {
      red = (uint8_t)(scrColor >> 16);
      green = (uint8_t)(scrColor >> 8);
      blue = (uint8_t)(scrColor >> 0);
      matrix->fillScreen(matrix->color555(red, green, blue));
      matrix->setCursor(startX, pos);    // start at top left, with 8 pixel of spacing
      for(int i=0; i<textLen; i++)
      {
        matrix->print(text[i]);
      }
      delay(time); 
    }
 }
 else if(cmd == CMD_ACT_DOWN_TOP)
 {
    for(pos=startY; pos >= -(textSize * 8); --pos) 
    {
      red = (uint8_t)(scrColor >> 16);
      green = (uint8_t)(scrColor >> 8);
      blue = (uint8_t)(scrColor >> 0);
      matrix->fillScreen(matrix->color555(red, green, blue));
      matrix->setCursor(startX, pos);    // start at top left, with 8 pixel of spacing
      for(int i=0; i<textLen; i++)
      {
        matrix->print(text[i]);
      }
      delay(time); 
    }
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
    delay(300);
    
    matrix->print(str[w]);  
  }
  matrix->println();
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
  for (int i=0; i<3; i++) 
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

void LedPannel::print_phone_num(void)
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


void LedPannel::print_exam_5(void)
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

void LedPannel::print_exam_6(void)
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
  print_phone_num();  
}

void LedPannel::print_exam_7(void)
{
  // draw a pixel in solid white
  matrix->drawPixel(0, 0, matrix->color444(15, 15, 15)); 
  delay(500);

  // fix the screen with green
  matrix->fillRect(0, 0, matrix->width(), matrix->height(), matrix->color444(0, 15, 0));
  delay(500);

  // draw a box in yellow
  matrix->drawRect(0, 0, matrix->width(), matrix->height(), matrix->color444(15, 15, 0));
  delay(500);
  
  // draw an 'X' in red
  matrix->drawLine(0, 0, matrix->width()-1, matrix->height()-1, matrix->color444(15, 0, 0));
  matrix->drawLine(matrix->width()-1, 0, 0, matrix->height()-1, matrix->color444(15, 0, 0));
  delay(500);
  
  // draw a blue circle
  matrix->drawCircle(10, 10, 10, matrix->color444(0, 0, 15));
  delay(500);
  
  // fill a violet circle
  matrix->fillCircle(40, 21, 10, matrix->color444(15, 0, 15));
  delay(500);
}



void LedPannel::print_exam_8(void) // japan language hiragana
{
  uint8_t w = 0;
  char ch[32]={0};
  int len;
  char str[] = "가천대 화이팅^^";

  matrix->setTextSize(1);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix->setTextColor(matrix->color444(7, 0, 0));
  matrix->setAttribute(UTF8_ENABLE , true);

  matrix->setCursor(10, 12);
  len = strlen(str);
  for (w=0; w<len; w++) 
  {
    if(w == 10) {
      matrix->println();
      matrix->setCursor(6, 27);    // start at top left, with 8 pixel of spacing
    }
    matrix->setTextColor(Wheel(matrix, w));
    //delay(500);  
    matrix->print(str[w]);  
  }
  matrix->println();
  
}

void LedPannel::print_exam_9(void)
{
  uint8_t w = 0;
  int len;
  char str[] = "SNIP";
  char str2[] = "nice to meet you.";
  
  // fill the screen with 'black'
  matrix->fillScreen(matrix->color444(0, 0, 0));
  // draw some text!
  matrix->setTextSize(2);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix->setCursor(8, 2);    // start at top left, with 8 pixel of spacing
  
  len = strlen(str);
  for (w=0; w<len; w++) 
  {
    matrix->setTextColor(Wheel(matrix, w));
    delay(300); 
    matrix->print(str[w]);  
  }
  matrix->println();

  matrix->setTextSize(1);     // size 1 == 8 pixels high
  matrix->setCursor(8, 17);    // start at top left, with 8 pixel of spacing  
  len = strlen(str2);
  for (w=0; w<len; w++) 
  {
    matrix->setTextColor(Wheel(matrix, w));
    delay(300);  
    matrix->print(str2[w]);  

    if(w == 7) {
      matrix->setCursor(5, 24);
      //matrix->println();
      //matrix->setCursor(6, 27);    // start at top left, with 8 pixel of spacing
    }
  }


}



void LedPannel::print_exam_a(void)
{
  // fill the screen with 'black'
  matrix->fillScreen(matrix->color444(0, 0, 0));
  // draw some text!
  matrix->setTextSize(1);     // size 1 == 8 pixels high
  matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  
  matrix->setCursor(5, 10);    // start at top left, with 8 pixel of spacing

   String someText = "SomeText";//generated by a method
   matrix->println(someText);
    int16_t x1, y1;
    uint16_t w1, h1; 
    matrix->getTextBounds(someText , 0, 0, &x1, &y1, &w1, &h1);//error here


    Serial.print("x1 : "); Serial.println(x1);
    Serial.print("y1 : "); Serial.println(y1);
    Serial.print("w1 : "); Serial.println(w1);
    Serial.print("h1 : "); Serial.println(h1);
  //print_phone_num();  
}