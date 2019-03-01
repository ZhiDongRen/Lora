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
	POINT_COLOR=GREEN;//��������Ϊ��ɫ	
	LCD_Clear(BLACK);  //Һ��������Ϊ��ɫ
	face_display();
}	
		  
int main(void)
{	
	u8 key;
	u8 i=0;	
 	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,4800); //����1��ʼ��  
	Timerx_Init(10000,7199);//10Khz�ļ���Ƶ�ʣ�������10000Ϊ500ms  	  
	LCD_Init();			//��ʼ��Һ��		  
	KEY_Init();			//������ʼ��
	LED_Init();         //LED��ʼ��

 	POINT_COLOR=GREEN;//��������Ϊ��ɫ	
	LCD_Clear(BLACK);  //Һ��������Ϊ��ɫ
	
	Touch_Init();	  //��������ʼ��
	JTAG_Set(JTAG_SWD_DISABLE);	
    face_display();	   //������ʾ
	while(1)
	{	//******************************************************************
	
	
	   	face_display();	   //������ʾ	
	   	Analysis_data();   //��������

	   	data_display();		//������ʾ

	 	key=KEY_Scan();
	
		if(Pen_Point.Key_Sta==Key_Down)//������������
		{
			Pen_Int_Set(0);//�ر��ж�
			Pen_Point.Key_Sta=Key_Up;
			do
			{
				Convert_Pos();
				
				if(((Pen_Point.X0>60)&&(Pen_Point.X0<180))&&((Pen_Point.Y0>245)&&(Pen_Point.Y0<290)))
				{
				    clear_data();	  //����������
				   	LCD_Fill(60,245,180,290,YELLOW);	  //���㰴��������ʾΪ��ɫ
					BACK_COLOR=YELLOW;
						POINT_COLOR=RED;
					Test_Show_CH_Font24(90,255,9,RED);		//����
					Test_Show_CH_Font24(124,255,10,RED);
				}					
				else 
				{
					PEN=1;
					delay_ms(10);	    
					GPIOC->ODR|=1<<1;    //PC1 ����	   
				}

			}while(PEN==0);//���PENһֱ��Ч,��һֱִ��
			Pen_Int_Set(1);//�����ж�
		}
		else
		{ 
			delay_ms(10);
			LCD_Fill(60,245,180,290,MAGENTA);	  //���㰴��û�а���ʱ������ʾ��
			BACK_COLOR=MAGENTA;
			POINT_COLOR=RED;
		Test_Show_CH_Font24(90,255,9,RED);		
			Test_Show_CH_Font24(124,255,10,RED);

		}
		if(key==1)//KEY0����,��ִ��У׼����
		{
			LCD_Clear(WHITE);//����
		    //Touch_Adjust();  //��ĻУ׼ 
			Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		if(key==2)	 //	KEY1���£�Ҳ�����㡣
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






