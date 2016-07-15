#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"area.h"

static _S_AREA *find(_S_AREA *pObj,const char *area_name)
{
	for(int i=0;i<8;i++){
		_S_AREA *pArea=pObj->node[i];
		if(pObj->node[i]!=NULL){
			if(strcmp(area_name,pArea->m_szName)==0){
				return pArea;
			}
		}
	}
	return NULL;
}

static void draw(_S_AREA *pObj)
{
	//dump해서 mapdata 찍어주기
	printf("당신은 현재 %s에 있습니다.\r\n",pObj->m_szName);
}

void area_init(_S_AREA *pObj)
{
	for(int i=0;i<8;i++){
		pObj->node[i]=NULL;
	}

	pObj->pfFind=find;
	pObj->pfDraw=draw;
}
