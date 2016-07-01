#ifndef __EXITROOM_H_
#define __EXIT_ROOM_H__

int buffer_map[64];

int nFSM=0;		//0=준비 1=게임플레이 2=게임클리어 3=게임오버
int player_xpos;
int player_ypos;
int player_inven;	//0:없음 1:키보유


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

	switch(buffer_map[player_xpos+player_ypos*8]){
		case 0:	//길
			break;
		case 1:	//벽
			player_ypos=old_ypos;
			player_xpos=old_xpos;
			break;
		case 2: //문
			printf("*미션클리어*\r\n");
			nFSM=2;
			break;
		case 3:
			break;
		case 4:
			if(player_inven==1){
				printf("*미션클리어*\r\n");
				nFSM=2;
			}
			else{
				player_ypos=old_ypos;
				player_xpos=old_xpos;
			}
			break;
		case 5:
			printf("키를 얻었습니다\r\n");
			player_inven=1;
			buffer_map[player_xpos+player_ypos*8]=0;
			break;
	
	}
	
	buffer_map[player_xpos+player_ypos*8]=3;


}

#endif
