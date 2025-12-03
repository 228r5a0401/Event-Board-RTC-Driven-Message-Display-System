#include<LPC21xx.h>
#include"mini_lcd_defines.h"

#define LCD 8
#define LCD_RS 16
#define LCD_RW 17
#define LCD_EN 18

void WriteLCD(unsigned int byte)
{
    IOPIN0 = ((IOPIN0 & ~(255<<LCD)) | (byte<<LCD));
    IOCLR0 = 1<<LCD_RW;
    IOSET0 = 1<<LCD_EN;
    dly_ms(1);
    IOCLR0 = 1<<LCD_EN;
    dly_ms(2);
}

void cmdLCD(unsigned int cmd)
{
    IOCLR0 = 1<<LCD_RS;
    WriteLCD(cmd);
}

void INIT_LCD()
{
    dly_ms(15);
    IODIR0 |= 255<<LCD;
    IODIR0 |= 7<<LCD_RS;

    cmdLCD(0x30); dly_ms(5);
    cmdLCD(0x30); dly_ms(1);
    cmdLCD(0x30);

    cmdLCD(0x38);
    cmdLCD(0x0c);
    cmdLCD(0x01);
    cmdLCD(0x06);
}

void CHAR(unsigned int c)
{
    IOSET0 = 1<<LCD_RS;
    WriteLCD(c);
}

void STR(unsigned char *p)
{
    while(*p)
        CHAR(*p++);
}

void INT(unsigned int n)
{
    int i=0;
    unsigned char s[10];
    if(n==0) CHAR('0');
    else
    {
        while(n)
        {
            s[i] = (n%10)+48;
            n/=10;
            i++;
        }
        for(--i; i>=0; i--)
            CHAR(s[i]);
    }
}

void SignINT(int n)
{
    if(n<0)
    {
        CHAR('-');
        n = -n;
    }
    INT(n);
}

void FLOAT(float f,unsigned int nDP)
{
    int n,j;
    if(f<0)
    {
        CHAR('-');
        f = -f;
    }
    n = f;
    INT(n);
    CHAR('.');
    for(j=0; j<nDP; j++)
    {
        f = (f-n)*10;
        n = f;
        CHAR(n+48);
    }
}

void CGRAM(unsigned char *p,unsigned char nBytes)
{
    unsigned int i;
    cmdLCD(0x40);
    IOSET0 = 1<<LCD_RS;
    for(i=0; i<nBytes; i++)
        WriteLCD(p[i]);
    cmdLCD(0xc0);
}
