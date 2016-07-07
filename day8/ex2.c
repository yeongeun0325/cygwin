#include<stdio.h>
#include<string.h>

struct _S_WEAPON{
	int m_nAttack;
	int m_nEndure;
};

struct _S_PLAYER{
	int m_nHP;
	int m_nMP;
	struct _S_WEAPON m_sWeapon;
};

int main()
{
	struct _S_PLAYER player1;

	player1.m_nHP=100;
	player1.m_nMP=50;

	player1.m_sWeapon.m_nAttack=5;
	player1.m_sWeapon.m_nEndure=10;

	return 0;
}
