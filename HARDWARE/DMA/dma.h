#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"


#define 	  DMATX1			300			 //DMA���䷢���ֽ���
#define		  DMARX1			250

#define 	  DMATX2			150			 //DMA���䷢���ֽ���
#define		  DMARX2			150


#define 	  DMATX3			120			 //DMA���䷢���ֽ���
#define		  DMARX3			120


#define       DMATX1C     		244
#define		  DMARX1C     		244

#define 	  DMATX2C			75			 //DMA���䷢���ֽ���
#define		  DMARX2C			76

#define 	  DMATX3C			120			 //DMA���䷢���ֽ���
#define		  DMARX3C			120

extern volatile u8  ucByteBufRX1[DMARX1];	 //����1ͨѶ����
extern volatile u8  ucByteBufTX1[DMATX1];

extern volatile u8  ucByteBufRX2[DMARX2];    //����2ͨѶ����
extern volatile u8  ucByteBufTX2[DMATX2];

extern volatile u8  ucByteBufRX3[DMARX3];    //����3ͨѶ����
extern volatile u8  ucByteBufTX3[DMATX3];




void DMA_USART1_Tx_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//����DMA1_CHx
void DMA_USART1_Rx_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//����DMA1_CHx

void DMA_USART2_Tx_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//����DMA2_CHx
void DMA_USART2_Rx_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//����DMA2_CHx

void DMA_USART1_Tx(DMA_Channel_TypeDef*DMA_CHx,u16 len);//ʹ��DMA1_CHx
void DMA_USART2_Tx(DMA_Channel_TypeDef*DMA_CHx,u16 len);//ʹ��DMA2_CHx		 
void DMA_USART3_Tx(DMA_Channel_TypeDef*DMA_CHx,u16 len);//ʹ��DMA3_CHx		


void DMA_USART3_Tx_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//����DMA3_CHx
void DMA_USART3_Rx_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//����DMA3_CHx


void DMA_SPI2_Tx_Config(void);
void DMA_SPI2_Tx(u8 *buff,u16 LEN);





#endif




