#include "gsm.h"
#include "bsp_usart.h"

//char PhoneNumber[12]="15708290686";//18208223504
char PhoneNumber[12]="18227814091";//13708290921


uint16 GsmRecvLen;
int8 GsmBuf[100];

//---------------------------------------------------------
//GSM所使用的串口的初始化
//---------------------------------------------------------
//void gsm_uart1_init(void)
//{
//    P3SEL |= BIT7+BIT6;                       // 选择P3.6和P3.7做UART通信端口
//    P3DIR &=~BIT7;                            //设置UART1的RX引脚为输入
//    P3DIR |=BIT6;                             //设置UART1的TX引脚为输出
//    ME2 |= UTXE1 + URXE1;                     // 使能USART0的发送和接受
//    UCTL1 |= CHAR;                            // 8位
//    UCTL1 &=~(PENA+SPB);                  //无校验，一位停止位
//    UTCTL1 |= SSEL1;                          // UCLK = SMCLK
////    UBR01 = 0x45;                             // 波特率115200
////    UBR11 = 0x00;                             //
////    UMCTL1 = 0x4a;                            // Modulation
//      
//    UBR01 = 0x41;                             // 波特率9600
//    UBR11 = 0x03;                             //7
//    UMCTL1 = 0x00;                            // Modulation 
// 
//    UCTL1 &= ~SWRST;                          // 初始化UART状态机
//    IE2 |= URXIE1;                   // 使能USART1的收中断  
//}

//---------------------------------------------------------
//函数名称：void send_char(void)
//函数功能：串口1发送一个字符
//输入参数：
//          c, 要发送的字符
//返回参数：无
//---------------------------------------------------------
//static void send_char(char c)
//{
//  while(!(U1IFG&UTXIFG1));//等待发送器空闲，当UTXIFG1为1时，发送缓冲区为空
//    TXBUF1  = c;        //将要发送的字符写入发送缓冲区
//  while(!(U1IFG&UTXIFG1));//等待发送完成

//}
//---------------------------------------------------------
//函数名称：void send_string(void)
//函数功能：串口1发送一个字符串
//输入参数：
//          str, 要发送的字符串
//返回参数：无
//---------------------------------------------------------
//static void send_string(char* str)
//{
//	uint8 i;

//	for (i = 0; str[i]; i++)
//		send_char(str[i]);
//}

//---------------------------------------------------------
//函数名称：void flush_recv_buf(void)
//函数功能：清除接收缓冲区
//输入参数：无
//返回参数：无
//---------------------------------------------------------
static void flush_recv_buf(void)
{
	GsmRecvLen = 0;
	memset(GsmBuf, 0, sizeof(GsmBuf));
}

//---------------------------------------------------------
//函数名称：void debug_print(void)
//函数功能：打印调试输出
//输入参数：无
//返回参数：无
//---------------------------------------------------------
static void debug_print(void)
{
	//printf("-----------------------------\n");
	//printf("%s", GsmBuf);
}

//---------------------------------------------------------
//函数名称：void Gsm_Init(void)
//函数功能：gsm初始化函数
//输入参数：无
//返回参数：无
//---------------------------------------------------------
//void gsm_IGT_start(void)
//{   	
//IGT_P5_3 |= BIT3;//IGT拉高
//delay_ms(200);
//IGT_P5_3 &= ~BIT3;//拉低IGT，至少持续1s
//delay_s(1);
//			delay_ms(100);
//IGT_P5_3 |= BIT3;//最后将IGT拉高
//			delay_ms(100);
//}
//---------------------------------------------------------
// 函数名称：uint8 gsm_send_cmd(char* pcmd)
// 函数功能：gsm命令字发送函数
// 输入参数：
//           pcmd,要发送的命令
// 返回参数：
//           0   ,命令发送成功
//           1   ,命令发送失败
//---------------------------------------------------------
uint8 gsm_send_cmd(uint8* pcmd)
{
	uint16 i;
	uint8  ret;

	flush_recv_buf();	// 清除串口缓冲区
	Usart_SendStr(USART1,pcmd);	// 发送命令

	for (i = 0; i < 500; i++)
	{
//	  delay_ms(10);
		delay(1);
	  if (strstr(GsmBuf, "OK"))// 命令发送成功
	  {
		ret = 0;
		break;
	  }
	  else if (strstr(GsmBuf, ">"))
	  {
		ret = 0; 
		break;
	  }
	  else if (strstr(GsmBuf, "ERROR"))// 命令发送失败
	  {
		ret = 1;
		break;
	  }
	  else
		ret = 1;
	}	
	debug_print();							// 打印调试信息
	return ret;
}

