#include "Arduino.h"
#include "uart.h"

static const unsigned short crc16tab[256]= {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

uint16_t crc16_ccitt(uint8_t *buf, int len)
{
	int counter;
	unsigned short crc = 0;
	for( counter = 0; counter < len; counter++)
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(uint8_t *)buf++)&0x00FF];
	return crc;
}

void transmit_data(uint8_t cmd, uint8_t* data, uint32_t len)
{
  uint16_t crc = 0;
  uint32_t inx = 0;
  uint8_t* send_data;
  uint32_t cmd_data_len;

  send_data = (uint8_t*)malloc(len + 20);
  send_data[inx++] = STX;
  cmd_data_len = len + 1;
  memcpy(&send_data[1], &cmd_data_len, sizeof(cmd_data_len));
  memcpy(&send_data[3], &cmd_data_len, sizeof(cmd_data_len));
  inx = inx + 4;
  send_data[inx++] = cmd;
  memcpy(&send_data[6], data, len);
  inx = inx + len;
  crc = crc16_ccitt((uint8_t*)&send_data[5], cmd_data_len);
  send_data[inx++] = (crc & 0xFF00) >> 8;
  send_data[inx++] = (crc & 0x00FF);
  send_data[inx++] = ETX;
  //HAL_UART_Transmit(&huart2, send_data, inx , 100);
  free(send_data);
}

boolean BufferSerial::recv_callback(BluetoothSerial* pSerialBT)
{
  boolean ret = false;
  while(1)
  {
    if (pSerialBT->available())
    {
      buf[tail] = pSerialBT->read();
      ///Serial.print(buf[tail]);Serial.print(" ");
      if (MAX_SERIAL_BUF <= tail + 1)
        tail = 0;
      else
        tail++;
      ret = true;
    }
    else {
      //Serial.println("A");
      break;
    }
  }
  return ret;
}

