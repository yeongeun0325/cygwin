#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <math.h>
#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"

#include "packet.h"
#include "plane.h"
#include "bullet.h"
#include "alien.h"
#include "plane_bullet.h"
#include "potal.h"
#include "potal_bullet.h"

#define PI 3.141592

pthread_t tid;
struct timespec work_timer;
double acc_tick,last_tick;
double acc_bullet_delay_tick;
int bLoop = 1;
int nStep = 1;

int socket_desc;
char read_buffer[2000];

int gnPlayerIndex;

_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;
_S_MAP_OBJECT gPlasmaModel;
_S_MAP_OBJECT gAlienModel;
_S_MAP_OBJECT gPlaneBulletModel;
_S_MAP_OBJECT gPotal;
_S_MAP_OBJECT gPotalBulletModel;

_S_Plane gPlayerObject[2];
_S_PLANE_BULLET_OBJECT gPlaneBulletObjects[32];
_S_ALIEN_OBJECT gAlienObjects[8];
_S_BULLET_OBJECT gPlasmaObjects[32];
_S_Potal gPlayerPotal;
_S_Potal_Bullet_Object gPotalBulletObject;

typedef struct _S_PACKET_RECV_POSITIONS {
	unsigned short header; //0
	unsigned short type; //2
	float m_afXpos[2]; //4
	float m_afYpos[2]; //12

} _S_PACKET_RECV_POSITIONS;

void *ListenThread(void *arg)
{
	while(bLoop) {
		if(recv(socket_desc,
			read_buffer,2000,0) < 0) {
			//puts("recv failed");
		}
		_S_PACKET_RECV_POSITIONS *pPacket = (_S_PACKET_RECV_POSITIONS *)read_buffer;
		if(pPacket->header == 1004) {
			gPlayerObject[0].m_fXpos = pPacket->m_afXpos[0];
			gPlayerObject[0].m_fYpos = pPacket->m_afYpos[0];
			gPlayerObject[1].m_fXpos = pPacket->m_afXpos[1];
			gPlayerObject[1].m_fYpos = pPacket->m_afYpos[1];
		}
	}
	return NULL;
}

void *InputThread(void *arg)
{
	float xpos = 30;
	float ypos = 20;

	while(bLoop)
	{
		if(kbhit() != 0 ) {

			char ch = getch();
			if(ch == 'q') {
				bLoop = 0;
				puts("bye~ \r");
			}

			//gPlayerObject.pfApply(&gPlayerObject,0,ch);
			switch(ch) {
				case 'w':
					ypos -= 1;
					break;
				case 's':
					ypos += 1;
					break;
				case 'a':
					xpos -= 1;
					break;
				case 'd':
					xpos += 1;
					break;
				case 'j':
					for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_PLANE_BULLET_OBJECT);i++) {			
						_S_PLANE_BULLET_OBJECT *pObj = &gPlaneBulletObjects[i];
						if(pObj->m_nFSM==0) { //슬립상태
							pObj->pfFire(pObj,gPlayerObject[0].m_fXpos,gPlayerObject[0].m_fYpos,10.0,5.0);
							break;
						}
					}
					
					break;
				case 'k':
					for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_PLANE_BULLET_OBJECT);i++) {			
						_S_PLANE_BULLET_OBJECT *pObj = &gPlaneBulletObjects[i];
						if(pObj->m_nFSM==0) { //슬립상태
							pObj->pfFire(pObj,gPlayerObject[1].m_fXpos,gPlayerObject[1].m_fYpos,10.0,5.0);
							break;
						}
					}
					break;
			}

			_S_PACKET_REQ_SETPOS packet_setpos = {
				{
					1004,
					200,
				},
				gnPlayerIndex,
				xpos,
				ypos
				
			};
			if(send(socket_desc,
						&packet_setpos,
						sizeof(packet_setpos),0) < 0) {
				puts("send failed");
			}

		}
		

	}
	return NULL;
}


