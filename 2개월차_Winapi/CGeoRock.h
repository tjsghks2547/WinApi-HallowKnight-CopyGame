#pragma once
#include "CObject.h"

class CTexture;

class CGeoRock :
    public CObject
{
	int         m_iHP;
	int			m_iCount;

	CTexture*	m_pTex;


public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

public:
	CGeoRock();
	~CGeoRock();

public:

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);


public:
	void Create_item();
	void Create_item1();
	void Create_item2();
	void Create_item3();
	void Create_item4();

};

