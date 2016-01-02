#include "myLib.h"



unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int r, int c, unsigned short color)
{
   videoBuffer[OFFSET(r,c,240)] = color;
}
/*
void drawRect(int row, int col, int height, int width, u16 color)
{
    int r, c;
    for(r=0;r<height; r++)
    {
        for(c=0; c<width; c++)
        {
            setPixel(row+r, col+c, color);
        }
    }
}
 * */

void drawRect(int row, int col, int height, int width, u16 color)
{
    int r;
    for(r=0;r<height; r++)
    {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
        DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
    }
}

void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}


void delay(int n)
{
    int i;
    volatile int x = 0;
    for(i=0; i<n*10000; i++)
    {
        x++;
    }
}  

void FillScreen3( volatile u16 color){
        DMA[3].src = &color;
        DMA[3].dst = videoBuffer;
        DMA[3].cnt = 38400| DMA_SOURCE_FIXED | DMA_ON;
}

void drawPicture3 (const unsigned short *picture){
    DMA[3].src=picture;
    DMA[3].dst=videoBuffer;
    DMA[3].cnt=38400| DMA_ON;
}
void drawRect4(int row, int col, int height, int width, u8 index)
{
    volatile u16 color = (index<<8) | index;
    int r;
    for(r=0;r<height; r++)
    {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)/2];
        DMA[3].cnt = (width/2) | DMA_SOURCE_FIXED | DMA_ON;
    }
}
void setPixel4(int row, int col, u8 index)
{
    int whichPixel = OFFSET(row, col, 240);
    int whichShort = whichPixel/2;
    if(col & 1)
    {
        // Odd column
        videoBuffer[whichPixel/2] 
           = (videoBuffer[whichPixel/2]&0x00FF) | (index<<8);
        
    }
    else
    {
        // Even column
        videoBuffer[whichShort] 
            = (videoBuffer[whichShort]&0xFF00) | (index);
    }
}

void FlipPage()
{
    if(REG_DISPCTL & BUFFER1FLAG)
    {
        // We were displaying Buffer 1
        REG_DISPCTL = REG_DISPCTL & ~BUFFER1FLAG;
        videoBuffer = BUFFER1;
    }
    else
    {
        // We were displaying Buffer 0
        REG_DISPCTL = REG_DISPCTL | BUFFER1FLAG;
        videoBuffer = BUFFER0;
    }
}



void fillScreen4(u8 index)
{
    volatile u16 color = (index<<8) | index;
    DMA[3].src = &color;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (38400/2) | DMA_ON | DMA_SOURCE_FIXED;
}

void drawPicture4(const unsigned char *pic)
{
    
    DMA[3].src = pic;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (38400/2) | DMA_ON;
}

void LoadPalette(const unsigned char *pal)
{
    DMA[3].src = pal;
    DMA[3].dst = PALETTE;
    DMA[3].cnt = 256 | DMA_ON;
}
    