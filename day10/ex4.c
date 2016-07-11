#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<sys/time.h>
#include<termios.h>
#include<sys/select.h>

#include"../engine/engine2d.h"

typedef struct{
	int m_nSkima;
	int m_nWidth;
	int m_nHeight;

}_S_MAP_HEADER;

typedef struct{
	_S_MAP_HEADER m_header;
	char *m_pBuf;

}_S_MAP_OBJECT;

_S_MAP_OBJECT MapObject;

int main()
{
	int bLoop=1;

	MapObject.m_header.m_nSkima=1;	//파일구조바꿀때 구분
	MapObject.m_pBuf=NULL;
	char TitlePalette[]={'.','#','@','%'};

	while(bLoop){
		char szCmd[32];
		gets(szCmd);
		char *pTemp=strtok(szCmd," ");

		if(!strcmp(pTemp,"exit")){
			bLoop=0;
			if(MapObject.m_pBuf){
				free(MapObject.m_pBuf);
			}
		}
		else if(!strcmp(pTemp,"dump")){
			putTitle(0,MapObject.m_header.m_nHeight,
			0,MapObject.m_header.m_nWidth,
			MapObject.m_header.m_nWidth,MapObject.m_pBuf,TitlePalette);
		}
		else if(!strcmp(pTemp,"new")){
			//new width height
			if(MapObject.m_pBuf!=NULL){
				free(MapObject.m_pBuf);
			}
			MapObject.m_header.m_nWidth=atoi(strtok(NULL," "));
			MapObject.m_header.m_nHeight=atoi(strtok(NULL," "));
			MapObject.m_pBuf=malloc(MapObject.m_header.m_nHeight*MapObject.m_header.m_nWidth);
			//초기화
			/*for(int i=0;i<MapObject.m_header.m_nHeight;i++){
			for(int j=0;j<MapObject.m_header.m_nWidth;j++){
				MapObject.m_pBuf[j*MapObject.m_header.m_nWidth+i]=0;
			}
		}*/
			for(int i=0;i<MapObject.m_header.m_nHeight*MapObject.m_header.m_nWidth;i++){
				MapObject.m_pBuf[i]=0;
			}

		}
		else if(!strcmp(pTemp,"put")){
			//put whidth height tile_index
			int x,y,tile_index;
		
			x=atoi(strtok(NULL," "));
			y=atoi(strtok(NULL," "));
			tile_index=atoi(strtok(NULL," "));

			MapObject.m_pBuf[y*MapObject.m_header.m_nWidth+x]=tile_index;
		}
		else if(!strcmp(pTemp,"hline")){
			int x,tile_index;

			x=atoi(strtok(NULL," "));
			tile_index=atoi(strtok(NULL," "));
			
			for(int y=0;y<MapObject.m_header.m_nHeight;y++){
					MapObject.m_pBuf[y*MapObject.m_header.m_nHeight+x]=tile_index;
			}

		}
		else if(!strcmp(pTemp,"vline")){
			int y,tile_index;

			y=atoi(strtok(NULL," "));
			tile_index=atoi(strtok(NULL," "));

			for(int x=0;x<MapObject.m_header.m_nWidth;x++){
				MapObject.m_pBuf[y*MapObject.m_header.m_nWidth+x]=tile_index;
			}
		}
		else if(!strcmp(pTemp,"save")){
			//save filename
		}
		else if(!strcmp(pTemp,"load")){
			//load filename
		}
	}

	return 0;
}
