#include "pch.h"
#include "CScene_End.h"
#include "CHornetBossRoom.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "C_Core.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"


#include "CPanelUI.h"
#include "CHpBarUI.h"
#include "CGeo.h"
#include "CSoulUI.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CResMgr.h"
#include "CLiquidUI.h"
#include "CBlackFilter.h"
#include "CHUD.h"
#include "CPlayerMgr.h"
#include "CEndingBackGround.h"


CScene_End::CScene_End()
{
}

CScene_End::~CScene_End()
{
	CScene::update();
}


void CScene_End::update()
{
}

void CScene_End::Enter()
{

	CCamera::GenInst()->FadeIn(5.f);
	CCamera::GenInst()->FadeOut(5.f);
	//배경 
	CObject* pEndingBackGround = new CEndingBackGround;
	pEndingBackGround->SetName(L"Ending_BackGround");
	pEndingBackGround->SetPos(Vec2(640.f, 380.f));
	AddObject(pEndingBackGround, GROUP_TYPE::BACKGROUND);

	// 타운 브금 깔아주기 
	CResMgr::GenInst()->LoadSound(L"ENDING_ROOM", L"sound\\232701435854D77602.wav");
	CSound* pEndingRoomBgm = CResMgr::GenInst()->FindSound(L"ENDING_ROOM");

	pEndingRoomBgm->PlayToBGM(false);


	start();
}

void CScene_End::Exit()
{
}


