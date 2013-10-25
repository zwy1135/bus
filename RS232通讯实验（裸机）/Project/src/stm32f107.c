/**
  ******************************************************************************
  * @file    stm32f107.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/20/2009
  * @brief   STM32F107 hardware configuration
  ******************************************************************************

/* Includes ------------------------------------------------------------------*/
#include "stm32f107.h"

void GPIO_Configuration(void);
void NVIC_Configuration(void);


void System_Setup(void)
{
  RCC_ClocksTypeDef RCC_Clocks;

  /* Setup STM32 clock, PLL and Flash configuration) */
  SystemInit();

}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE,ENABLE);
  /********************************************************************
  void RCC_APB1PeriphClockCmd(u32 RCC_APB1Periph, FunctionalState NewState):
		�ú������ܣ�ʹ�ܻ�ʧ�� APB1����ʱ�ӣ�
		�ú������ܣ�ʹ�ܻ�ʧ�� APB1����ʱ�ӣ�
		RCC_APB1Periph: �ſ�APB1����ʱ��
		NewState��ָ������ʱ�ӵ���״̬��ֵΪENABLE����DISABLE
		RCC_APB1Periph������
							RCC_APB1Periph_TIM2
							RCC_APB1Periph_TIM3
							RCC_APB1Periph_TIM4
							RCC_APB1Periph_WWDG
							RCC_APB1Periph_SPI2
							RCC_APB1Periph_USART2
							RCC_APB1Periph_USART3
							RCC_APB1Periph_I2C1
							RCC_APB1Periph_I2C2
							RCC_APB1Periph_USB
							RCC_APB1Periph_CAN
  *********************************************************************/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap2_CAN1,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_CAN2,ENABLE);
  /********************************************************************
  void GPIO_PinRemapConfig(u32 GPIO_Remap, FunctionalState NewState):
  �ú��������Ǹı�ָ���ܽŵ�ӳ�䡣
  GPIO_Remap: ѡ����ӳ��Ĺܽš�
  NewState��ֵΪENABLE����DISABLE��
  GPIO_Remap����ȡ��ֵΪ��
  						GPIO_Remap_SPI1           	SPI1���ù���ӳ��
						GPIO_Remap_I2C1				I2C1���ù���ӳ��
						GPIO_Remap_USART1			USART1���ù���ӳ��
						GPIO_PartialRemap_USART3 	USART2���ù���ӳ��
						GPIO_FullRemap_USART3 		USART3���ù�����ȫӳ��
						GPIO_PartialRemap_TIM1 		USART3���ù��ܲ���ӳ��
						GPIO_FullRemap_TIM1 		TIM1���ù�����ȫӳ��
						GPIO_PartialRemap1_TIM2 	TIM2���ù��ܲ���ӳ��1
						GPIO_PartialRemap2_TIM2 	TIM2���ù��ܲ���ӳ��2
						GPIO_FullRemap_TIM2 		TIM2���ù�����ȫӳ��
						GPIO_PartialRemap_TIM3 		TIM3���ù��ܲ���ӳ��
						GPIO_FullRemap_TIM3 		TIM3���ù�����ȫӳ��
						GPIO_Remap_TIM4 			TIM4���ù���ӳ��
						GPIO_Remap1_CAN1 			CAN���ù���ӳ��1
						GPIO_Remap2_CAN2 			CAN���ù���ӳ��2
						GPIO_Remap_PD01			    PD01���ù���ӳ��
						GPIO_Remap_SWJ_NoJTRST 		��JTRST��SWJ��ȫʹ�ܣ�JTAG+SW-DP��
						GPIO_Remap_SWJ_JTAGDisable  JTAG-DPʧ�� + SW-DPʹ��
						GPIO_Remap_SWJ_Disable      SWJ��ȫʧ�ܣ�JTAG+SW-DP�
  ********************************************************************/
	/* Configure CAN1 pin: RX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure);  
  /********************************************************************
  void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
  �ú����Ĺ����ǣ�����GPIO_InitStruct��ָ���Ĳ�����ʼ������GPIOx�Ĵ�����
  typedef struct { 
					  u16 GPIO_Pin; 
					  GPIOSpeed_TypeDef GPIO_Speed; 
					  GPIOMode_TypeDef GPIO_Mode; 
				  } GPIO_InitTypeDef;

				  GPIO_Pin��ȡֵΪGPIO_Pin_0~15��GPIO_Pin_ALL.

				  GPIO_Speed��������ѡ�йܽŵ�����:
				  GPIO_Speed_10MHz 			����������
				  10MHz GPIO_Speed_2MHz 	����������
				  2MHz GPIO_Speed_50MHz 	����������50MHz
			   	  
				  GPIO_Mode��������ѡ�йܽŵĹ���״̬:
				  GPIO_Mode_AIN 			ģ������ 
				  GPIO_Mode_IN_FLOATING 	�������� 
				  GPIO_Mode_IPD 			�������� 
				  GPIO_Mode_IPU 			�������� 
				  GPIO_Mode_Out_OD 			��©��� 
				  GPIO_Mode_Out_PP 			������� 
				  GPIO_Mode_AF_OD 			���ÿ�©��� 
				  GPIO_Mode_AF_PP 			�����������


  ********************************************************************/
    
/*LED����*/			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);

}

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef   NVIC_InitStructure;

  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

  /* 2 bit for pre-emption priority, 2 bits for subpriority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
  
  /* Enable the Ethernet global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   
  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}

