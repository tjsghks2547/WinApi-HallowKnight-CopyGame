#pragma once
#include "CObject.h"


enum class KNIGHT_STATE
{
	IDLE,
	JUMP_ANTICIPATE,
	JUMP,
	JUMP_LAND,
	RUSH_ANTICIPATE,
	RUSH,
	ATTACK_ANTICIPATE,
	ATTACK,
	ATTACK_RECOVER,
	ANGRY_ATTACK_ANTICIPATE,
	ANGRY_ATTACK,
	ANGRY_ATTACK_RECOVER,
	STUN_OPEN,
	ROLL,
	ROLLEND,
	DEAD,
};

class CFalseKnight : public CObject
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

	Vec2 m_vCenterPos;
	float m_fSpeed;
	float m_fMaxDistance;


	KNIGHT_STATE  m_eCurState;
	KNIGHT_STATE  m_ePreState;

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
	CFalseKnight();
	~CFalseKnight();

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
	void CreateFallStone();
	void CreateAttackWave();
	void CreateJumpWave();
	void CreateStunEffect();
};

