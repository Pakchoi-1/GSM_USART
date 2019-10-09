#include "gsm.h"
#include "bsp_usart.h"

//char PhoneNumber[12]="15708290686";//18208223504
char PhoneNumber[12]="18227814091";//13708290921


uint16 GsmRecvLen;
int8 GsmBuf[100];

//---------------------------------------------------------
//GSM��ʹ�õĴ��ڵĳ�ʼ��
//---------------------------------------------------------
//void gsm_uart1_init(void)
//{
//    P3SEL |= BIT7+BIT6;                       // ѡ��P3.6��P3.7��UARTͨ�Ŷ˿�
//    P3DIR &=~BIT7;                            //����UART1��RX����Ϊ����
//    P3DIR |=BIT6;                             //����UART1��TX����Ϊ���
//    ME2 |= UTXE1 + URXE1;                     // ʹ��USART0�ķ��ͺͽ���
//    UCTL1 |= CHAR;                            // 8λ
//    UCTL1 &=~(PENA+SPB);                  //��У�飬һλֹͣλ
//    UTCTL1 |= SSEL1;                          // UCLK = SMCLK
////    UBR01 = 0x45;                             // ������115200
////    UBR11 = 0x00;                             //
////    UMCTL1 = 0x4a;                            // Modulation
//      
//    UBR01 = 0x41;                             // ������9600
//    UBR11 = 0x03;                             //7
//    UMCTL1 = 0x00;                            // Modulation 
// 
//    UCTL1 &= ~SWRST;                          // ��ʼ��UART״̬��
//    IE2 |= URXIE1;                   // ʹ��USART1�����ж�  
//}

//---------------------------------------------------------
//�������ƣ�void send_char(void)
//�������ܣ�����1����һ���ַ�
//���������
//          c, Ҫ���͵��ַ�
//���ز�������
//---------------------------------------------------------
//static void send_char(char c)
//{
//  while(!(U1IFG&UTXIFG1));//�ȴ����������У���UTXIFG1Ϊ1ʱ�����ͻ�����Ϊ��
//    TXBUF1  = c;        //��Ҫ���͵��ַ�д�뷢�ͻ�����
//  while(!(U1IFG&UTXIFG1));//�ȴ��������

//}
//---------------------------------------------------------
//�������ƣ�void send_string(void)
//�������ܣ�����1����һ���ַ���
//���������
//          str, Ҫ���͵��ַ���
//���ز�������
//---------------------------------------------------------
//static void send_string(char* str)
//{
//	uint8 i;

//	for (i = 0; str[i]; i++)
//		send_char(str[i]);
//}

//---------------------------------------------------------
//�������ƣ�void flush_recv_buf(void)
//�������ܣ�������ջ�����
//�����������
//���ز�������
//---------------------------------------------------------
static void flush_recv_buf(void)
{
	GsmRecvLen = 0;
	memset(GsmBuf, 0, sizeof(GsmBuf));
}

//---------------------------------------------------------
//�������ƣ�void debug_print(void)
//�������ܣ���ӡ�������
//�����������
//���ز�������
//---------------------------------------------------------
static void debug_print(void)
{
	//printf("-----------------------------\n");
	//printf("%s", GsmBuf);
}

//---------------------------------------------------------
//�������ƣ�void Gsm_Init(void)
//�������ܣ�gsm��ʼ������
//�����������
//���ز�������
//---------------------------------------------------------
//void gsm_IGT_start(void)
//{   	
//IGT_P5_3 |= BIT3;//IGT����
//delay_ms(200);
//IGT_P5_3 &= ~BIT3;//����IGT�����ٳ���1s
//delay_s(1);
//			delay_ms(100);
//IGT_P5_3 |= BIT3;//���IGT����
//			delay_ms(100);
//}
//---------------------------------------------------------
// �������ƣ�uint8 gsm_send_cmd(char* pcmd)
// �������ܣ�gsm�����ַ��ͺ���
// ���������
//           pcmd,Ҫ���͵�����
// ���ز�����
//           0   ,����ͳɹ�
//           1   ,�����ʧ��
//---------------------------------------------------------
uint8 gsm_send_cmd(uint8* pcmd)
{
	uint16 i;
	uint8  ret;

	flush_recv_buf();	// ������ڻ�����
	Usart_SendStr(USART1,pcmd);	// ��������

	for (i = 0; i < 500; i++)
	{
//	  delay_ms(10);
		delay(1);
	  if (strstr(GsmBuf, "OK"))// ����ͳɹ�
	  {
		ret = 0;
		break;
	  }
	  else if (strstr(GsmBuf, ">"))
	  {
		ret = 0; 
		break;
	  }
	  else if (strstr(GsmBuf, "ERROR"))// �����ʧ��
	  {
		ret = 1;
		break;
	  }
	  else
		ret = 1;
	}	
	debug_print();							// ��ӡ������Ϣ
	return ret;
}

