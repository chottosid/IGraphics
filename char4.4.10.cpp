# include "iGraphics.h"
# include "gl.h"
#include <mmsystem.h>
#define WindowHeight 750
#define WindowWidth 1450
#define SideBar 20
#define LeftSideBar 50
#define Ground1 75
#define Ground2 95
#include <stdbool.h>
#include<stdlib.h>
#include <string.h>
#include<iostream>
#define relativespeed 3
#define upperbgspeed 50
#define runspeed 5
#define buttons 4


int scene=0;
int just_paused=0;
int just_changed=0,lowerbgspeed=0;
int temp=0,temp2=0;
struct mainchar
{
    int x,y,dx,dy;
    bool jump1,jump2,idle,runright,runleft,shoot;
} mc;
struct Button
{
    int x,y;
} press[buttons];
//struct mainchar mc;
struct Bullet
{
    int x,y;
    bool active;
} bullet[4];
int runrighttemp=0;
int runlefttemp=5;
int shoottemp=0;
int Score=0,MaxScore;
struct Bird
{
    int x,y,dx,bmbx,bmby,birdindex,explosioncounter;
    bool alive,bmbstart,bmbend,bmbexplodestart,bmbexplodeend;
};
char BirdImages[][100]= {"Bird/skeleton-animation_00.bmp",
                         "Bird/skeleton-animation_01.bmp",
                         "Bird/skeleton-animation_02.bmp",
                         "Bird/skeleton-animation_03.bmp",
                         "Bird/skeleton-animation_04.bmp",
                         "Bird/skeleton-animation_05.bmp",
                         "Bird/skeleton-animation_06.bmp",
                         "Bird/skeleton-animation_07.bmp",
                         "Bird/skeleton-animation_08.bmp",
                         "Bird/skeleton-animation_09.bmp",
                         "Bird/skeleton-animation_010.bmp",
                         "Bird/skeleton-animation_011.bmp",
                         "Bird/skeleton-animation_012.bmp"
                        };
struct Monster
{
    int x,y=Ground2,dx,monsterindex,life;
    bool alive;
} monster[10];
char MonsterImages[][100]= {"Monster/Walk (1).bmp",
                            "Monster/Walk (2).bmp",
                            "Monster/Walk (3).bmp",
                            "Monster/Walk (4).bmp",
                            "Monster/Walk (5).bmp",
                            "Monster/Walk (6).bmp",
                            "Monster/Walk (7).bmp",
                            "Monster/Walk (8).bmp",
                            "Monster/Walk (9).bmp",
                            "Monster/Walk (10).bmp"
                           };
int monstertemp=0,monstercount=2;
struct Bird bird[15];
int birdnum=5,birdsalive;
char bg2[][100]= {"BG2/row-1-column-1.bmp",
                  "BG2/row-1-column-2.bmp",
                  "BG2/row-1-column-3.bmp",
                  "BG2/row-1-column-4.bmp",
                  "BG2/row-1-column-5.bmp",
                  "BG2/row-1-column-6.bmp",
                  "BG2/row-1-column-7.bmp",
                  "BG2/row-1-column-8.bmp",
                  "BG2/row-1-column-9.bmp",
                  "BG2/row-1-column-10.bmp",
                  "BG2/row-1-column-11.bmp",
                  "BG2/row-1-column-12.bmp",
                  "BG2/row-1-column-13.bmp",
                  "BG2/row-1-column-14.bmp",
                  "BG2/row-1-column-15.bmp",
                  "BG2/row-1-column-16.bmp",
                  "BG2/row-1-column-17.bmp",
                  "BG2/row-1-column-18.bmp",
                  "BG2/row-1-column-19.bmp",
                  "BG2/row-1-column-20.bmp"
                 };
