#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myeditor.h"


typedef struct{
	char *m_szToken;
	void (*_fp)(char *ptr);
}_S_PRO_OBJECT;

int bLoop=1;
char *pTemp;
char strCmd[128];
static _S_STR_LINE *pHeader=NULL;

void me_exit()
{
	bLoop=0;
}

void me_push()
{
	pTemp = strtok(NULL,"");
	char *pstr = (char *)malloc(strlen(pTemp)+1);
	strcpy(pstr,pTemp);

	_S_STR_LINE *pLine=(_S_STR_LINE *)malloc(sizeof(_S_STR_LINE));

	pLine->m_szStr=pstr;
	pLine->m_pNext=NULL;

	if(pHeader==NULL){
		pHeader=pLine;
	}
	else{
		//끝까지 찾아들어가기
		_S_STR_LINE *pNext=(_S_STR_LINE *)pHeader;

		while(pNext!=NULL){
			if(pNext->m_pNext==NULL){
				pNext->m_pNext=pLine;
				pNext=NULL;
			}
			else{
				pNext=pNext->m_pNext;
			}
		}
	}
}

void me_delete()
{
	_S_STR_LINE *_pGarbage=pHeader;
	pHeader=pHeader->m_pNext;

	free(_pGarbage->m_szStr);
	free(_pGarbage);
}

void me_dump()
{
	puts("---------------------------");
	_S_STR_LINE *pLine=pHeader;

	while(pLine!=NULL){
		puts(pLine->m_szStr);
		pLine=pLine->m_pNext;
	}

	puts("---------------------------");

}


