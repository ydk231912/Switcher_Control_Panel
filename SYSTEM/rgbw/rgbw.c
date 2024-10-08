#include "rgbw.h"
#include "spi.h"
#include "dma.h"
#include "delay.h"
//�������Դ�SPI���ݻ���
u8 gWs2812bDat_SPI[WS2812B_AMOUNT * 32] = {0};	//����Ҫ������������
//�����Դ�
u8 rgbw2814[WS2812B_AMOUNT]={0};  				//�ƿ�������

//===================================================================================
//��ɫ r�� g �� b �� w ��
void WS2812b_Set(u16 Ws2b812b_NUM, u8 rgbw,u8 r, u8 g, u8 b,u8 w ,u8 temp)
{
	u8 i;

	//���ݵ�����ɫ����˳��
	u8 *pR = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 32 + 8];  //������ɫ��ֵ
	u8 *pW = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 32];
	u8 *pG = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 32 + 16];
	u8 *pB = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 32 + 24];
	
	//�жϵ���ÿ����ɫ�ֽ�ÿλ״̬��ÿ��״̬λ��ֵ��һ���ֽڷ��������һ��λ��ÿ��������ɫ��64��λ
	//��ɣ�ÿ8��λ��ɵ�����ɫ�ֽڵ�һ��λ����Ҫ����SPIͨѶ����
	for(i = 0; i < 8; i++) 
	{
		if((rgbw==1)&&(i<w)) *pW = CODE_1;    //�� �жϵ���λ���أ���ֵ��ӳ���һ���ֽ�
          
		else *pW = CODE_0; 
			
		if((rgbw==2)&&(i<r)) *pR = CODE_1;    //�� �жϵ���λ���أ���ֵ��ӳ���һ���ֽ�
          
		else *pR = CODE_0; 
		
		
		if((rgbw==3)&&(i<g)) *pG = CODE_1;    // �жϵ���λ���أ���ֵ��ӳ���һ���ֽ�
          
		else *pG = CODE_0; 
		
		
		if((rgbw==4)&&(i<b)) *pB = CODE_1;    // �жϵ���λ���أ���ֵ��ӳ���һ���ֽ�
          
		else *pB = CODE_0; 
				
		pR++;      //ָ�����ӣ�����ÿ�ֽڶ�Ӧһ��λ��
		pG++;
		pB++;
		pW++;
	}
}

//===================================================================================
void WS2812B_Task(void)
{
	u8 dat = 0;
	u8 iLED;
	u8 rgbwtemp;
	u16 len;
	len=sizeof(gWs2812bDat_SPI);
	//����WS2814����   //WS2812B_AMOUNT   8
	
	for( iLED = 0; iLED < WS2812B_AMOUNT; iLED++) //
	{
		rgbwtemp=rgbw2814[iLED]&0x0f;
		WS2812b_Set(iLED,rgbwtemp ,1,1,1,1,0);   //�ѵ�����ɫ״̬д�뵽gWs2812bDat_SPI��������
	}
	
	SPI2_WriteByte(gWs2812bDat_SPI,len);
	SPI2_WriteByte(&dat,2);
	
//	DMA_SPI2_Tx(gWs2812bDat_SPI,sizeof(gWs2812bDat_SPI));
//	DMA_SPI2_Tx(&dat,1)
}

//===================================================================================
/*
//���³���Ϊ���Ե�������RGBW����
u8 gWs2812bDat_SPI[WS2812B_AMOUNT * 32] = {0};	//����Ҫ������������
//�����Դ�
tWs2812bCache_TypeDef gWs2812bDat[WS2812B_AMOUNT] = {
//R    G      B    W
0X00, 0X00, 0X00,	0X0F,//0
0X00, 0X00, 0X00,	0X0F,//1
0X00, 0X00, 0X00,	0X0F,//2
0X00, 0X00, 0X00,	0X0F,//3
0X00, 0X00, 0X00,	0X0F,//4
0X00, 0X00, 0X00,	0X0F,//5
0X00, 0X00, 0X00,	0X0F,//6
0X00, 0X00, 0X00,	0X0F,//7
};

//===================================================================================
void WS2812b_Set(u16 Ws2b812b_NUM, u8 r,u8 g,u8 b,u8 w)
{
	u8 i;
	//���ݵ�����ɫ����˳��
	uint8_t *pR = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 32 + 8];  //������ɫ��ֵ
	uint8_t *pG = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 32];
	uint8_t *pB = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 32 + 16];
	uint8_t *pW = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 32 + 24];
	

	

	
	//�жϵ���ÿ����ɫ�ֽ�ÿλ״̬��ÿ��״̬λ��ֵ��һ���ֽڷ��������һ��λ��ÿ��������ɫ��64��λ
	//��ɣ�ÿ8��λ��ɵ�����ɫ�ֽڵ�һ��λ����Ҫ����SPIͨѶ����
	for(i = 0; i < 8; i++) 
	{
		if(g & 0x80)     // �жϵ���λ���أ���ֵ��ӳ���һ���ֽ�
			{
			*pG = CODE_1;   //0xF8  1111 1000
		  }           
		else 
			{           
			*pG = CODE_0;   //0xE0  1110 0000
		  }           
		if(r & 0x80) 
			{           
			*pR = CODE_1;
		  }           
		else 
			{           
			*pR = CODE_0;
		  }           
		if(b & 0x80) 
			{           
			*pB = CODE_1;
		  }           
		else 
			{           
			*pB = CODE_0;
		  }
			
		if(w & 0x80) 
			{           
			*pW = CODE_1;
		  }    	
			else 
			{           
			*pW = CODE_0;
		  }
			
		  r <<= 1;  //��λ�ж�ÿ����ɫ��λ״̬
		  g <<= 1;
	  	b <<= 1;
			w <<= 1;
		  pR++;      //ָ�����ӣ�����ÿ�ֽڶ�Ӧһ��λ��
		  pG++;
		  pB++;
			pW++;
	}
}

//===================================================================================
void WS2812B_Task(void)
{
	u8 dat = 0;
	u8 iLED;
	//����WS2814����   //WS2812B_AMOUNT   8
	for( iLED = 0; iLED < WS2812B_AMOUNT; iLED++) //
	{
		//�ѵ�����ɫ״̬д�뵽gWs2812bDat_SPI��������
		WS2812b_Set(iLED, gWs2812bDat[iLED].R, gWs2812bDat[iLED].G, gWs2812bDat[iLED].B,gWs2812bDat[iLED].W);
	}
	//�����������
	//HAL_SPI_Transmit(&hspi1, gWs2812bDat_SPI, sizeof(gWs2812bDat_SPI), 100);
	//ʹ��������͵�ƽ
//	HAL_SPI_Transmit(&hspi1, &dat, 1, 100);
	//֡�źţ�һ������50�ĵ͵�ƽ
	//HAL_Delay(1);	
	
	SPI2_WriteByte(gWs2812bDat_SPI,sizeof(gWs2812bDat_SPI));
	SPI2_WriteByte(&dat,1);
	
}
*/

