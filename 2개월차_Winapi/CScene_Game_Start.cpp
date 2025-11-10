#include "pch.h"
#include "CScene_Game_Start.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CSound.h"

#include "CObject.h"

#include "C_Core.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CStartBackGround.h"
#include "CStartCusor.h"
#include "CResMgr.h"

CScene_Game_Start::CScene_Game_Start()
{
	
}

CScene_Game_Start::~CScene_Game_Start()
{

}

void CScene_Game_Start::update()
{
	CScene::update();
}

void CScene_Game_Start::Enter()
{

	CObject* pStartCusor = new CStartCusor;
	pStartCusor->SetName(L"Start_Cusor");
	pStartCusor->SetPos(Vec2(-100.f, -100.5f));
	AddObject(pStartCusor, GROUP_TYPE::UI);
	

	CObject* pStartBackground = new CStartBackGround;
	pStartBackground->SetName(L"Start_Background");
	pStartBackground->SetPos(Vec2(640.f, 360.f));
	AddObject(pStartBackground, GROUP_TYPE::BACKGROUND);

	CResMgr::GenInst()->LoadSound(L"Start_Bgm", L"sound\\Title.wav");
	CSound* pStartBGM = CResMgr::GenInst()->FindSound(L"Start_Bgm");

	pStartBGM->PlayToBGM(false);
	pStartBGM->SetVolume(80.f);
	
}

void CScene_Game_Start::Exit()
{
	DeleteAll();
}


