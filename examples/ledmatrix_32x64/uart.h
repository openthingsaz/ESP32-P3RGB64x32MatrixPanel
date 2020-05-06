#ifndef _SERIAL_
#define _SERIAL_

#include "BluetoothSerial.h"

#define MAX_SERIAL_BUF 1024
#define PACKET_SIZE (9*1024)+20 // 9Kbyte + 20byte
#define STX 0x02
#define ETX 0x03
//#define ACK 0x06
#define NCK 0x15
#define SET_DRAW 0x11
#define SET_TEX 0x21


class BufferSerial {
private:
	uint8_t  buf[MAX_SERIAL_BUF];
	uint16_t head;
	uint16_t tail;
	char packet[PACKET_SIZE];
	boolean recv_callback(BluetoothSerial* pSerialBT);
public:
	BufferSerial(){
  		memset(buf, 0, sizeof(buf));
		head = 0;
		tail = 0;
	}
	void process(BluetoothSerial* pSerialBT);
	

};

#endif
