#pragma once
#include "CObject.h"

class CBeetle_New : public CObject
{

	//6월 15일 추가한코드  몬스터 HP설정
	int         m_iHP;

	int			m_iCount;

	Vec2 m_vCenterPos;
	float m_fSpeed;
	float m_fMaxDistance;


	MON_STATE  m_eCurState;
	MON_STATE  m_ePreState;

	int m_iDir; //1,-1 값을 넣음 1이면 양의방향 -1이면 음의 방향

	



public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }

	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

public:
	CBeetle_New();
	~CBeetle_New();

public:

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);


public: 

	void update_move();
	void update_state();
	void update_animation(); 


	void Create_item(); 

};

