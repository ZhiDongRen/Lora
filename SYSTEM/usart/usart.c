#include "sys.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����1��ʼ��		   

//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////

#ifdef EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[64];     //���ջ���,���64���ֽ�.
u8 USART_TX_BUF[64];     //���ͻ���,���64���ֽ�.

UART_Buffer USART1_Buf;
u8 USART1_ReFlag=0;
//����״̬
//bit7��������ɱ�־
//bit6�����յ�0x0d
//bit5~0�����յ�����Ч�ֽ���Ŀ
u8 USART_RX_STA=0;       //����״̬���	  


CRC_C crcnow;
//union crcdata 
//{ 
//	unsigned int word16; 
//    unsigned char byte[2]; 
//}crcnow;
	 
void USART1_IRQHandler(void)
{
//	u8 res;
	//LCD_ShowString(80,50,"enter it");	    
	if(USART1->SR&(1<<5))//���յ�����
	{	
	   //LCD_ShowString(80,70,"have data");
		USART1_Buf.bRxBuffer[USART1_Buf.bRxLength++]=USART1->DR;
		if(USART1_Buf.bRxLength==1)
		{
		   if(USART1_Buf.bRxBuffer[0]!=0x01)
		   USART1_Buf.bRxLength=0;
		}
		if(USART1_Buf.bRxLength==2)
		{
		   if(USART1_Buf.bRxBuffer[1]!=0x03)
		   USART1_Buf.bRxLength=0;
		}
		if(USART1_Buf.bRxLength==18)
		{
		//	LCD_ShowString(80,90,"18 data");
			crcnow.word16=chkcrc(USART1_Buf.bRxBuffer,15);
		 	if(crcnow.byte[0]==USART1_Buf.bRxBuffer[16]&&crcnow.byte[1]==USART1_Buf.bRxBuffer[15])
			{
			   USART1_ReFlag=0x01;		  //�������
			   USART1_Buf.bRxLength=0;
			  // LCD_ShowString(80,110,"ok");
			}

		} 
		if(USART1_Buf.bRxLength>18)
		{
			USART1_Buf.bRxLength=0;
		}				 									     
	}  											 
} 
#endif										 
//��ʼ��IO ����1
//pclk2:PCLK2ʱ��Ƶ��(Mhz)
//bound:������
//CHECK OK
//091209
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F; 
	GPIOA->CRH|=0X000008B0;//IO״̬����
		  
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
#ifdef EN_USART1_RX		  //���ʹ���˽���
	//ʹ�ܽ����ж�
	USART1->CR1|=1<<8;    //PE�ж�ʹ��
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(3,3,USART1_IRQChannel,2);//��2��������ȼ� 
#endif
}
void USART1_Send(u8 Data)
{
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   	
	USART1->DR = (Data & (u8)0xFF);   
}
void USART1_SendStr(u8 *str, u8 nCount)
{
	nCount++;
	while ( nCount-- > 0 ) 
	{
		USART1_Send(*(str++) );		
	}
}
unsigned int calccrc(unsigned char crcbuf,unsigned int crc)   
{   
        unsigned char i;   
        unsigned char chk;   
        crc=crc ^ crcbuf;   
        for(i=0;i<8;i++)   
        {               
                chk=( unsigned char)(crc&1);   
                crc=crc>>1;   
                crc=crc&0x7fff;     
                if (chk==1) 
                crc=crc^0xa001;     
                crc=crc&0xffff;     
        } 
        return crc;   
} 

unsigned int chkcrc(unsigned char *buf,unsigned char len) 
{   
        unsigned char hi,lo;   
        unsigned int i;     
        unsigned int crc;     
        crc=0xFFFF;   
        for(i=0;i<len;i++)   
        {   
                crc=calccrc(*buf,crc);   
                buf++;   
        }   
        hi=( unsigned char)(crc%256);   
        lo=( unsigned char)(crc/256); 
        crc=(((unsigned int)(hi))<<8)|lo;   
        return crc;     
} 
