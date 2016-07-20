#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//tcp/ip

typedef struct _S_PACKET_BASE{
	unsigned short header;
	unsigned short request_type;
}_S_PACKET_BASE;

int main()
{
	int socket_disc;
	struct sockaddr_in server;
	static char read_buffer[2000];
	
	_S_PACKET_BASE testPacket={1004,103};

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
	if(send(socket_disc,&testPacket,sizeof(testPacket),0) < 0){
		puts("send failed");
	}
	puts("send success");

	return 0;
}
