#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"area.h"


int main()
{
	_S_AREA town,basic_dungeon;

	area_init(&town);
	town.m_szName="town";
	area_init(&basic_dungeon);
	basic_dungeon.m_szName="basic-dungeon";

	town.node[0]=&basic_dungeon;
	basic_dungeon.node[0]=&town;
	
	_S_AREA *pCurrentArea=&town;

	int bLoop=1;
	while(bLoop){
		char szCmd[32];
		gets(szCmd);
		char *pTemp=strtok(szCmd," ");

		if(!strcmp(pTemp,"look")){
			pCurrentArea->pfDraw(pCurrentArea);
		}
		else if(!strcmp(pTemp,"move")){
			char *pszArea=strtok(NULL,"");
			printf("당신은 %s (으)로 이동합니다.\r\n",pszArea);
			_S_AREA *pTemp=pCurrentArea->pfFind(pCurrentArea,pszArea);
			if(pTemp){
				puts("success\r\n");
				pCurrentArea=pTemp;
			}
			else{
				puts("cannot move\r\n");
			}

		}
		else if(!strcmp(pTemp,"exit")){
			bLoop=0;
		}
	}

	return 0;
}
