
/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
# include "iGraphics.h"
# include "gl.h"
#include <mmsystem.h>
#define WindowHeight 580
#define WindowWidth 1020
#define SideBar 20
#define Ground1 58
#define Ground2 136
#include <stdbool.h>
#include <string.h>
#include<iostream>
int x,y,r=10;
int dx,ay;
int dy;
int scene=1,just_changed=0;
bool jump1,jump2=false;
struct mainchar{
    int x,y;
};
struct bird{
    int x,y,dx,bmbx,bmby;
    bool bmbstart;
};
struct bird brd[100];
int birdnum,birdsalive;
char bg2[][100]={"BG/gravballbg2ground_01.bmp","BG/gravballbg2ground_02.bmp","BG/gravballbg2ground_03.bmp","BG/gravballbg2ground_04.bmp","BG/gravballbg2ground_05.bmp","BG/gravballbg2ground_06.bmp","BG/gravballbg2ground_07.bmp","BG/gravballbg2ground_08.bmp","BG/gravballbg2ground_09.bmp","BG/gravballbg2ground_10.bmp","BG/gravballbg2ground_11.bmp","BG/gravballbg2ground_12.bmp","BG/gravballbg2ground_13.bmp","BG/gravballbg2ground_14.bmp","BG/gravballbg2ground_15.bmp","BG/gravballbg2ground_16.bmp","BG/gravballbg2ground_17.bmp","BG/gravballbg2ground_18.bmp","BG/gravballbg2ground_19.bmp","BG/gravballbg2ground_20.bmp"};
int bg2index=0;
/*
	function iDraw() is called again and again by the system.
*/
int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

void iDraw()
{
    //place your drawing codes here

    iClear();
    //iShowBMP(100,100,"DonaldTrump.bmp");
    if(scene==1)
    {
        iShowBMP(0,0,"gravballbg.bmp");
        iSetColor(250, 0, 0);
        iFilledCircle(x, y, r);
    }
    else if(scene==2)
    {
        iShowBMP(0,0,"gravballbg2.bmp");
        for(int i=1;i<=20;i++){
            iShowBMP2((i-1)*50,0,bg2[(bg2index+i)%20],-1);
        }
        iSetColor(250, 0, 0);
        iFilledCircle(x, y, r);
        for(int i=0;i<birdnum;i++){
            iSetColor(0,0,200);
            iFilledCircle(brd[i].x,brd[i].y,3);
            if(brd[i].bmbstart && brd[i].x<brd[i].bmbx && brd[i].bmby>Ground2){
                iSetColor(0,0,0);
                iFilledCircle(brd[i].bmbx,brd[i].bmby,2);
            }
        }

    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        printf(("%d %d"),mx,my);
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key=='y' && jump1==false)
    {
        jump1=true;
        dy=30;
    }
    if(key=='y' && jump1==true && jump2==false)
    {
        jump2=true;
        dy=20;

    }
    if(key=='j' && x<WindowWidth-r ){
        if(scene==1) x+=20;
        if(scene==2) {(++bg2index)%=20;for(int i=0;i<birdnum;i++){brd[i].x-=1;brd[i].bmbx-=1;}}
    }
    if(key=='f' && x>r) {
           if(scene==1) x-=20;
           if(scene==2){
            (--bg2index)%=20;
            bg2index=bg2index<0?20+bg2index:bg2index;
            for(int i=0;i<birdnum;i++){brd[i].x+=1;brd[i].bmbx+=1;}
           }
    }
    if(key=='p') iPauseTimer(0);
    if(key=='r') iResumeTimer(0);
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    //place your codes for other keys here
}

void cord()
{
    if(scene==1)
    {
        if(just_changed){x=r+2;y=Ground2+r+2;just_changed=0;}
        if(jump1){
            dy+=-2;
            y+=dy;
            if(y<Ground1+2*r){
                jump1=false;
                jump2=false;
            }
        }
        else{
            y=Ground1+r;
        }
        if(x>WindowWidth-2*r){
            scene=2;
            just_changed=1;
        }
    }
    if(scene==2)
    {
        if(!birdsalive){
            birdnum=random(1,10)%20;
            for(int i=0;i<birdnum;i++){
                brd[i].y=random(300,500);
                brd[i].x=WindowWidth-SideBar;
                brd[i].dx=-(random(2,4));
                brd[i].bmbstart=random(0,1);
                if(brd[i].bmbstart){brd[i].bmby=brd[i].y-5;brd[i].bmbx=random(400,800);}
            }
            birdsalive=1;
        }
        else{
            for(int i=0;i<birdnum;i++){
                brd[i].x+=brd[i].dx;
                if(brd[i].bmbstart && brd[i].x<brd[i].bmbx){
                    brd[i].bmby-=2;
                }
            }
        }
        int flag=0;
        for(int i=0;i<birdnum;i++){
                if(brd[i].x>100) {flag=1; break;}
            }
        if(flag==0) birdsalive=0;
        if(just_changed){x=300;y=Ground2+r+2;just_changed=0;}
        if(jump1){
            dy+=-2;
            y+=dy;
            if(y<Ground2+2*r){
                jump1=false;
                jump2=false;
            }
        }
        else{
            y=Ground2+r;
        }
        if(x>WindowWidth-2*r){
            scene=1;
            just_changed=1;
        }
    }
}

int main()
{
//    DWORD dwError = GetLastError();

    //place your own initialization codes here.
    x=400,y=Ground1+r+2,dy=0,ay=-1;
    birdsalive=0;
    iSetTimer(20, cord);
    iInitialize(WindowWidth, WindowHeight, "bounce");

    return 0;
}



