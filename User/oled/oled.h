#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PA4��SCL��
//              D1   ��PA3��SDA��
//              RES  ��PA2
//              DC   ��PA1 (RS)
//              CS   ��PA5               
//              ----------------------------------------------------------------
//OLEDģʽ����
//0: 4�ߴ���ģʽ  ��ģ���BS1��BS2����GND��
//1: ����8080ģʽ ��ģ���BS1��BS2����VCC��
#define OLED_MODE 	0 

//-------------------���ж˿��������ú�----------------------//
#define OLED_CS_PORT           GPIOA
#define OLED_CS_PIN            GPIO_Pin_0
#define OLED_RS_PORT           GPIOA
#define OLED_RS_PIN            GPIO_Pin_1
#define OLED_RST_PORT          GPIOA
#define OLED_RST_PIN           GPIO_Pin_2

#define OLED_SDIN_PORT         GPIOA
#define OLED_SDIN_PIN          GPIO_Pin_3
#define OLED_SCLK_PORT         GPIOA
#define OLED_SCLK_PIN          GPIO_Pin_4
#define RCC_APB2Periph_GPIOX   RCC_APB2Periph_GPIOA

//---------------���ö���---------------------//
#define OLED_CS  PAout(0)                     // Ƭѡ
#define OLED_RS  PAout(1)                     // RS/DC  ����/����˿� 
#define OLED_RST PAout(2) 	                  // ��λ
//----------------------OLE���ڶ˿ڶ���---------------  //ʹ��4�ߴ��нӿ�ʱʹ�� 
#define OLED_SDIN PAout(3)                  // SDIN/MOSI   ����
#define OLED_SCLK PAout(4)                  // CLK    ʱ��

//-----------------���ڶ���-------------------//
#define OLED_WR  PGout(14)		  
#define OLED_RD  PGout(13)	   
//PC0~7,��Ϊ������
#define DATAOUT(x) GPIO_Write(GPIOC,x);//���  
  

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);  		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
#endif  
	 







 

