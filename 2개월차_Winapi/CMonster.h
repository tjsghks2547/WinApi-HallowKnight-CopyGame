#pragma once
#include "CObject.h"

class CTexture;
class AI;

enum class Monster_STATE
{
	IDLE,
	WALK,
	ATTACK,
	JUMP,
	DEAD,
};


struct tMonInfo
{
	float		fHP;		   //	체력
	float		fSpeed;      //	속도
	float       fRecogRange; //	인지 범위 
	float		fAttRange;   //	공격 범위
	float       fAtt;		   //   공격력 
};

class CMonster : public CObject
{
protected:

	tMonInfo	m_tInfo;
	CTexture*   m_pTex;
	AI*			m_pAI;

	
public:
    float GetSpeed() { return m_tInfo.fSpeed; }
	void  SetSpeed(float _f) { m_tInfo.fSpeed = _f;  }

	void  SetAI(AI* _AI);
	const tMonInfo& GetInfo() { return m_tInfo; }

private:
	void  SetMonInfo(const tMonInfo& _info){ m_tInfo = _info;}
	

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

public:
	CMonster();
	~CMonster();

public:

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);


public:
	void CreateMissile();

	friend class CMonFactory;


private:

	CMonster* Clone() { return new CMonster(*this); }
};

