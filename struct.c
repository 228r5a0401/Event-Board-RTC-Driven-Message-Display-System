
//struct.c

#include<string.h>                                                                              #include"mini_lcd_defines.h"                                                                    #include"mini_defines.h"                                                                        #define MAX 10                                                                                  extern int flag;                                                                                void scroll_string(char *c);//scroll event in LCD first line                                    void insert_struct(struct msg *MS)                                                              {                                                                                                   MS[0].hour=7;                                                                                       MS[0].min=45;                                                                                   strcpy(MS[0].text,"  good morning! classes start soon   ");                                     MS[0].enable=1;                                                                                 MS[1].hour=13;                                                                                  MS[1].min=45;                                                                                   strcpy(MS[1].text,"  C Programming Session in class number 2   ");                              MS[1].enable=1;                                                                                 MS[2].hour=10;                                                                                  MS[2].min=15;                                                                                   strcpy(MS[2].text,"  C module theory examin 4th floor lab 1   ");                               MS[2].enable=1;                                                                                 MS[3].hour=10;                                                                                  MS[3].min=15;                                                                                   strcpy(MS[3].text,"  C module lab exam in 4th floor lab2 and middle lab at 10;30AM   ");        MS[3].enable=1;
        MS[4].hour=12;
        MS[4].min=45;
        strcpy(MS[4].text,"  Lunch Break from 1PM-2PM   ");
        MS[4].enable=1;
        MS[5].hour=9;
        MS[5].min=45;
        strcpy(MS[5].text,"  ARM Workshop on external iterrupts in LAB1 at 10AM   ");
        MS[5].enable=1;
        MS[6].hour=9;
        MS[6].min=45;
        strcpy(MS[6].text,"  ARM kit issue time from 10:00AM-10:30AM in middle lab   ");
        MS[6].enable=1;
        MS[7].hour=15;
        MS[7].min=15;
        strcpy(MS[7].text,"  Only 15 mins break time for next ARM session  ");
        MS[7].enable=1;
 MS[8].hour=17;
        MS[8].min=0;
        strcpy(MS[8].text,"  Revise today's Class programs at home  ");
        MS[8].enable=1;
    MS[9].hour=17;
        MS[9].min=0;
        strcpy(MS[9].text,"  End of day-See you Tomorrow  ");
        MS[9].enable=1;
}
int check_event(struct msg*MS,int hours,int minutes)
{
        int status=1,i,hr,min1,min2;
                char copy[80]={0};
        for(i=0;i<MAX;i++)
        {
                if(MS[i].min<45)
                {
                    min1=MS[i].min;
                    if(MS[i].hour==hours&&(minutes>=min1&&minutes<min1+15)&&MS[i].enable==1)
                        {
               status=0;
                           strcpy(copy,MS[i].text);//copy index i string  to copy string
                           cmdLCD(0xc0);
                       STR("   EVENT BOARD ");
                           scroll_string(copy);//pass copy string to scroll
        }
                }
                else if(MS[i].min>=45)
                {
                 hr=MS[i].hour;
                 min1=MS[i].min;
                 min2=60-min1;
                 if((hours==hr||hours==hr+1)&&((minutes>=min1&&minutes<=59)||(minutes<(15-min2)))&&MS[i].enable==1)
                  {
               status=0;
                           strcpy(copy,MS[i].text);//copy index i strinv to copy string
                           cmdLCD(0xc0);
                       STR("   EVENT BOARD ");
 scroll_string(copy);//pass copy string to scroll
          }
                 }
                 }
        return status;
}
void scroll_string(char *str)
{
        int i,size;
        char temp[17]={0};
        size=strlen(str);
                cmdLCD(0x01);
                cmdLCD(0xc0);
                STR("   EVENT BOARD ");
                cmdLCD(0x80);
        for(i=0;i<(size-16);i++)
        {                 if(flag)//to check interrupt status for break
                          {
                             flag=0;
                                         cmdLCD(0x01);
                             return;
                          }
                  strncpy(temp,str+i,16);//copy 16 length of string to temp by increasing index
                  STR((unsigned char *)temp);//pass 16 length temp string to LCD
                  dly_ms(300);
                                  cmdLCD(0x80);
                }
                dly_ms(70);
        STR("                ");
}
