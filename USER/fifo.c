#include "stm32f10x.h"
#include "fifo.h"

FIFOTypeDef FIFO1;
FIFOTypeDef FIFO2;
FIFOTypeDef FIFOTmp;

/*******************************************************************************
* Function Name : FIFO_Reset
* Description   : ����FIFOx������
* Input         : FIFOx
* Output        : None
* Return        : None
*******************************************************************************/
void FIFO_Reset(FIFOTypeDef* FIFOx)
{
    FIFOx->Write = 0;
    FIFOx->Read = 0;
}

/*******************************************************************************
* Function Name : FIFO_PutChar
* Description   : ������д�뵽FIFOx�Ļ���������ջ��
* Input         : c
* Output        : None
* Return        : None
*******************************************************************************/
void FIFO_Push(FIFOTypeDef* FIFOx,uint8_t c)
{
	//д�����ݵ�������
  FIFOx->Buf[FIFOx->Write] = c;  
  //д��ָ�볬�����������ֵ���������λ��
  if(++FIFOx->Write >= FIFO_SIZE)	   
  {
    FIFOx->Write = 0;
  }
}

/*******************************************************************************
* Function Name  : FIFO_GetChar
* Description    : ��FIFO��������ȡ���ݣ���ջ��
* Input          : c
* Output         : None
* Return         : 0 
*******************************************************************************/
uint8_t FIFO_Pop(FIFOTypeDef* FIFOx,uint8_t* c)
{
	//���û�д������ݣ��򷵻�0
  if(FIFOx->Read == FIFOx->Write)	  
  {
    return 0;
  }
  else
  {
		//��ȡ���ݣ����뵽ָ��c
    *c = FIFOx->Buf[FIFOx->Read];	 
    //��ȡָ�볬�����������ֵ���������λ��
    if (++FIFOx->Read >= FIFO_SIZE)	 
    {
      FIFOx->Read = 0;
    }
		//�ɹ���ȡ���ݷ���1
    return 1;	
  }
}

/*******************************************************************************
* Function Name  : FIFO_GetChar
* Description    : ��ȡFIFO������ָ�����������ݣ�����ȡ��
* Input          : c��������ֽڣ�,i��index��������
* Output         : None
* Return         : 0 
*******************************************************************************/
uint8_t FIFO_Get(FIFOTypeDef* FIFOx,uint8_t i,uint8_t* c)
{
	//���û�д������ݣ��򷵻�0
  if(FIFOx->Read == FIFOx->Write)	  
  {
    return 0;
  }
  else
  {
		//��ȡ���ݣ����뵽ָ��c
    *c = FIFOx->Buf[i];	 
		//�ɹ���ȡ���ݷ���1
    return 1;	
  }
}
