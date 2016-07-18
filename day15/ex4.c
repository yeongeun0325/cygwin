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
#include "plane.h"

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuffer[2];
_S_MAP_OBJECT gPlayerModel;
_S_MAP_OBJECT gBulletModel;

//게임오브잭트 선언 
_S_Plane gPlayerObject;
_S_BULLET_OBJECT gBulletObject;

int getDirection(_S_BULLET_OBJECT *pBullet,_S_Plane *pPlane,double vx,double vy)
{
	double bullet_posx=pBullet->m_fXpos;
	double bullet_posy=pBullet->m_fYpos;

	double target_posx=pPlane.m_fXpos;
	double target_posy=pPlane.m_fYpos;

	double vx=target_posx-bullet_posx;
	double vy=target_posy-bullet_posy;

	double dist=sqrt(vx*vx+vy*vy);

	*vx/=dist; *vy/=dist;

	*_vx=vx; *_vy=vy;

}

int getDist(_S_BULLET_OBJECT *pBullet,_S_BULLET_OBJECT *pPlane)
{
	double bullet_posx=pBullet->m_fXpos;
	double bullet_posy=pBullet->m_fYpos;

	double target_posx=pPlane.m_fXpos;
	double target_posy=pPlane.m_fYpos;

	double vx=target_posx-bullet_posx;
	double vy=target_posy-bullet_posy;

	double dist=sqrt(vx*vx+vy*vy);

	return dist;

}

int main()
{	
	system("clear");

	for(int i=0;i<2;i++){
		map_init(&gScreenBuffer[i]);
		gScreenBuffer[i].fpnew(&gScreenBuffer[i],35,16);
		//map_new(&gScreenBuffer[i],35,16);
	}

	map_init(&gPlayerModel);
	map_load(&gPlayerModel,"plane.dat");

	Plane_init(&gPlayerObject,&gPlayerModel,17,10);
	bullet_init(&gBulletObject,0,0,0,&gPlayerModel);

	map_init(&gBulletModel);
	map_load(&gBulletModel,"plasma.dat");

	bullet_init(&gBulletObject,0,0,0,&gBulletModel);
	
	set_conio_terminal_mode();
	acc_tick=last_tick=0;

	//play상태
	gPlayerObject.m_nFSM=1;

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
				double vx,vy;
				gBulletObject.m_fXpos=0;
				gBulletObject.m_fYpos=0;

				getDirection(&gBulletModel,&gPlayerObject,vx,vy);

				gBulletObject.pfFire(&gBulletObject,bullet_posx,bullet_posy,10,vx,vy,10.0);
			}
			gPlayerObject.pfApply(&gPlayerObject,delta_tick,ch);
			//Plane_Apply(&gPlayerObject,delta_tick,ch);
		}

		//apply위치
		gBulletObject.pfApply(&gBulletObject,delta_tick);

		//충돌여부확인-거리계산
		if(gBulletObject.m_nFSM!=0){
			double dist=getDist(&gBulletObject,&gPlayerObject);

			if(dist<0.1){
				gBulletObject.m_nFSM=0;
				gPlayerObject.m_nFSM=0;
			}

		}

	
		//타이밍 계산 
		acc_tick += delta_tick;
		gBulletObject.pfApply(&gBulletObject,delta_tick);
		
		if(acc_tick > 0.1) {
			//puts("tick..\r");
			gotoxy(0,0);
			map_drawTile(&gScreenBuffer[0],0,0,&gScreenBuffer[1]);
			gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuffer[1]);
			gBulletObject.pfDraw(&gBulletObject,&gScreenBuffer[1]);
			
			//Plane_Draw(&gPlayerObject,&gScreenBuffer[1]);
			map_dump(&gScreenBuffer[1],Default_Tilepalete);
			acc_tick = 0;
		}

	}

	return 0;

}