int main(int argc,char *argv[])
{
	if(argc < 2) {
		gnPlayerIndex = 0;
	}
	else {
		gnPlayerIndex = atoi(argv[1]);
	}

	printf("ready player %d \r\n",gnPlayerIndex);
	

//소켓 연결 시도...
	struct sockaddr_in server;

	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1)
	{
		puts("err create socket");
	}
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	if(connect(socket_desc,(struct sockaddr *)&server,sizeof(server)) < 0) {
		puts("connect error");
		return 1;
	}

	puts("connect ok!");
//쓰레드 기동 ..
	{
		int err = pthread_create(&tid,NULL,&InputThread,NULL);
		if(err != 0) {
			printf("err : %s \r\n",strerror(err));
		}
		else {
			printf("thread create success \r\n");
		}
	}

	{
		int err = pthread_create(&tid,NULL,&ListenThread,NULL);
		if(err != 0) {
			printf("err : %s \r\n",strerror(err));
		}
		else {
			printf("thread create success \r\n");
		}
	}

	puts("system ready!");
	sleep(3);

//게임 리소스 로딩 
	for(int i=0;i<2;i++)
	{
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],60,30);
	}

	map_init(&gPlayerModel);
	map_load(&gPlayerModel,"plane1.dat");

	map_init(&gPlaneBulletModel);
	map_load(&gPlaneBulletModel,"bullet1.dat");

	map_init(&gPotal);
	map_load(&gPotal,"potal.dat");

	map_init(&gAlienModel);
	map_load(&gAlienModel,"alien.dat");

	map_init(&gPlasmaModel);
	map_load(&gPlasmaModel,"plasma.dat");

    Plane_init(&gPlayerObject[0],&gPlayerModel,5,25);
	gPlayerObject[0].m_nFSM = 1;

    Plane_init(&gPlayerObject[1],&gPlayerModel,50,25);
	gPlayerObject[1].m_nFSM = 1;

	Potal_init(&gPlayerPotal,&gPotal,1,1);

    for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_PLANE_BULLET_OBJECT);i++){
		plane_bullet_init(&gPlaneBulletObjects[i],0,0,0,&gPlaneBulletModel);
	}

	for(int i=0;i<sizeof(gPlasmaObjects)/sizeof(_S_BULLET_OBJECT);i++){
		bullet_init(&gPlasmaObjects[i],0,0,0,&gPlasmaModel);
	}

    double TablePosition[]={0,10,20,30,40,50,60};

	for(int i=0;i<6;i++){
		_S_ALIEN_OBJECT *pObj=&gAlienObjects[i];
		alien_init(pObj,&gAlienModel);
		pObj->m_fXpos=TablePosition[i];
		pObj->m_fYpos=5;
		pObj->m_nFSM=1;
		gAlienObjects[i].m_pBullet=&gPlasmaObjects[i];

	}

	puts("object setup ok!");
	sleep(1);

	system("clear");

	set_conio_terminal_mode();
	acc_tick=last_tick=0;

	while(bLoop) {
		//타이밍처리 
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + 
			(double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;
		last_tick = cur_tick;

        for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_PLANE_BULLET_OBJECT);i++) {
			_S_PLANE_BULLET_OBJECT *pObj=&gPlaneBulletObjects[i];
			pObj->pfApply(pObj,delta_tick);

		}

		for(int i=0;i<6;i++ ){
			_S_ALIEN_OBJECT *pObj=&gAlienObjects[i];
			pObj->pfApply(pObj,delta_tick);

		}

		// _S_Potal_Bullet_Object *pObj=&gPotalBulletObject;
		// 	if(pObj->m_nFSM==0){
        //             double potal_bullet_posx=gPlayerPotal.m_nXpos;
        //             double potal_bullet_posy=gPlayerPotal.m_nYpos;

        //             double target_x=gPlayerObject[0].m_fXpos;
        //             double target_y=gPlayerObject[0].m_fYpos;

		// 			double vx=target_x-potal_bullet_posx;
        //             double vy=target_y-potal_bullet_posy;

        //             double dist=sqrt(vx*vx+vy*vy);
        //             vx/=dist; vy/=dist;

		// 			Potal_Bullet_Fire(&gPotalBulletObject,gPlayerPotal.m_nXpos,gPlayerPotal.m_nYpos,10,vx,vy,10.0);
		// 	}

		//총알 맞았을때 게임오버
		for(int i=0;i<sizeof(gPlasmaObjects)/sizeof(_S_BULLET_OBJECT);i++) {
			if(gPlasmaObjects[i].m_nFSM!=0) {
				
				double bullet_posx=gPlasmaObjects[i].m_fXpos;
				double bullet_posy=gPlasmaObjects[i].m_fYpos;

				double target_posx=gPlayerObject[0].m_fXpos;
				double target_posy=gPlayerObject[0].m_fYpos;

				double vx=target_posx-bullet_posx;
				double vy=target_posy-bullet_posy;

				double dist=sqrt(vx*vx+vy*vy);

				if(dist<0.1) {
					gPlasmaObjects[i].m_nFSM=0;
					gPlayerObject[0].m_nFSM=0;
					gAlienObjects[i].m_nFSM=0;
					system("clear");
					printf("----------------------\r\n");
					printf("      Game over\r\n");
					printf("----------------------\r\n");

					bLoop=0;
				}
			}
		}

		//alien 총알 맞았을때
		for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_PLANE_BULLET_OBJECT);i++) {
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

		for(int i=0;i<sizeof(gPlasmaObjects)/sizeof(_S_BULLET_OBJECT);i++) {
			gPlasmaObjects[i].pfApply(&gPlasmaObjects[i],delta_tick);

		}

		Potal_Bullet_Apply(&gPotalBulletObject,delta_tick);

        //충돌여부확인-거리계산
        {
            double potal_bullet_posx=gPlayerPotal.m_nXpos;
            double potal_bullet_posy=gPlayerPotal.m_nYpos;

            double target_x=gPlayerObject[0].m_fXpos;
            double target_y=gPlayerObject[0].m_fYpos;

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

			double target_posx=gPlayerObject[0].m_fXpos;
			double target_posy=gPlayerObject[0].m_fYpos;

			double vx=target_posx-bullet_posx;
			double vy=target_posy-bullet_posy;

			double dist=sqrt(vx*vx+vy*vy);

			vx/=dist; vy/=dist;

			gPotalBulletObject.m_fvx=vx;
			gPotalBulletObject.m_fvy=vy;
		}

		//타이밍 계산 
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);
			
			for(int i=0;i<2;i++){
		    	gPlayerObject[i].pfDraw(&gPlayerObject[i],&gScreenBuf[1]);
            }

			Potal_Draw(&gPlayerPotal,&gScreenBuf[1]);
			Potal_Bullet_Draw(&gPotalBulletObject,&gScreenBuf[1]);

            for(int i=0;i<sizeof(gPlaneBulletObjects)/sizeof(_S_PLANE_BULLET_OBJECT);i++){
				_S_PLANE_BULLET_OBJECT *pObj = &gPlaneBulletObjects[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}

            for(int i=0;i<6;i++) {
				_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}

			for(int i=0;i<sizeof(gPlasmaObjects)/sizeof(_S_BULLET_OBJECT);i++){
				gPlasmaObjects[i].pfDraw(&gPlasmaObjects[i],&gScreenBuf[1]);
			}
			
			puts("------------------------------------------------------------\r");
			map_dump(&gScreenBuf[1],Default_Tilepalete);
			puts("------------------------------------------------------------\r");

			puts("move :  w,  a,  s,  d \r");
            puts("player0 fire : j   player1 fire : k");
			puts("quit : q \r");
			acc_tick = 0;
		}

	}

	return 0;

}