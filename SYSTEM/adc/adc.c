#include "sys.h"
#include "adc.h"
#include "led.h"
//#include "tim.h"

u32 ADC_tempdata1;	  //ADCת��
u16 ADC_out1;
u16  ADC_cnt1;

u32 ADC_tempdata2;	  //ADCת��
u16 ADC_out2;
u16 ADC_cnt2;

u32 ADC_tempdata3;	  //ADCת��
u16 ADC_out3;
u16 ADC_cnt3;

u32 ADC_tempdata4;	  //ADCת��
u16 ADC_out4;
u16 ADC_cnt4;

u32 ADC_tempdata4;	  //ADCת��
u16 ADC_out4;
u16 ADC_cnt4;

u32 ADC_tempdata5;	  //ADCת��
u16 ADC_out5;
u16 ADC_cnt5;

u16 reference_V;     //��ǰ��ѹ
u32 reference_Vtemp;

u8 ADC_Ch_cnt;   //ͨ��ת������

s16 ADC1_X,ADC1_Y,ADC2_A,ADC2_B;

s16 ADCtemp[10];   //��λ��У��ֵ

//=====================================================================================	
void  Adc_Init(void)	   //173
{    

	//�ȳ�ʼ��IO��  /ADC12_IN5 6 7 8 9
	
	RCC->APB2ENR|=1<<2;    //ʹ��PORTA��ʱ�� 
	GPIOA->CRL&=0X000FFFFF;//PA1 anolog����  PA5 6 7 
	
 	RCC->APB2ENR|=1<<3;    //ʹ��PORTB��ʱ�� 
	GPIOB->CRL&=0XFFFFFF00;//PB1 anolog����  PB0 1
	 
	RCC->APB2ENR|=1<<9;    //ADC1ʱ��ʹ��	  
	RCC->APB2RSTR|=1<<9;   //ADC1��λ
	RCC->APB2RSTR&=~(1<<9);//��λ����	    
	RCC->CFGR&=~(3<<14);   //��Ƶ��������	

	RCC->CFGR|=2<<14;      //ѡ�� PLL ��Ϊϵͳʱ��Դ
	ADC1->CR1&=0XF0FFFF;   //����ģʽ����
	ADC1->CR1|=0<<16;      //��������ģʽ  
	ADC1->CR1&=~(1<<8);    //��ɨ��ģʽ	
	  
	ADC1->CR2&=~(1<<1);    //����ת��ģʽ
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //�������ת��  
	ADC1->CR2|=1<<20;      //ʹ�����ⲿ����(SWSTART)!!!	����ʹ��һ���¼�������
	ADC1->CR2&=~(1<<11);   //�Ҷ���	
	 
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     //1��ת���ڹ��������� Ҳ����ֻת����������1 	
				   
	//����ͨ��1�Ĳ���ʱ��
	ADC1->SMPR2&=~(7<<3);  //ͨ��1����ʱ�����	  
 	ADC1->SMPR2|=7<<3;     //ͨ��1  239.5����,��߲���ʱ�������߾�ȷ��
		 
	ADC1->SMPR1&=~(7<<18);  //���ͨ��16ԭ��������		 
	ADC1->SMPR1|=7<<18;     //ͨ��16  239.5����,��߲���ʱ�������߾�ȷ��	 	 
		 
		 
	ADC1->CR2|=1<<0;	   //����ADת����	 
	ADC1->CR2|=1<<3;       //ʹ�ܸ�λУ׼  

	while(ADC1->CR2&1<<3); //�ȴ�У׼���� 			 
       //��λ��������ò���Ӳ���������У׼�Ĵ�������ʼ�����λ��������� 		 
	ADC1->CR2|=1<<2;        //����ADУ׼	   
	while(ADC1->CR2&1<<2);  //�ȴ�У׼����
	//��λ����������Կ�ʼУ׼������У׼����ʱ��Ӳ�����  
}				  

