#ifndef __POTAL_H__
#define __POTAL_H__

typedef struct _S_Potal{
	int m_nFSM;
	int m_nStep;

	double m_fXpos;
	double m_fYpos;

	double m_fCenterX;
	double m_fCenterY;

	_S_MAP_OBJECT *m_pBody;
	void (*pfDraw)(struct _S_Potal *,_S_MAP_OBJECT *);
} _S_Potal;

void Potal_init(_S_Potal *,_S_MAP_OBJECT *,int ,int );
//void Potal_Draw(_S_Potal *, _S_MAP_OBJECT *);


#endif