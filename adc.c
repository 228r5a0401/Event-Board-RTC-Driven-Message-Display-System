                  
   //adc

#include<LPC21xx.h>
#include"ADC_defines.h"
#define FOSC 12000000
#define CCLK FOSC*5
#define PCLK ((CCLK)/4)
void dly_us(unsigned int dlyUS);
void INIT_ADC()
{
//cfg 27 input pin pin connect
PINSEL1=((PINSEL1&~(3<<(28-16)*2))|(AN0_INPUT_PIN<<(28-16)*2));//30:27 4 input ADC pins
ADCR=(1<<POW_BIT)|(CLK_DIV<<CLK_DIV_BIT);
}
void read_ADC(unsigned int chNo,float * eAR,unsigned int *ediv)
{
ADCR&=0xffffff00;// clear selection bits 7:0
ADCR|=(1<<START_BIT)|(1<<chNo);//start bit 26:24 and channel 2129 have channel 1
dly_us(3);
while(((ADDR>>DONE_BIT)&1)==0); // wait done bit 31;
ADCR&=~(1<<START_BIT);//start bit 26:24 and channel 2129 have channel 1
*ediv=((ADDR>>RES_BIT)&1023); //read result 15:6 10 bits
*eAR=*ediv*(3.3/1024); //vref 3.3/2^N -1 N=10
}         

//password
#include"mini_keypad_defines.h"
#include"mini_lcd_defines.h"
#include"mini_defines.h"
#include<string.h>
const char password[4]="111";
int size=strlen(password);
int check_password(void)
{
char user_password[4];
int attempts=0,i,num;
while(attempts<3)
{
cmdLCD(0x01);
cmdLCD(0x80);
STR("Enter password");
for(i=0;i<=size;i++)
{
num=keyscan();
if(num=='=')
break;
else if(num=='c'&&i!=0)
{
user_password[i]='\0';
STR((unsigned char *)user_pasword);
i--;
}
else
{
user_password[i]=num;
cmdLCD(0xc0);
STR((unsigned char *)user_password);
}
while(!(colscan()));
}
if(!(strcmp(password,user_password)))
{
cmdLCD(0x01);
STR("password matched");
dly_ms(1000);
return 1;  
}
else
{
cmdLCD(0x01);
STR(" wrong password ");
strcpy(user_password,"   ");
dly_ms(1000);
attempts++;
}
}
cmdLCD(0x01);
STR("  3 attempts  ");
cmdLCD(0xc0);
STR("    completed   ");
dly_ms(1000);
cmdLCD(0x01);
return 0;
}                      
                                                  
                                   
                                    
                                                                                                             
