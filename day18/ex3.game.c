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

typedef struct _S_PACKET_RECV_POS{
	unsigned short header;	//0	byte
	unsigned short type;		//2
	float m_afXpos[2];		//4
	float m_afYpos[2];		//

}_S_PACKET_RECV_POS;

pthread_t tid;
struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

int socket_desc;
char read_buffer[2000];


void *ListenThread(void *arg)
{
	while(1){
		puts("listen start..");
		if(recv(socket_desc,read_buffer,2000,0) < 0){
			puts("recv failed");
		}
		puts("recv success");
		_S_PACKET_RECV_POS *pPacket=(_S_PACKET_RECV_POS *)read_buffer;
		printf("%d %d\r\n",pPacket->header,pPacket->type);
		printf("%f %f\r\n",pPacket->m_afXpos,pPacket->m_afYpos);

		//sleep(1);
	}

	return NULL;
}

int main(int argc,char *argv[])
{
		//소켓 connet
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

	puts("connet success");
	sleep(1);
	
	//접속후
	{
		int err = pthread_create(&tid,NULL,&ListenThread,NULL);
		if(err != 0) {
			printf("err : %s \r\n",strerror(err));
		}
		else {
			printf("thread create success \r\n");
		}
	}
	
	while(bLoop) {
		char ch=getch();
		if(ch=='q'){
			bLoop=0;
		}
	}

	return 0;

}
