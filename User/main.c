	
#include "include.h"

uint8 sms_data[100]={0};
const int Figure[10] = {'0','1','2','3','4','5','6','7','8','9'};
	u8 temperature;  	    
	u8 humidity;

uint8  lock=1,error=0,agree=0;

unsigned char send_message(void);
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	 	    
	u8 t,cot=0;   
	
  delay_init();	    	 //延时函数初始化	 
	USART_Config();
	OLED_Init();			//初始化OLED  
	LED_GPIO_Config();
  GPIOC->ODR|=(1<<13);

 	while(DHT11_Init())	//DHT11初始化	
	{
		OLED_ShowString(60,40,"DHT11 Error",12);
		delay_ms(200);	
	}
  OLED_Clear();
	OLED_ShowString(0,0,"GSM Te_Hu",24);  
//		OLED_Refresh_Gram();		//更新显示到OLED 
  OLED_ShowString(0,32,"temp:",12);  
  OLED_ShowString(0,48,"humi:",12); 	
	
		while(1)
	{	    	    
 		if(t%10==0)			//每100ms读取一次
		{									  
		DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值
		OLED_ShowNum(28,32,temperature,2,12);//显示温度	  
		OLED_ShowNum(28,48,humidity,2,12);//显示湿度	
		OLED_Refresh_Gram();		//更新显示到OLED 
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{	t=0;

		if(lock==1)	
		 {	
			 send_message();
			 lock=2;
		 }	
			
//			if((error==1)&&(agree==0)) cot++;
//			else 	cot=0;
//			if(cot==50){ lock=2;agree=1;error=0;}

		}
		
//		if((lock==0) && strstr(GsmBuf, "+PBREADY"))lock=1;	  //开机成功
		
		
	  if(!(GPIOA->IDR&(1<<6)))
		{      
				delay_ms(20);
			if(!(GPIOA->IDR&(1<<6)))
			{
				LED1_TOGGLE;
			  lock=1;
//				agree=0;
				
			}
			while(!(GPIOA->IDR&(1<<6)));
				OLED_Fill(60,40,120,52,0);
			  OLED_ShowString(60,40,"Key Down",12);
		}
		
		
	}
}


unsigned char send_message(void)
{
	char heard[] = "gsm test temperature and humidity";
	
	int i,j,len;
	
	char dat[5];
	
	delay_ms(50);
	DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值
	
	dat[1] = (temperature/10) ;
	dat[0]= (temperature%10) ;
	dat[3] = (humidity/10) ;
	dat[2] =(humidity%10) ;
	
	for(j=0;j<4;j++)
	{
		for(i=0;i<10;i++)
		{
			if(i==dat[j])
				dat[j]=Figure[i];
		}
 }
	
 
  memset(sms_data, 0, sizeof(sms_data));
	sprintf(sms_data,"%s",heard);
	strcat(sms_data,"\ntemperature:");
  len = strlen(sms_data);
  memcpy(sms_data+len, &dat[1], 1);
  memcpy(sms_data+len+1, &dat[0], 1);

	strcat(sms_data,"\nhumidity:");
  len = strlen(sms_data);
  memcpy(sms_data+len, &dat[3], 1);
  memcpy(sms_data+len+1, &dat[2], 1); 
	
	delay_ms(10);
	
  gsm_send_cmd("AT\r\n");
	gsm_send_cmd("AT\r\n");
  gsm_send_cmd("AT+CSCS=\"GSM\"\r\n"); 			// 设置GSM字符集
  gsm_send_cmd("AT+CMGF=1\r\n");				// 设置短消息为text模式
	delay_ms(5);
	gsm_send_message(sms_data);
	
	delay_ms(10000);
	OLED_Fill(60,40,120,52,0);
	if (strstr(GsmBuf, "OK"))// 命令发送成功
	{
	  OLED_ShowString(60,40,"Send scuss",12);
	
	}
	else 	
	{
		OLED_ShowString(60,40,"Send scuss",12);
	  error=1;
	}
	
	
}

/*********************************************END OF FILE**********************/












