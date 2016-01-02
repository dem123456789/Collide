#include "myLib.h"


#ifndef TEXT_H
#define	TEXT_H

extern const unsigned char fontdata_6x8[12288];

void drawChar3(int row, int col, char ch, u16 color);
void drawString3(int row,int col,char *str, u16 color);
void drawChar4(int row, int col, char ch, u8 color);
void drawString4(int row, int col, char *str, u8 color);

#endif	/* MYLIB_H */