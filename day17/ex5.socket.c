#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//tcp/ip

typedef struct _S_PACKET_REQ_GETPOS{
	unsigned short header;
	unsigned short request_type;
	unsigned int m_nIndex;
}_S_PACKET_REQ_GETPOS;

typedef struct _S_PACKET_RCV_POS{
	unsigned short header;
	unsigned int m_nIndex;
	float m_fXpos;
	float m_fYpos;
}_S_PACKET_RCV_POS;

int main()
{
	int socket_disc;
	struct sockaddr_in server;
	static char read_buffer[2000];
	
	_S_PACKET_REQ_GETPOS testPacket={1004,201,0};

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
	
	if(recv(socket_disc,read_buffer,2000,0) < 0){
		puts("recive failed");
	}
	
	_S_PACKET_RCV_POS *recv_pos=(_S_PACKET_RCV_POS *)read_buffer;

	printf("%d %d %f %f\r\n",recv_pos->header,recv_pos->m_nIndex,recv_pos->m_fXpos,recv_pos->m_fYpos);

	return 0;
}
