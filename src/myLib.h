/* 
 * File:   myLib.h
 * Author: bleahy
 *
 * Created on February 18, 2013, 1:23 PM
 */

#ifndef MYLIB_H
#define	MYLIB_H

typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;


#define REG_DISPCTL *(unsigned short *)0x4000000
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define COLOR(r, g, b)  ((r) | (g)<<5 | (b)<<10)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define CYAN COLOR(0,31, 31)
#define MAGENTA COLOR(31,0,31)
#define YELLOW COLOR(31,31,0)
#define WHITE COLOR(31,31,31)
#define BLACK 0
#define PINK COLOR(31, 20, 20)
#define GREY COLOR(17,17,17)
#define OFFSET(r,c,numcols) ((r)*(numcols)+(c))

//Mode 4
#define MODE4 4
#define BUFFER0 (unsigned short *)0x6000000
#define BUFFER1 (unsigned short *)0x600A000
#define BUFFER1FLAG (1<<4)

#define PALETTE ((unsigned short *)0x5000000)


// *** Input =========================================================

// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT           (1<<2)
#define BUTTON_START            (1<<3)
#define BUTTON_RIGHT            (1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)
#define BUTTONS *(volatile unsigned short *)0x4000130
#define KEY_DOWN_NOW(key)  (~BUTTONS & key)





extern unsigned short *videoBuffer;


/* DMA */

#define REG_DMA0SAD         *(const volatile u32*)0x40000B0 // source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(const volatile u32*)0x40000BC // source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(const volatile u32*)0x40000C8 // source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(const volatile u32*)0x40000D4 // source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)


#define COLLISION (((((ptr->col)>=(ptr2->col))&&((ptr->col)<=((ptr2->col)+(ptr2->size))))&&(((ptr->row)>=(ptr2->row)) &&((ptr->row)<=((ptr2->row)+(ptr2->size)))))||((((ptr2->col)>=(ptr->col)) && ((ptr2->col)<=((ptr->col)+(ptr->size))))&&(((ptr2->row)>=(ptr->row)) &&((ptr2->row)<=((ptr->row)+(ptr->size)))))||(((((ptr->col)+(ptr->size))>=(ptr2->col)) && ((ptr->col)<=(ptr2->col)))&&(((ptr->row)>=(ptr2->row)) &&((ptr->row)<=((ptr2->row)+(ptr2->size)))))||(((((ptr2->col)+(ptr2->size))>=(ptr->col)) && ((ptr2->col)<=(ptr->col)))&&(((ptr2->row)>=(ptr->row)) && ((ptr2->row)<=((ptr->row)+(ptr->size)))))) 



void setPixel(int r, int c, unsigned short color);
void drawRect(int row, int col, int height, int width, u16 color);
void waitForVblank();
void FillScreen3(volatile u16 color);
void drawPicture3(const unsigned short *picture);
void setPixel4(int row, int col, u8 index);
void FlipPage();
void fillScreen4(u8 index);
void drawRect4(int row, int col, int height, int width, u8 index);
void drawPicture4(const unsigned char *pic);
void LoadPalette(const unsigned char *pal);
void delay(int n);
#endif	/* MYLIB_H */

