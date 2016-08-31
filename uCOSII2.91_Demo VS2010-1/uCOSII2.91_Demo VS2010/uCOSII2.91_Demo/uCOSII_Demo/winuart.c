#include "uart.h"
#include "uartdef.h"
#include "winuart.h"


// Ĭ�����ô���
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
						0,                                      //��ռ��ʽ
						0,
						OPEN_EXISTING, 
						0,                                      //ͬ����ʽ
						0);

	if(INVALID_HANDLE_VALUE == mPort)
	{
		return FALSE;
	}

	//���뻺����������������Ĵ�С����1024
	SetupComm(mPort,MAX_DEVICE_BUFFER_SIZE,MAX_DEVICE_BUFFER_SIZE); 

	//�趨����ʱ
	//�ڶ�һ�����뻺���������ݺ���������������أ��������Ƿ������Ҫ����ַ���
	TimeOuts.ReadIntervalTimeout            = 0xffffffff;
	TimeOuts.ReadTotalTimeoutMultiplier     = 0;
	TimeOuts.ReadTotalTimeoutConstant       = 0;

	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier    = 100;
	TimeOuts.WriteTotalTimeoutConstant      = 500;
	SetCommTimeouts(mPort, &TimeOuts);

	GetCommState(mPort, &dcb);
	dcb.BaudRate    = uartCfg.mBoardRate;                                       //������
	dcb.ByteSize    = uartCfg.mDataBits;                                        //ÿ���ֽ��м�λ
	dcb.Parity      = uartCfg.mBarity;                                          //��żУ��λ
	dcb.StopBits    = uartCfg.mStopBits;                                         //ֹͣλ
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