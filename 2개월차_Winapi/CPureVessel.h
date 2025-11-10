#pragma once
#include "CObject.h"

enum class PURE_VESSEL_STATE
{
    IDLE,
    COUNTER,
    DARK_TENTACLE,
	DART_SHOT_ANTICIPATE,
    DART_SHOT,
	DART_SHOT_END,
	DASH_ANTICIPATE,
    DASH,
	DASH_END,
	ROAR_ANTICIPATE,
    ROAR,
	ROAR_END,
	SLASH_ANTICIPATE,
    SLASH,
    SPIKE_ATTACK_ANTICIPATE,
	SPIKE_ATTACK,
	SPIKE_ATTACK_END,
	TELEPORT_ANTICIPATE,
	TELEPORT,
	TELEPORT_DART_ANTICIPATE,
	TELEPORT_DART,
	DEAD,

};

class CPureVessel :
    public CObject
{
	int			m_iSlashCount;
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

	bool         m_bSpearMinus20;
	bool		 m_bSpear8_5Angle;
	bool		 m_bSpear5Angle;
	bool         m_bSpear15Angle;
	bool		 m_bSpear30Angle;


	bool         m_bCircleEffect1;
	bool		 m_bCircleEffect2;
	bool		 m_bCircleEffect3;
	bool         m_bCircleEffect4;
	bool		 m_bCircleEffect5;
	bool		 m_bCircleEffect6;
	bool		 m_bCircleEffect7;

	Vec2 m_vCenterPos;
	float m_fSpeed;
	float m_fMaxDistance;


	PURE_VESSEL_STATE  m_eCurState;
	PURE_VESSEL_STATE  m_ePreState;

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
	CPureVessel();
	~CPureVessel();

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
	void CreateSpikeAnticipateEffect();
	
	void CreateMinus45SpearEffect();
	void CreateMinus20SpearEffect();
	void Create5AngleSpearEffect();
	void Create8_5AngleSpearEffect();
	void Create15AngleSpearEffect();
	void Create30AngleSpearEffect();


	void CreateCirCleEffect1();
	void CreateCirCleEffect2();
	void CreateCirCleEffect3();
	void CreateCirCleEffect4();
	void CreateCirCleEffect5();
	void CreateCirCleEffect6();
	void CreateCirCleEffect7();
};

