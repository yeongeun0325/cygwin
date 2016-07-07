#include<stdio.h>

typedef struct{
	char m_szName[32];
	int m_nHP;
}_S_PLAYER;

int main()
{	
	_S_PLAYER player={
		"안철수",
		100
	};

	FILE *pf=fopen("test.dat","wb"); //바이너리로 저장

	fwrite(&player,sizeof(_S_PLAYER),1,pf);	
	fclose(pf);

	
	return 0;
}