//=====================================================================================	5
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
void Get_Adc_Average1(u16 times)
{			
 if(ADC_Ch_cnt==0)  //ҡ��X
 {
	  ADC1->SQR3&=0XFFFFFFF0;//ͨ��1 ��������1 ͨ��ch
	  ADC1->SQR3|=5;
	  ADC1->CR2|=1<<22;
	if(ADC1->SR&1<<1)
	{
	  ADC_cnt1++;
	  ADC_tempdata1+=ADC1->DR;	  
	}

	if(ADC_cnt1>=times)
	{
	 ADC_tempdata1/=times;
	 ADC_out1=ADC_tempdata1;
	 ADC_tempdata1=0;
	 ADC_cnt1=0;
	 ADC_Ch_cnt=1;	
	}
 }
//=======================================================6

  if(ADC_Ch_cnt==1)  //ͨ��2ҡ��Y
	{
	 ADC1->SQR3&=0XFFFFFFF0;//��������1 ͨ��ch
	 ADC1->SQR3|=6;
	 ADC1->CR2|=1<<22;

	 if(ADC1->SR&1<<1)
	 {
	  ADC_cnt2++;
		ADC_tempdata2+=ADC1->DR;
		
	 }

	if(ADC_cnt2>=times)
	{
	 ADC_tempdata2/=times;
	 ADC_out2=ADC_tempdata2;
	 ADC_tempdata2=0;
	 ADC_cnt2=0;
	 ADC_Ch_cnt=2;
	}
   } 
//=======================================================	7
	if(ADC_Ch_cnt==2)  //
	{
	 ADC1->CR2|=1<<23;      //��λ��A
	 ADC1->SQR3&=0XFFFFFFF0;//��������1 ͨ��ch
	 ADC1->SQR3|=7;
	 ADC1->CR2|=1<<22;

	 if(ADC1->SR&1<<1)
	 {
	  ADC_cnt3++;
		ADC_tempdata3+=ADC1->DR;		
	 }

	if(ADC_cnt3>=times)
	{
	 ADC_tempdata3/=times;
	 ADC_out3=ADC_tempdata3;
	 ADC_tempdata3=0;
	 ADC_cnt3=0;
	 ADC_Ch_cnt=3;	
	}
	}
//=======================================================	8
	
	if(ADC_Ch_cnt==3)  //
	{
	 ADC1->CR2|=1<<23;      //��λ��B
	 ADC1->SQR3&=0XFFFFFFF0;//��������1 ͨ��ch
	 ADC1->SQR3|=8;
	 ADC1->CR2|=1<<22;

	 if(ADC1->SR&1<<1)
	 {
	  ADC_cnt4++;
		ADC_tempdata4+=ADC1->DR;
		
	 }

	if(ADC_cnt4>=times)
	{
	 ADC_tempdata4/=times;
	 ADC_out4=ADC_tempdata4;
	 ADC_tempdata4=0;
	 ADC_cnt4=0;
	 ADC_Ch_cnt=4;
	}
	}
	
//=======================================================9		
	
if(ADC_Ch_cnt==4)  //
	{
	 ADC1->CR2|=1<<23;      //��ѹ���
	 ADC1->SQR3&=0XFFFFFFF0;//��������1 ͨ��ch
	 ADC1->SQR3|=9;
	 ADC1->CR2|=1<<22;

	 if(ADC1->SR&1<<1)
	 {
	  ADC_cnt5++;
		ADC_tempdata5+=ADC1->DR;		
	 }

	if(ADC_cnt5>=times)
	{
	 ADC_tempdata5/=times;
	 ADC_out5=ADC_tempdata5;
	 ADC_tempdata5=0;
	 ADC_cnt5=0;
	 ADC_Ch_cnt=5;
	}
	}	
	
   if((ADC_Ch_cnt>=5))	 //�жϼ������ڷ�Χ��  0.2139   0.2248
	 ADC_Ch_cnt=0; 

	 //reference_V=reference_Vtemp=ADC_out5*1000*2/805;//���㵱ǰ��ѹ  	  3347
	 	 
	 reference_V=ADC_out5;   //�ɼ��ⲿ��ѹ
	  
//===============ҡ��================================================	 
	/* 
	 ADC_Time++;   //�ϵ���ʱУ����λ��  ADCtemp[0]=ADC_out1*12378/10000; 
	 
	 if((ADC_Time>800)&&(ADC_Time<900))
	 {
		 ADCtemp[0]=ADC_out1*14378/10000;  //���
	   ADCtemp[1]=ADC_out2*14378/10000;		 
   }	
	 
	 else if(ADC_Time>900)
	 {
		  ADC1_X=ADC_out1*14378/10000-ADCtemp[0];	 
	    ADC1_Y=ADC_out2*14378/10000-ADCtemp[1];
   }
	 else ;
	 	 
	 if(ADC_Time>900)	ADC_Time=10000;

	 
	   if(ADC1_X>2047)ADC1_X=2048;            //�������ֵ����
	   if(ADC1_X<(-2047))ADC1_X=-2048; 
	 
	   if((ADC1_X>0)&&(ADC1_X<90))ADC1_X=0;   //С�����ֵ����
	   if((ADC1_X<0)&&(ADC1_X>-90))ADC1_X=0;
 
	   if(ADC1_Y>2047)ADC1_Y=2048;            //�������ֵ����
	   if(ADC1_Y<(-2047))ADC1_Y=-2048; 
	 
	   if((ADC1_Y>0)&&(ADC1_Y<90))ADC1_Y=0;   //С�����ֵ����
	   if((ADC1_Y<0)&&(ADC1_Y>-90))ADC1_Y=0;
	 	*/
//================================================================	

	  ADC2_A=ADC_out3*12930/10000;  //���ֵ��Ҳ���ֶ�	
	  ADC2_B=ADC_out4*12930/10000;
		  
	  if(ADC2_A>4095)ADC2_A=4095;   //�����С��������
	  if(ADC2_A<60)ADC2_A=0;
	  if(ADC2_B>4095)ADC2_B=4095;
	  if(ADC2_B<60)ADC2_B=0;
	
//
}

//========================================================

void ADC_zero_calibration(void)  //���������
{
	;
	
}












/*
//4.557  0.66

3000/4095=0.732

��λ�����ֵ������ֵ4095�Ĳ���Ե�λ�����ֵ��









*/




