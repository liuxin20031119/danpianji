#include <REGX52.H>
#include <Delay.h>
#include "UART.h"
#include <stdio.h>
#include "LCD1602.h"
#include "juzhenganjian.h"


unsigned char Keynum;

void main()
{
    UART_Init();
	   TI=1;
     puts("µÁ–≈2302");
		puts("¡ıˆŒ");
	
			while(!TI);
	Delay(200);
			TI=0;
   
	
    
 LCD_Init();
    while(1)
    {
        LCD_ShowString(1,1,"DianXin");
        LCD_ShowNum(1,8,2302,4);
			LCD_ShowString(2,1,"LiuXin");
			LCD_ShowNum(2,8,00,2);
			
		Keynum=juzhenganjian();
		
			if(Keynum)
			{
				
				LCD_ShowNum(2,13,Keynum,2);
				UART_SendByte(Keynum);
		
			}
			
   }
 
}
