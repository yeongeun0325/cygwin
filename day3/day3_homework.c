#include<stdio.h>
#include<stdlib.h>
#include"../hwork.h"

int drawCrab(int nXpos,int nYpos,int nColor)
{
	int ix,iy;
	int jx,jy;
	int kx,ky;
	ix=5;iy=5;
	jx=1;jy=5;
	kx=12;ky=5;

	//몸통
	setColor(31,41);
	for(iy=5;iy<8;iy++){
		for(ix=5;ix<12;ix++){
			gotoxy(ix+nXpos,iy+nYpos);
			printf(" ");
		}
	}
	
	//왼쪽다리
	setColor(31,40);
	for(jy=5;jy<8;jy++){
			for(jx=1;jx<5;jx++){
			gotoxy(jx+nXpos,jy+nYpos);
			printf("-");
			}
	}

	//오른쪽다리
	for(ky=5;ky<8;ky++){
			for(kx=12;kx<16;kx++){
			gotoxy(kx+nXpos,ky+nYpos);
			printf("-");
			}
	}

	//눈	
	setColor(30,47);
	for(ky=5;ky<6;ky++){
		for(kx=6;kx<11;kx+=4){
			gotoxy(kx+nXpos,ky+nYpos);
			printf("■");
		}
	}

	setColor(0,0);
}


int main()
{
	system("clear");

	int bLoop=1;
	char cmd;
	int xpos,ypos;
	xpos=1;ypos=1;

	while(bLoop){
		scanf("%c",&cmd);
		switch(cmd){
			case 'u':
				ypos-=1;
				break;
			case 'd':
				ypos+=1;
				break;
			case 'l':
				xpos-=1;
				break;
			case 'r':
				xpos+=1;
				break;
			case 'q':
				bLoop=0;
				break;
		}
		system("clear");
		drawCrab(xpos,ypos,41);
		gotoxy(0,20);
		printf("--------------------");
		
		printf("xpos:%d ypos:%d \r\n",xpos,ypos);

	}
	
}
