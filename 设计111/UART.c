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

void T0_inti()//T0定时1s
{
	TMOD&=0xf0;
  TMOD|=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TR0=0;
	ET0=0;
}
 
