#ifndef __GSM_H
#define __GSM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define	  uint8       unsigned char
#define	  int8        char
#define	  uint16      unsigned int
#define	  int16       int
	
extern int8 GsmBuf[];
extern uint16 GsmRecvLen;

extern void gsm_uart1_init(void);
extern void gsm_IGT_start(void);
extern uint8 gsm_send_cmd(uint8* pcmd);
extern uint8 gsm_check_simcard(void);
extern uint8 gsm_setup(void);
extern void gsm_send_message(uint8* pmsg);
extern uint8 gsm_check_network(void);
extern uint8 gsm_check_CSQ(void);
void delay(int n);
#endif
