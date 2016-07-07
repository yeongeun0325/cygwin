#include<stdio.h>

struct _S_PLAYER{
	int m_nHP;
	int m_MP;
};

int main()
{
	struct _S_PLAYER player1={
		100,50
	};

	struct _S_PLAYER player2;
	struct _S_PLAYER *pPlayer;

	player2=player1;	//복사
	pPlayer=&player1;	//포인터 참조
	
	player1->m_nHP=240;
	player2.m_MP=30;;
	printf("%d\r\n",player1.m_nHP);

	return 0;
}

