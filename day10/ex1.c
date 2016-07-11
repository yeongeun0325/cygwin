#include<stdio.h>

void draw_line(int n,char c)
{
	for(int i=0;i<n;i++){
		putchar(c);
	}
}

void draw_tri1()
{
	int ix,iy;
	for(iy=0;iy<10;iy++){
		for(ix=0;ix<iy;ix++){
			putchar('*');
		}
		puts("");
	}
}

void draw_tri2()
{
	int ix,iy;
	for(iy=10;iy>0;iy--){
		for(ix=0;ix<iy;ix++){
			putchar('*');
		}
		puts("");
	}
}

void draw_tri3()
{
	int iy;
	for(iy=0;iy<10;iy++){
		draw_line(9-iy,' ');
		draw_line(iy,'*');
		puts("");
	}
	/*
	 for(oy=0;iy=10;iy++){
		 draw_line(9-iy;' ');
		 draw_line((iy*2)+1,'*');
		 puts("");
	 */
}

void drwq_tri4()
{
	int iy;
	
	for(iy=0;iy<10;iy++){
		draw_line(9-iy,' ');
		draw_line(iy+2,'*');
		draw_line(iy,'*');
		puts("");
	}
	for(iy=0;iy<5;iy++){
		draw_line(6,' ');
		draw_line(8,'*');
		puts("");
		//draw_line();
	}
}

int main()
 {
	draw_tri1();
	draw_tri2();
	draw_tri3();
	drwq_tri4();

	return 0;
}
