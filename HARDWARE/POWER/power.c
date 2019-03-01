#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "ILI93xx.h"


u16 Voltage_data;  //��ѹ
u16 Current_data;  //����
u16 Power_data;   //����
u32 Energy_data;   //����
u16 Pf_data;       //����
//������ʾ
void face_display(void)
{
   	BACK_COLOR=BLACK;	   //���屳����ɫ

	Test_Show_CH_Font24(30,30,11,RED);		//��ǰ�����
	Test_Show_CH_Font24(60,30,12,RED);
	Test_Show_CH_Font24(90,30,13,RED);
	Test_Show_CH_Font24(120,30,14,RED);
	Test_Show_CH_Font24(150,30,15,RED);
	Test_Show_CH_Font24(180,30,16,RED);

	//GUI_DrawFont24(10, 70, BLACK, GREEN, "����",0);
	Test_Show_CH_Font24(10,70,0,GREEN);	   //��ѹ
	Test_Show_CH_Font24(34,70,1,GREEN);
	LCD_ShowString(60,73,":");

	Test_Show_CH_Font24(10,105,0,GREEN);	//����
	Test_Show_CH_Font24(34,105,2,GREEN);
	LCD_ShowString(60,108,":");
	
	Test_Show_CH_Font24(10,140,3,GREEN);	//����
	Test_Show_CH_Font24(34,140,4,GREEN);
	LCD_ShowString(60,143,":");
	
	Test_Show_CH_Font24(10,175,5,GREEN);	//����
	Test_Show_CH_Font24(34,175,6,GREEN);
	LCD_ShowString(60,178,":");	

	Test_Show_CH_Font24(10,210,0,GREEN);		//����
	Test_Show_CH_Font24(34,210,7,GREEN);
	LCD_ShowString(60,213,":");

	LCD_Fill(60,245,180,290,MAGENTA);
	BACK_COLOR=MAGENTA;
	POINT_COLOR=RED;
	Test_Show_CH_Font24(90,255,9,RED);		//����
	Test_Show_CH_Font24(124,255,10,RED);
}
//��ȡ��ѹ�����������ʣ����غ͵���ֵ
void read_data(void) 
{ 
     //   if((Clock.Second%2)==1)      //2 ���һ�� 
        {       
			USART_TX_BUF[0]=0x01;      //����ģ��� ID ��   
            USART_TX_BUF[1]=0x03; 
            USART_TX_BUF[2]=0x00; 
            USART_TX_BUF[3]=0x48; 
            USART_TX_BUF[4]=0x00; 
            USART_TX_BUF[5]=0x06; 
            crcnow.word16=chkcrc(USART_TX_BUF,6); 
            USART_TX_BUF[6]=crcnow.byte[1];        //CRC Ч����ֽ���ǰ 
            USART_TX_BUF[7]=crcnow.byte[0]; 
            USART1_SendStr(USART_TX_BUF,8);      //���� 8 �����ݣ�

        } 
}
//�������ֵ
void clear_data(void)
{
			USART_TX_BUF[0]=0x01;      //����ģ��� ID ��   
            USART_TX_BUF[1]=0x10; 
            USART_TX_BUF[2]=0x00; 
            USART_TX_BUF[3]=0x0C; 
            USART_TX_BUF[4]=0x00; 
            USART_TX_BUF[5]=0x02; 
			USART_TX_BUF[6]=0x04;
			USART_TX_BUF[7]=0x00;
			USART_TX_BUF[8]=0x00;
			USART_TX_BUF[9]=0x00;
			USART_TX_BUF[10]=0x00;
            crcnow.word16=chkcrc(USART_TX_BUF,11); 
            USART_TX_BUF[11]=crcnow.byte[1];        //CRC Ч����ֽ���ǰ 
            USART_TX_BUF[12]=crcnow.byte[0]; 
            USART1_SendStr(USART_TX_BUF,13);      //���� 13 �����ݣ�
} 
void Analysis_data(void) 
{ 
	unsigned char i; 
    if(USART1_ReFlag==0x01)    //������� 
    { 
		USART1_ReFlag=0;
		USART1_Buf.bRxLength=0;

        Voltage_data=(((unsigned int)(USART1_Buf.bRxBuffer[3]))<<8)|USART1_Buf.bRxBuffer[4]; //Voltage_data Ϊ unsigned int �� 
        Current_data=(((unsigned int)(USART1_Buf.bRxBuffer[5]))<<8)|USART1_Buf.bRxBuffer[6]; //Current_data Ϊ unsigned int �� 
        Power_data=(((unsigned int)(USART1_Buf.bRxBuffer[7]))<<8)|USART1_Buf.bRxBuffer[8];    //Power_data Ϊ unsigned int �� 
        Energy_data=(((unsigned   long)(USART1_Buf.bRxBuffer[9]))<<24)|(((unsigned   long)(USART1_Buf.bRxBuffer[10]))<<16)|(((unsigned long)(USART1_Buf.bRxBuffer[11]))<<8)|USART1_Buf.bRxBuffer[12];    ////Energy_data Ϊ unsigned long �� 
        Pf_data=(((unsigned int)(USART1_Buf.bRxBuffer[13]))<<8)|USART1_Buf.bRxBuffer[14];    //Pf_data Ϊ unsigned int �� 
        for(i=0;i<18;i++) 
		{
		   USART1_Buf.bRxBuffer[i]=0;
		}  
    }
      
} 

void data_display(void)
{

	u16 Voltage_H,Voltage_L;
	u16 Current_H,Current_L;
//	u16 Power_H,Power_L;
	u16 Energy_H,Energy_L;
	u16 Pf_H,Pf_L;
	u16 temp;


	Voltage_H = Voltage_data/100;		//��ѹ��ʾֵ����
	Voltage_L = (Voltage_data%100)/10;

	Current_H = Current_data/1000;	  //������ʾֵ����
	Current_L = Current_data%1000;

//	Power_H =  Power_data/1000;		 //������ʾֵ����
//	Power_L =  Power_data%1000;

	Pf_H = Pf_data/1000;			//������ʾֵ����
	Pf_L = Pf_data%1000;

	temp = Energy_data/32;			//��������

	Energy_H = temp/100;			  //������ʾֵ����
	Energy_L = temp%100;

	BACK_COLOR=BLACK;
	POINT_COLOR=WHITE;

	LCD_ShowNum(120,72,Voltage_H,3,16);		 //��ѹ����������ʾ
	LCD_ShowString(144,72,".");				 //С����
	LCD_ShowNum(152,72,Voltage_L,1,16);		 //��ѹС��������ʾ
	LCD_ShowString(168,72,"V");				 //��λ

	LCD_ShowNum(120,107,Current_H,1,16);	 //��������������ʾ
	LCD_ShowString(128,107,".");			 //С����
	LCD_Show2Num(136,107,Current_L,3,16,0);	 //����С��������ʾ
	LCD_ShowString(168,107,"A");			 //��λ

	LCD_ShowNum(120,177,Pf_H,1,16);		    //��������������ʾ
	LCD_ShowString(128,177,".");		    //С����
	LCD_Show2Num(136,177,Pf_L,3,16,0);	    //����С��������ʾ

	LCD_ShowNum(120,142,Power_data,5,16);	//����
	LCD_ShowString(168,142,"W");		   //��λ

	LCD_ShowNum(112,212,Energy_H,3,16);		 //��������������ʾ
	LCD_ShowString(136,212,".");			 //С����
    LCD_Show2Num(144,212,Energy_L,2,16,0);	 //����С��������ʾ
	LCD_ShowString(168,212,"KWh");			 //��λ


}
