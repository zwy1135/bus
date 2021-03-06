
#include "main.h"
#include "SCI.H"
void NVIC_Configuration(void); 
void USART_Configuration(void);

int main(void)
{
	
	/* Setup STM32 system (clocks, GPIO, NVIC) */
	System_Setup();
    NVIC_Configuration(); 
    USART_Configuration();       
	//RS_485_RX_EN;			//默认RS485接收使能
	while (1)
	{
		if(RS232_REC_Flag == 1)//RS232接收到了数据
		{
			RS232_REC_Flag = 0;
			RS232_Send_Data(RS232_buff,RS232_rec_counter); //将接收到的数据发送出去
			RS232_rec_counter = 0;	//发送完将接收计数器清零
		}
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
