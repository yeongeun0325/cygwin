#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<sys/time.h>
#include<termios.h>
#include<sys/select.h>

#include"../engine/engine2d.h"
#include"../mapEditor/map.h"

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
			map_dump(&MapObject,TitlePalette);
		}
		else if(!strcmp(pTemp,"new")){
			//new width height
			int nWidth=atoi(strtok(NULL," "));
			int nHeight=atoi(strtok(NULL," "));
			map_new(&MapObject,nWidth,nHeight);

		}
		else if(!strcmp(pTemp,"put")){
			//put whidth height tile_index
			int x,y,tile_index;
		
			x=atoi(strtok(NULL," "));
			y=atoi(strtok(NULL," "));
			tile_index=atoi(strtok(NULL," "));

			//MapObject.m_pBuf[y*MapObject.m_header.m_nWidth+x]=tile_index;
			map_PutTile(&MapObject,x,y,tile_index);
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
			char *szFileName=strtok(NULL," ");
			
			puts("save ok");
			
			map_save(&MapObject,szFileName);
		}
		else if(!strcmp(pTemp,"load")){
			//load filename
			char *szFileName=strtok(NULL," ");
			
			puts("load ok");

			map_load(&MapObject,szFileName);
		}
		else if(!strcmp(pTemp,"tridraw_1")){
			//맵사이즈만큼 삼각형그림

			int nHeight,nWidth,tile_index;
			nWidth=MapObject.m_header.m_nWidth;
			nHeight=MapObject.m_header.m_nHeight;
			tile_index=atoi(strtok(NULL," "));

			for(int y=0;y<nHeight;y++){
				for(int x=0;(x<y)&&(x<nWidth);x++){
					MapObject.m_pBuf[y*nWidth+x]=tile_index;
				}
			}
		}
		else if(!strcmp(pTemp,"draw_cross")){
			//draw_cross 1 2 1
			int x,y,tile_index;
			x = atoi( strtok(NULL," ") );
			y = atoi( strtok(NULL," ") );
			tile_index = atoi( strtok(NULL," ") ); 

			MapObject.m_pBuf[y*MapObject.m_header.m_nWidth+x]=tile_index;
			MapObject.m_pBuf[y*MapObject.m_header.m_nWidth+(x+1)]=tile_index;
			MapObject.m_pBuf[y*MapObject.m_header.m_nWidth+(x-1)]=tile_index;
			MapObject.m_pBuf[(y-1)*MapObject.m_header.m_nWidth+x]=tile_index;
			MapObject.m_pBuf[(y+1)*MapObject.m_header.m_nWidth+x]=tile_index;
		}
	}

	return 0;
}
