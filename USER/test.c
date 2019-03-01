#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "lcd.h"	   
#include "rtc.h"
#include "wkup.h"
#include "adc.h"
#include "dma.h"
#include "24cxx.h"
#include "flash.h"
#include "touch.h" 	  
#include "power.h" 
	   			
void Load_Drow_Dialog(void)
{
	POINT_COLOR=GREEN;//设置字体为绿色	
	LCD_Clear(BLACK);  //液晶屏背景为黑色
	face_display();
}	
		  
int main(void)
{	
	u8 key;
	u8 i=0;	
 	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,4800); //串口1初始化  
	Timerx_Init(10000,7199);//10Khz的计数频率，计数到10000为500ms  	  
	LCD_Init();			//初始化液晶		  
	KEY_Init();			//按键初始化
	LED_Init();         //LED初始化

 	POINT_COLOR=GREEN;//设置字体为蓝色	
	LCD_Clear(BLACK);  //液晶屏背景为黑色
	
	Touch_Init();	  //触摸屏初始化
	JTAG_Set(JTAG_SWD_DISABLE);	
    face_display();	   //界面显示
	while(1)
	{	//******************************************************************
	
	
	   	face_display();	   //界面显示	
	   	Analysis_data();   //解析数据

	   	data_display();		//数据显示

	 	key=KEY_Scan();
	
		if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
		{
			Pen_Int_Set(0);//关闭中断
			Pen_Point.Key_Sta=Key_Up;
			do
			{
				Convert_Pos();
				
				if(((Pen_Point.X0>60)&&(Pen_Point.X0<180))&&((Pen_Point.Y0>245)&&(Pen_Point.Y0<290)))
				{
				    clear_data();	  //触摸屏清零
				   	LCD_Fill(60,245,180,290,YELLOW);	  //清零按键按下显示为黄色
					BACK_COLOR=YELLOW;
						POINT_COLOR=RED;
					Test_Show_CH_Font24(90,255,9,RED);		//清零
					Test_Show_CH_Font24(124,255,10,RED);
				}					
				else 
				{
					PEN=1;
					delay_ms(10);	    
					GPIOC->ODR|=1<<1;    //PC1 上拉	   
				}

			}while(PEN==0);//如果PEN一直有效,则一直执行
			Pen_Int_Set(1);//开启中断
		}
		else
		{ 
			delay_ms(10);
			LCD_Fill(60,245,180,290,MAGENTA);	  //清零按键没有按下时正常显示。
			BACK_COLOR=MAGENTA;
			POINT_COLOR=RED;
		Test_Show_CH_Font24(90,255,9,RED);		
			Test_Show_CH_Font24(124,255,10,RED);

		}
		if(key==1)//KEY0按下,则执行校准程序
		{
			LCD_Clear(WHITE);//清屏
		    //Touch_Adjust();  //屏幕校准 
			Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		if(key==2)	 //	KEY1按下，也可清零。
		{
		   	clear_data();
			delay_ms(10);
		}
		i++;
		if(i==20)
		{
			i=0;
			LED1=!LED1;
	
	  delay_ms(200);
	}
delay_ms(20);		   		  
}


}				 






