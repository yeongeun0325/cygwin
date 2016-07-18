#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <math.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"
#include "alien.h"
#include "bullet.h"

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuffer[2];
_S_MAP_OBJECT gAlienModel;
_S_MAP_OBJECT gPlasmaModel;

//게임오브잭트 선언 
_S_ALIEN_OBJECT gAlienObject;
_S_BULLET_OBJECT gPlasmaObject;

int main()
{	
	system("clear");
	
	for(int i=0;i<2;i++){
		map_init(&gScreenBuffer[i]);
		gScreenBuffer[i].fpnew(&gScreenBuffer[i],35,16);
		//map_new(&gScreenBuffer[i],35,16);
	}

	map_init(&gAlienModel);
	map_load(&gAlienModel,"alien.dat");

	map_init(&gPlasmaModel);
	map_load(&gPlasmaModel,"plasma.dat");

	Alien_init(&gAlienObject,&gAlienModel);
	bullet_init(&gPlasmaObject,0,0,0,&gPlasmaModel);

	gPlasmaObject.m_pBullet=&gPlasmaObject;

	gAlienObject.m_nFSM=1;
	gAlienObject.m_fXpos=5;
	gAlienObject.m_fYpos=5;


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
		}

		//타이밍 계산 
		acc_tick += delta_tick;
		gAlienObject.pfApply(&gAlienObject,delta_tick);
		gPlasmaObject.pfApply(&gPlasmaObject,delta_tick);

		if(acc_tick > 0.1) {
			//puts("tick..\r");
			gotoxy(0,0);
			map_drawTile(&gScreenBuffer[0],0,0,&gScreenBuffer[1]);
			gAlienObject.pfDraw(&gAlienObject,&gScreenBuffer[1]);
			gPlasmaObject.pfDraw(&gPlasmaObject,&gScreenBuffer[1]);

			map_dump(&gScreenBuffer[1],Default_Tilepalete);
			acc_tick = 0;
		}

	}

	return 0;

}
