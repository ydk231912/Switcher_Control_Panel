#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "dma.h"
#include "tim.h"
#include "fun.h"
#include "spi.h"
#include "oled.h"
#include "can.h"
#include "adc.h"

u8 dat=0;
s8 OLEDW=0;

 int main(void)
 {	 
	delay_init();	    	 		//��ʱ������ʼ��	 

//	JTAG_Set(JTAG_SWD_DISABLE); 	/*??JTAG??*/   
//  JTAG_Set(SWD_ENABLE);    		/*??SWD?? ???????SWD????*/ 
	NVIC_Configuration(); 	 		//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 
	uart1_init(72,115200);	 		//���ڳ�ʼ��Ϊ115200
	uart2_init(36,115200);
	uart3_init(36,500000);  
	 
 	LED_Init();			     		//LED�˿ڳ�ʼ��
	 
	TIM3_Int_Init(20,7199);     	//��ʱ��3 -- 1ms
	TIM2_Int_Init(100,7199);		//��ʱ��2
//	TIM2_Int_Init(20,7199);			//��ʱ��2
	
//	SPI1_Init();
	SPI2_Init();
//	SPI3_Init();
	     
	DMA_USART1_Tx_Config(DMA1_Channel4,(u32)&(USART1->DR),(u32)&ucByteBufTX1,DMATX1); 
	DMA_USART1_Rx_Config(DMA1_Channel5,(u32)&(USART1->DR),(u32)&ucByteBufRX1,DMARX1);
	 
	DMA_USART2_Tx_Config(DMA1_Channel7,(u32)&(USART2->DR),(u32)&ucByteBufTX2,DMATX2);
	DMA_USART2_Rx_Config(DMA1_Channel6,(u32)&(USART2->DR),(u32)&ucByteBufRX2,DMARX2);
	 
	DMA_USART3_Tx_Config(DMA1_Channel2,(u32)&(USART3->DR),(u32)&ucByteBufTX3,DMATX3);
	DMA_USART3_Rx_Config(DMA1_Channel3,(u32)&(USART3->DR),(u32)&ucByteBufRX3,DMARX3); 
	
	CAN1_Mode_Init(1,3,2,6,0);  

	KEY_Init();
	Adc_Init();	 
	SPI2_WriteByte(&dat,2);
	 
	OLED_Init();					//��ʼ��OLED  
	OLED_Clear(); 
		
// 		OLED_ShowString(30,0,"OLED TEST");
// 		OLED_ShowString(8,2,"ZHONGJINGYUAN");  
// 		OLED_ShowString(20,4,"2014/05/01");  
// 		OLED_ShowString(0,6,"ASCII:");  
// 		OLED_ShowString(63,6,"CODE:");  
// 		t=' '; 
// 		OLED_ShowCHinese(0,0,0);//��
// 		OLED_ShowCHinese(18,0,1);//��
// 		OLED_ShowCHinese(36,0,2);//԰
// 		OLED_ShowCHinese(54,0,3);//��
// 		OLED_ShowCHinese(72,0,4);//��
// 		OLED_ShowCHinese(90,0,5);//��
// 		OLED_ShowCHinese(108,0,6);//��
		
	while(1)
	{	    
//		99=6   0= -16   100=12
		fun();
//		OLED_Clear();
//		OLED_ShowChar(48,6,2);//��ʾASCII�ַ�	   		
//  	OLED_ShowString(20,4,"2014/05/01"); 
// 		if((oleddata>=0)&&(oleddata<10))OLEDW=-16;
// 		if((oleddata>=10)&&(oleddata<100))OLEDW=6;
// 		if(oleddata>=100)OLEDW=12;
		OLED_ShowNum(0,0,oleddata,3,64); //�����������ʾ��
//		OLED_ShowString(20,4,"67"); 

	}			    

}
		   
	
	
	
	

