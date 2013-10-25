/***********************************************************************
�ļ����ƣ�LED.h
��    �ܣ�led  IO��ʼ��
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/

#ifndef _LED_H_
#define _LED_H_

#define LED1_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_2)
#define LED2_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_3)
#define LED3_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_4)
#define LED4_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_5)

#define LED1_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_2)
#define LED2_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_3)
#define LED3_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_4)
#define LED4_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_5)

void LED_Configuration(void);
void LED_Blink(void);
void One_LED_ON(unsigned char led_num);


#endif