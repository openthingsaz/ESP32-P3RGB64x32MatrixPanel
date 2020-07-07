#ifndef _LEDPANNEL_
#define _LEDPANNEL_

#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>

#define POINT1_NEXT_LINE_SIZE 12
#define POINT2_NEXT_LINE_SIZE 22
#define POINT3_NEXT_LINE_SIZE 32

class LedPannel {
private:
    P3RGB64x32MatrixPanel* matrix;
    uint8_t ser_recev_len2;
    char temp2[100];
    String scrollText;
    String blinkText;
    uint8_t displayTextLen;
    uint8_t displayTextSize;
    int displayFontColor;
    int displayColor;
    uint8_t displayStartX; 
    uint8_t displayStartY;
    uint8_t scrollCmd;
    uint16_t displayTime;

public:
    void setup(P3RGB64x32MatrixPanel* mat);
    void scroll_text(String text, uint8_t textFontSize, int fontColor, int scrColor, uint8_t startX, uint8_t startY, uint8_t cmd, uint16_t time);
    void set_scroll_text(String text, uint8_t textSize, int fontColor, int scrColor, uint8_t startX, uint8_t startY, uint8_t cmd, uint16_t time);
    void set_blink_text(String text, uint8_t textSize, int fontColor, int scrColor, uint8_t startX, uint8_t startY, uint8_t cmd, uint16_t time);
    void blink_text(String text, uint8_t textSize, int fontColor, int scrColor, uint8_t startX, uint8_t startY, uint8_t cmd, uint16_t time);
    void setupFont(uint8_t sel);
    void set_action_off(void);
    uint16_t get_disp_width(void);
    uint16_t get_disp_height(void);
    void command_excute(void);
    void print_exam_1(void);
    void print_exam_2(void);
    void print_exam_3(void);
    void print_exam_4(void);
    void print_exam_5(void);
    void print_exam_6(void);
    void print_exam_7(void);
    void print_exam_8(void);
    void print_exam_9(void);
    void print_exam_a(void);    
    void print_phone_num(void);
};

#endif
