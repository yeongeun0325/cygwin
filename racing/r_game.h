#ifndef __RGAME_H__
#define __RGAME_H__

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

#endif
