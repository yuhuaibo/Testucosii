#include "uart.h"
#include "uartdef.h"
#include "winuart.h"


// 默认配置串口
UART_CONFIG uartCfg;
HANDLE mPort;

int Uart_WinOpen();

void Uart_Init()
{
	uartCfg.mUartIndex = 1;
	uartCfg.mBoardRate = UART_BOARD_RATE_115200;
	uartCfg.mBarity = UART_PARITY_BITS_NO;
	uartCfg.mDataBits = UART_TOTAL_BITS_8;
	uartCfg.mStopBits = UART_STOP_BITS_1;
	uartCfg.mRecvMode = UART_RECV_ISR;
	uartCfg.mSensMode = UART_SEND_ISR;

	Uart_WinOpen();

}


int Uart_WinOpen()
{
	DCB dcb;
	COMMTIMEOUTS TimeOuts;

	char uartName[10] = "COM1";
	mPort = CreateFile(	uartName,									//COM?
						GENERIC_READ|GENERIC_WRITE, 
						0,                                      //独占方式
						0,
						OPEN_EXISTING, 
						0,                                      //同步方式
						0);

	if(INVALID_HANDLE_VALUE == mPort)
	{
		return FALSE;
	}

	//输入缓冲区和输出缓冲区的大小都是1024
	SetupComm(mPort,MAX_DEVICE_BUFFER_SIZE,MAX_DEVICE_BUFFER_SIZE); 

	//设定读超时
	//在读一次输入缓冲区的内容后读操作就立即返回，而不管是否读入了要求的字符。
	TimeOuts.ReadIntervalTimeout            = 0xffffffff;
	TimeOuts.ReadTotalTimeoutMultiplier     = 0;
	TimeOuts.ReadTotalTimeoutConstant       = 0;

	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier    = 100;
	TimeOuts.WriteTotalTimeoutConstant      = 500;
	SetCommTimeouts(mPort, &TimeOuts);

	GetCommState(mPort, &dcb);
	dcb.BaudRate    = uartCfg.mBoardRate;                                       //波特率
	dcb.ByteSize    = uartCfg.mDataBits;                                        //每个字节有几位
	dcb.Parity      = uartCfg.mBarity;                                          //奇偶校验位
	dcb.StopBits    = uartCfg.mStopBits;                                         //停止位
	SetCommState(mPort, &dcb);

	return 0;
}


VOID UartTask(VOID *param)
{
	DWORD	dwReaded	= 0;
	DWORD	dwWrited	= 0;
	BOOL	bReadStat	= FALSE;
	void*	pvData1;
	void*	pvData2;


	while(TRUE)
	{
		bReadStat = ReadFile(mPort, pvData1, 100, &dwReaded, 0);
		bReadStat = WriteFile(mPort, pvData2, 100, &dwWrited, 0);
	}
}