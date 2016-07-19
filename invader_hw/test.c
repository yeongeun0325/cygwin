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

#include "plane.h"
#include "bullet.h"
#include "alien.h"
#include "potal.h"
#include "potal_bullet.h"

#define PI 3.141592

struct timespec work_timer;
double acc_tick,last_tick;
double acc_guid_delay_tick;
double acc_bullet_delay_tick;
int bLoop=1;
int nStep=1;

_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;
_S_MAP_OBJECT gPlasmaModel;
_S_MAP_OBJECT gAlienModel;
_S_MAP_OBJECT gPlaneBulletModel;
_S_MAP_OBJECT gPotal;
_S_MAP_OBJECT gPotalBulletModel;

_S_Plane gPlayerObject;
_S_BULLET_OBJECT gBulletObjects[32];
_S_ALIEN_OBJECT gAlienObjects[8];
_S_BULLET_OBJECT gPlaneBulletObjects[32];
_S_Potal gPlayerPotal;
_S_Potal_Bullet_Object gPotalBulletObject;

int main()
{

	for(int i=0;i<2;i++){
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],45,30);
	}

	map_init(&gPlayerModel);
	map_load(&gPlayerModel,"plane1.dat");

	map_init(&gPlasmaModel);
	map_load(&gPlasmaModel,"plasma.dat");

	map_init(&gAlienModel);
	map_load(&gAlienModel,"alien.dat");

	map_init(&gPlaneBulletModel);
	map_load(&gPlaneBulletModel,"bullet1.dat");

	map_init(&gPotal);
	map_load(&gPotal,"potal.dat");

	map_init(&gPotalBulletModel);
	map_load(&gPotalBulletModel,"potal_bullet.dat");

	Plane_init(&gPlayerObject,&gPlayerModel,30,26);
	Potal_init(&gPlayerPotal,&gPotal,1,1);
	Potal_Bullet_init(&gPotalBulletObject,0,0,0,&gPotalBulletModel);

	gPlayerObject.m_nFSM=1;

	for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_BULLET_OBJECT);i++){
		bullet_init(&gPlaneBulletObjects[i],0,0,0,&gPlaneBulletModel);
	}

	for(int i=0;i<sizeof(gBulletObjects)/sizeof(_S_BULLET_OBJECT);i++){
		bullet_init(&gBulletObjects[i],0,0,0,&gPlasmaModel);
	}

	double TablePosition[]={0,10,20,30,40};

	for(int i=0;i<5;i++){
		_S_ALIEN_OBJECT *pObj=&gAlienObjects[i];
		alien_init(pObj,&gAlienModel);
		pObj->m_fXpos=TablePosition[i];
		pObj->m_fYpos=5;
		pObj->m_nFSM=1;
		gAlienObjects[i].m_pBullet=&gBulletObjects[i];

	}

	system("clear");

	set_conio_terminal_mode();
	acc_tick=last_tick=0;
	acc_guid_delay_tick=0;
	acc_bullet_delay_tick=0;

	while(bLoop) {
		//타이밍처리 
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + 
			(double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;
		last_tick = cur_tick;

		//실시간 입력
		if(kbhit()!=0) {
			char ch = getch();
			if(ch=='q') {
				bLoop=0;
				puts("bye~ \r");
			}

			else if(ch=='j') {

				for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_BULLET_OBJECT);i++) {
					double vx,vy,c;

					vx=gAlienObjects[i].m_fXpos-gPlayerObject.m_fXpos;
					vy=gAlienObjects[i].m_fYpos-gPlayerObject.m_fYpos;
					c=sqrt(vx*vx+vy*vy);
					vx/=c;	vy/=c;

					_S_BULLET_OBJECT *pObj = &gPlaneBulletObjects[i];
					if(pObj->m_nFSM==0) { //슬립상태
						pObj->pfFire(pObj,gPlayerObject.m_fXpos,gPlayerObject.m_fYpos,10.0,vx,vy,10.0);
						break;
					}
				}

			}
			_S_Potal_Bullet_Object *pObj=&gPotalBulletObject;
			if(pObj->m_nFSM==0){
				double potal_bullet_posx=gPlayerPotal.m_nXpos;
				double potal_bullet_posy=gPlayerPotal.m_nYpos;

				double target_x=gPlayerObject.m_fXpos;
				double target_y=gPlayerObject.m_fYpos;

				double vx=target_x-potal_bullet_posx;
				double vy=target_y-potal_bullet_posy;

				/*  double angle=0;
					angle+=(delta_tick*45);
					double rad=(angle/180.0)*PI;

					double vx=(target_x-potal_bullet_posx)*cos(rad)-(target_y-potal_bullet_posy)*sin(rad);
					double vy=(target_x-potal_bullet_posx)*sin(rad)+(target_y-potal_bullet_posy)*cos(rad);

*/
				double dist=sqrt(vx*vx+vy*vy);
				vx/=dist; vy/=dist;

				Potal_Bullet_Fire(&gPotalBulletObject,gPlayerPotal.m_nXpos,gPlayerPotal.m_nYpos,10,vx,vy,10.0);
			}
			gPlayerObject.pfApply(&gPlayerObject,delta_tick,ch);	

		}
		//apply
		Potal_Bullet_Apply(&gPotalBulletObject,delta_tick);

		for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_BULLET_OBJECT);i++) {
			_S_BULLET_OBJECT *pObj=&gPlaneBulletObjects[i];
			pObj->pfApply(pObj,delta_tick);

		}

		for(int i=0;i<5;i++ ){
			_S_ALIEN_OBJECT *pObj=&gAlienObjects[i];
			pObj->pfApply(pObj,delta_tick);

		}

		{
			double potal_bullet_posx=gPlayerPotal.m_nXpos;
			double potal_bullet_posy=gPlayerPotal.m_nYpos;

			double target_x=gPlayerObject.m_fXpos;
			double target_y=gPlayerObject.m_fYpos;

			/*	double vx=target_x-potal_bullet_posx;
				double vy=target_y-potal_bullet_posy;*/

			double angle=0;
			angle+=(delta_tick*45);
			double rad=(angle/180.0)*PI;

			double vx=(target_x-potal_bullet_posx)*cos(rad)-(target_y-potal_bullet_posy)*sin(rad);
			double vy=(target_x-potal_bullet_posx)*sin(rad)+(target_y-potal_bullet_posy)*cos(rad);

			double dist=sqrt(vx*vx+vy*vy);

			if(dist<0.1){
				gPotalBulletObject.m_nFSM=0;
			}
		}

		acc_bullet_delay_tick+=delta_tick;
		if(acc_bullet_delay_tick>2.0){	//2초동안 방향설정

			acc_bullet_delay_tick=0;

			double bullet_posx=gPotalBulletObject.m_fXpos;
			double bullet_posy=gPotalBulletObject.m_fYpos;

			double target_posx=gPlayerObject.m_fXpos;
			double target_posy=gPlayerObject.m_fYpos;

			double vx=target_posx-bullet_posx;
			double vy=target_posy-bullet_posy;

			double dist=sqrt(vx*vx+vy*vy);

			vx/=dist; vy/=dist;

			gPotalBulletObject.m_fvx=vx;
			gPotalBulletObject.m_fvy=vy;
		}

		//총알 맞았을때 게임오버
		for(int i=0;i<sizeof(gBulletObjects)/sizeof(_S_BULLET_OBJECT);i++) {
			if(gBulletObjects[i].m_nFSM!=0) {
				double bullet_posx=gBulletObjects[i].m_fXpos;
				double bullet_posy=gBulletObjects[i].m_fYpos;

				double target_posx=gPlayerObject.m_fXpos;
				double target_posy=gPlayerObject.m_fYpos;

				double vx=target_posx-bullet_posx;
				double vy=target_posy-bullet_posy;

				double dist=sqrt(vx*vx+vy*vy);

				if(dist<0.1) {
					gBulletObjects[i].m_nFSM=0;
					gPlayerObject.m_nFSM=0;
					gAlienObjects[i].m_nFSM=0;
				}
			}
		}

		//alien 총알 맞았을때
		for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_BULLET_OBJECT);i++) {
			if(gPlaneBulletObjects[i].m_nFSM!=0) {
				double bullet_posx=gPlaneBulletObjects[i].m_fXpos;
				double bullet_posy=gPlaneBulletObjects[i].m_fYpos;

				double target_posx= gAlienObjects[i].m_fXpos;
				double target_posy= gAlienObjects[i].m_fYpos;

				double vx=target_posx-bullet_posx;
				double vy=target_posy-bullet_posy;
				double dist=sqrt(vx*vx+vy*vy);

				if(dist<5.0) {
					gAlienObjects[i].m_nFSM=0;
				}
			}
		}	

		for(int i=0;i<sizeof(gBulletObjects)/sizeof(_S_BULLET_OBJECT);i++) {
			gBulletObjects[i].pfApply(&gBulletObjects[i],delta_tick);

		}

		//타이밍 계산 
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);

			gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuf[1]);
			Potal_Draw(&gPlayerPotal,&gScreenBuf[1]);

			for(int i=0;i<5;i++) {
				_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}

			for(int i=0;i<sizeof(gBulletObjects)/sizeof(_S_BULLET_OBJECT);i++){
				gBulletObjects[i].pfDraw(&gBulletObjects[i],&gScreenBuf[1]);
			}

			for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_BULLET_OBJECT);i++){
				_S_BULLET_OBJECT *pObj = &gPlaneBulletObjects[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}

			map_dump(&gScreenBuf[1],Default_Tilepalete);
			acc_tick = 0;

		}

	}

	return 0;

}
