#ifndef __USART_H
#define __USART_H
#include <stm32f10x_lib.h>
#include "stdio.h"	 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/5/27
//�汾��V1.3
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
////////////////////////////////////////////////////////////////////////////////// 	 

#define EN_USART1_RX //ʹ�ܴ���1���� 

typedef struct {
 vu8 bRxLength;				  // �Ѿ����յ����ݳ���
 vu8 bTxLength;				  // �Ѿ����͵����ݳ���
 vu8 bTxBufferLength;			  // ���ͻ������е����ݳ���
 u8 bRxBuffer[18];	  // �������ݻ�����
 u8 bTxBuffer[18];	  // �������ݻ�����
}UART_Buffer;
extern UART_Buffer USART1_Buf;

typedef union  { 
	unsigned int word16; 
    unsigned char byte[2]; 
}CRC_C; 
extern CRC_C crcnow;	  	
extern u8 USART_RX_BUF[64];     //���ջ���,���63���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART_TX_BUF[64];
extern u8 USART_RX_STA;         //����״̬���	
extern u8 USART1_ReFlag;

//����봮���жϽ��գ��벻Ҫע�����º궨��

void uart_init(u32 pclk2,u32 bound);
extern unsigned int chkcrc(unsigned char *buf,unsigned char len);
extern void USART1_SendStr(u8 *str, u8 nCount);
#endif	   
















