
#include "stm32f10x.h"
#include "SCI.H"
/***********************************************************************
�ļ����ƣ�SCI.C
��    �ܣ���ɶ�usart1��usart2�Ĳ���
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺��������ͨ���ж������ض����ַ���ȷ��һ֡�����Ƿ�����ġ�
***********************************************************************/

volatile unsigned char RS232_REC_Flag = 0;
volatile unsigned char RS485_REC_Flag = 0;
volatile unsigned char RS232_buff[RS232_REC_BUFF_SIZE] = 0;//���ڽ�������
volatile unsigned char RS485_buff[RS485_REC_BUFF_SIZE] = 0;//���ڽ�������
volatile unsigned int RS232_rec_counter = 0;//����RS232���ռ���
volatile unsigned int RS485_rec_counter = 0;//����RS485���ռ���
static void RS485_Delay(uint32_t nCount);

void USART_Configuration(void)
{ 
  
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 

 /********************����ΪUSART1����**************************/
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO,ENABLE);
  /*
  *  USART1_TX -> PA9 , USART1_RX ->	PA10
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);		   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_9b;//9λ����
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//1λֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_Even;//żУ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //���ͺͽ���ʹ��
  USART_Init(USART1, &USART_InitStructure); 

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  /***********************************************************************************
	  void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
	  ʹ�ܻ���ʧ��USART����
	  USARTx��x������1��2����3����ѡ��USART����
	  NewState: ����USARTx����״̬
	  �����������ȡ��ENABLE����DISABLE
  ***********************************************************************************/
  USART_Cmd(USART1, ENABLE); 
  USART_ClearITPendingBit(USART1, USART_IT_TC);//����ж�TCλ



 /********************����ΪUSART2����**************************/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
  /*
  *  USART1_TX -> PA2 , USART1_RX ->	PA3
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);		   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 38400;
  USART_InitStructure.USART_WordLength = USART_WordLength_9b;//9λ����
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//1λֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_Odd;//żУ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //���ͺͽ���ʹ��
  USART_Init(USART2, &USART_InitStructure); 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART2, ENABLE); 
  USART_ClearITPendingBit(USART2, USART_IT_TC);//����ж�TCλ

/***********************************GPIOD.4��RS485�������******************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/***********************************************************************
�������ƣ�void USART1_IRQHandler(void) 
��    �ܣ����SCI�����ݵĽ��գ�������ʶ
���������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    ��  RS485�õ���USART1.
***********************************************************************/
void USART1_IRQHandler(void)  
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{	
		RS485_buff[RS485_rec_counter] = USART1->DR;//
		RS485_rec_counter ++;
/********��RS485_END_FLAG1��RS485_END_FLAG2������ַ���Ϊһ֡���ݵĽ�����ʶ************/
		if(RS485_rec_counter >= 2)	//ֻ�н��յ�2���������ϲ����ж�
		{
			if(RS485_buff[RS485_rec_counter - 2] == RS485_END_FLAG1 && RS485_buff[RS485_rec_counter - 1] == RS485_END_FLAG2) 	//֡��ʼ��־   
			{
				RS485_REC_Flag = 1;
			}
		}
		if(RS485_rec_counter > RS485_REC_BUFF_SIZE)//�������ջ�������С
		{
			RS485_rec_counter = 0;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) 
	{
        USART_ClearITPendingBit(USART1, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
    }	
}


/***********************************************************************
�������ƣ�void USART2_IRQHandler(void) 
��    �ܣ����SCI�����ݵĽ��գ�������ʶ
���������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺RS232�õ���USART2
***********************************************************************/
void USART2_IRQHandler(void)  
{

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�������
	{	
		RS232_buff[RS232_rec_counter] = USART2->DR;//
		RS232_rec_counter ++;
/********��RS232_END_FLAG1��RS232_END_FLAG2������ַ���Ϊһ֡���ݵĽ�����ʶ************/
		if(RS232_rec_counter >= 2)	//ֻ�н��յ�2���������ϲ����ж�
		{
			if(RS232_buff[RS232_rec_counter - 2] == RS232_END_FLAG1 && RS232_buff[RS232_rec_counter - 1] == RS232_END_FLAG2) 	//֡��ʼ��־   
			{
				RS232_REC_Flag = 1;
			}
		}
		if(RS232_rec_counter > RS232_REC_BUFF_SIZE)//�������ջ�������С
		{
			RS232_rec_counter = 0;
		}
	}
	if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET) 
	{
        USART_ClearITPendingBit(USART2, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
    }
}

/***********************************************************************
�������ƣ�RS232_Send_Data(unsigned char *send_buff,unsigned int length)
��    �ܣ�RS232�����ַ���
���������send_buff:�����͵�����ָ�룻length�����͵����ݳ��ȣ��ַ�������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
void RS232_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	for(i = 0;i < length;i ++)
	{			
		USART2->DR = send_buff[i];
		while((USART2->SR&0X40)==0);	
	}	
}

/***********************************************************************
�������ƣ�RS485_Send(unsigned char ch)
��    �ܣ�RS485���͸��ַ�
���������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
void RS485_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	RS_485_TX_EN;		//485����ʹ��
	RS485_Delay(100);		//������ʱ��ע����ʱ�ĳ��̸��ݲ�����������������ԽС����ʱӦ��Խ��
	for(i = 0;i < length;i ++)
	{			
		USART1->DR = send_buff[i];
		while((USART1->SR&0X40)==0);	
	}
	RS485_Delay(10); 		//������ʱ��ע����ʱ�ĳ��̸��ݲ�����������������ԽС����ʱӦ��Խ��
	RS_485_RX_EN;  		//485����ʹ��
}

/***********************************************************************
�������ƣ�void RS485_Delay(uint32_t nCount)
��    �ܣ�RS485�շ���ʱ����
���������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
static void RS485_Delay(uint32_t nCount)
{ 
  while(nCount > 0)
  { 
  	  nCount --;   
  }
}