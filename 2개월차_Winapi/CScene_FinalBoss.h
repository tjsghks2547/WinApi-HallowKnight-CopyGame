#pragma once
#include "CScene.h"
class CScene_FinalBoss :
    public CScene
{
public:
	virtual void update();
	virtual void Enter() override;
	virtual void Exit() override;


public:
	CScene_FinalBoss();
	virtual ~CScene_FinalBoss() override;
};