//---------------------------------------------------------
//�������ƣ�void gsm_uart_rx_isr(void)
//�������ܣ�gsm�����жϴ�����
//���������
//          ��
//���ز�����
//          ��
//---------------------------------------------------------
//#pragma vector=UART1RX_VECTOR
//__interrupt void uart1_rx_isr(void)
//{
//	uint8 stat;
//        stat=URCTL1;
// 	if (!(stat & RXERR))//�������Ƿ����
//	{
//	  // �������ݱ��浽���ݻ�����
//	  GsmBuf[GsmRecvLen++] = RXBUF1;
//	}	
//}

//---------------------------------------------------------
//�������ƣ�uint8 gsm_start(void)
//�������ܣ���ѯTC35�Ƿ�����
//�����������
//���ز�����
//          0,�����ɹ�
//          1,����ʧ��
//---------------------------------------------------------
uint8 gsm_setup(void)
{
	uint8 ret;

	ret = gsm_send_cmd("AT\r\n");
#if 0     
        
	gsm_send_cmd("AT+CMGF=1\r\n");				// ���ö���ϢΪtextģʽ
	gsm_send_cmd("AT+CSMP=17,167,0,0\r\n"); 	
	gsm_send_cmd("AT+CSCS=\"GSM\"\r\n"); 			// ����GSM�ַ���
#endif
	return ret;
}

//---------------------------------------------------------
//�������ƣ�uint8 gsm_check_simcard(void)
//�������ܣ����SIM��
//�����������
//���ز�����
//          0,SIM�����ɹ�
//          1,SIM�����ʧ��
//---------------------------------------------------------
uint8 gsm_check_simcard(void)
{
  
  return (gsm_send_cmd("AT+CIMI\r\n"));
 
}

//---------------------------------------------------------
//�������ƣ�uint8 gsm_check_network(void)
//�������ܣ����SIM��
//�����������
//���ز�����
//          0,����ע��ɹ�
//          1,����ע��ʧ��
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
//�������ƣ�uint8 gsm_check_CSQ(void)
//�������ܣ��źż��
//�����������
//���ز�����
//          0,�ɹ�
//          1,ʧ��
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
//�������ƣ�void gsm_send_message(char* pmsg)
//�������ܣ����Ͷ���Ϣ
//���������
//          pmsg,����Ϣָ��
//���ز�������
//---------------------------------------------------------
void gsm_send_message(uint8* pmsg)
{
	uint8 cmd[23] = {"AT+CMGS=\"00000000000\"\r\n"};
        *(pmsg + strlen((char*)pmsg)) = '\x01a';
//
//	gsm_send_cmd("AT+CMGF=1\r\n");				// ���ö���ϢΪtextģʽ
// 	//gsm_send_cmd("AT+CSMP=17,167,0,0\r\n"); 	
//	gsm_send_cmd("AT+CSCS=GSM\r\n"); 			// ����GSM�ַ���
//	gsm_send_cmd("AT+CMGS=+8615840956725\r\n");	// ����Ŀ���ֻ����� 
//	gsm_send_cmd("tc35 recieve cmd ok!\x01a");// ���ö���Ϣ
	
	gsm_send_cmd("AT\r\n");
	gsm_send_cmd("AT\r\n");
	gsm_send_cmd("AT\r\n");
  gsm_send_cmd("AT+CSCS=\"GSM\"\r\n"); 			// ����GSM�ַ���
  gsm_send_cmd("AT+CMGF=1\r\n");				// ���ö���ϢΪtextģʽ
	delay(5);
	
	memcpy((cmd+9), PhoneNumber, 11);//�����ǽ���Ϣ���͵����Ͷ��Ų�ѯ���ֻ��ϡ����Ըĳ����ʱ����Ҫ����һ���̶��ĺ���
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
