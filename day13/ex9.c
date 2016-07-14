#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"

#include "bullet.h"
#include "plane.h"

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuffer[2];
_S_MAP_OBJECT gPlayer;

_S_Plane gPlayerObject;

_S_MAP_OBJECT gBulletModel;
_S_BULLET_OBJECT gBulletObject;

//게임오브잭트 선언 

int main()
{	
	system("clear");

	for(int i=0;i<2;i++){
		map_init(&gScreenBuffer[i]);
		gScreenBuffer[i].fpnew(&gScreenBuffer[i],35,16);
		//map_new(&gScreenBuffer[i],35,16);
	}

	map_init(&gPlayer);
	gPlayer.fpload(&gPlayer,"plane.dat");
	//map_load(&gPlayer,"plane.dat");

	Plane_init(&gPlayerObject,&gPlayer,17,10);

	map_init(&gBulletModel);
	gBulletModel.fpload(&gBulletModel,"bullet1.dat");
	//map_load(&gBulletModel,"bullet1.dat");

	bullet_init(&gBulletObject,0,0,0,&gBulletModel);
	
	set_conio_terminal_mode();
	acc_tick=last_tick=0;

	while(bLoop) {
		//타이밍처리 
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + 
			(double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;
		last_tick = cur_tick;
		//실시간 입력
		if(kbhit() != 0) {
			char ch = getch();
			if(ch == 'q') {
				bLoop = 0;
				puts("bye~ \r");
			}
			gPlayerObject.fpApply(&gPlayerObject,delta_tick,ch);
			//Plane_Apply(&gPlayerObject,delta_tick,ch);
		}
	
		//타이밍 계산 
		acc_tick += delta_tick;
		bullet_apply(&gBulletObject,delta_tick);
		
		if(acc_tick > 0.1) {
			//puts("tick..\r");
			gotoxy(0,0);
			gScreenBuffer[0].fpdrawTile(&gScreenBuffer[0],0,0,&gScreenBuffer[1]);
			//map_drawTile(&gScreenBuffer[0],0,0,&gScreenBuffer[1]);
			gPlayerObject.fpDraw(&gPlayerObject,&gScreenBuffer[1]);
			//Plane_Draw(&gPlayerObject,&gScreenBuffer[1]);
			gScreenBuffer[1].fpdump(&gScreenBuffer[1],Default_Tilepalete);
			//map_dump(&gScreenBuffer[1],Default_Tilepalete);
			acc_tick = 0;
		}

	}

	return 0;

}