char bg2upper[][100]= {"BG2UPPER/row-1-column-1.bmp",
                       "BG2UPPER/row-1-column-2.bmp",
                       "BG2UPPER/row-1-column-3.bmp",
                       "BG2UPPER/row-1-column-4.bmp",
                       "BG2UPPER/row-1-column-5.bmp",
                       "BG2UPPER/row-1-column-6.bmp",
                       "BG2UPPER/row-1-column-7.bmp",
                       "BG2UPPER/row-1-column-8.bmp",
                       "BG2UPPER/row-1-column-9.bmp",
                       "BG2UPPER/row-1-column-10.bmp",
                       "BG2UPPER/row-1-column-11.bmp",
                       "BG2UPPER/row-1-column-12.bmp",
                       "BG2UPPER/row-1-column-13.bmp",
                       "BG2UPPER/row-1-column-14.bmp",
                       "BG2UPPER/row-1-column-15.bmp",
                       "BG2UPPER/row-1-column-16.bmp",
                       "BG2UPPER/row-1-column-17.bmp",
                       "BG2UPPER/row-1-column-18.bmp",
                       "BG2UPPER/row-1-column-19.bmp",
                       "BG2UPPER/row-1-column-20.bmp",
                       "BG2UPPER/row-1-column-21.bmp",
                       "BG2UPPER/row-1-column-22.bmp",
                       "BG2UPPER/row-1-column-23.bmp",
                       "BG2UPPER/row-1-column-24.bmp",
                       "BG2UPPER/row-1-column-25.bmp",
                       "BG2UPPER/row-1-column-26.bmp",
                       "BG2UPPER/row-1-column-27.bmp",
                       "BG2UPPER/row-1-column-28.bmp",
                       "BG2UPPER/row-1-column-29.bmp",
                       "BG2UPPER/row-1-column-30.bmp"
                      };
int bg2upperindex=0;
int bg2index=0;
char idle[][100]= {"Char/IDLE/Idle_(1).bmp",
                   "Char/IDLE/Idle_(2).bmp",
                   "Char/IDLE/Idle_(3).bmp",
                   "Char/IDLE/Idle_(4).bmp",
                   "Char/IDLE/Idle_(5).bmp",
                   "Char/IDLE/Idle_(6).bmp",
                   "Char/IDLE/Idle_(7).bmp",
                   "Char/IDLE/Idle_(8).bmp",
                   "Char/IDLE/Idle_(9).bmp",
                   "Char/IDLE/Idle_(10).bmp"
                  };
int idleindex=0;
char jump[][100]= {"Char/JUMP/Jump_(1).bmp",
                   "Char/JUMP/Jump_(2).bmp",
                   "Char/JUMP/Jump_(3).bmp",
                   "Char/JUMP/Jump_(4).bmp",
                   "Char/JUMP/Jump_(5).bmp",
                   "Char/JUMP/Jump_(6).bmp",
                   "Char/JUMP/Jump_(7).bmp",
                   "Char/JUMP/Jump_(8).bmp",
                   "Char/JUMP/Jump_(9).bmp",
                   "Char/JUMP/Jump_(10).bmp"
                  };
int jumpindex=0;
char run[][100]= {"Char/RUN/Run_(1).bmp",
                  "Char/RUN/Run_(2).bmp",
                  "Char/RUN/Run_(3).bmp",
                  "Char/RUN/Run_(4).bmp",
                  "Char/RUN/Run_(5).bmp",
                  "Char/RUN/Run_(6).bmp",
                  "Char/RUN/Run_(7).bmp",
                  "Char/RUN/Run_(8).bmp"
                 };
