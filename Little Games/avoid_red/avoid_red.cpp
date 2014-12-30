#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "colorConsole.h"   
using namespace std;



HANDLE handle;
int x=7,y=20;
int dx=18,dy=2;
int map[20][12]={0};
int count=300;
int heihei=2;
int haha=0;
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






void gameover();
void init();
bool available(int x,int y);
void draw(int x,int y);
void clear(int x,int y);




DWORD WINAPI TT ( LPVOID lpParam)
{
	int q=(int)lpParam;
	for (int y=1;y<21;y++)
	{
	if(map[y][q]==1){y--;continue;}
		draw(q,y);
		Sleep(count);
		if(map[y+1][q]==2)gameover();
		clear(q,y);
	}
	return TRUE;
}

DWORD WINAPI ThreadFunc ( LPVOID lpParam)
{
	WORD wColors[1];
	wColors[0]=FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY;
	DWORD dw;
	while(1)
	{
		int x=1+rand()%12;
		CreateThread(NULL,0,TT,(void*)x,0,&dw);
		Sleep(count);
	}
	return TRUE;
}
void main(void)
{
	srand(unsigned(time(0)));
	init();
	char s[5];
	textout(handle,50,6,color+3,1,itoa(haha,s,10));
	DWORD dwThreadId;
	CreateThread(NULL,0,ThreadFunc,0,0,&dwThreadId);
	textout(handle,dx+2*x,y-1+dy,color+3,1,"¡ô");
	map[y][x]=2;
	while(1)
	{
	
		if(_kbhit())
	    {
		
			int ch=_getch();
			switch(ch)
			{
			case 72:
				if(available(x,y-1))
				{
					haha++;
					textout(handle,dx+2*x,y-1+dy,color+3,1,"  ");
				map[y][x]=0;
				y--;
				textout(handle,dx+2*x,y-1+dy,color+3,1,"¡ô");
				map[y][x]=2;
				textout(handle,50,6,color+3,1,"     ");
				textout(handle,50,6,color+3,1,itoa(haha,s,10));
				if(count>(heihei+1))
				count=count-heihei;
				}
			break;
		    case 80:
				if(available(x,y+1))
				{
					haha++;
				textout(handle,dx+2*x,y-1+dy,color+3,1,"  ");
				map[y][x]=0;
				y++;
				textout(handle,dx+2*x,y-1+dy,color+3,1,"¡ô");
				map[y][x]=2;
				textout(handle,50,6,color+3,1,"     ");
				textout(handle,50,6,color+3,1,itoa(haha,s,10));
				if(count>(heihei+1))
				count=count-heihei;
				}
			break;
			case 75:
				if(available(x-1,y))
				{
					haha++;
				textout(handle,dx+2*x,y-1+dy,color+3,1,"  ");
				map[y][x]=0;
				x--;
				textout(handle,dx+2*x,y-1+dy,color+3,1,"¡ô");
				map[y][x]=2;
				textout(handle,50,6,color+3,1,"     ");
				textout(handle,50,6,color+3,1,itoa(haha,s,10));
				if(count>(heihei+1))
				count=count-heihei;
				}
			break;
		    case 77:
				if(available(x+1,y))
				{
					haha++;
				textout(handle,dx+2*x,y-1+dy,color+3,1,"  ");
				map[y][x]=0;
				x++;
				textout(handle,dx+2*x,y-1+dy,color+3,1,"¡ô");
				map[y][x]=2;
				textout(handle,50,6,color+3,1,"     ");
				textout(handle,50,6,color+3,1,itoa(haha,s,10));
				if(count>(heihei+1))
				count=count-heihei;
				}
			break;
			case 27:
				{
						 exit(EXIT_SUCCESS);
				}	 
					 break;

			}
		}
	}
}



void init()
{
	handle=initiate();
	textout(handle,dx,dy-1,color,1,"¡ó¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¡ó");
	textout(handle,dx,dy+20,color,1,"¡ó¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¡ó");
	for (int i=0;i<20;i++)
		textout(handle,dx,dy+i,color,1,"¨U");
	for (int i=0;i<20;i++)
		textout(handle,dx+26,dy+i,color,1,"¨U");
	textout(handle,2,4,color+1,1,"Don't touch reds");
	textout(handle,2,5,color+1,1,"Declining faster");
	textout(handle,2,6,color+1,1,"and faster");
}
	

bool available(int x,int y)
{
	if((x<=0)||(x>=13)||(y<=0)||(y>=21))return false;
	if(map[y][x]==1)
		gameover();
	return true;
}

	

void draw(int x,int y)
{
	textout(handle,dx+2*x,y-1+dy,color,1,"¡ö");
	map[y][x]=1;
}

void clear(int x,int y)
{
	textout(handle,dx+2*x,y-1+dy,color,1,"  ");
	map[y][x]=0;
}



void gameover()
{
	
	textout(handle,50,7,color,1,"You lost!");
	Sleep(3000);
	exit(EXIT_SUCCESS);
}





