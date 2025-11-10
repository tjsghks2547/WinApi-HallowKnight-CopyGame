#pragma once
#include "CScene.h"



class CScene_Thrid : public CScene
{
public:
	virtual void update();
	virtual void Enter() override;
	virtual void Exit() override;


public:
	CScene_Thrid();
	virtual ~CScene_Thrid() override;
};

