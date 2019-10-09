#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PA4（SCL）
//              D1   接PA3（SDA）
//              RES  接PA2
//              DC   接PA1 (RS)
//              CS   接PA5               
//              ----------------------------------------------------------------
//OLED模式设置
//0: 4线串行模式  （模块的BS1，BS2均接GND）
//1: 并行8080模式 （模块的BS1，BS2均接VCC）
#define OLED_MODE 	0 

//-------------------串行端口引脚配置宏----------------------//
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

//---------------共用定义---------------------//
#define OLED_CS  PAout(0)                     // 片选
#define OLED_RS  PAout(1)                     // RS/DC  数据/命令端口 
#define OLED_RST PAout(2) 	                  // 复位
//----------------------OLE串口端口定义---------------  //使用4线串行接口时使用 
#define OLED_SDIN PAout(3)                  // SDIN/MOSI   数据
#define OLED_SCLK PAout(4)                  // CLK    时钟

//-----------------并口定义-------------------//
#define OLED_WR  PGout(14)		  
#define OLED_RD  PGout(13)	   
//PC0~7,作为数据线
#define DATAOUT(x) GPIO_Write(GPIOC,x);//输出  
  

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
//OLED控制用函数
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
	 







 

