#pragma once
#include "CObject.h"
class CStone :
    public CObject
{

public:
	CStone();
	~CStone();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

	virtual void OnCollisionEnter(CCollider* _pOther);


private:
	void update_move();
	void update_animation();
	ULONGLONG dwtime;
};

