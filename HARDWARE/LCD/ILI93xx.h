#ifndef __ILI93XX_H__
#define __ILI93XX_H__
#include "sys.h"
#include "ili93xx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ili93xx ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2010/6/13 
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
extern u16 POINT_COLOR;
extern u16 BACK_COLOR;
//extern void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
extern void Draw_Circle(u16 x0,u16 y0,u8 r);
//extern LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);
extern void LCD_DrawPoint(u16 x,u16 y);
extern u32 mypow(u8 m,u8 n);
extern void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
extern void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len,u8 size,u8 mode);
extern void LCD_ShowString(u16 x,u16 y,const u8 *p);
extern void Test_Show_CHAR_Font48(u16 x,u16 y,u8 index,u16 color);
#endif

