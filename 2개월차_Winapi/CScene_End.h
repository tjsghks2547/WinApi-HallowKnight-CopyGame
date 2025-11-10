#pragma once
#include "CScene.h"
class CScene_End :
    public CScene
{
	virtual void update();
	virtual void Enter() override;
	virtual void Exit() override;


public:
	CScene_End();
	virtual ~CScene_End() override;
};

