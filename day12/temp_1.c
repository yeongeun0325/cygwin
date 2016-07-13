#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<termios.h>

#include"../engine/engine2d.h"
#include"../mapEditor/map.h"

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop=1;

_S_MAP_OBJECT gScreenBuffer;
_S_MAP_OBJECT gF22Raptor;
_S_MAP_OBJECT gScreenBuffer2;

int xpos,ypos;

int main()
{
	set_conio_terminal_mode();
	acc_tick=last_tick=0;
	system("clear");

	map_init(&gScreenBuffer);
	map_new(&gScreenBuffer,17,16);

	map_init(&gF22Raptor);
	map_new(&gF22Raptor,35,16);
	map_init(&gF22Raptor);
	map_load(&gF22Raptor,"plane.dat");
	
	map_init(&gScreenBuffer2);
	map_new(&gScreenBuffer2,17,16);

	while(bLoop){
		//타이밍처리
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick=work_timer.tv_sec+(double)(work_timer.tv_nsec*1e-9);
		double delta_tick=cur_tick-last_tick;
		last_tick=cur_tick;	

		//실시간입력
		if(kbhit()!=0){
			char ch=getch();
			if(ch=='q'){
				bLoop=0;
				puts("bye bye~\r\n");
			}
			else if(ch=='w'){
				ypos+=1;
			}
			else if(ch=='s'){
				ypos-=1;
			}
			else if(ch=='d'){
				xpos+=1;
			}
			else if(ch=='a'){
				xpos-=1;
			}
		}

		//타이밍 계싼
		acc_tick+=delta_tick;
		if(acc_tick>1.0){
			
			map_drawTile(&gScreenBuffer2,xpos,ypos,&gScreenBuffer);
			map_drawTile_trn(&gF22Raptor,xpos,ypos,&gScreenBuffer);

			gotoxy(0,0);
			map_dump(&gScreenBuffer,Default_Tilepalette);
			puts("move : w,a,s,d\r\n");
			puts"quit:q\r\n");
			acc_tick=0;
		}
	}

	return 0;
}