int runindex=0;
char shoot[][100]= {"Char/SHOOT/Shoot_(1).bmp","Char/SHOOT/Shoot_(2).bmp","Char/SHOOT/Shoot_(1).bmp"};
int shootindex;
struct Obstacle{
    int x,y;
} obstacle1;
/*
	function iDraw() is called again and again by the system.
*/
int random(int min, int max) //range : [min, max]
{
    static bool first = true;
    if (first)
    {
        srand( time(NULL) );
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
}

void itoa(int n,char *str)
{
    int i=0,z;
    if(n/10==0){ str[0]='0',str[1]='0',str[2]=n+'0',str[3]='\0';}
    else if(n/100==0){str[0]='0',str[1]=(n/10)%10+'0',str[2]=n%10+'0',str[3]='\0';}
    else if(n/1000==0){str[0]=(n/100)%10+'0',str[1]=(n/10)%10+'0',str[2]=n%10+'0',str[3]='\0';}
}

void ShowStats()
{
    char score[20]="Score: ";
    //char health[20]="Health: ";
    char temp[10];
    itoa(Score,temp);
    strcat(score,temp);
    //itoa(Health,temp);
    //strcat(health,temp);
    iSetColor(0,0,00);
    iText(100,WindowHeight-100,score);
    //iText(100,WindowHeight-50,health);
}
struct HealthBar{
    int x=100,y=WindowHeight-50,health=120,index=0;//
} healthbar;
char HealthImages[][100]={"Bird/HEALTH0.bmp",
"Bird/HEALTH1.bmp",
"Bird/HEALTH2.bmp",
"Bird/HEALTH3.bmp",
"Bird/HEALTH4.bmp",
"Bird/HEALTH5.bmp",
"Bird/HEALTH6.bmp"};

void iDraw()
{

    iClear();
    if(scene==0)
    {
        iShowBMP(0,0,"bg0.bmp");

        for(int i=0; i<3; i++)
        {
            iShowBMP2(press[i].x,press[i].y,"Buttons/playbutton.bmp",0xffffff);
        }
    }
    if(scene==1)
    {
        if(healthbar.health<=0){
            MaxScore=MaxScore>Score?MaxScore:Score;
            scene=3;
            FILE * fp;
            fp=fopen("Scores.txt","w");
            fprintf(fp,"%d",MaxScore);
            fclose(fp);
        }
        iShowBMP(0,0,"gravballbg.bmp");
        ShowStats();
        if(mc.idle)
        {
            iShowBMP2(mc.x,mc.y,idle[idleindex],0xffffff);
        }
        else if(mc.jump1)
        {
            iShowBMP2(mc.x,mc.y,jump[jumpindex],0xffffff);
        }
        else if(mc.runright || mc.runleft)
        {
            iShowBMP2(mc.x,mc.y,run[runindex],0xffffff);
        }
        else if(mc.shoot)
        {
            iShowBMP2(mc.x,mc.y,shoot[shootindex],0xffffff);
        }
        for(int i=0; i<sizeof(bullet)/sizeof(bullet[0]); i++)
        {
            if(bullet[i].active) iShowBMP2(bullet[i].x,bullet[i].y,"Char/SHOOT/Bullet1.bmp",0x000000);
        }
        int z;
        if(healthbar.health<=0){
            z=0;
        }
        else z=healthbar.health/20;
        iShowBMP2(healthbar.x,healthbar.y,HealthImages[z],0xffffff);
    }
    if(scene==2)
    {
        if(healthbar.health<=0) {
            MaxScore=MaxScore>Score?MaxScore:Score;
            scene=3;
            FILE * fp;
            fp=fopen("Scores.txt","w");
            fprintf(fp,"%d",MaxScore);
            fclose(fp);
        }
        for(int i=0; i<(sizeof(bg2upper)/sizeof(bg2upper[0])); i++)
        {
            iShowBMP2(i*50-temp,107,bg2upper[(bg2upperindex+i)%(sizeof(bg2upper)/sizeof(bg2upper[0]))],-1);
        }
        for(int i=0; i<(sizeof(bg2)/sizeof(bg2[0])); i++)
        {
            iShowBMP2(i*75,0,bg2[(bg2index+i)%(sizeof(bg2)/sizeof(bg2[0]))],-1);
        }
        iShowBMP(0,107,bg2upper[0]);
        ShowStats();
        if(mc.idle)
        {
            iShowBMP2(mc.x,mc.y,idle[idleindex],0xffffff);
        }
        else if(mc.jump1)
        {
            iShowBMP2(mc.x,mc.y,jump[jumpindex],0xffffff);
        }
        else if(mc.runright || mc.runleft)
        {
            iShowBMP2(mc.x,mc.y,run[runindex],0xffffff);
        }
        else if(mc.shoot)
        {
            iShowBMP2(mc.x,mc.y,shoot[shootindex],0xffffff);
        }
        for(int i=0; i<sizeof(bullet)/sizeof(bullet[0]); i++)
        {
            if(bullet[i].active) iShowBMP2(bullet[i].x,bullet[i].y,"Char/SHOOT/Bullet1.bmp",0x000000);
        }
        for(int i=0; i<birdnum; i++)
        {
            //iSetColor(0,0,200);
            if(bird[i].alive) iShowBMP2(bird[i].x,bird[i].y,BirdImages[bird[i].birdindex],0xffffff);
            if(bird[i].bmbstart && !bird[i].bmbend)
            {
                //iSetColor(0,0,255);
                //iFilledCircle(bird[i].bmbx,bird[i].bmby,10);
                iShowBMP2(bird[i].bmbx,bird[i].bmby,"Char/SHOOT/bomb.bmp",0xffffff);
            }
            if(bird[i].bmbexplodestart && !bird[i].bmbexplodeend){
                ++bird[i].explosioncounter;
                iShowBMP2(bird[i].bmbx-25,bird[i].bmby-25,"Char/SHOOT/explosion1.bmp",0xffffff);
            }
            if(bird[i].explosioncounter>15){
                bird[i].explosioncounter=0;
                bird[i].bmbexplodeend=true;
            }
        }
        for(int i=0; i<monstercount; i++)
        {
            if(monster[i].alive)
            {
                iShowBMP2(monster[i].x,monster[i].y,MonsterImages[monster[i].monsterindex],0xffffff);
            }
        }
        int z;
        if(healthbar.health<=0){
            z=0;
        }
        else z=healthbar.health/20;
        iShowBMP2(healthbar.x,healthbar.y,HealthImages[z],0xffffff);
    }
    if(scene==3){
        iShowBMP2(0, 0, "GameOverScreen.bmp", -1);
        FILE * fp;
        fp=fopen("Scores.txt","r");
        int z;
        fscanf(fp,"%d",&z);
        fclose(fp);
        char str[500]="Your Score is ";
        char num[10];
        itoa(z,num);
        strcat(str,num);
        iSetColor(255,255,255);
        iText(650, 400,str, GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(press[3].x,press[3].y,"Buttons/menubutton.bmp",0xffffff);
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
        printf("(%d %d)\n",mx,my);
        if(scene==0)
        {
            for(int i=0; i<buttons; i++)
            {
                if(mx<press[i].x+200 && mx>press[i].x && my<press[i].y+121 && my>press[i].y)
                {
                    scene=1;
                    break;
                }
            }
        }
        if(scene==3){
            if(mx<press[3].x+200 && mx>press[3].x && my<press[3].y+121 && my>press[3].y) scene=0;
        }
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
    if(key=='y' && mc.jump1==false && mc.jump2==false)
    {
        mc.jump1=true;
        mc.dy=20;
        mc.idle=mc.runleft=mc.runright=mc.shoot=false;
    }
    else if(key=='y' && mc.jump1==true && mc.jump2==false)
    {
        mc.jump1=true;
        mc.jump2=true;
        mc.dy=20;
        mc.idle=mc.runleft=mc.runright=mc.shoot=false;
    }
    if(key=='j' && mc.x<WindowWidth)
    {
        if(scene==2)
        {
            (++temp);
            if(temp>upperbgspeed)
            {
                (++bg2upperindex)%=sizeof(bg2upper)/sizeof(bg2upper[0]);
                temp=0;
            }
            ++lowerbgspeed;
            if(lowerbgspeed>2)
            {
                (++bg2index)%=sizeof(bg2)/sizeof(bg2[0]);
                lowerbgspeed=0;
            }
            for(int i=0; i<birdnum; i++)
            {
                bird[i].x-=relativespeed;
                if(bird[i].bmbstart && !bird[i].bmbexplodeend) bird[i].bmbx-=relativespeed;
            }
            for(int i=0; i<sizeof(MonsterImages)/sizeof(MonsterImages[0]); i++)
            {
                if(monster[i].alive)
                {
                    monster[i].x-=relativespeed;
                }
            }
        }
        mc.idle=false;
        mc.runright=true;
        mc.runleft=false;
        runrighttemp=0;
    }
    if(key=='f' && mc.x>0)
    {
        if(scene==2)
        {
            --temp;
            if(temp<0)
            {
                (--bg2upperindex);
                bg2upperindex=bg2upperindex<0?sizeof(bg2upper)/sizeof(bg2upper[0])+bg2upperindex:bg2upperindex;
                temp=upperbgspeed;
            }
            --lowerbgspeed;
            if(lowerbgspeed<0)
            {
                --bg2index;
                bg2index=bg2index<0?sizeof(bg2)/sizeof(bg2[0])+bg2index:bg2index;
                lowerbgspeed=2;
            }
            for(int i=0; i<birdnum; i++)
            {
                bird[i].x+=relativespeed;
                if(bird[i].bmbstart && !bird[i].bmbexplodeend) bird[i].bmbx+=relativespeed;
            }
            for(int i=0; i<sizeof(MonsterImages)/sizeof(MonsterImages[0]); i++)
            {
                if(monster[i].alive)
                {
                    monster[i].x+=relativespeed;
                }
            }
        }
        mc.runright=false;
        mc.idle=false;
        mc.runleft=true;
        runlefttemp=5;
    }
    if(key=='i')
    {
        mc.shoot=true;
        for(int i=0; i<sizeof(bullet)/sizeof(bullet[0]); i++)
        {
            if(!bullet[i].active)
            {
                bullet[i].active=true;
                bullet[i].x=mc.x+124;
                bullet[i].y=(scene==2)?128:108;
                break;
            }
        }
        mc.jump1=mc.jump2=mc.idle=mc.runleft=mc.runright=false;
    }
    int z=scene;
    if(key=='p')
    {
        just_paused=scene;
        iPauseTimer(0);
        scene=0;
    }
    if(key=='r')
    {
        iResumeTimer(0);
        scene=just_paused;
        just_paused=0;
    }
    if(key=='x')
    {
        (++scene)%=4;
    }
    if(key=='S')
    {
        if(monstercount<10)
        {
            monstercount++;
        }
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
    //place your codes for other keys here
}

void CharCord()
{
    if(scene==1)
    {
        if(mc.shoot)
        {
            (++shootindex)%=sizeof(shoot)/sizeof(shoot[0]);
            shoottemp++;
            if(shoottemp>5)
            {
                mc.shoot=false;
                mc.idle=true;
                shoottemp=0;
            }
        }
        else if(mc.idle)
        {
            (++idleindex)%=sizeof(idle)/sizeof(idle[0]);
        }
        else if(mc.runright)
        {
            mc.x+=10;
            (++runindex)%=sizeof(run)/sizeof(run[0]);
            runrighttemp++;
            if(runrighttemp>5)
            {
                mc.runright=false;
                mc.idle=true;
                runrighttemp=0;
            }
        }
        else if(mc.runleft)
        {
            mc.x-=10;
            runindex=--runindex<0?sizeof(run)/sizeof(run[0])+runindex:runindex;
            runlefttemp--;
            if(runlefttemp<0)
            {
                mc.runleft=false;
                mc.idle=true;
                runlefttemp=5;
            }
        }
        for(int i=0; i<sizeof(bullet)/sizeof(bullet[0]); i++)
        {
            if(bullet[i].active)
            {
                bullet[i].x+=8;
            }
        }
        if(mc.jump1)
        {
            if(jumpindex<sizeof(jump)/sizeof(jump[0])-4)
            {
                jumpindex++;
            }
            //mc.runleft=mc.runright=false;
            mc.dy+=-2;
            mc.y+=mc.dy;
            if(mc.y<Ground1)
            {
                mc.jump1=false;
                mc.jump2=false;
                mc.idle=true;
                jumpindex=0;
            }
        }
        else
        {
            mc.y=Ground1;
        }
        if(mc.x>WindowWidth-10)
        {
            scene=2;
            just_changed=1;
            Score=20;
        }
    }
    if(scene==2)
    {
        if(just_changed)
        {
            mc.x=300;
            mc.y=Ground2+2;
            just_changed=0;
        }
        if(mc.shoot)
        {
            (++shootindex)%=sizeof(shoot)/sizeof(shoot[0]);
            shoottemp++;
            if(shoottemp>5)
            {
                mc.shoot=false;
                mc.idle=true;
                shoottemp=0;
            }
        }
        else if(mc.idle)
        {
            (++idleindex)%=sizeof(idle)/sizeof(idle[0]);
        }
        else if(mc.runright)
        {
            temp2++;
            (++runindex)%=sizeof(run)/sizeof(run[0]);
            runrighttemp++;
            if(runrighttemp>runspeed)
            {
                mc.runright=false;
                mc.idle=true;
                runrighttemp=0;
            }
        }
        else if(mc.runleft)
        {
            runindex=--runindex<0?sizeof(run)/sizeof(run[0])+runindex:runindex;
            runlefttemp--;
            if(runlefttemp<0)
            {
                mc.runleft=false;
                mc.idle=true;
                runlefttemp=runspeed;
            }
        }
        for(int i=0; i<sizeof(bullet)/sizeof(bullet[0]); i++)
        {
            if(bullet[i].active)
            {
                bullet[i].x+=8;
                for(int j=0; j<monstercount; j++)
                {
                    if(monster[j].alive && bullet[i].x>monster[j].x)
                    {
                        monster[j].life--;
                        bullet[i].active=false;
                        if(monster[j].life==0) {monster[j].alive=false;Score+=5;}
                    }
                }
            }
        }
        if(mc.jump1)
        {
            if(jumpindex<sizeof(jump)/sizeof(jump[0])-4)
            {
                jumpindex++;
            }
            mc.dy+=-2;
            mc.y+=mc.dy;
            if(mc.y<Ground2)
            {
                mc.jump1=mc.jump2=false;
                jumpindex=0;
                mc.idle=true;
            }
        }
        else
        {
            mc.y=Ground2;
        }
    }
}
void MonsterCord()
{
    if(scene==2)
    {
        if(Score>250) monstercount=10;
        else if(Score>200) monstercount=8;
        else if(Score>150) monstercount=6;
        else if(Score>100) monstercount=4;
        else if(Score>50) monstercount=3;
        (++monstertemp);
        if(monstertemp>5)
        {
            for(int i=0; i<monstercount; i++)
            {
                if(monster[i].alive)
                {
                    monster[i].x+=monster[i].dx;
                    (++monster[i].monsterindex)%=sizeof(MonsterImages)/sizeof(MonsterImages[0]);
                }
                if(monster[i].alive && (monster[i].x-mc.x<100))
                {
                    monster[i].alive=false;
                    healthbar.health-=20;
                }
                if(!monster[i].alive)
                {
                    monster[i].alive=true;//random(1,100)>70?true:false;
                    if(monster[i].alive)
                    {
                        monster[i].life=2;
                        monster[i].dx=-random(8,12);
                        monster[i].monsterindex=random(0,sizeof(MonsterImages)/sizeof(MonsterImages[0])-1);
                        if(i==0) monster[i].x=WindowWidth;
                        else monster[i].x=monster[i-1].x+random(50,200);
                    }
                }
            }
            monstertemp=0;
        }
    }
}

void BirdCord()
{
    if(scene==2)
    {
        if(Score>250) birdnum=15;
        else if(Score>200) birdnum=12;
        else if(Score>150) birdnum=10;
        else if(Score>100) birdnum=8;
        else if(Score>50) birdnum=6;
        for(int i=0; i<birdnum; i++)
        {
            if(!bird[i].alive)
            {
                bird[i].x=random(WindowWidth-SideBar,WindowWidth+300);
                bird[i].y=random(450,600);
                bird[i].alive=true;
                bird[i].dx=-random(2,5);
                bird[i].bmbx=random(mc.x-10,mc.x+300);
                bird[i].bmby=bird[i].y;
            }
            if(bird[i].alive)
            {
                bird[i].x+=bird[i].dx;
                (++bird[i].birdindex)%=sizeof(BirdImages)/sizeof(BirdImages[0]);
            }
            if(!bird[i].bmbstart && bird[i].x<bird[i].bmbx)
            {
                bird[i].bmbstart=true;
            }
            if(bird[i].bmbstart && !bird[i].bmbend)
            {
                bird[i].bmby-=5;
            }
            if(bird[i].bmbstart && bird[i].bmby<=Ground2)
            {
                bird[i].bmbend=true;
                bird[i].bmbexplodestart=true;
            }
            if(bird[i].bmbexplodestart && !bird[i].bmbexplodeend && abs(mc.x+50-bird[i].bmbx)<=64 &&bird[i].explosioncounter==1){
                healthbar.health-=10;
            }
            if(bird[i].x<10 && bird[i].bmbexplodeend)
            {
                bird[i].alive=bird[i].bmbstart=bird[i].bmbend=bird[i].bmbexplodestart=bird[i].bmbexplodeend=false;

            }
        }
    }
}
int main()
{
    mc.x=400,mc.y=Ground1+2,mc.dy=0,mc.idle=true;
    birdsalive=0;
    int s=0;
    obstacle1.x=400;
    obstacle1.y=Ground1-2;
    for(int i=0; i<3; i++)
    {
        press[i].x=100;
        press[i].y=500-s;
        s+=200;
    }
    press[3].x=638,press[3].y=250;
    //bullet.active=false;
    for(int i=0;i<10;i++){
        monster[i].life=2;
        monster[i].alive=false;
    }
    FILE * fp;
    fp=fopen("Scores.txt","r");
    fscanf(fp,"%d",&MaxScore);
    fclose(fp);
    iSetTimer(40, CharCord);
    iSetTimer(60,BirdCord);
    iSetTimer(60,MonsterCord);
    iInitialize(WindowWidth, WindowHeight, "bounce");

    return 0;
}




