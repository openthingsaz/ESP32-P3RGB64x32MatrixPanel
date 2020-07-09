#ifndef _COMMAND_
#define _COMMAND_

#define SET_DRAW 0x11
#define SET_TEXT 0x21
#define SET_TEXT_ACTION 0x22
#define SET_SCR_CLEAR 0x31
#define SET_SCR_COLOR 0x41
#define SET_TEXT_ONE           0x51
#define SET_TEXT_ONE_ACTION    0x52
#define SET_FIRM_UPDATE         0x61
#define GET_BOARD_INFO          0x91
#define SET_EXAM 0x81

#define CMD_ACT_LEFT_RIGHT 0x01
#define CMD_ACT_RIGHT_LEFT 0x02
#define CMD_ACT_TOP_DOWN  0x03
#define CMD_ACT_DOWN_TOP  0x04
#define CMD_ACT_BLINK  0x05

#endif
