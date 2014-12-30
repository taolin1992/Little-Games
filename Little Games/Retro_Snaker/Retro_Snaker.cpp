#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "colorConsole.h"    




HANDLE handle;
int dx=18;
int dy=2;
int fx,fy;
int lasttail=75;
int lasthead=77;
int hx(5),hy(1),tx(1),ty(1);
int direction=77;
int max_delay=50;
int count=0;
bool oneloop=true;
int map[20][24]={77,77,77,77};
struct snakehead
{
	int x;
	int y;
}head={hx,hy};
struct snaketail
{
	int x;
	int y;
}tail={tx,ty};
WORD color[7] =
{ 
	FOREGROUND_RED|FOREGROUND_INTENSITY,
    FOREGROUND_GREEN|FOREGROUND_INTENSITY,
	FOREGROUND_BLUE|FOREGROUND_INTENSITY,
	FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY,
	FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
	FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
	FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
};		





void init();
void drawsnake(int x,int y);
void clearsnake(int x,int y);
void gameover();
bool available(int x,int y);
void createfruit();









void main()
{
	srand(unsigned(time(0)));
	init();

	while(oneloop)
	{
		int delay=0;
		while(delay<max_delay)
		{
			 if(_kbhit())
			 {
				 int ch=_getch();
				 switch (ch)
				 {
				 case 72:
					 {
						 direction=72;
					 }
					 break;
				 case 80:
					 {
                         direction=80;
					 }
					 break;
				 case 75:
					 {
						 direction=75;
					 }
					 break;
				 case 77:
					 {
						 direction=77;
					 }
					 break;
				 case 27:
					 {
						 exit(EXIT_SUCCESS);
					 }
					 break;
				 }
			 }
		 Sleep(4);
		 delay++;
		}
		switch (map[(tail.y)-1][(tail.x)-1])
        {
				 case 72:
					 {
						 clearsnake(tail.x,tail.y);
						 (tail.y)--;
						 lasttail=80;
					 }
					 break;
				 case 80:
					 {
						 clearsnake(tail.x,tail.y);
                         (tail.y)++;
						 lasttail=72;
					 }
					 break;
				 case 75:
					 {
						 clearsnake(tail.x,tail.y);
						 (tail.x)--;
						 lasttail=77;
					 }
					 break;
				 case 77:
					 {
						 clearsnake(tail.x,tail.y);
						 (tail.x)++;
						 lasttail=75;
					 }
					 break;
		}
		map[(head.y)-1][(head.x)-1]=direction;
		if(((lasthead==80)&&(direction==72))||((lasthead==72)&&(direction==80))||((lasthead==75)&&(direction==77))||((lasthead==77)&&(direction==75)))
						 {
							 map[(head.y)-1][(head.x)-1]=lasthead;
							 direction=lasthead;
						 }
		switch (map[(head.y)-1][(head.x)-1])
		{
				 case 72:
					 {
						 if(available(head.x,head.y-1))
						 {
						 (head.y)--;
						 drawsnake(head.x,head.y);
						 if(map[(head.y)-1][(head.x)-1]==-1)
						 {
							 switch (lasttail)
							 {
							 case 72:
								 {
									 tail.y--;
								     drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=80;
								 }
								 break;
							 case 80:
								 {
									 tail.y++;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=72;
								 }
								 break;
							 case 75:
								 {
									 tail.x--;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=77;
								 }
								 break;
							 case 77:
								 {
									 tail.x++;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=75;
								 }
								 break;
							 }
							 createfruit();
							 count++;
							 char string[5];
							 textout(handle,10,7,color+3,1,"     ");
							 textout(handle,10,7,color+3,1,itoa(count,string,10));
						 }
						 }
						 else gameover();
					 }
					 break;
				 case 80:
					 {
						  if(available(head.x,head.y+1))
						  {
                         (head.y)++;
						 drawsnake(head.x,head.y);
						 if(map[(head.y)-1][(head.x)-1]==-1)
						 {
							 switch (lasttail)
							 {
							 case 72:
								 {
									 tail.y--;
								     drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=80;
								 }
								 break;
							 case 80:
								 {
									 tail.y++;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=72;
								 }
								 break;
							 case 75:
								 {
									 tail.x--;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=77;
								 }
								 break;
							 case 77:
								 {
									 tail.x++;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=75;
								 }
								 break;
							 }
							 createfruit();
							 count++;
							 char string[5];
							 textout(handle,10,7,color+3,1,"     ");
							 textout(handle,10,7,color+3,1,itoa(count,string,10));
						 }
						  }
						  else gameover();
					 }
					 break;
				 case 75:
					 {
						  if(available(head.x-1,head.y))
						  {
						 (head.x)--;
						 drawsnake(head.x,head.y);
						 if(map[(head.y)-1][(head.x)-1]==-1)
						 {
							 switch (lasttail)
							 {
							 case 72:
								 {
									 tail.y--;
								     drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=80;
								 }
								 break;
							 case 80:
								 {
									 tail.y++;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=72;
								 }
								 break;
							 case 75:
								 {
									 tail.x--;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=77;
								 }
								 break;
							 case 77:
								 {
									 tail.x++;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=75;
								 }
								 break;
							 }
							 createfruit();
							 count++;
							 char string[5];
							 textout(handle,10,7,color+3,1,"     ");
							 textout(handle,10,7,color+3,1,itoa(count,string,10));
						 }
						  }
						  else gameover();
					 }
					 break;
				 case 77:
					 {
						 if(available(head.x+1,head.y))
						 {
						 (head.x)++;
						 drawsnake(head.x,head.y);
						 if(map[(head.y)-1][(head.x)-1]==-1)
						 {
							 switch (lasttail)
							 {
							 case 72:
								 {
									 tail.y--;
								     drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=80;
								 }
								 break;
							 case 80:
								 {
									 tail.y++;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=72;
								 }
								 break;
							 case 75:
								 {
									 tail.x--;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=77;
								 }
								 break;
							 case 77:
								 {
									 tail.x++;
									 drawsnake(tail.x,tail.y);
									 map[tail.y-1][tail.x-1]=75;
								 }
								 break;
							 }
							 createfruit();
							 count++;
							 char string[5];
							 textout(handle,10,7,color+3,1,"     ");
							 textout(handle,10,7,color+3,1,itoa(count,string,10));
						 }
						 }
						 else gameover();
					 }
					 break;
		}
		lasthead=direction;
	}
}




