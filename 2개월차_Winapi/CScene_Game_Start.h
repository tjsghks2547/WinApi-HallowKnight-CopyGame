#pragma once
#include "CScene.h"
class CScene_Game_Start :
    public CScene
{
public:
	virtual void update();
	virtual void Enter() override;
	virtual void Exit() override;


public:
	CScene_Game_Start();
	virtual ~CScene_Game_Start() override;

};

