#ifndef __RGAME_H__
#define __RGAME_H__
#include"../engine/engine2d.h"

//렌더링
void drawGame(int mx,int my,char *pBuf)
{
	gotoxy(1,1);
	int x,y;
	for(y=0;y<my;y++){
		for(x=0;x<mx;x++){
			switch(pBuf[mx*y+x]){	//현제 셀값
				case 0:
					putchar('.');
					break;
				case 1:
					setColor(33,43);
					putchar('$');
					setColor(37,40);
					break;
				case 2:
					putchar('A');
					break;
				case 3:
					setColor(32,42);
					putchar('#');
					setColor(37,40);
					break;
			}
		}
		printf("\r\n");
	}
}

#endif
