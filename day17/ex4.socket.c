#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//tcp/ip

typedef struct _S_PACKET_REQ_SETPOS{
	unsigned short header;
	unsigned short request_type;
	unsigned short index;
	float m_fXpos;
	float m_fYpos;
	unsigned char extra[2];
}_S_PACKET_REQ_SETPOS;

int main()
{
	int socket_disc;
	struct sockaddr_in server;
	static char read_buffer[2000];
	
	_S_PACKET_REQ_SETPOS testPacket={1004,200,0,15,17.0};

	printf("%d %d\r\n",testPacket.header,testPacket.request_type);

	socket_disc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_disc==-1){
		puts("err create socket");
	}
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	if(connect(socket_disc,(struct sockaddr *)&server,sizeof(server)) < 0){
		puts("connect error");
		return 1;
	}
	printf("%d\r\n",sizeof(testPacket));
	if(send(socket_disc,&testPacket,sizeof(testPacket),0) < 0){
		puts("send failed");
	}
	puts("send success");

	return 0;
}
