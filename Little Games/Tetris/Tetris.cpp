#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "colorConsole.h"   
using namespace std;



HANDLE handle;
int vc=7;
int deletelinenum=0;
int max_delay=250;
int downdelay=1000;
int num,nextnum;
int maph=22;
int mapw=18;
int level=1;
int score=0;
int cscore=0;
int dx=18;
int dy=2;
int x,y;
int a[4][4];
int b[4][4];
int map[20][12]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
int h=4,w=4;
bool oneloop=true;
WORD square_color[7] =
{ 
	FOREGROUND_RED|FOREGROUND_INTENSITY,
    FOREGROUND_GREEN|FOREGROUND_INTENSITY,
	FOREGROUND_BLUE|FOREGROUND_INTENSITY,
	FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY,
	FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
	FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
	FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
};		
int blocks[50][4][4]=
{
	{1,1,1,1},
	{2,2,2,0,2},
	{3,3,3,0,0,0,3},
	{4,4,4,0,0,4},
	{5,5,0,0,0,5,5},
	{0,6,6,0,6,6},
	{7,7,0,0,7,7},
	{1,1,1,1},
	{2,2,2,0,2},
	{3,3,3,0,0,0,3},
	{4,4,4,0,0,4},
	{5,5,0,0,0,5,5},
	{0,6,6,0,6,6},
	{7,7,0,0,7,7},
	{1,1,1,1},
	{2,2,2,0,2},
	{3,3,3,0,0,0,3},
	{4,4,4,0,0,4},
	{5,5,0,0,0,5,5},
	{0,6,6,0,6,6},
	{7,7,0,0,7,7},
	{1,1,1,1},
	{2,2,2,0,2},
	{3,3,3,0,0,0,3},
	{4,4,4,0,0,4},
	{5,5,0,0,0,5,5},
	{0,6,6,0,6,6},
	{7,7,0,0,7,7},
	{{0,1},{1,1,1},{0,1}},
	{{0,1},{1,1,1},{0,1}},
    {{2,2},{0,2},{2,2}},
    {{0,3,3},{0,3},{3,3}},
    {{4,4,4},{4,0,4}},
	{{7,7,7},{7,0,7}},
    {{5,5,5},{0,5},{0,5}},
    {{0,1},{2,3,4},{7,5,6}},
	{1,1,1,1},
	{2,2,2,0,2},
	{3,3,3,0,0,0,3},
	{4,4,4,0,0,4},
	{5,5,0,0,0,5,5},
	{0,6,6,0,6,6},
	{7,7,0,0,7,7},
	{1,1,1,1},
	{2,2,2,0,2},
	{3,3,3,0,0,0,3},
	{4,4,4,0,0,4},
	{5,5,0,0,0,5,5},
	{0,6,6,0,6,6},
	{7,7,0,0,7,7}
};


			



void drawblocks(int a[],int x, int y , int w, int h);
void clearblocks(int a[], int x ,int y,int w, int h);
void init();
void turn(int a[][4]);
bool available(int a[],int x,int y,int w,int h);
void deleteline(int map[][12],int y);
void creatblocks(int num);



void main()
{
	srand(unsigned(time(0)));
	init();
	nextnum=rand()%vc;
	num=nextnum;
	nextnum=rand()%vc;
	creatblocks(nextnum);
	drawblocks(&a[0][0],17,17,w,h);
	creatblocks(num);
	drawblocks(&a[0][0],x,y,w,h);
	char string[5];
	textout(handle,dx+17*2,dy+2,square_color+3,1,itoa(score,string,10));
	textout(handle,dx+17*2,dy+6,square_color+3,1,itoa(level,string,10));
	textout(handle,dx+17*2,dy+10,square_color+3,1,itoa(downdelay,string,10));
	textout(handle,dx+50,dy+2,square_color+3,1,itoa(deletelinenum,string,10));
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
						 clearblocks(&a[0][0],x,y,w,h);
					     turn(a);
						 if(available(&a[0][0],x,y,w,h))
						 {
					         drawblocks(&a[0][0],x,y,w,h);
						 }
						 else
						 {
							 for(int i=0;i<3;i++)
								 turn(a);
							 drawblocks(&a[0][0],x,y,w,h);
						 }
					 }
					 break;
				 case 80:
					 {
                         delay=max_delay;
					 }
					 break;
				 case 75:
					 {
						 if(available(&a[0][0],x-1,y,w,h))
						 {
						 clearblocks(&a[0][0],x,y,w,h);
						 x--;
						 drawblocks(&a[0][0],x,y,w,h);
						 }
					 }
					 break;
				 case 77:
					 {
						 if(available(&a[0][0],x+1,y,w,h))
						 {
						 clearblocks(&a[0][0],x,y,w,h);
						 x++;
						 drawblocks(&a[0][0],x,y,w,h);
						 }
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
		if(available(&a[0][0],x,y+1,w,h))
		{
			clearblocks(&a[0][0],x,y,w,h);
			y++;
			drawblocks(&a[0][0],x,y,w,h);
		}
		else
		{
			if(y<=1)exit(EXIT_SUCCESS);
			for(int i=0;i<h;i++)
				for (int j=0;j<w;j++)
					if(a[i][j]>0)
					map[y+i-1][x+j-1]=a[i][j];
		    deleteline(map,y);
            num=nextnum;
			nextnum=rand()%vc;
			creatblocks(nextnum);
			for (int i=0;i<4;i++)
				for (int j=0;j<4;j++)
					textout(handle,dx+17*2+j*2,dy+16+i,square_color,1,"  ");
			drawblocks(&a[0][0],17,17,w,h);
			creatblocks(num);
			drawblocks(&a[0][0],x,y,w,h);
		}
	}
}



