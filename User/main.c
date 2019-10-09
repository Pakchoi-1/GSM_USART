/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����led
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-�Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "delay.h"
#include "gsm.h"
#include "dht11.h" 
#include "sys.h"

uint8 sms_data[150]="huangyujieshizhu_GSM TEST";

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	uint8  lock=0,ret,ok,cot=0;
	u8 temperature;  	    
	u8 humidity;   
	
  delay_init();	    	 //��ʱ������ʼ��	 
	USART_Config();
	
  while(!DHT11_Init())	//DHT11��ʼ��
		
	while (1)
	{
//	gsm_send_cmd("AT\r\n");
//		delay(2);
//		gsm_check_network();
//		delay(2);
//		gsm_check_CSQ();  
//		delay(2);
		

if((lock==0) && strstr(GsmBuf, "+PBREADY"))ok=1;
	else if((lock==0) && (cot==200))
		{  ok=1;
			cot=0;
		}
		
	delay_ms(10);

  if(ok==1)
	{
		gsm_send_message(sms_data);
		ok=2;
		lock=1;
	}
		
	cot++;	
	}
	
			DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ					    
//			LCD_ShowNum(30+40,150,temperature,2,16);	//��ʾ�¶�	   		   
//			LCD_ShowNum(30+40,170,humidity,2,16);		//��ʾʪ��	
}
/*********************************************END OF FILE**********************/












