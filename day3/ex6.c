#include<stdio.h>
#include<stdlib.h>
#include"../hwork.h"

int main()
{
	system("clear");

	int bLoop=1;
	char cmd;
	int xpos,ypos;
	xpos=1;ypos=1;
	
	int orc_xpos=10;
	int orc_ypos=10;

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
		//human
		drawMyBox(xpos,ypos,43,1);
		//orc AI
		if(orc_xpos>xpos){
			orc_xpos-=1;
		}
		else if(orc_xpos<xpos){
			orc_xpos+=1;
		}
		else{
			
		}
		//orc
		drawMyBox(orc_xpos,orc_ypos,41,2);
		gotoxy(0,20);
		printf("--------------------");
		
		printf("xpos:%d ypos:%d \r\n",xpos,ypos);

	}
	
}