//---------------------------------------------------------
//函数名称：void gsm_uart_rx_isr(void)
//函数功能：gsm接收中断处理函数
//输入参数：
//          无
//返回参数：
//          无
//---------------------------------------------------------
//#pragma vector=UART1RX_VECTOR
//__interrupt void uart1_rx_isr(void)
//{
//	uint8 stat;
//        stat=URCTL1;
// 	if (!(stat & RXERR))//检查接收是否出错
//	{
//	  // 串口数据保存到数据缓冲区
//	  GsmBuf[GsmRecvLen++] = RXBUF1;
//	}	
//}

//---------------------------------------------------------
//函数名称：uint8 gsm_start(void)
//函数功能：查询TC35是否启动
//输入参数：无
//返回参数：
//          0,启动成功
//          1,启动失败
//---------------------------------------------------------
uint8 gsm_setup(void)
{
	uint8 ret;

	ret = gsm_send_cmd("AT\r\n");
#if 0     
        
	gsm_send_cmd("AT+CMGF=1\r\n");				// 设置短消息为text模式
	gsm_send_cmd("AT+CSMP=17,167,0,0\r\n"); 	
	gsm_send_cmd("AT+CSCS=\"GSM\"\r\n"); 			// 设置GSM字符集
#endif
	return ret;
}

//---------------------------------------------------------
//函数名称：uint8 gsm_check_simcard(void)
//函数功能：检测SIM卡
//输入参数：无
//返回参数：
//          0,SIM卡检测成功
//          1,SIM卡检测失败
//---------------------------------------------------------
uint8 gsm_check_simcard(void)
{
  
  return (gsm_send_cmd("AT+CIMI\r\n"));
 
}

//---------------------------------------------------------
//函数名称：uint8 gsm_check_network(void)
//函数功能：检测SIM卡
//输入参数：无
//返回参数：
//          0,网络注册成功
//          1,网络注册失败
//---------------------------------------------------------
uint8 gsm_check_network(void)
{
	uint8 ret;	

	ret = gsm_send_cmd("AT+CREG?\r\n");
	
	if (ret == 0)
	{
		if (!strstr(GsmBuf, "+CREG: 0,0"))
			ret = 0;
		else
			ret = 1;
	}
	else
		ret = 1;

	return ret;
}
//---------------------------------------------------------
//函数名称：uint8 gsm_check_CSQ(void)
//函数功能：信号检测
//输入参数：无
//返回参数：
//          0,成功
//          1,失败
uint8 gsm_check_CSQ(void)
{
	uint8 ret;	

	ret = gsm_send_cmd("AT+CSQ\r\n");
	if (ret == 0)
	{
		if ((!strstr(GsmBuf, "+CSQ: 99,99"))&&(!strstr(GsmBuf, "+CSQ: 0,99")))
			ret = 0;
		else
			ret = 1;
	}
	else
		ret = 1;

	return ret;
}

//---------------------------------------------------------
//函数名称：void gsm_send_message(char* pmsg)
//函数功能：发送短消息
//输入参数：
//          pmsg,短消息指针
//返回参数：无
//---------------------------------------------------------
void gsm_send_message(uint8* pmsg)
{
	uint8 cmd[23] = {"AT+CMGS=\"00000000000\"\r\n"};
        *(pmsg + strlen((char*)pmsg)) = '\x01a';
//
//	gsm_send_cmd("AT+CMGF=1\r\n");				// 设置短消息为text模式
// 	//gsm_send_cmd("AT+CSMP=17,167,0,0\r\n"); 	
//	gsm_send_cmd("AT+CSCS=GSM\r\n"); 			// 设置GSM字符集
//	gsm_send_cmd("AT+CMGS=+8615840956725\r\n");	// 设置目的手机号码 
//	gsm_send_cmd("tc35 recieve cmd ok!\x01a");// 设置短消息
	
	gsm_send_cmd("AT\r\n");
	gsm_send_cmd("AT\r\n");
	gsm_send_cmd("AT\r\n");
  gsm_send_cmd("AT+CSCS=\"GSM\"\r\n"); 			// 设置GSM字符集
  gsm_send_cmd("AT+CMGF=1\r\n");				// 设置短消息为text模式
	delay(5);
	
	memcpy((cmd+9), PhoneNumber, 11);//这里是将消息发送到发送短信查询的手机上。所以改程序的时候需要设置一个固定的号码
	gsm_send_cmd(cmd);
	gsm_send_cmd(pmsg);
}

void delay(int n)
{
	int i,j;
	for(;n>0;n--)
	 for(i=0;i<50;i++)
	  for(j=0;j<500;j++);
	
}
