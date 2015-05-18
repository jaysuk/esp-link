#ifndef __SER_BRIDGE_H__
#define __SER_BRIDGE_H__

#include <ip_addr.h>
#include <c_types.h>
#include <espconn.h>

#define MAX_CONN 5
#define SER_BRIDGE_TIMEOUT 28799

//Max send buffer len
#define MAX_TXBUFFER 1024

typedef struct serbridgeConnData serbridgeConnData;

enum connModes {
	cmInit = 0,        // initialization mode: nothing received yet
	cmTransparent,     // transparent mode
	cmAVR,             // Arduino/AVR programming mode
	cmARM,             // ARM (LPC8xx) programming
	cmEcho,            // simply echo characters (used for debugging latency)
	cmCommand,         // AT command mode
};

struct serbridgeConnData {
	struct espconn *conn;
	enum connModes conn_mode;   // connection mode
	char           *txbuffer;   // buffer for the data to send
	uint16         txbufferlen; // length of data in txbuffer
	bool           readytosend; // true, if txbuffer can send by espconn_sent
	uint8          skip_chars;  // number of chars to skip from uart, used in Arduino reset sequence
};

void ICACHE_FLASH_ATTR serbridgeInit(int port);
void ICACHE_FLASH_ATTR serbridgeUartCb(char *buf, int len);

#endif /* __SER_BRIDGE_H__ */
