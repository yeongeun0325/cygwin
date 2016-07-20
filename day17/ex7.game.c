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

pthread_t tid;
struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

int socket_desc;
char read_buffer[2000];

_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;

_S_Plane gPlayerObject;

void *InputThread(void *arg)
{
	while(1)
	{
		if(kbhit() != 0 ) {

			char ch = getch();
			if(ch == 'q') {
				bLoop = 0;
				puts("bye~ \r");
			}

			gPlayerObject.pfApply(&gPlayerObject,0,ch);
		}
		_S_PACKET_REQ_GETPOS packet_req_getpos = {{1004,201},0};

		if(send(socket_desc,
			&packet_req_getpos,
			sizeof(packet_req_getpos),0) < 0) {
			puts("send failed");
		}
		puts("send success");

		if(recv(socket_desc,read_buffer,2000,0) < 0) {
			puts("recv failed");
		}

		_S_PACKET_RCV_POS *recv_pos = (_S_PACKET_RCV_POS *)read_buffer;

		printf("%d , %d ,%f,%f \r\n",recv_pos->header,recv_pos->m_nIndex,
				recv_pos->m_fxpos,
				recv_pos->m_fypos);

		gPlayerObject.m_fXpos = recv_pos->m_fxpos;
		gPlayerObject.m_fYpos = recv_pos->m_fypos;

		sleep(1);

	}
	return NULL;
}


int main()
{
	{
		int err = pthread_create(&tid,NULL,&InputThread,NULL);
		if(err != 0) {
			printf("err : %s \r\n",strerror(err));
		}
		else {
			printf("thread create success \r\n");
		}
	}

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

	for(int i=0;i<2;i++)
	{
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],35,16);
	}

	map_init(&gPlayerModel);
	map_load(&gPlayerModel,"plane.dat");

	Plane_init(&gPlayerObject,&gPlayerModel,15,10);
	gPlayerObject.m_nFSM = 1;
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

		//타이밍 계산 
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);
		
			gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuf[1]);
			
			map_dump(&gScreenBuf[1],Default_Tilepalete);
			acc_tick = 0;
		}

	}

	return 0;

}