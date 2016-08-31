#ifndef _UART_DEF_H_
#define _UART_DEF_H_

//#include "MC_OS.h"
#include "Uart.h"

/*defines*/
#define     HICP_RECV_MAX               280
#define	    RECEIVE_BUF_LEN             6*HICP_RECV_MAX
#define	    SEND_BUF_LEN                6*HICP_RECV_MAX
#define     RX_ISR_BUF_LEN              300
#define     TX_ISR_BUF_LEN              300
#define     UART_MAX_NUMBER_SUPPORTED   50          // ÷ß≥÷÷ÿ÷√

/*enums*/
enum ENUM_VAL_CONVATE
{
	ENUM_VAL_CONVATE_2VAL,
	ENUM_VAL_CONVATE_2ENUM,

	ENUM_VAL_CONVATE_MAX,
};

/*struct*/
typedef struct {
	unsigned int nRateVal;
	UART_BOARD_RATE eRate;
}RATE_VAL_MAP;

typedef struct {
	unsigned int nBits;
	UART_TOTAL_BITS eBits;
}BITS_VAL_MAP;

typedef struct {
	unsigned int nBits;
	UART_STOP_BITS eBits;
}STOP_BITS_VAL_MAP;

typedef struct {
	unsigned int nVal;
	UART_PARITY eParity;
}PARITY_VAL_MAP;

#endif