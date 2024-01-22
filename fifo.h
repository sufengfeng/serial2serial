#ifndef _FIFO_H_
#define _FIFO_H_

#include "stm32f10x.h"

#define FIFO_SIZE 1024

typedef struct
{
	//���建��������С��FIFO_SIZE����
  uint8_t Buf[FIFO_SIZE];	   
	//�����ȡָ��
  volatile uint32_t Read;
	//����д��ָ��
  volatile uint32_t Write;   
}FIFOTypeDef;
//����1���ݻ�����
extern FIFOTypeDef FIFO1;
//����2���ݻ�����
extern FIFOTypeDef FIFO2;
//��ʱ���ݻ�����
extern FIFOTypeDef FIFOTmp;

void FIFO_Reset(FIFOTypeDef* FIFOx);
void FIFO_Push(FIFOTypeDef* FIFOx,uint8_t c);
uint8_t FIFO_Pop(FIFOTypeDef* FIFOx,uint8_t* c);
uint8_t FIFO_Get(FIFOTypeDef* FIFOx,uint8_t i,uint8_t* c);

#endif
