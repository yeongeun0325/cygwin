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
#include "bullet.h"

#define PI 3.141592

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuffer[2];
_S_MAP_OBJECT gBulletModel;
_S_BULLET_OBJECT gBulletObject;

int main()
{
	set_conio_terminal_mode();
	acc_tick=last_tick=0;

	for(int i=0;i<2;i++){
		map_init(&gScreenBuffer[i]);
		map_new(&gScreenBuffer[i],35,15);
	}
	
	map_init(&gBulletModel);
	map_load(&gBulletModel,"plasma.dat");

	bullet_init(&gBulletObject,0,0,0,&gBulletModel);

	system("clear");

	int target_x,target_y;
	target_x=3; target_y=2;

	int fire_x=24;
	int fire_y=12;

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
			else if(ch=='j'){
				double vx,vy,c;
				double vx2,vy2;
				double angle=0;

				angle+=(delta_tick*45);
				double rad=(angle/180.0)*PI;

				vx=(target_x-fire_x)*cos(rad)-(target_y-fire_y)*sin(rad);
				vy=(target_x-fire_x)*sin(rad)+(target_y-fire_y)*cos(rad);

				c=sqrt(vx*vx+vy*vy);

				vx2=targetx-fire_x;
				vy2=targety-fire_y;
								
				vx/=c; vy/=c;

				if(){

				}

				bullet_fire(&gBulletObject,fire_x,fire_y,10.0,vx,vy,10.0);
			}
			else if(ch=='a'){
				target_x-=1;
			}
			else if(ch=='d'){
				target_x+=1;
			}
		}
		//apply 위치..
		bullet_apply(&gBulletObject,delta_tick);
		
		//타이밍 계산
		acc_tick += delta_tick;
		if(acc_tick > 1.0) {
			//puts("tick...\r");
			
			map_drawTile(&gScreenBuffer[0],0,0,&gScreenBuffer[1]);
			bullet_draw(&gBulletObject,&gScreenBuffer[1]);
			gotoxy(0,0);
			
			map_PutTile(&gScreenBuffer[1],target_x,target_y,5);
			map_PutTile(&gScreenBuffer[1],fire_x,fire_y,1);

			map_dump(&gScreenBuffer[1],Default_Tilepalete);
			acc_tick = 0;
		}

	}

	return 0;

}
