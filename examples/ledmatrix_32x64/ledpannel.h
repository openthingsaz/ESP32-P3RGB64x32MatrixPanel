#ifndef _LEDPANNEL_
#define _LEDPANNEL_

#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>

class LedPannel {
private:
    P3RGB64x32MatrixPanel* matrix;
    uint8_t ser_recev_len2;
    char temp2[100];

public:
    void setup(P3RGB64x32MatrixPanel* mat);
    void scoll_text(char* data, uint8_t ser_recev_len);
    void print_exam_1(void);
    void print_exam_2(void);
    void print_exam_3(void);
    void print_exam_4(void);
    void print_exam_5(void);
    void print_exam_6(void);
    void print_exam_7(void);
    void print_exam_8(void);
    void print_exam_9(void);
    void print_exam_10(void);
    void print_exam_11(void);
    void print_exam_12(void);
};

#endif
