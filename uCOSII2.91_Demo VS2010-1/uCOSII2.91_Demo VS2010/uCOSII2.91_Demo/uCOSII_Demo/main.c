#include "SystemConfig.h"

#include "uart.h"
#include "uartdef.h"
#include "winuart.h"

/* �����ջ*/
OS_STK MainTask_Stk[MainTask_StkSize];
OS_STK App1Task_Stk[App1Task_StkSize];
OS_STK App2Task_Stk[App2Task_StkSize];

/* ������Ϣ����*/
OS_EVENT *KeyQEvent; 
void *Qstart[10];
char* str1 = "MainTask";
char* str2 = "App1Task";
char* str3 = "App2Task";
INT8U err;

int main(void)
{
	/* ϵͳ��ʼ��*/
	OSInit(); 

	/* ����������*/
	OSTaskCreate(MainTask, (void *)0, &MainTask_Stk[MainTask_StkSize-1], MainTask_Prio);
	OSTaskCreate(App1Task, (void *)0, &App1Task_Stk[App1Task_StkSize-1], App1Task_Prio);
	//OSTaskCreate(App2Task, (void *)0, &App2Task_Stk[App2Task_StkSize-1], App2Task_Prio);

	KeyQEvent = OSQCreate(&Qstart[0],10);

	OSStart(); /* ��ʼ�������*/
	return 0;
}

/* ������*/
void MainTask(void *p_arg)
{
	//p_arg = p_arg;
	//char* str = "MainTask Hello";

	//OSStatInit(); /* ͳ�������ʼ��*/

		while(1)
		{
			/* ������������*/
			//OSTaskCreate(App1Task, (void *)0, &App1Task_Stk[App1Task_StkSize-1], App1Task_Prio);
			//OSTaskCreate(App2Task, (void *)0, &App2Task_Stk[App2Task_StkSize-1], App2Task_Prio);

			OSQPost(KeyQEvent, str1);
			printf("MainTask Hello\n");
			OSTimeDlyHMSM(0,0,5,0); /* �������*/		
			//OSTaskDel(OS_PRIO_SELF); /* ɾ��������*/
		}
}

/* App1Task */
void App1Task(void *p_arg)
{
	char* temp = NULL;
	//p_arg = p_arg;


	while(1)
	{
		temp = OSQPend(KeyQEvent,0,&err);

		printf("%s\n",temp);

		printf("Hello,I am App1!\n");

		//OSTimeDlyHMSM(0, 0, 1, 0); /* �������*/
		//OSTaskDel(OS_PRIO_SELF); /* ɾ��������*/
	}
}

/* App2Task */
void App2Task(void *p_arg)
{
	//p_arg = p_arg;
	char* temp = NULL;

	//while(1)
	//{
		temp = OSQPend(KeyQEvent,0,&err);

		//printf("%s\n",temp);

		printf("Hello,I am App2!\n");

		//OSTimeDlyHMSM(0, 0, 1, 0); /* �������*/
		//OSTaskDel(OS_PRIO_SELF); /* ɾ��������*/
		//printf("Hello,uCOS-IIIIII!\n");
	//}
}