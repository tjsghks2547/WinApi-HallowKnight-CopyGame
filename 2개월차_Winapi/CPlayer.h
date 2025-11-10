#pragma once
#include "CObject.h"


enum class PLAYER_STATE
{
	IDLE,
	WALK,
	SLASH,
	UPSLASH,
	ATTACK,
	JUMP,
	DOUBLE_JUMP,
	DASH,
	FOCUS,
	FIREBALL,
	STUN,
	DOWN_SLASH,
	FALL,
	DEAD,
};

enum class PLAYER_HP_STATE
{
	HP_STATE_UP,
	HP_STATE_DOWN,

	END,
};

class CTexture;



class CPlayer : public CObject
{

private:
	int				m_i_SlashCount;
	int				m_i_JumpCount;
	int				i_Count;
	int				m_iTest;
	int				m_iUpSlashEffectCount;
	int				m_iDownSlashEffectCount;

	int				m_iHP;
	int				m_iDir; // 플레이어 방향
	int				m_iPrevDir; // 이전 플레이어 방향 

	PLAYER_STATE	m_ePreState;
	PLAYER_STATE	m_eCurState;

	PLAYER_HP_STATE m_eHpState; 

	bool			m_bGround;

public:
	CPlayer();
	~CPlayer();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;
	

	
	//virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
	
private:
	void update_state();
	void update_move();
	void update_animation();
	void update_sound();
	
	


	CPlayer* Clone() { return new CPlayer(*this); }

	void CreateSlash();
	void CreateFocusEffect(); 
	void CreateFireBallEffect();
	void CreateFireBall();
	void CreateDashEffect();
	void CreateNewDashEffect();

	void CreateUpSlashEffect();
	void CreateDownSlashEffect();
	void CreateDamagedEffect();

	void CreateWingEffect();
	void CreateStunEffect();

private:
	ULONGLONG dwtime; 

	bool   m_bFallLeftAnimationSet;
	bool   m_bFallRightAnimationSet;

};

