#pragma once
#include "CScene.h"

class CScene_Start : public CScene
{
private:
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
	CScene_Start();
	virtual ~CScene_Start() override;


};

