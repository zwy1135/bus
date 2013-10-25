/* Includes ------------------------------------------------------------------*/
#include <includes.h>
#include "LED.h"
int main (void)
{
    LED_Configuration(); 
    /* Init Host Library */
    USBH_Init(&USB_OTG_FS_dev, &HID_cb , &USR_Callbacks);
	/***Ï¨Ãð4¸öledµÆ***/
    LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
   	for(;;)
   	{  
       /* Host Task handler */
       USBH_Process();
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
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
