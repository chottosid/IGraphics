
/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
# include "iGraphics.h"
# include "gl.h"
#include<math.h>

int x,y,r=10;
int dx,dy,ax,ay;
double dir=-1.0;

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here

	iClear();
    //iShowBMP(100,100,"DonaldTrump.bmp");
    iSetColor(250, 0, 0);
	iFilledCircle(x, y, r);

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
		//place your codes here
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
	if(key == 'p')
	{
		//do something with 'q'
		iPauseTimer(0);
	}
	if(key == 'r')
	{
		iResumeTimer(0);
	}
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
    if(key== GLUT_KEY_UP && dy<=1){
            dy++;
    }
    if(key== GLUT_KEY_DOWN && y>=r && dy>=-1){
            dy--;
    }
    if(key==GLUT_KEY_RIGHT && x<800-r && dx<=1) dx++;
    if(key==GLUT_KEY_LEFT && x>r && dx>=-1 ) dx--;
	//place your codes for other keys here
}

void cord(){
	if(y<=r && dir==-1){
        dir=1;
	}
	if(fabs(dy)<1e-5&& dir==1) dir=-1;
	if(fabs(dy)<1e-5&& dir==-1 && fabs(y-r)<1e-5) {dir=1;ay=0;}
	if(x<r|| x>800-r){
        dx=-dx;
	}
	if(y>700-r){
            dir=-1;
    }
	dy=dy+ay/dir;
    y+=dy*dir;
	dx+=ax;
	x+=dx;
}

int main()
{
//    PlaySound((LPCSTR) "C:\\Users\\Public\\Music\\Sample Music\\Sleep Away.mp3", NULL, SND_FILENAME | SND_ASYNC);
//    DWORD dwError = GetLastError();

	//place your own initialization codes here.
	x=60.0,y=600.0,dx=3.0,dy=-5.0000,ax=0.0,ay=-1.0;
	iSetTimer(20, cord);
	iInitialize(800, 700, "bounce");

	return 0;
}

