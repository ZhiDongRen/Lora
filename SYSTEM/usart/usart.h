#ifndef __USART_H
#define __USART_H
#include <stm32f10x_lib.h>
#include "stdio.h"	 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/5/27
//版本：V1.3
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
////////////////////////////////////////////////////////////////////////////////// 	 

#define EN_USART1_RX //使能串口1接收 

typedef struct {
 vu8 bRxLength;				  // 已经接收的数据长度
 vu8 bTxLength;				  // 已经发送的数据长度
 vu8 bTxBufferLength;			  // 发送缓冲区中的数据长度
 u8 bRxBuffer[18];	  // 接收数据缓冲区
 u8 bTxBuffer[18];	  // 发送数据缓冲区
}UART_Buffer;
extern UART_Buffer USART1_Buf;

typedef union  { 
	unsigned int word16; 
    unsigned char byte[2]; 
}CRC_C; 
extern CRC_C crcnow;	  	
extern u8 USART_RX_BUF[64];     //接收缓冲,最大63个字节.末字节为换行符 
extern u8 USART_TX_BUF[64];
extern u8 USART_RX_STA;         //接收状态标记	
extern u8 USART1_ReFlag;

//如果想串口中断接收，请不要注释以下宏定义

void uart_init(u32 pclk2,u32 bound);
extern unsigned int chkcrc(unsigned char *buf,unsigned char len);
extern void USART1_SendStr(u8 *str, u8 nCount);
#endif	   
















