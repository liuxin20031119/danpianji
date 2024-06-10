#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
#include "LCD1602.h"
#define uchar unsigned char
#define uint unsigned int
#define BUFFER_SIZE 11 
 
uchar rx_buffer[BUFFER_SIZE]; 
uchar rx_index = 0; 

 
  unsigned char hour=0,min=0,sec=0;
 
   uchar con=0;
 
bit D_flag=0;

 


 
 void ProcessReceivedData(unsigned char *data_d)  
{
	uchar hour_s,hour_g,min_s,min_g,sec_s,sec_g;
	
	   
		if(data_d[0]=='S')
	 {   TR0=0;
       ET0=0;		 
	     hour_s=data_d[2]-'0';
	     hour_g=data_d[3]-'0';
	    hour=hour_s*10+hour_g;
	
	     min_s=data_d[5]-'0';
	     min_g=data_d[6]-'0';
	    min=min_s*10+min_g;
	
	     sec_s=data_d[8]-'0';
	     sec_g=data_d[9]-'0';
	    sec=sec_s*10+sec_g;	
      	TR0=1	;
        ET0=1;		 
	 }
	
}
void sentdata()
{
	     uint i;
    for(i=0;i<BUFFER_SIZE;i++)	
	{
	  SBUF=rx_buffer[i];
		while(!TI);
		TI=0;
	}
}
 
 
void main()
{
 LCD_Init();
  T0_inti();
	 
UART_Init();				
	while(1)
	{
	      
				LCD_ShowNum(1,1,hour/10+0x30,1);
				LCD_ShowNum(1,2,hour%10+0x30,1);
		     LCD_ShowChar(1,3,':');
				LCD_ShowNum(1,4,min/10+0x30,1);
				LCD_ShowNum(1,5,min%10+0x30,1);
		    LCD_ShowChar(1,6,':');
		     LCD_ShowNum(1,7,sec/10+0x30,1);
				LCD_ShowNum(1,8,sec%10+0x30,1);
        
			
				
	
	}
 
}
 
void T0_EX0()interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
    if(++con==20)//1s
	{
		con=0;
		if(++sec==60)//1min
		{
			  sec=0;
				if(++min==60)//1hour
				{		min=0;
						if(++hour==24)//1day
							hour=0;
				}		
		}
 
  }
	
}
 
void Serial_ISR() interrupt 4 
{
	
    if (RI) { 
        RI = 0; 		
        rx_buffer[rx_index++] = SBUF; 
        
        
        if (rx_buffer[rx_index - 1] == '\n' )
					{
           
					   sentdata();
						rx_index=0;
            ProcessReceivedData(rx_buffer);
           
         }
			
			
			
    }
		
    
}