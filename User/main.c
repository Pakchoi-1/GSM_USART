/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   测试led
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
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
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	uint8  lock=0,ret,ok,cot=0;
	u8 temperature;  	    
	u8 humidity;   
	
  delay_init();	    	 //延时函数初始化	 
	USART_Config();
	
  while(!DHT11_Init())	//DHT11初始化
		
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
	
			DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值					    
//			LCD_ShowNum(30+40,150,temperature,2,16);	//显示温度	   		   
//			LCD_ShowNum(30+40,170,humidity,2,16);		//显示湿度	
}
/*********************************************END OF FILE**********************/