void drawblocks(int a[],int x, int y , int w, int h)
{
	for (int i=0;i<h;i++)
		for ( int j=0;j<w;j++)
			if(a[i*w+j]>0)
			textout(handle,2*x+2*j+dx,y+i+dy-1,square_color+a[i*w+j]-1,1,"¡ö");
}


void clearblocks(int a[],int x,int y, int w , int h )
{
	for (int i=0;i<h;i++)
		for ( int j=0;j<w;j++)
			if (a[i*w+j]>0)
				textout(handle,2*x+2*j+dx,y+i+dy-1,square_color,1,"  ");
}



void init()
{
	handle = initiate();
	textout(handle,dx,dy-1,square_color,1,"¡ó¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¡ó");
	textout(handle,dx,dy+20,square_color,1,"¡ó¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¡ó");
	for (int i=0;i<20;i++)
		textout(handle,dx,dy+i,square_color,1,"¨U");
	for (int i=0;i<20;i++)
		textout(handle,dx+26,dy+i,square_color,1,"¨U");
	textout(handle,dx+30,dy,square_color+3,1,"Score:");
	textout(handle,dx+42,dy,square_color+3,1,"Lines eliminated:");
	textout(handle,dx+30,dy+4,square_color+3,1,"Level:");
	textout(handle,dx+30,dy+8,square_color+3,1,"Latency:");
	textout(handle,dx+30,dy+13,square_color+3,1,"Next:");
	textout(handle,22,7,square_color+6,1,"Press 'A' or 'B'");
	int re=77;
	while(true)
	{
		re=_getch();
		if(re=='a')
		{
			vc=7;
			break;
		}
		if(re=='b')
		{
			vc=50;
			break;
		}
		else
		{
		    textout(handle,22,7,square_color+6,1,"Press 'A' or 'B'");
		}
	}
	textout(handle,26,11,square_color+6,1,"          ");
    textout(handle,26,12,square_color+6,1,"          ");
	textout(handle,22,7,square_color+6,1,"                   ");
	textout(handle,20,16,square_color+6,1,"                       ");
	textout(handle,2,4,square_color+1,1,"'A': easy mode");
	textout(handle,2,5,square_color+1,1,"'B': crazy mode");
}



void turn(int a[][4])//change dimension
{
	int b[4][4];
	
	for (int i=3;i>=0;i--)
		for (int j=0;j<4;j++)
			b[j][h-1-i]=a[i][j];	
	int line=0;//change dimension
	for (int i=0;i<4;i++)
	{
		if(!(b[0][line]||b[1][line]||b[2][line]||b[3][line]))
		{
			for(int q=1;q<=3;q++)
				for (int e=0;e<4;e++)
					b[e][q-1]=b[e][q];
			for (int q=0;q<4;q++)
				b[q][3]=0;
		}
	}
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			a[i][j]=b[i][j];
}

		


bool available(int a[],int x,int y,int w,int h)
{
	int e,f;
	f=0;
	for(int i=0;i<h;i++)
		for (int j=0;j<w;j++)
			if(a[w*i+j]>0)
			{
				e=i;
				if(j>f)
					f=j;
			}
	if(f+x>=13)return false;
	if(x<1)return false;
	if(y+e>=21) return false;
	for (int i=0;i<h;i++)
		for (int j=0;j<w;j++)
			if(map[i+y-1][x+j-1]&&a[w*i+j])
				return false;
	return true;
}



void deleteline(int map[][12],int y)//change dimension
{
	int p=3;
	if(p+y>20)
				p=3-(p+y-20);
	int v=p;
        for(;p>=0;p--)
		{
				if(map[y+v-1][0]&&map[y+v-1][1]&&map[y+v-1][2]&&map[y+v-1][3]&&map[y+v-1][4]&&map[y+v-1][5]&&map[y+v-1][6]&&map[y+v-1][7]&&map[y+v-1][8]&&map[y+v-1][9]&&map[y+v-1][10]&&map[y+v-1][11])
				{
					clearblocks(&map[y+v-1][0],1,y+v,12,1);
					Sleep(100);
					for(int o=y+v-1;o>0;o--)
					{
						clearblocks(&map[o-1][0],1,o,12,1);
						for(int j=0;j<12;j++)
						{
							map[o][j]=map[o-1][j];			
						}
						drawblocks(&map[o][0],1,o+1,12,1);	
					}
					for(int i=0;i<12;i++)
						map[0][i]=0;
					deletelinenum++;
					score=score+level;
					cscore++;
					if(cscore>=8)
					{
						level++;
						cscore=0;
						if(max_delay>10)
			                max_delay=250-(level-1)*20;
						downdelay=4*max_delay;
					}
					char qstring[5];
					textout(handle,dx+17*2,dy+6,square_color+3,1,"     ");
					textout(handle,dx+17*2,dy+6,square_color+3,1,itoa(level,qstring,10));
					textout(handle,dx+17*2,dy+2,square_color+3,1,"     ");
					textout(handle,dx+17*2,dy+2,square_color+3,1,itoa(score,qstring,10));
					textout(handle,dx+17*2,dy+10,square_color+3,1,"     ");
					textout(handle,dx+17*2,dy+10,square_color+3,1,itoa(downdelay,qstring,10));
					textout(handle,dx+50,dy+2,square_color+3,1,"     ");
					textout(handle,dx+50,dy+2,square_color+3,1,itoa(deletelinenum,qstring,10));
					Sleep(300);			
				}
				else
					v--;
		}
}




void creatblocks(int num)
{
	for (int i=0;i<h;i++)
		for (int j=0;j<w;j++)
			a[i][j]=blocks[num][i][j];
	x=6;
	y=1;
}

