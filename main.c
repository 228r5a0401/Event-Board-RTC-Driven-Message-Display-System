// main.c
#include<LPC21xx.h>
#include"mini_defines.h"
#include"mini_lcd_defines.h"
#include"mini_RTC_Defines.h"
#include"mini_keypad_defines.h"
#include"ADC_defines.h"

#define MAX 10
#define EVENT_LED 3
#define CLOCK_LED 4

void change_enable(int,int); // change enable by user

struct msg MS[MAX];

int hour = 7, min = 45, sec = 45;
int day = 6, mon = 7, year = 2025, date = 25;
int flag = 0;

int main()
{
    unsigned int temp = 0, chNo = 2;
    float temperature = 0.0;

    IODIR0 |= 3<<EVENT_LED;

    INIT_RTC();
    INIT_LCD();
    INIT_INTERRUPT();
    INIT_KEYPAD();
    INIT_ADC();

    insert_struct(MS);

    setTime(hour, min, sec);
    setDate(date, mon, year);
    setDay(day);

    while(1)
    {
        if(check_event(MS, HOUR, MIN))
        {
            IOPIN0 = 0<<EVENT_LED;
            IOPIN0 = 1<<CLOCK_LED;

            GetTime(&hour, &min, &sec);
            DisplayTime(hour, min, sec);

            GetDate(&date, &mon, &year);
            DisplayDate(date, mon, year);

            Getday(&day);
            DisplayDay(day);

            cmdLCD(0xc0+10);
            CHAR(' ');

            cmdLCD(0xc0+11);
            read_ADC(chNo, &temperature, &temp);

            CHAR('T');
            CHAR('=');
            FLOAT(temperature, 1);
        }
        else
        {
            IOPIN0 = 0<<CLOCK_LED;
            IOPIN0 = 1<<EVENT_LED;
        }
    }
}

void change_enable(int i, int enable)
{
    MS[i].enable = enable;   // user enables or disables message
}
