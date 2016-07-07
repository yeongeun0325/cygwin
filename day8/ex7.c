#include<stdio.h>

typedef struct {
	int m_nHP;
	char m_szName[128];
}_s_player;

//typedef struct _S_PLAYER _s_player;

/*
 * c++용
 * class _s_player{
 * }
 */

int main()
{
	_s_player player={100,"player1"};
	//struct _S_PLAYER player;
	
	puts(player.m_szName);

	return 0;
}
