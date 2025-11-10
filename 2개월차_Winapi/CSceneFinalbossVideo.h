#pragma once
#include "CScene.h"
class CSceneFinalbossVideo :
    public CScene
{
public:
	virtual void update();
	virtual void Enter() override;
	virtual void Exit() override;


public:
	CSceneFinalbossVideo();
	virtual ~CSceneFinalbossVideo() override;

private:
	HWND m_hVideo;
};

