#ifndef _WIN_UART_H_
#define _WIN_UART_H_

#ifdef WIN32
#include <windows.h>
#endif

void Uart_Init();
void Uart_RecvData();
void Uart_SendData();

#define MAX_DEVICE_BUFFER_SIZE 1024



#endif