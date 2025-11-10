#pragma once
#include "CMonster.h"
class CBeetle :
    public CMonster
{
private:

	int				m_iDir; // 방향
	int				m_iPrevDir; // 이전 플레이어 방향 

	MON_STATE	m_ePreState;
	MON_STATE	m_eCurState;

public:
	CBeetle();
	~CBeetle();

public:
	void update_state();
	void update_move();
	void update_animation();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

