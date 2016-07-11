#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<sys/time.h>
#include<termios.h>
#include<sys/select.h>

#include"../engine/engine2d.h"

char pstr[]={
	0,0,0,1,0,0,0,0,
	0,0,0,1,0,0,0,0,
	0,0,0,1,0,0,0,0,
	0,0,0,1,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,
	0,1,0,1,0,1,1,0
	};

char *pMapBuf;
char chTable[]={'.','#','@','*'};



int main()
{
	int width,height;

	FILE *pf;
	pf=fopen("./ex2.data.txt","r");
	
	char buf[256];

	fgets(buf,256,pf);
	puts(buf);

	char *pTemp=strtok(buf,",");
	//puts(pTemp);
	width=atoi(pTemp);
	pTemp=strtok(NULL,",");
	//puts(pTemp);
	height=atoi(pTemp);
	
	pMapBuf=(char *)malloc(width*height);

	int ix,iy;

	for(iy=0;iy<height;iy++){
		fgets(buf,256,pf);
		pTemp=strtok(buf,",");
		pMapBuf[iy*width+ix]=atoi(pTemp);
		for(ix=1;ix<width;ix++){
			pTemp=strtok(NULL,",");
			pMapBuf[iy*width+ix]=atoi(pTemp);
		}

	}
	//printf("%d",pMapBuf[3]);
	putTitle(0,height,0,width,width,pMapBuf,chTable);
	
	free(pMapBuf);
	fclose(pf);

	return 0;
}
