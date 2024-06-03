#include <REGX52.H>


void  UART_Init()
{
    SCON=0x50;
		PCON &= 0x7F;	
    TMOD &= 0x0F;
    TMOD |= 0x20;
    TL1 = 0xFD;		//设定定时初值
		TH1 = 0xFD;		//设定定时器重装
    ET1 = 0;
		TR1 =1;
		EA=1;
		ES=1;
    
}

void UART_SendByte(unsigned char Byte)
  {
    SBUF = Byte;
    while(TI==0);
    TI=0;
  }


