#pragma once
#include "CObject.h"



enum class HORNET_STATE
{
	IDLE,
	COUNTER_ANTICIPATE,
	COUNTER_STANCE,
	COUNTER_END,
	COUNTER_ATTACK_ANTICIPATE,
	COUNTER_ATTACK,
	COUNTER_ATTACK_RECOVER,
	JUMP_ANTICIPATE,
	JUMP,
	JUMP_RUSH,
	JUMP_LAND,
	RUSH_ANTICIPATE,
	RUSH,
	RUSH_RECOVER,
	ATTACK_ANTICIPATE,
	ATTACK,
	ATTACK_RECOVER,
	THROW_ANTICIPATE,
	THROW,
	THROW_RECOVER,
	STUN_ANTICIPATE,
	STUN,
	EVADE_ANTICIPATE,
	EVADE,
	SPHERE_ANTICIPATE,
	SPHERE,
	SPHERE_RECOVER,

	DEAD,
};

class CHornet : public CObject
{
	int			m_iStunCount;
	int			m_iGetVelocityCount;
	int         m_bAngryCount;
	bool		m_bSoundPlayed;
	//6월 15일 추가한코드  몬스터 HP설정
	int         m_iPatternCount;
	int         m_iCount;
	int         m_iHP;
	int			m_iStoneCount;
	//7월 12일 추가한 코드 
	bool		GroundOn;
	Vec2		vDir;

	Vec2 m_vCenterPos;
	float m_fSpeed;
	float m_fMaxDistance;


	HORNET_STATE  m_eCurState;
	HORNET_STATE  m_ePreState;

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
	CHornet();
	~CHornet();

public:

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);


public:

	void update_move();
	void update_state();
	void update_sound();
	void update_animation();



private:
	ULONGLONG dwtime;
	void CreateDashEffect();
	void CreateNeedle();
	void CreateThread();
	void CreateThrowEffect();
	void CreateSphereBallEffect();
	void CreateStunEffect();
};

