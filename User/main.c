	
#include "include.h"

uint8 sms_data[100]={0};
const int Figure[10] = {'0','1','2','3','4','5','6','7','8','9'};
	u8 temperature;  	    
	u8 humidity;

uint8  lock=0;

unsigned char send_message(void);
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	 	    
	u8 t,cot=0;   
	
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
			cot++;
			if(cot==10){ lock=1;}
//   LED1_TOGGLE;
		GPIOC->ODR&=~(1<<13);
		}
		
//		if((lock==0) && strstr(GsmBuf, "+PBREADY"))lock=1;	  //������Ϣ
//	  if((!(GPIOA->IDR&(1<<6)))&&(lock==2)) lock=1;
		if(lock==1)	
		 {	
			 send_message();
			 lock=4;
		 }		

	}
}


unsigned char send_message(void)
{
	char heard[] = "gsm temperature and humidity";
	
	int i,j,len;
	
	char dat[5];
	
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
	
	sprintf(sms_data,"\n%s",heard);
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
	
  gsm_send_cmd("AT+CSCS=\"GSM\"\r\n"); 			// ����GSM�ַ���
  gsm_send_cmd("AT+CMGF=1\r\n");				// ���ö���ϢΪtextģʽ
	delay_ms(5);
	gsm_send_message(sms_data);
	
	delay_ms(50);
	
	if (strstr(GsmBuf, "OK"))// ����ͳɹ�
	{
	  OLED_ShowString(60,48,"DHT11 scuss",12);
	
	}
	else 	OLED_ShowString(60,48,"DHT11 failed",12);
}

/*********************************************END OF FILE**********************/












