	
#include "include.h"

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
	u8 humidity,t;   
	
  delay_init();	    	 //��ʱ������ʼ��	 
	USART_Config();
	OLED_Init();			//��ʼ��OLED   
  GPIOC->ODR|=(1<<13);

 	while(DHT11_Init())	//DHT11��ʼ��	
	{
		OLED_ShowString(60,48,"DHT11 Error",12);
		delay_ms(200);	
	}
  OLED_Clear();
	OLED_ShowString(0,0,"GSM Te_Hu",24);  
//		OLED_Refresh_Gram();		//������ʾ��OLED 
  OLED_ShowString(0,32,"temp:",12);  
  OLED_ShowString(0,48,"humi:",12); 	
	
		while(1)
	{	    	    
 		if(t%10==0)			//ÿ100ms��ȡһ��
		{									  
		DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ
		OLED_ShowNum(28,32,temperature,2,12);//��ʾ�¶�	  
		OLED_ShowNum(28,48,humidity,2,12);//��ʾʪ��	
			
	 	OLED_ShowString(120,0,"*",12);  
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
//   LED1_TOGGLE;
		GPIOC->ODR&=~(1<<13);
		}
	}
	

		
	
	
//	while (1)
//	{
////	gsm_send_cmd("AT\r\n");
////		delay(2);
////		gsm_check_network();
////		delay(2);
////		gsm_check_CSQ();  
////		delay(2);
//		

//if((lock==0) && strstr(GsmBuf, "+PBREADY"))ok=1;
//	else if((lock==0) && (cot==200))
//		{  ok=1;
//			cot=0;
//		}
//		
//	delay_ms(10);

//  if(ok==1)
//	{
//		gsm_send_message(sms_data);
//		ok=2;
//		lock=1;
//	}
//		
//	cot++;	
//	}
//	

}
/*********************************************END OF FILE**********************/












