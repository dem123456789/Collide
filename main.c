#include "myLib.h"
#include <stdlib.h>
#include "text.h"
#include <stdio.h>
#include "splash.h"
#include "enter.h"
#include "you_lose.h"
#include "you_win.h"
#include "warning.h"
#include "game.h"






typedef struct _movobj{
    int row;
    int col;
    int rd;
    int cd;
    int size;
    u16 color;
} MOVOBJ;

#define WINUM 100
#define REDIDX2 247
int main();
int warning();
int splash();
int enter();
int win();
int lose();
int game(int randomizer,int num);
enum {WARNING,SPLASH,ENTER,GAME,WIN,LOSE};
enum {REDIDX=240, GREENIDX, BLUEIDX, MAGENTAIDX, YELLOWIDX, 
CYANIDX, WHITEIDX, PINKIDX};



int main(){
      REG_DISPCTL = MODE4 | BG2_ENABLE;
    int state = WARNING;
    int randomizer = 0;
    int num = 0;
    while(1){
        switch(state){
            case WARNING:
                warning();
                state=SPLASH;
                break;
            case SPLASH:
                randomizer=splash();
                state=ENTER;
                break;
            case ENTER:
                num=enter();
                state=GAME;
                break;
            case GAME:
                state=game(randomizer,num);
                break;
            case WIN:
                win();
                state=SPLASH;
                randomizer = 0;
                num = 0;
                break;
            case LOSE:
                lose();
                state=SPLASH;
                randomizer = 0;
                num = 0;
                break;
        }}
    return 0;
}
int warning(){
    LoadPalette(warningPal);
     int fontcolor= REDIDX2;
     FlipPage();
     waitForVblank();
        drawPicture4(warningBitmap);
        drawString4(6,102,"WARNING",fontcolor);
        drawString4(15, 5, "This is a Blocks Game.", fontcolor);
        drawString4(24,5,"You can choose up to 10 auto Blocks.",fontcolor);
        drawString4(33, 5, "You will control one Block.",fontcolor);
        drawString4(42,5,"You get one score:", fontcolor);
        drawString4(51,5,"When one auto Block hits the wall.",fontcolor);
        drawString4(60, 5, "Once you gain 100 Scores, You Win!!", fontcolor);
        drawString4(69, 5, "You cannot hit the wall .", fontcolor);
        drawString4(78,5, "You cannot hit any auto Blocks.",fontcolor);
        drawString4(87, 5, "Choose more auto Blocks: ",fontcolor);
        drawString4(96, 5, "Score faster but also more dangerous.", fontcolor);
        drawString4(105, 5, "You will start to get scores:",fontcolor);  
        drawString4(114, 5, "When you start to move your Block.",fontcolor); 
        drawString4(145, 5, "Press Start (Enter)",fontcolor); 
        FlipPage();
            while(!KEY_DOWN_NOW(BUTTON_START));
             while(KEY_DOWN_NOW(BUTTON_START));
    return 0;
}
int splash()
{
    LoadPalette(splashPal);
    FlipPage();
    int count = 0;
    waitForVblank();
    drawPicture4(splashBitmap);
    drawString4(45, 5, "GET 100 SCORE!!", BLACK);
    drawString4(75, 5, "Press Start (Enter)", BLACK);
    FlipPage();
    while(!KEY_DOWN_NOW(BUTTON_START));  
    while(KEY_DOWN_NOW(BUTTON_START)){count++;}
        return count; 
    }
  
int enter(){
    LoadPalette(enterPal);
    int num=1;
    char buffer1[20];
    while(1){
     if(KEY_DOWN_NOW(BUTTON_UP)){
         delay(6);
           num++;}
        if(KEY_DOWN_NOW(BUTTON_DOWN)){
            delay(6);
           num--;}
        if( num<1){
             num=1;}
        if( num>9){
             num=10;}
        waitForVblank();
        drawPicture4(enterBitmap);
        drawString4(45,10,"How many blocks do you want to have?",BLACK);
        sprintf(buffer1,"%d",num);
        drawString4(60,115,buffer1,BLACK);
        if((KEY_DOWN_NOW(BUTTON_START))){
            return num;
        }
        FlipPage();
    } 
}
int win(){
     LoadPalette(you_winPal); 
     FlipPage();
     waitForVblank();
     drawPicture4(you_winBitmap);
     drawString4(145,5,"Press Start (Enter)",BLACK);
     FlipPage();
    while(!KEY_DOWN_NOW(BUTTON_START));
    while(KEY_DOWN_NOW(BUTTON_START));
     return 0;

}
int lose(){
    LoadPalette(you_losePal);
     FlipPage();     
     waitForVblank();
     drawPicture4(you_loseBitmap);
     drawString4(120,120,"Press Start (Enter)",BLACK);
     FlipPage();
    while(!KEY_DOWN_NOW(BUTTON_START));
    while(KEY_DOWN_NOW(BUTTON_START));
     return 0;

}

