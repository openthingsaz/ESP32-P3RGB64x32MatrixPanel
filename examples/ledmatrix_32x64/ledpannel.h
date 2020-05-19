#ifndef _LEDPANNEL_
#define _LEDPANNEL_

#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>

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

    void set_action_off(void);
    uint16_t get_display_width(void);
    void command_excute(void);
    void print_exam_1(void);
    void print_exam_2(void);
    void print_exam_3(void);
    void print_exam_4(void);
    void print_exam_5(void);
    void print_exam_6(void);
    void print_exam_7(void);
    void print_exam_8(void);
};

#endif
