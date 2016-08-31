#include "SystemConfig.h"

#include "uart.h"
#include "uartdef.h"
#include "winuart.h"

/* 定义堆栈*/
OS_STK MainTask_Stk[MainTask_StkSize];
OS_STK App1Task_Stk[App1Task_StkSize];
OS_STK App2Task_Stk[App2Task_StkSize];

/* 定义消息队列*/
OS_EVENT *KeyQEvent; 
void *Qstart[10];
char* str1 = "MainTask";
char* str2 = "App1Task";
char* str3 = "App2Task";
INT8U err;

int main(void)
{
	/* 系统初始化*/
	OSInit(); 

	/* 创建主任务*/
	OSTaskCreate(MainTask, (void *)0, &MainTask_Stk[MainTask_StkSize-1], MainTask_Prio);
	OSTaskCreate(App1Task, (void *)0, &App1Task_Stk[App1Task_StkSize-1], App1Task_Prio);
	//OSTaskCreate(App2Task, (void *)0, &App2Task_Stk[App2Task_StkSize-1], App2Task_Prio);

	KeyQEvent = OSQCreate(&Qstart[0],10);

	OSStart(); /* 开始任务调度*/
	return 0;
}

/* 主任务*/
void MainTask(void *p_arg)
{
	//p_arg = p_arg;
	//char* str = "MainTask Hello";

	//OSStatInit(); /* 统计任务初始化*/

		while(1)
		{
			/* 创建其他任务*/
			//OSTaskCreate(App1Task, (void *)0, &App1Task_Stk[App1Task_StkSize-1], App1Task_Prio);
			//OSTaskCreate(App2Task, (void *)0, &App2Task_Stk[App2Task_StkSize-1], App2Task_Prio);

			OSQPost(KeyQEvent, str1);
			printf("MainTask Hello\n");
			OSTimeDlyHMSM(0,0,5,0); /* 任务调度*/		
			//OSTaskDel(OS_PRIO_SELF); /* 删除主任务*/
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

		//OSTimeDlyHMSM(0, 0, 1, 0); /* 任务调度*/
		//OSTaskDel(OS_PRIO_SELF); /* 删除主任务*/
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

		//OSTimeDlyHMSM(0, 0, 1, 0); /* 任务调度*/
		//OSTaskDel(OS_PRIO_SELF); /* 删除主任务*/
		//printf("Hello,uCOS-IIIIII!\n");
	//}
}