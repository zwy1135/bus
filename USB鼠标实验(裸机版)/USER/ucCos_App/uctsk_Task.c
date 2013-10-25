/* Includes ------------------------------------------------------------------*/
#include <includes.h>            
#include "LED.h"
static void uctsk_Mouse (void) 
{  
    LED_Configuration(); 
	BSP_Init();
  
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


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
