#include<stdio.h>
#include<stdlib.h>

void setColor(int fore_color,int backg_color)
{
	printf("%c[%d;%dm",0x1b,fore_color,backg_color);
}

void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1b,y,x);
}

int main()
{
	int fore_color;
	fore_color=31;
	system("clear");
	
	//"\x1b[31m"
	//printf("%c[%dm",0x1b,fore_color);
	
	setColor(33,44);
	gotoxy(3,3);
	printf("hello");
	setColor(32,43);
	gotoxy(3,10);
	printf("world");
	setColor(0,0);	//reset ansi command
	
	gotoxy(20,1);
	printf("|");
	gotoxy(20,2);
	printf("|");
	gotoxy(20,3);
	printf("|");
	gotoxy(20,4);
	printf("|");
	gotoxy(20,5);
	printf("|");
	gotoxy(20,6);
	printf("|");
	gotoxy(20,7);
	printf("|");
	gotoxy(20,8);
	printf("|");
	gotoxy(20,9);
	printf("|");
	gotoxy(20,10);
	printf("|");

	gotoxy(20,11);
	printf("|");

	gotoxy(0,11);
	printf("====================");
	return 0;
}
