#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "fifo.h"
#include "timer.h"
#include "uart.h"

/*******************************************************************************
* Function Name : TIM2_Config 
* Description   : ��ʼ��TIM2
* Input         : None
* Return        : None 
*******************************************************************************/
void TIM2_Config(void)	//����1ms������
{
	//����ṹ��
	TIM_TypeDef* TIMx=TIM2;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ,������100Ϊ10ms
	TIM_TimeBaseStructure.TIM_Period = 2; 
	//Ԥ��Ƶϵ��Ϊ36000-1������������ʱ��Ϊ72MHz/36000 = 2kHz
	TIM_TimeBaseStructure.TIM_Prescaler =36000 - 1;
	//����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); 
	//ʹ�ܻ���ʧ��ָ����TIM�ж�
	TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//ʹ��TIMx���� ��ʱ��ʹ��
	TIM_Cmd(TIMx, ENABLE);		 
}

/*******************************************************************************
* Function Name : TIM2_IRQHandler 
* Description   : TIM2�жϷ������
* Input         : None
* Return        : None 
*******************************************************************************/
void TIM2_IRQHandler(void)
{ 
	//����ṹ��
	TIM_TypeDef* TIMx=TIM2;
	//���ָ����TIM�жϷ������:TIM �ж�Դ 
	if (TIM_GetITStatus(TIMx, TIM_IT_Update) != RESET) 
	{
		// Frame_Handler(&FIFO1,USART2);
		// Frame_Handler(&FIFO2,USART1);
		UpdataSoftTimer();
		//���TIMx���жϴ�����λ:TIM �ж�Դ 
		TIM_ClearITPendingBit(TIMx, TIM_IT_Update);
		
	};
}


/*******************************************************************************
* Function Name : Frame_Handler 
* Description   : ��������֡����ȡ��������֡����У�����ݣ�
* Input         : None
* Return        : None 
*******************************************************************************/
// void Frame_Handler_(FIFOTypeDef* FIFOx,USART_TypeDef* USARTx){
// 	uint8_t byte;
// 	uint8_t dataLength;
// 	uint8_t frameLength;
// 	uint8_t crc;
// 	//��ȡ�жϰ�ͷ�Ƿ���ȷ
// 	if(FIFO_Get(FIFOx,0,&byte)){
// 		if(byte!=0x02){
// 			FIFO_Pop(FIFOx,&byte);
// 		}
// 		else{
// 			//��ȡ��е�벢�ж��Ƿ���ȷ
// 			if(FIFO_Get(FIFOx,1,&byte)){
// 				if(byte!=0x01){
// 					FIFO_Pop(FIFOx,&byte);
// 				}
// 				else{
// 					//��ȡ���Ȳ��ж��Ƿ���ȷ
// 					if(FIFO_Get(FIFOx,2,&byte)){
// 						if(byte<=0x30){
// 							FIFO_Pop(FIFOx,&byte);
// 						}
// 						else{
// 							//������ת��Ϊ�ֽڳ��ȣ�ASCII������ִ�30��ʼ
// 							dataLength=byte-0x30;
// 							//����֡����=��ͷ+��е��+����+����+У����
// 							frameLength=dataLength+4;
// 							if(FIFO_Get(FIFOx,frameLength-1,&byte)){
// 								Frame_GetCrc(FIFOx,frameLength-1,&crc);
// 								if(byte!=crc){
// 									FIFO_Pop(FIFOx,&byte);
// 								}
// 								else{
// 									USART_SendByte(USARTx,crc);
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// }
