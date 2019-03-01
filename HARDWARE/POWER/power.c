#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "ILI93xx.h"


u16 Voltage_data;  //电压
u16 Current_data;  //电流
u16 Power_data;   //功率
u32 Energy_data;   //电能
u16 Pf_data;       //因素
//界面显示
void face_display(void)
{
   	BACK_COLOR=BLACK;	   //字体背景颜色

	Test_Show_CH_Font24(30,30,11,RED);		//当前电参数
	Test_Show_CH_Font24(60,30,12,RED);
	Test_Show_CH_Font24(90,30,13,RED);
	Test_Show_CH_Font24(120,30,14,RED);
	Test_Show_CH_Font24(150,30,15,RED);
	Test_Show_CH_Font24(180,30,16,RED);

	//GUI_DrawFont24(10, 70, BLACK, GREEN, "深圳",0);
	Test_Show_CH_Font24(10,70,0,GREEN);	   //电压
	Test_Show_CH_Font24(34,70,1,GREEN);
	LCD_ShowString(60,73,":");

	Test_Show_CH_Font24(10,105,0,GREEN);	//电流
	Test_Show_CH_Font24(34,105,2,GREEN);
	LCD_ShowString(60,108,":");
	
	Test_Show_CH_Font24(10,140,3,GREEN);	//功率
	Test_Show_CH_Font24(34,140,4,GREEN);
	LCD_ShowString(60,143,":");
	
	Test_Show_CH_Font24(10,175,5,GREEN);	//因素
	Test_Show_CH_Font24(34,175,6,GREEN);
	LCD_ShowString(60,178,":");	

	Test_Show_CH_Font24(10,210,0,GREEN);		//电量
	Test_Show_CH_Font24(34,210,7,GREEN);
	LCD_ShowString(60,213,":");

	LCD_Fill(60,245,180,290,MAGENTA);
	BACK_COLOR=MAGENTA;
	POINT_COLOR=RED;
	Test_Show_CH_Font24(90,255,9,RED);		//清零
	Test_Show_CH_Font24(124,255,10,RED);
}
//读取电压，电流，功率，因素和电量值
void read_data(void) 
{ 
     //   if((Clock.Second%2)==1)      //2 秒读一次 
        {       
			USART_TX_BUF[0]=0x01;      //抄读模块的 ID 号   
            USART_TX_BUF[1]=0x03; 
            USART_TX_BUF[2]=0x00; 
            USART_TX_BUF[3]=0x48; 
            USART_TX_BUF[4]=0x00; 
            USART_TX_BUF[5]=0x06; 
            crcnow.word16=chkcrc(USART_TX_BUF,6); 
            USART_TX_BUF[6]=crcnow.byte[1];        //CRC 效验低字节在前 
            USART_TX_BUF[7]=crcnow.byte[0]; 
            USART1_SendStr(USART_TX_BUF,8);      //发送 8 个数据，

        } 
}
//清零电量值
void clear_data(void)
{
			USART_TX_BUF[0]=0x01;      //抄读模块的 ID 号   
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
            USART_TX_BUF[11]=crcnow.byte[1];        //CRC 效验低字节在前 
            USART_TX_BUF[12]=crcnow.byte[0]; 
            USART1_SendStr(USART_TX_BUF,13);      //发送 13 个数据，
} 
void Analysis_data(void) 
{ 
	unsigned char i; 
    if(USART1_ReFlag==0x01)    //接收完成 
    { 
		USART1_ReFlag=0;
		USART1_Buf.bRxLength=0;

        Voltage_data=(((unsigned int)(USART1_Buf.bRxBuffer[3]))<<8)|USART1_Buf.bRxBuffer[4]; //Voltage_data 为 unsigned int 型 
        Current_data=(((unsigned int)(USART1_Buf.bRxBuffer[5]))<<8)|USART1_Buf.bRxBuffer[6]; //Current_data 为 unsigned int 型 
        Power_data=(((unsigned int)(USART1_Buf.bRxBuffer[7]))<<8)|USART1_Buf.bRxBuffer[8];    //Power_data 为 unsigned int 型 
        Energy_data=(((unsigned   long)(USART1_Buf.bRxBuffer[9]))<<24)|(((unsigned   long)(USART1_Buf.bRxBuffer[10]))<<16)|(((unsigned long)(USART1_Buf.bRxBuffer[11]))<<8)|USART1_Buf.bRxBuffer[12];    ////Energy_data 为 unsigned long 型 
        Pf_data=(((unsigned int)(USART1_Buf.bRxBuffer[13]))<<8)|USART1_Buf.bRxBuffer[14];    //Pf_data 为 unsigned int 型 
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


	Voltage_H = Voltage_data/100;		//电压显示值处理
	Voltage_L = (Voltage_data%100)/10;

	Current_H = Current_data/1000;	  //电流显示值处理
	Current_L = Current_data%1000;

//	Power_H =  Power_data/1000;		 //功率显示值处理
//	Power_L =  Power_data%1000;

	Pf_H = Pf_data/1000;			//因素显示值处理
	Pf_L = Pf_data%1000;

	temp = Energy_data/32;			//电量换算

	Energy_H = temp/100;			  //电量显示值处理
	Energy_L = temp%100;

	BACK_COLOR=BLACK;
	POINT_COLOR=WHITE;

	LCD_ShowNum(120,72,Voltage_H,3,16);		 //电压整数部分显示
	LCD_ShowString(144,72,".");				 //小数点
	LCD_ShowNum(152,72,Voltage_L,1,16);		 //电压小数部分显示
	LCD_ShowString(168,72,"V");				 //单位

	LCD_ShowNum(120,107,Current_H,1,16);	 //电流整数部分显示
	LCD_ShowString(128,107,".");			 //小数点
	LCD_Show2Num(136,107,Current_L,3,16,0);	 //电流小数部分显示
	LCD_ShowString(168,107,"A");			 //单位

	LCD_ShowNum(120,177,Pf_H,1,16);		    //因素整数部分显示
	LCD_ShowString(128,177,".");		    //小数点
	LCD_Show2Num(136,177,Pf_L,3,16,0);	    //因素小数部分显示

	LCD_ShowNum(120,142,Power_data,5,16);	//功率
	LCD_ShowString(168,142,"W");		   //单位

	LCD_ShowNum(112,212,Energy_H,3,16);		 //电量整数部分显示
	LCD_ShowString(136,212,".");			 //小数点
    LCD_Show2Num(144,212,Energy_L,2,16,0);	 //电量小数部分显示
	LCD_ShowString(168,212,"KWh");			 //单位


}
