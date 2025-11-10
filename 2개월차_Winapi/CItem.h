#pragma once
#include "CObject.h"
class CItem :
    public CObject
{
	
public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

public:
	CItem();
	~CItem();

public:

	//virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	//virtual void OnCollisionExit(CCollider* _pOther);


public:

	void update_move();
	void update_state();
	void update_animation();

public:
	void SetGravityXgive(float _f); 


};

