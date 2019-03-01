#ifndef __ILI93XX_H__
#define __ILI93XX_H__
#include "sys.h"
#include "ili93xx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//ili93xx 驱动函数	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2010/6/13 
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
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

