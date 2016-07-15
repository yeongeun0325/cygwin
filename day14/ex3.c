#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _S_ITEM{
	char m_szName[32];

	int m_nType;
	int m_nValue;

}_S_ITEM;

_S_ITEM item_list[]={
	{"short sword",0,10},
	{"wood shield",0,5},
	{"dagger",0,6},
	{"sling",0,3},
	{"staff",0,7}
};

unsigned long getHashCode(const char *szStr)
{
	int nLength=strlen(szStr);
	int nHash=5381;
	
	for(int i=0;i<nLength;i++){
		//printf("%d\r\n",szStr[i]);
		//nHash+=szStr[i];
		int c=szStr[i];
		nHash=((nHash<<5)+nHash)+c;
	}

	return nHash;
}

_S_ITEM *finditem(const char *szName)
{
	int item_list_lenght=sizeof(item_list)/sizeof(_S_ITEM);
	unsigned long hcode1=getHashCode(szName);

	for(int i=0;i<item_list_lenght;i++){
		_S_ITEM *pitem=&(item_list[i]);
		//if(strcmp(szName,pitem->m_szName)==0){
		if(getHashCode(pitem->m_szName)==hcode1){
			return pitem;
		}
	}
	
}

int main()
{
	_S_ITEM *pItem=finditem("short sword");
	printf("%s %d\r\n",pItem->m_szName,pItem->m_nValue);

	return 0;
}
