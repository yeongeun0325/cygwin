#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<termios.h>

#include"../engine/engine2d.h"
#include"r_game.h"

char screen_buffer[8*8];

double rock_acc_tick;
int rock_xpos,rock_ypos;
int rock_pos_table[8]={1,3,2,3,4,5,7,2};
int rock_cur_table_index=0;

int car_xpos,car_ypos;
struct timespec work_timer;

int bLoop=1;
double acc_tick,last_tick;

int nFSM=0;
static int nStep=0;

void rg_PlayGame(double delta_tick)
{
	switch(nStep){
		case 0:
			nStep++;
			system("clear");
			break;
		case 1:


			//사용자 입력처리
			if(kbhit()!=0){
				char ch=getch();
				if(ch=='q'){
					printf("quit\r\n");
					bLoop=0;
				}
				else if(ch=='a'){
					car_xpos-=1;
				}
				else if(ch=='d'){
					car_xpos+=1;
				}

			}

			//바위 움직이기
			rock_acc_tick+=delta_tick;

			if(rock_acc_tick>0.5){
				rock_acc_tick=0;
				rock_ypos+=1;

				//화면끝 도달
				if(rock_ypos>=8){
					rock_ypos=0;
					rock_cur_table_index++;
					rock_cur_table_index%=8;
					rock_xpos=rock_pos_table[rock_cur_table_index];
				}
			}

			//게임 로직 (판정)
			if(rock_ypos==car_ypos && rock_xpos==car_xpos){
				bLoop=0;
				//drawGame(screen_buffer);
				printf("충돌발생! game over!\r\n");
			}

			//버퍼초기화
			for(int i=0;i<64;i++){
				screen_buffer[i]=0;
			}	

			//자동차 그리기
			screen_buffer[car_ypos*8+car_xpos]=2;

			//바위 그리기
			screen_buffer[rock_ypos*8+rock_xpos]=1;

			acc_tick+=delta_tick;
			if(acc_tick>0.1 || bLoop==0){
				acc_tick=0;
				drawGame(8,8,screen_buffer);			

			}
			break;
	}

}

void rg_apply_mainTitle(double delta_tick)
{
	switch(nStep){
		case 0:
			puts("press to start");
			nStep=1;
			break;
		case 1:
			//사용자 입력처리
			if(kbhit()!=0){
				char ch=getch();
				//system("clear");
				nFSM=1;
				nStep=0;
			}
			break;
	}
}

int main()
{
	//버퍼초기화
	for(int i=0;i<64;i++){
		screen_buffer[i]=0;
	}

	set_conio_terminal_mode();
	
	acc_tick=last_tick=0;

	system("clear");

	car_ypos=7;
	car_xpos=3;

	rock_xpos=rock_pos_table[rock_cur_table_index];
	rock_ypos=0;


	
	while(bLoop){

		//타이밍처리
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick=work_timer.tv_sec+(double)(work_timer.tv_nsec*1e-9);
		double delta_tick=cur_tick-last_tick;
		last_tick=cur_tick;	
		
		if(nFSM==0){		//타이틀 메뉴 상태
			rg_apply_mainTitle(delta_tick);
		}
		else if(nFSM==1){	//게임상태
			rg_PlayGame(delta_tick);
		}
		else{
		}

			}
	return 0;
}

