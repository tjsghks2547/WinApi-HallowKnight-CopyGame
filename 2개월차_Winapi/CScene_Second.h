#pragma once
#include "CScene.h"
class CScene_Second : public CScene
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
	CScene_Second();
	virtual ~CScene_Second() override;

};