void init()
{
	handle=initiate();
	textout(handle,dx,dy-1,color,1,"¡ó¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¡ó");
	textout(handle,dx,dy+20,color,1,"¡ó¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¡ó");
	for (int i=0;i<20;i++)
		textout(handle,dx,dy+i,color,1,"¨U");
	for (int i=0;i<20;i++)
		textout(handle,dx+50,dy+i,color,1,"¨U");
	drawsnake(1,1);
	drawsnake(2,1);
	drawsnake(3,1);
	drawsnake(4,1);
	drawsnake(5,1);
	char string[5];
    textout(handle,10,7,color+3,1,itoa(count,string,10));
	textout(handle,30,7,color+3,1,"Press 1-4");
	char q='q';
    while((q!='1')&&(q!='2')&&(q!='3')&&(q!='4'))
	{
		q=_getch();
	}
	switch (q)
	{
	case '1':
        max_delay=50;
		break;
	case '2':
		max_delay=25;
		break;
	case '3':
		max_delay=20;
		break;
	case '4':
		max_delay=15;
		break;
	}
	textout(handle,30,7,color+3,1,"               ");
	createfruit();

}


void drawsnake(int x,int y)
{
	textout(handle,dx+2*x,dy+y-1,color+1,1,"¡ö");
}


void clearsnake(int x,int y)
{
	textout(handle,dx+2*x,dy+y-1,color+1,1,"  ");
	map[y-1][x-1]=0;
}


void gameover()
{
	textout(handle,3,3,color+4,1,"You lost!!!!");
	switch (lasttail)
							 {
							 case 72:
								 {
									 tail.y--;
								     drawsnake(tail.x,tail.y);
								 }
								 break;
							 case 80:
								 {
									 tail.y++;
									 drawsnake(tail.x,tail.y);
								 }
								 break;
							 case 75:
								 {
									 tail.x--;
									 drawsnake(tail.x,tail.y);
								 }
								 break;
							 case 77:
								 {
									 tail.x++;
									 drawsnake(tail.x,tail.y);
								 }
								 break;
							 }
	Sleep(1000);
	exit(EXIT_SUCCESS);
}


bool available(int x,int y)
{
	if((x<1)||(x>24)||(y<1)||(y>20))return false;
	if(map[y-1][x-1]>0)return false;
	return true;
}


void createfruit()
{
	fx=1+rand()%24;
	fy=1+rand()%20;
	while(map[fy-1][fx-1]!=0)
	{
		fx=1+rand()%24;
	    fy=1+rand()%20;
	}
	map[fy-1][fx-1]=-1;
	textout(handle,dx+2*fx,dy+fy-1,color+2,1,"¡ô");
}


