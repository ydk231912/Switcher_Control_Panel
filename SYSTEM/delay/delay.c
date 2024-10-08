#include "delay.h"
#include "sys.h"

static u8  fac_us=0;		//us��ʱ������

//=====================================================================================
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif

//=====================================================================================
void delay_ms(u16 time)
{	 	
	u16 i=0; 	
	
	while(time--)
	{
		i=12000;

		while(i--);
	}			
}

//=====================================================================================
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;    //��ʼ����	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));			//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;    //�رռ�����
	SysTick->VAL =0X00;       					//��ռ�����	 
} 





























