#include<stdio.h>
#include<stdlib.h>
#include"../hwork.h"
#include"room.h"

/*
 1:벽 #
 2:열린문 M
 3:유저 A
 4:잠긴문 m
 5:키 K
 */

int game_version=100;
char *game_name="방탈출 게임";

int main()
{
	char cmd;
	int bLoop=1;

	while(bLoop){
		switch(nFSM){
			case 0:
				printf("%s에 오신 것을 환영합니다. v. %d\r\n",game_name,game_version);
				printf("select -> p(start),q(quit) \r\n");
				break;
			case 1:
				printf("명령을 입력하세요.\r\nj(left),k(right),i(up),m(down)\r\ns(show map),q(quit)\r\n");
				break;
			case 2:
				printf("명령을 입력하세요.\r\nj(left),k(right),i(up),m(down)\r\ns(show map),q(quit)\r\n");
				break;
		}
		
		//버퍼 초기화
		setStage(player_stage);

		scanf("%c",&cmd);
		getchar();
		
		//준비상태
		if(nFSM==0){
			switch(cmd){
				case 'p':	//게임시작
					nFSM=1;
					player_xpos=1;
					player_ypos=5;
					player_stage=1;
					player_inven=0;
					printf("게임을 시작합니다\r\n");
					break;
				case 'q':
					bLoop=0;
					printf("bye bye~~");
					break;
			}
		}
		//게임플레이
		else if(nFSM==1){	
		
			move_player(cmd);

			printf("\r\n");

			//게임 로직
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
		else if(nFSM==2){
			nFSM=0;

		}
	}
	return 0;

}
