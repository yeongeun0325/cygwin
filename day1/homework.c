#include <stdio.h>
#include <stdlib.h>

void setColor(int fore_color,int backg_color)
{
	printf("%c[%d;%dm",0x1b,fore_color,backg_color);
}

void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1b,y,x);
}

void xy_star(int x,int y)
{
	printf("%c[%d;%df",0x1b,y,x);
	printf("◆");
}

int main()
{
	int fore_color;
	fore_color=32;
	system("clear");

	setColor(33,44);
	gotoxy(18,6);
	printf("water");
	setColor(32,43);
	gotoxy(18,8);
	printf("melon");
	setColor(31,47);
	gotoxy(17,11);
	printf("icecream");
	setColor(0,0);  //reset ansi command
	
	xy_star(20,1);	xy_star(19,2);	xy_star(18,3);	xy_star(17,4);
	xy_star(16,5);	xy_star(15,6);	xy_star(14,7); 	xy_star(13,8);
	xy_star(12,9);	xy_star(11,10);	xy_star(10,11);	xy_star(9,12);
	xy_star(8,13);

	xy_star(20,1);  xy_star(21,2);  xy_star(22,3);  xy_star(23,4);
	xy_star(24,5);  xy_star(25,6);  xy_star(26,7);  xy_star(27,8);
	xy_star(28,9);  xy_star(29,10); xy_star(30,11); xy_star(31,12);
	xy_star(32,13);

	xy_star(8,13);	xy_star(9,13);	xy_star(10,13);	xy_star(11,13);	xy_star(12,13);
	xy_star(13,13);	xy_star(14,13);	xy_star(15,13);	xy_star(16,13);	xy_star(17,13);	
	xy_star(18,13);	xy_star(19,13); xy_star(20,13); xy_star(21,13); xy_star(22,13);
	xy_star(23,13);	xy_star(24,13); xy_star(25,13); xy_star(26,13); xy_star(27,13);
	xy_star(28,13); xy_star(29,13); xy_star(30,13); xy_star(31,13);
	
	xy_star(8,14); xy_star(8,15); xy_star(32,14); xy_star(32,15);

	xy_star(8,15);  xy_star(9,15);  xy_star(10,15); xy_star(11,15); xy_star(12,15);
	xy_star(13,15); xy_star(14,15); xy_star(15,15); xy_star(16,15); xy_star(17,15);
	xy_star(18,15); xy_star(19,15); xy_star(20,15); xy_star(21,15); xy_star(22,15);
	xy_star(23,15); xy_star(24,15); xy_star(25,15); xy_star(26,15); xy_star(27,15);
	xy_star(28,15); xy_star(29,15); xy_star(30,15); xy_star(31,15);	xy_star(32,15);


	xy_star(19,16);xy_star(19,17);xy_star(19,18);xy_star(19,19);xy_star(19,20);
	xy_star(19,21);xy_star(19,22);

	xy_star(20,16);xy_star(20,17);xy_star(20,18);xy_star(20,19);xy_star(20,20);
	xy_star(20,21);xy_star(20,22);

	
	gotoxy(0,30);

	return 0;
}
