// keypad.c
#include<LPC21xx.h>
#include"mini_keypad_defines.h"

#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19

#define COL0 20
#define COL1 21
#define COL2 22
#define COL3 23

unsigned int key[4][4]=
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'c','0','=','D'},
};

void INIT_KEYPAD(void)
{
    IODIR1 |= 15<<ROW0;
}

unsigned int colscan(void)
{
    unsigned int n;
    n = ((IOPIN1>>COL0) & 15);
    return !(n < 15);
}

unsigned int rowcheck(void)
{
    unsigned int r;
    for(r=0; r<=3; r++)
    {
        IOPIN1 = ((IOPIN1 & ~(15<<ROW0)) | ((~(1<<r))<<ROW0));
        if(!(colscan()))
            break;
    }
    IOPIN1 = ((IOPIN1 & ~(15<<ROW0)) | (0<<ROW0));
    return r;
}

unsigned int colcheck(void)
{
    unsigned int c;
    for(c=0; c<=3; c++)
        if(!((IOPIN1>>(COL0+c)) & 1))
            break;
    return c;
}

unsigned int keyscan(void)
{
    unsigned int r, c;
    while(colscan());
    r = rowcheck();
    c = colcheck();
    return key[r][c];
}

unsigned int ReadNum(void)
{
    int num = 0, sum = 0;
    while(1)
    {
        num = keyscan();
        if((num>='0') && (num<='9'))
        {
            sum = (sum*10) + (num-48);
            while(!(colscan()));
        }
        else
        {
            while(!(colscan()));
            break;
        }
    }
    return sum;
}