void cmd_process(P3RGB64x32MatrixPanel* matrix, LedPannel* ledpannel, char cmd, char* data, int len)
{
  switch (cmd) {
    case SET_TEXT : 
    {
      int textLen = len-1-3-3; // -1 is font size, -3 is colorFont[3], -3 is colorScr[3], Only Text Box Data
      int textNullLen = textLen+1; /* For strings, +1 it must insert null at the end of the string. */
      char* textData = (char*)malloc(textNullLen);
      char colorFont[3]; 
      char colorScr[3];
      uint8_t fontSize = 0; 
      String textBoxData;

      
      memcpy(textData, data, textNullLen);
      textData[textLen] = 0;
      textBoxData = textData;
      fontSize = (uint8_t)data[textLen];
      memcpy(colorFont, data + textLen + sizeof(fontSize), sizeof(colorFont));
      memcpy(colorScr, data + textLen + sizeof(fontSize) + sizeof(colorFont), sizeof(colorScr));
      Serial.print("Text :"); Serial.println(textBoxData);
      Serial.print("Text Size:"); Serial.println(fontSize);
      Serial.print("Font Color :"); Serial.print(colorFont[0], HEX); Serial.print(" "); Serial.print(colorFont[1], HEX); Serial.print(" "); Serial.print(colorFont[2], HEX); Serial.print(" ");
      Serial.print("Scr Color :"); Serial.print(colorScr[0], HEX); Serial.print(" "); Serial.print(colorScr[1], HEX); Serial.print(" "); Serial.print(colorScr[2], HEX); Serial.println(" ");

      ledpannel->set_action_off(); /* scrolling text off */
      matrix->fillScreen(matrix->color555(colorScr[0], colorScr[1], colorScr[2]));
      matrix->setTextSize(fontSize);     // size 1 == 8 pixels high
      matrix->setTextWrap(false); // Don't wrap at end of line - will do ourselves
      matrix->setCursor(0, 15 - (fontSize * 3));    // start at top left, with 8 pixel of spacing
      matrix->setTextColor(matrix->color555(colorFont[0], colorFont[1], colorFont[2]));
      matrix->print(textBoxData);

      free(textData);
      break;
    }
    case SET_TEXT_ACTION : 
    {
      int textLen = len-1-3-3-3; // -1 is font size, -3 is colorFont[3], -3 is colorScr[3], -3 is Action Datas, Only Text Box Data
      int textNullLen = textLen+1; /* For strings, +1 it must insert null at the end of the string. */
      char* textData = (char*)malloc(textNullLen);
      char colorFont[3]; 
      char colorScr[3]; 
      int colorRgbFont;
      int colorRgbScr;
      char actionCmd; 
      uint8_t fontSize = 0; 
      unsigned short actionTime;


      String textBoxData;
      memcpy(textData, data, textNullLen);
      textData[textLen] = 0;
      textBoxData = textData;
      fontSize = (uint8_t)data[textLen];
      
      memcpy(colorFont, data + textLen + sizeof(fontSize), sizeof(colorFont));
      memcpy(colorScr, data + textLen + sizeof(fontSize) + sizeof(colorFont), sizeof(colorScr));
      actionCmd = data[textLen + sizeof(fontSize) + sizeof(colorFont) + sizeof(colorScr)];
      actionTime = actionTime | data[textLen + sizeof(fontSize) + sizeof(colorFont) + sizeof(colorScr) + 1] << 8;
      actionTime = actionTime | data[textLen + sizeof(fontSize) + sizeof(colorFont) + sizeof(colorScr) + 2];

      Serial.print("Text :"); Serial.println(textBoxData);
      Serial.print("Font Color :"); Serial.print(colorFont[0], HEX); Serial.print(" "); Serial.print(colorFont[1], HEX); Serial.print(" "); Serial.print(colorFont[2], HEX); Serial.println(" ");
      Serial.print("Scr Color :"); Serial.print(colorScr[0], HEX); Serial.print(" "); Serial.print(colorScr[1], HEX); Serial.print(" "); Serial.print(colorScr[2], HEX); Serial.println(" ");
      Serial.print("Action Command :"); Serial.println(actionCmd, DEC); 
      Serial.print("Action Time :"); Serial.println(actionTime, DEC); 

      //matrix->fillScreen(matrix->color444(0, 0, 0));
      // draw some text!
      colorRgbFont = (int)(colorFont[0] << 16 | colorFont[1] << 8 | colorFont[2]);
      colorRgbScr = (int)(colorScr[0] << 16 | colorScr[1] << 8 | colorScr[2]);
      ledpannel->set_action_off(); /* previous scrolling text off */
      if(actionCmd == CMD_ACT_RIGHT_LEFT)
        ledpannel->set_scroll_text(textBoxData, fontSize, colorRgbFont, colorRgbScr, ledpannel->get_display_width(), 15 - (fontSize * 3), CMD_ACT_RIGHT_LEFT, actionTime);        
      else if(actionCmd == CMD_ACT_LEFT_RIGHT)
        ledpannel->set_scroll_text(textBoxData, fontSize, colorRgbFont, colorRgbScr, ledpannel->get_display_width(), 15 - (fontSize * 3), CMD_ACT_LEFT_RIGHT, actionTime);
      else if(actionCmd == CMD_ACT_TOP_DOWN)
        ledpannel->set_scroll_text(textBoxData, fontSize, colorRgbFont, colorRgbScr, 5, 0, CMD_ACT_TOP_DOWN, actionTime);  
      else if(actionCmd == CMD_ACT_DOWN_TOP)
        ledpannel->set_scroll_text(textBoxData, fontSize, colorRgbFont, colorRgbScr, 5, 32, CMD_ACT_DOWN_TOP, actionTime);  
      else if(actionCmd == CMD_ACT_BLINK)
        ledpannel->set_blink_text(textBoxData, fontSize, colorRgbFont, colorRgbScr, 5, 15 - (fontSize * 3), CMD_ACT_BLINK, actionTime);

      free(textData);
      break;
    }
    case SET_DRAW : 
    {
      byte pointX;
      byte pointY;
      byte colorFont[3];
      int dataLen = len;
      char tempData[5];

      for(int i=0; i<(dataLen/5); i++)
      {
        memset(tempData, 0, sizeof(tempData));
        memcpy(tempData, data + (i*5), 5);
        pointX = (byte)tempData[0];
        pointY = (byte)tempData[1];
        memcpy(colorFont, tempData + sizeof(pointX) + sizeof(pointY), sizeof(colorFont));

        Serial.println("");
        Serial.print("dataLen : "); Serial.println(dataLen);
        Serial.print("Point X : "); Serial.println(pointX);
        Serial.print("Point Y : "); Serial.println(pointY);
        Serial.print("Font Color :"); Serial.print(colorFont[0], HEX); Serial.print(" "); Serial.print(colorFont[1], HEX); Serial.print(" "); Serial.print(colorFont[2], HEX); Serial.print(" "); 
        Serial.println("");
        matrix->drawPixel(pointX, pointY, matrix->color444(colorFont[0], colorFont[1], colorFont[2]));
      }
      break;
    }
    
    case SET_SCR_CLEAR : 
    {
      Serial.println("screen clear");
      matrix->fillScreen(matrix->color444(0, 0, 0)); 
      break;
    }
    case SET_SCR_COLOR : 
    {
      Serial.println("screen clolor");
      byte ScrColor[3];
      memcpy(ScrColor, data, sizeof(ScrColor));      
      matrix->fillScreen(matrix->color555(ScrColor[0], ScrColor[1], ScrColor[2])); 
      break;
    }
    case SET_EXAM : 
    {
      if (data[0] == 0x01){
        ledpannel->print_exam_1();
      }
      else if (data[0] == 0x02){
        ledpannel->print_exam_2();
      }
      else if (data[0] == 0x03){
        ledpannel->print_exam_3();
      }
      else if (data[0] == 0x04){
        ledpannel->print_exam_4();
      }
      else if (data[0] == 0x05){
        ledpannel->print_exam_5();
      }
      else if (data[0] == 0x06){
        ledpannel->print_exam_6();
      }
      else if (data[0] == 0x07){
        ledpannel->print_exam_7();
      }
      break;
    }
    default:
      Serial.println("default");
      break;
  }
}

