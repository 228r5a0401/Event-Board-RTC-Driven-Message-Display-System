
//rtc.c

#include<lpc214x.h>
#include"mini_lcd_defines.h"
#include"Mini_RTC_Defines.h"
#include"mini_keypad_defines.h"
void change_enable(int,int);
void INIT_RTC(void)
{
CCR=1<<1;
PREINT=PREINT_VAL;
PREFRAC=PREFACT_VAL;
#ifndef _LPC2148_
CCR=1<<0;
#else
CCR=1<<0|1<<4;
#endif
}
unsigned char Week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
void GetTime(int *hour,int *min,int *sec)
{
*hour=HOUR;
*min=MIN;
*sec=SEC;
}
void GetDate(int *date,int *mon,int*year)
{
        *date=DOM;
        *mon=MONTH;
        *year=YEAR;
}
void Getday(int *day)
{
*day=DOW;
}
void setTime(unsigned int hour,unsigned int min,unsigned int sec)
{
HOUR=hour;
MIN=min;
SEC=sec;
}
void setDay(unsigned int day)
{
DOW=day;}
void setDate(unsigned int date,unsigned int mon,unsigned int year)
{
        DOM=date;
        MONTH=mon;
        YEAR=year;
}
void DisplayTime(int hour,int min,int sec)
{
cmdLCD(0x80);
CHAR((hour/10)+48);
CHAR((hour%10)+48);
        CHAR(':');
CHAR((min/10)+48);
        CHAR((min%10)+48);
CHAR(':');
CHAR((sec/10)+48);
CHAR((sec%10)+48);
}
void DisplayDate(int date,int mon,int year)
{
        cmdLCD(0xc0);
CHAR((date/10)+48);
CHAR((date%10)+48);
        CHAR('/');
CHAR((mon/10)+48);
        CHAR((mon%10)+48);
CHAR('/');
INT(year);
}
void DisplayDay(int day)
{
cmdLCD(0x80+11);
STR(Week[day]);
}
void SET_TIME(void)     //set time by user choice
{
        int msg_num=0,choice,enable,hour,min,sec;
 cmdLCD(0x01);
        STR("set Time");
        cmdLCD(0xc0);
        STR("1.Yes 2.No");
                choice=(keyscan()-48);
                while(!(colscan()));
        cmdLCD(0x01);
        if(choice==1)
        {
            STR("enter time");
                hour=ReadNum();
                    if(hour>23)
                    hour=23;
            cmdLCD(0x01);
            STR("enter min");
                    min=ReadNum();
                    if(min>60)
                    min=0;
            cmdLCD(0x01);
            STR("enter sec");
                    sec=ReadNum();
                    if(sec>60)
                    sec=0;
                    choice=0;
            cmdLCD(0x01);
            STR("Modify time");
                    cmdLCD(0xc0);
            STR("1.Yes 2.No");
                    choice=keyscan()-48;
                    while(!(colscan()));
            if(choice==1)
            {
                           setTime(hour,min,sec);
               cmdLCD(0x01);
               STR("setTime done");
                           dly_ms(1000);
               choice=0;
            }
        }
 cmdLCD(0x01);
        while(1)
        {
                STR("Enter MSG number");
                msg_num=ReadNum();
                if(msg_num>10||msg_num==0)
                {
                        cmdLCD(0x01);
                        STR("only 10 msg");
                        dly_ms(1000);
                        cmdLCD(0x01);
                        continue;
                }
                break;
        }
    cmdLCD(0x01);
    STR("Modify enable");
    cmdLCD(0xc0);
    STR("1.enable 0.N0");
        enable=keyscan()-48;
        while(!(colscan()));
    cmdLCD(0x01);
    STR(" modify data");
    cmdLCD(0xc0);
    STR("1.Yes 2.NO");
        choice=keyscan()-48;
        while(!(colscan()));
    if(choice==1)
    {
        change_enable(msg_num-1,enable);
                choice=0;
        cmdLCD(0x01);
        STR(" data modified");
        dly_ms(1000);
                cmdLCD(0x01);
    }
