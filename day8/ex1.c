#include<stdio.h>
#include<string.h>

struct _S_HUMAN{
	int m_nHP;
	int m_nMP;
	int m_nLevel;
	double m_dbAp;
	char m_szName[128];

};

int main()
{
	struct _S_HUMAN human;
	
	human.m_nHP=100;
	human.m_nMP=50;
	human.m_nLevel=1;
	human.m_dbAp=3.5;
	strcpy(human.m_szName,"athuser");

	printf("hp:%d mp:%d level:%d ap:%.2f name:%s\r\n",human.m_nHP,human.m_nMP,
	human.m_nLevel,human.m_dbAp,human.m_szName);


	return 0;
}