int game(int randomizer,int num)
{
     LoadPalette(gamePal);
    int i=0;
    int start=0;
    int score=0;
    int size1 = 5;
    int size2= 10;
    int dels[] = { -2, -1, 1, 2};
    int numdels = sizeof(dels)/sizeof(dels[0]);
    u16 colors[] = {RED, GREEN, BLUE, MAGENTA, YELLOW, CYAN, WHITE};
    int numcolors = sizeof(colors)/sizeof(colors[0]);
    for(i=0; i< numcolors; i++)
    {
        PALETTE[i+240] = colors[i];
    }
    PALETTE[numcolors+240] = PINK;
    int oldsize = size1;
    char buffer2[41];
    //REG_DISPCTL = MODE4 | BG2_ENABLE;
    srand(randomizer);      
    MOVOBJ objs[num];
    MOVOBJ oldobjs[num];
    MOVOBJ ctrl_objs[1];
    MOVOBJ old_ctrl_objs[1];
    MOVOBJ *ptr=objs;
    MOVOBJ *ptr2=ctrl_objs;
        for(i=0; i<num; i++)
    {
        objs[i].row = 10 + rand()%140;
        objs[i].col = 10+ rand()%220;
        objs[i].rd = dels[rand()%numdels];
        objs[i].cd = dels[rand()%numdels];
        objs[i].color = (i%numcolors)+240;
        objs[i].size = size1;
        oldobjs[i] = objs[i];
    }
            ctrl_objs[0].row=80;
            ctrl_objs[0].col=120;
            ctrl_objs[0].rd= 0;
            ctrl_objs[0].cd = 0;
            ctrl_objs[0].color=(i%numcolors)+240;
            ctrl_objs[0].size=size2;
            old_ctrl_objs[0]=ctrl_objs[0];
    while(1)
    {   
         fillScreen4(PINKIDX);
         ptr2->row += ptr2->rd;
         ptr2->col += ptr2->cd;
        if (KEY_DOWN_NOW(BUTTON_UP)){
            start=1;
            ptr2->rd=-2;
            ptr2->cd=0;}
        if (KEY_DOWN_NOW(BUTTON_DOWN)){
            start=1;
            ptr2->rd=2;
            ptr2->cd=0;}
        if (KEY_DOWN_NOW(BUTTON_RIGHT)){
            start=1;
            ptr2->cd=2;
            ptr2->rd=0;}
        if (KEY_DOWN_NOW(BUTTON_LEFT)){
            start=1;
            ptr2->cd=-2;
            ptr2->rd=0;}
        if( ptr2->row < 0){
            ptr2->row = 0;
            return LOSE;}
         if(ptr2->row > 159-ptr2->size){
            ptr2->row = 159 - ptr2->size;
            return LOSE;}
          if(ptr2->col <0){
            ptr2->col = 0;
            return LOSE;}
         if(ptr2->col>239-ptr2->size){
            ptr2->col= 239-ptr2->size;
            return LOSE;}
        for(i=0; i<num; i++)
        {
            ptr = objs+i;
            ptr->row += ptr->rd;
            ptr->col += ptr->cd;
            if(ptr->row <0)
            {
                ptr->row = 0;
                ptr->rd = -ptr->rd;
                if(start==1){
                score++;}
            }
            if(ptr->row>159-ptr->size)
            {
                ptr->row = 159-ptr->size;
                ptr->rd = -ptr->rd;
                if(start==1){
                score++;}
            }
            if(ptr->col < 0)
            {
                ptr->col = 0;
                ptr->cd = -ptr->cd;
                if(start==1){
                score++;}
            }
            if(ptr->col > 239-ptr->size)
            {
                ptr->col = 239-ptr->size;
                ptr->cd = -ptr->cd;
                if(start==1){
                score++;}
            }
        } 
        sprintf(buffer2, "Score: %d", score);
        waitForVblank();
        drawRect4(150, 5, 8, 15*6, PINKIDX);
        drawString4(150, 5, buffer2, REDIDX);
        if (score>=WINUM){
            return WIN;
        }
        for(i=0;i<num;i++){
            ptr = objs+i;
                if(COLLISION&&start==1){
                return LOSE;}
        }
        drawRect4(old_ctrl_objs[0].row, old_ctrl_objs[0].col, old_ctrl_objs[0].size, old_ctrl_objs[0].size, PINKIDX);
        drawRect4(ptr2->row, ptr2->col, ptr2->size, ptr2->size, ptr2->color);
        old_ctrl_objs[0]=ctrl_objs[0];
        for(i=0; i<num;i++)
        {
            ptr = objs+i;
            drawRect4(oldobjs[i].row, oldobjs[i].col, oldsize, oldsize, PINKIDX);
            drawRect4(ptr->row, ptr->col, ptr->size, ptr->size, ptr->color);
            oldobjs[i] = objs[i];          
        }
        FlipPage();
 }  
    return 0;
}

