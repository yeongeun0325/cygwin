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
#include "potal.h"
#include "potal_bullet.h"

#define PI 3.141592

struct timespec work_timer;
double acc_tick,last_tick;
double acc_bullet_delay_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuffer;
_S_MAP_OBJECT gBackBuffer;
_S_MAP_OBJECT gF22Raptor;
_S_MAP_OBJECT gF22Bullet;
_S_MAP_OBJECT gPotal;
_S_MAP_OBJECT gPotalBulletModel;

//게임오브젝트 선언 
_S_Plane gPlayerPlane;
_S_Potal gPlayerPotal;
_S_Potal_Bullet_Object gPotalBulletObject;
_S_Bullet_Object g_bullets[32];

int main()
{
	set_conio_terminal_mode();
	acc_tick=last_tick=0;
    acc_bullet_delay_tick=0;
	system("clear");

	map_init(&gScreenBuffer);
	map_new(&gScreenBuffer,45,20);

	map_init(&gBackBuffer);
	map_new(&gBackBuffer,45,20);

	map_init(&gF22Raptor);
	map_load(&gF22Raptor,"plane.dat");

	map_init(&gF22Bullet);
	map_load(&gF22Bullet,"bullet1.dat");

	map_init(&gPotal);
	map_load(&gPotal,"potal.dat");

	map_init(&gPotalBulletModel);
	map_load(&gPotalBulletModel,"plasma.dat");

	Plane_init(&gPlayerPlane,&gF22Raptor,35,17);
	Potal_init(&gPlayerPotal,&gPotal,1,1);
	Potal_Bullet_init(&gPotalBulletObject,0,0,0,&gPotalBulletModel);

	for(int i=0;i<sizeof(g_bullets)/sizeof(_S_Bullet_Object);i++){
		bullet_init(&g_bullets[i],0,0,0,&gF22Bullet);
	}

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
				for(int i=0;i<sizeof(g_bullets)/sizeof(_S_Bullet_Object);i++){
					_S_Bullet_Object *pObj=&g_bullets[i];
					if(pObj->m_nFSM==0){	//슬립상태
						bullet_fire(pObj,gPlayerPlane.m_nXpos,gPlayerPlane.m_nYpos,10,5.0);
						break;
					}
				}
			}

            _S_Potal_Bullet_Object *pObj=&gPotalBulletObject;
			if(pObj->m_nFSM==0){
                    double potal_bullet_posx=gPlayerPotal.m_nXpos;
                    double potal_bullet_posy=gPlayerPotal.m_nYpos;

                    double target_x=gPlayerPlane.m_nXpos;
                    double target_y=gPlayerPlane.m_nYpos;

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
	
			Plane_Apply(&gPlayerPlane,delta_tick,ch);

		}

		for(int i=0;i<sizeof(g_bullets)/sizeof(_S_Bullet_Object);i++){
				_S_Bullet_Object *pObj=&g_bullets[i];
				bullet_apply(pObj,delta_tick);
		}
		//apply 위치..
		Potal_Bullet_Apply(&gPotalBulletObject,delta_tick);

        //충돌여부확인-거리계산
        {
            double potal_bullet_posx=gPlayerPotal.m_nXpos;
            double potal_bullet_posy=gPlayerPotal.m_nYpos;

            double target_x=gPlayerPlane.m_nXpos;
            double target_y=gPlayerPlane.m_nYpos;

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

			double target_posx=gPlayerPlane.m_nXpos;
			double target_posy=gPlayerPlane.m_nYpos;

			double vx=target_posx-bullet_posx;
			double vy=target_posy-bullet_posy;

			double dist=sqrt(vx*vx+vy*vy);

			vx/=dist; vy/=dist;

			gPotalBulletObject.m_fvx=vx;
			gPotalBulletObject.m_fvy=vy;
		}

		//타이밍 계산 
		acc_tick += delta_tick;
        if(acc_tick> 0.1) {
			
			map_drawTile(&gBackBuffer,0,0,&gScreenBuffer); //클리어 

			//map_drawTile_trn(&gF22Raptor,xpos,ypos,&gScreenBuffer);//오브잭트 출력 
			
			Plane_Draw(&gPlayerPlane,&gScreenBuffer);
			Potal_Draw(&gPlayerPotal,&gScreenBuffer);
            Potal_Bullet_Draw(&gPotalBulletObject,&gScreenBuffer);

			for(int i=0;i<sizeof(g_bullets)/sizeof(_S_Bullet_Object);i++){
				_S_Bullet_Object *pObj=&g_bullets[i];
				bullet_draw(pObj,&gScreenBuffer);
			}

			gotoxy(0,0);
			puts("---------------------------------------------\r");
			map_dump(&gScreenBuffer,Default_Tilepalete);
			puts("---------------------------------------------\r");

			puts("move : w,a,s,d \r");
			puts("quit : q \r");
			
			acc_tick = 0;
		}

	}

	return 0;

}
