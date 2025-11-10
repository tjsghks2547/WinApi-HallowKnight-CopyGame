#pragma once
#include "CObject.h"



enum class PLAYER_ATTACK_STATE
{
	SLASH,
	NORMAL_ATT_2,
	NORMAL_ATT_3,
	NONE,
	END,
};



class CSLASH :public CObject
{
private:

	int				i_Count; // 7월 1일 추가한 내용
	int				m_iDir; // 플레이어 방향
	int				m_iPrevDir; // 이전 플레이어 방향 




public:
	CSLASH();
	~CSLASH();

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;



	//virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	//virtual void OnCollisionExit(CCollider* _pOther);

private:
	void update_state();
	void update_animation();

public:

	void SetDir(int _iDir) { m_iDir = _iDir; }
	void CreateHitEffect();

};

