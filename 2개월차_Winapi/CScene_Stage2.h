#pragma once
#include "CScene.h"
class CScene_Stage2 :
    public CScene
{
private:

	int	  m_iCount;
	Vec2  m_vForcePos;
	float m_fForceRadius;
	float m_fCurRadius;
	float m_fForce;
	bool  m_bUseForce;

public:
	virtual void update();
	virtual void Enter() override;
	virtual void Exit() override;

public:
	void CreateForce();

public:
	CScene_Stage2();
	virtual ~CScene_Stage2() override;
};

