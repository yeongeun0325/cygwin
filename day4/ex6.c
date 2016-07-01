#include<stdio.h>
#include<stdlib.h>
#include"../hwork.h"

int world_map[]={
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,2,
	1,0,1,0,1,1,0,2,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1

};

int buffer_map[64];

int player_xpos=1;
int player_ypos=5;

void move_player(char cmd)
{
	int old_xpos=player_xpos;
	int old_ypos=player_ypos;

	switch(cmd){
		case 'i' :
			printf("위로 한칸 이동했습니다\r\n");
			player_ypos-=1;
			break;
		case 'j' :
			printf("왼쪽으로 한칸 이동했습니다\r\n");
			player_xpos-=1;
			break;
		case 'k' :
			printf("오른쪽으로 한칸 이동했습니다\r\n");
			player_xpos+=1;
			break;
		case 'm' :
			printf("아래로 한칸 이동합니다.\r\n");
			player_ypos+=1;
			break;

	}

	if(buffer_map[player_xpos+player_ypos*8]==0){
		printf("이동성공!\r\n");
	}
	else{
		printf("막다른 길입니다\r\n\r\n");
		player_xpos=old_xpos;
		player_ypos=old_ypos;
	}


}

int main()
{
	char cmd;
	int bLoop=1;

	while(bLoop){
		printf("명령을 입력하세요,\r\nj(left),k(right)\r\ni(up),m(down),s(show map),q(quit)\r\n");
	
		for(int i=0;i<64;i++){
			buffer_map[i]=world_map[i];
		}

		scanf("%c",&cmd);
		getchar();
		move_player(cmd);

		printf("\r\n");
		buffer_map[player_xpos+player_ypos*8]=3;

		switch(cmd){
			case 's' :
				map_drawAll(buffer_map);
				break;
			case 'q' :
				bLoop=0;
				printf("bye bye~\r\n");
				break;
		
			}
	}

	return 0;

}