void BufferSerial::process(P3RGB64x32MatrixPanel* matrix, LedPannel* ledpannel, BluetoothSerial* pSerialBT)
{ 
  uint16_t serCrc = 0;
  bool recv_end = false;
  char cmd;
  uint32_t data;
  uint8_t recv_step  = 0;
  uint16_t data_chk = 0;
  uint16_t data_chk2 = 0;
  uint8_t inx = 0;
  uint16_t dataLen = 0;
  uint16_t dataLen2 = 0;
  uint16_t dataLenTmp = 0;
  uint16_t crc_chk = 0;
  uint16_t crc = 0;
  

  if(recv_callback(pSerialBT) == true)
  {
    uint16_t serHead = 0;
    uint16_t serTail = 0;
    uint16_t serRxLen = 0;
    serHead = head;
    serTail = tail;  
  
    if (serHead != serTail) 
    {
      if (serHead <= serTail)
        serRxLen = serTail - serHead;
      else
        serRxLen = serTail + MAX_SERIAL_BUF - serHead;

      if (serRxLen)
      {
        for (int i=0; i<serRxLen; i++) 
        {
          if (recv_step == 0) {
            if (inx == 0 && buf[head+i] == STX) {
              recv_step = 1;
              dataLen = 0;
              data_chk = 0;
              inx = 0;
              continue;
            }
          }
          
          else if (recv_step == 1) {
            if (data_chk == 0) 
            {
              dataLen = buf[head+i];
              ++data_chk;
              continue;
            }
            
            else {
              dataLen = dataLen | (buf[head+i] << 8);
              dataLenTmp = dataLen;
              memset(packet, 0, sizeof(packet));
              data_chk = 0;
              recv_step = 2;
              continue;
            }
            
          }
          else if (recv_step == 2) {
            packet[inx++] = buf[head+i];
            --dataLenTmp;
            if (dataLenTmp == 0) {
              recv_step = 3;
              continue;
            }
          }
          else if (recv_step == 3) {
            packet[inx++] = buf[head+i];
            ++crc_chk;
            if (crc_chk >= 2) 
            {
              crc_chk = 0;
              recv_step = 4;
              continue;
            }
          }
          else if (recv_step == 4) 
          {
            if (buf[head+i] == ETX) {
              recv_end = true;
            }
            else {
              dataLen = 0;
              dataLenTmp = 0;
            }
            recv_step = 0;
            inx = 0;
          }
        }
        while (serRxLen--)
        {
          if (MAX_SERIAL_BUF <= head + 1)
          {
            head = 0;
          }
          else
          {
            head++;
          }
        }
        
        if (recv_end == true) 
        {
          crc = crc16_ccitt((uint8_t*)&packet[0], dataLen + 2); // + 2 is crc
          if (crc == 0) // Crc OK
          {
            cmd = packet[0];
            cmd_process(matrix, ledpannel, cmd, &packet[1], dataLen-1); // -1 is command
          }
          else {
            //send NACK
            buf[0] = NCK;
            //HAL_UART_Transmit(&huart2, SerialTx.buf, 1, 1);
            Serial.println("NACK");
          }
          dataLen = 0;
          inx = 0;
        }
      }
    }
  }
}