//===================================================================================
/*
//�������Դ�SPI���ݻ���
u8 gWs2812bDat_SPI[WS2812B_AMOUNT * 24] = {0};	//����Ҫ������������
//�����Դ�
tWs2812bCache_TypeDef gWs2812bDat[WS2812B_AMOUNT] = {
//R    G      B
0X0F, 0X0F, 0X0F,	//0
0X0F, 0X0F, 0X0F,	//1
0X0F, 0X0F, 0X0F,	//2
0X0F, 0X0F, 0X0F,	//3
0X0F, 0X0F, 0X0F,	//4
0X0F, 0X0F, 0X0F,	//5
0X0F, 0X0F, 0X0F,	//6
0X0F, 0X0F, 0X0F,	//7
};

//===================================================================================
void WS2812b_Set(uint16_t Ws2b812b_NUM, uint8_t r,uint8_t g,uint8_t b)
{
	u8 i;
	//���ݵ�����ɫ����˳��
	uint8_t *pR = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 24 + 8];  //������ɫ��ֵ
	uint8_t *pG = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 24];
	uint8_t *pB = &gWs2812bDat_SPI[(Ws2b812b_NUM) * 24 + 16];
	
	
	//�жϵ���ÿ����ɫ�ֽ�ÿλ״̬��ÿ��״̬λ��ֵ��һ���ֽڷ��������һ��λ��ÿ��������ɫ��64��λ
	//��ɣ�ÿ8��λ��ɵ�����ɫ�ֽڵ�һ��λ����Ҫ����SPIͨѶ����
	for(i = 0; i < 8; i++) 
	{
		if(g & 0x80)     // �жϵ���λ���أ���ֵ��ӳ���һ���ֽ�
			{
			*pG = CODE_1;   //0xF8  1111 1000
		  }           
		else 
			{           
			*pG = CODE_0;   //0xE0  1110 0000
		  }           
		if(r & 0x80) 
			{           
			*pR = CODE_1;
		  }           
		else 
			{           
			*pR = CODE_0;
		  }           
		if(b & 0x80) 
			{           
			*pB = CODE_1;
		  }           
		else 
			{           
			*pB = CODE_0;
		  }
		  r <<= 1;  //��λ�ж�ÿ����ɫ��λ״̬
		  g <<= 1;
	  	b <<= 1;
		  pR++;      //ָ�����ӣ�����ÿ�ֽڶ�Ӧһ��λ��
		  pG++;
		  pB++;
	}
}

//===================================================================================
void WS2812B_Task(void)
{
	u8 dat = 0;
	u8 iLED;
	//����WS2814����   //WS2812B_AMOUNT   8
	for( iLED = 0; iLED < WS2812B_AMOUNT; iLED++) //
	{
		//�ѵ�����ɫ״̬д�뵽gWs2812bDat_SPI��������
		WS2812b_Set(iLED, gWs2812bDat[iLED].R, gWs2812bDat[iLED].G, gWs2812bDat[iLED].B);
	}
	//�����������
	//HAL_SPI_Transmit(&hspi1, gWs2812bDat_SPI, sizeof(gWs2812bDat_SPI), 100);
	//ʹ��������͵�ƽ
//	HAL_SPI_Transmit(&hspi1, &dat, 1, 100);
	//֡�źţ�һ������50�ĵ͵�ƽ
	//HAL_Delay(1);	
	
	SPI2_WriteByte(gWs2812bDat_SPI,sizeof(gWs2812bDat_SPI));
	
	SPI2_WriteByte(&dat,1);
	
	
}

*/


