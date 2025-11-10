#pragma once
#include "CObject.h"
class CNpc :
    public CObject
{

public:
	CNpc();
	~CNpc();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

	virtual void OnCollision(CCollider* _pOther);


private:

	void update_animation();

};

