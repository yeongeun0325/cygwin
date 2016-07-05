#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<termios.h>

#include"../engine/engine2d.h"

char screen_buffer[8*8];

double rock_acc_tick;
int rock_xpos,rock_ypos;

int car_xpos,car_ypos;

int main()
{
	//버퍼초기화
	for(int i=0;i<64;i++){
		screen_buffer[i]=0;
	}

	struct timespec work_timer;
	set_conio_terminal_mode();
	
	int bLoop=1;
	double acc_tick,last_tick;
	acc_tick=last_tick=0;

	system("clear");
	
	car_xpos=3;
	car_ypos=7;

	rock_xpos=0;
	rock_ypos=3;

	while(bLoop){

		//타이밍처리
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick=work_timer.tv_sec+(double)(work_timer.tv_nsec*1e-9);
		double delta_tick=cur_tick-last_tick;
		last_tick=cur_tick;	
		
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

			if(rock_ypos>=8){
				rock_ypos=0;
			}
		}

		//게임 로직 (판정)
		if(rock_ypos==car_ypos && rock_xpos==car_xpos){
			bLoop=0;
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
		if(acc_tick>0.1){
			acc_tick=0;

			//렌더링
			gotoxy(1,1);
			int x,y;
			for(y=0;y<8;y++){
				for(x=0;x<8;x++){
					switch(screen_buffer[8*y+x]){	//현제 셀값
						case 0:
							putchar('.');
							break;
						case 1:
							putchar('#');
							break;
						case 2:
							putchar('A');
							break;
					}
				}
				printf("\r\n");
			}

		}
	}
	return 0;
}

