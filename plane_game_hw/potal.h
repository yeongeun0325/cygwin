#ifndef __POTAL_H__
#define __POTAL_H__

typedef struct _S_Potal{
	int m_nXpos;
	int m_nYpos;
	_S_MAP_OBJECT *m_pBody;
	void (*fpDraw)(struct _S_Potal *,_S_MAP_OBJECT *);
} _S_Potal;

void Potal_init(_S_Potal *,_S_MAP_OBJECT *,int ,int );
void Potal_Draw(_S_Potal *, _S_MAP_OBJECT *);


#endif