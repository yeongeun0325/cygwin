#ifndef __ENGINE_2D__
#define __ENGINE_2D__

void setColor(int fore_color,int backg_color)
{
		printf("%c[%d;%dm",0x1b,fore_color,backg_color);
}

void gotoxy(int x,int y)
{
		printf("%c[%d;%df",0x1b,y,x);
}

#endif	

