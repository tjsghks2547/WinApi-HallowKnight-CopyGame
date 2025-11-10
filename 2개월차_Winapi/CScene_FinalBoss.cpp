#include "pch.h"
#include "CScene_FinalBoss.h"
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

#include "CKeyMgr.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CGround.h"

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
#include "CFinalBossRoom.h"
#include "CPureVessel.h"




CScene_FinalBoss::CScene_FinalBoss()
{

}

CScene_FinalBoss::~CScene_FinalBoss()
{

}

void CScene_FinalBoss::update()
{
	CScene::update();

}

void CScene_FinalBoss::Enter()
{
	//Player 추가 
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(1125.f, 1250.f)); // x좌표 500 y좌표 1000 이였음 //중간 7000,2500
	pObj->SetScale(Vec2(100.f, 100.f));

	AddObject(pObj, GROUP_TYPE::PLAYER);

	//플레이어를 관리하기 위해 세팅 ( Start Scene에서) 
	//RegisterPlayer(pObj);


	Vec2 vResolution = CCore::GenInst()->GetResolution();

	CUI* pHpBarUI = new CHpBarUI;
	pHpBarUI->SetName(L"HpBarUI1");
	pHpBarUI->SetPos(Vec2(200.f, 120.f));
	AddObject(pHpBarUI, GROUP_TYPE::UI);

	CUI* pHpBarUI2 = new CHpBarUI;
	pHpBarUI2->SetName(L"HpBarUI2");
	pHpBarUI2->SetPos(Vec2(270.f, 120.f));
	AddObject(pHpBarUI2, GROUP_TYPE::UI);

	CUI* pHpBarUI3 = new CHpBarUI;
	pHpBarUI3->SetName(L"HpBarUI3");
	pHpBarUI3->SetPos(Vec2(340.f, 120.f));
	AddObject(pHpBarUI3, GROUP_TYPE::UI);

	CUI* pHpBarUI4 = new CHpBarUI;
	pHpBarUI4->SetName(L"HpBarUI4");
	pHpBarUI4->SetPos(Vec2(410.f, 120.f));
	AddObject(pHpBarUI4, GROUP_TYPE::UI);

	CUI* pHpBarUI5 = new CHpBarUI;
	pHpBarUI5->SetName(L"HpBarUI5");
	pHpBarUI5->SetPos(Vec2(480.f, 120.f));
	AddObject(pHpBarUI5, GROUP_TYPE::UI);

	//CUI* pGeo = new CGeo; 
	//pGeo->SetName(L"GEO");
	//pGeo->SetPos(Vec2(100.f, 150.f));
	//AddObject(pGeo, GROUP_TYPE::UI);


	CHUD* pHudUI = new CHUD;
	pHudUI->SetName(L"HUD_UI");
	pHudUI->SetPos(Vec2(154.f, 84.f));
	AddObject(pHudUI, GROUP_TYPE::UI);

	CBlackFilter* pBlackFilter = new CBlackFilter;
	pBlackFilter->SetName(L"Black_fiter");
	pBlackFilter->SetPos(Vec2(71.f, 69.f));
	AddObject(pBlackFilter, GROUP_TYPE::UI);

	CLiquidUI* pSoulUI_Liquid = new CLiquidUI;
	pSoulUI_Liquid->SetName(L"SOUL_UI_GLOW");
	pSoulUI_Liquid->SetPos(Vec2(71.f, 69.f));
	AddObject(pSoulUI_Liquid, GROUP_TYPE::UI);

	CUI* pSoulUI = new CSoulUI;
	pSoulUI->SetName(L"SOUL_UI");
	pSoulUI->SetPos(Vec2(100.f, 100.f));
	AddObject(pSoulUI, GROUP_TYPE::UI);


	//보스몬스터 
	CObject* pPureVessel = new CPureVessel;
	pPureVessel->SetName(L"Pure_Vessel");
	pPureVessel->SetPos(Vec2(1700.f, 1000.f));
	AddObject(pPureVessel, GROUP_TYPE::MONSTER);



	CObject* pFinalBoss_Ground1 = new CGround;
	pFinalBoss_Ground1->SetName(L"Ground");
	pFinalBoss_Ground1->SetPos(Vec2(3559.f, 1300.f));
	pFinalBoss_Ground1->SetScale(Vec2(6000.f, 5.f));

	AddObject(pFinalBoss_Ground1, GROUP_TYPE::GROUND);

	CObject* pFinalBoss_Ground2 = new CGround;
	pFinalBoss_Ground2->SetName(L"Ground");
	pFinalBoss_Ground2->SetPos(Vec2(668.f, 850.f));
	pFinalBoss_Ground2->SetScale(Vec2(5.f, 3000.f));
	AddObject(pFinalBoss_Ground2, GROUP_TYPE::GROUND);

	CObject* pFinalBoss_Ground3 = new CGround;
	pFinalBoss_Ground3->SetName(L"Ground");
	pFinalBoss_Ground3->SetPos(Vec2(1971.f, 850.f));
	pFinalBoss_Ground3->SetScale(Vec2(5.f, 3000.f));

	AddObject(pFinalBoss_Ground3, GROUP_TYPE::GROUND);



	//배경 
	CObject* pBackGround = new CFinalBossRoom;
	pBackGround->SetName(L"Fianl_Boss_BackGround");
	pBackGround->SetPos(Vec2(0.f, 0.f));
	AddObject(pBackGround, GROUP_TYPE::BACKGROUND);


	// 타운 브금 깔아주기 
	CResMgr::GenInst()->LoadSound(L"BGM_BOSS_ROOM", L"sound\\Vessel_bgm.wav");
	CSound* pFianlBossBgm = CResMgr::GenInst()->FindSound(L"BGM_BOSS_ROOM");
	
	pFianlBossBgm->SetVolume(90.f);
	pFianlBossBgm->PlayToBGM(true);

	CCamera::GenInst()->SetTarget(pObj);



	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::SKILLEFFECT, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::SKILLEFFECT, GROUP_TYPE::PLAYER);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::SKILLEFFECT, GROUP_TYPE::MONSTER);



	start();

}

void CScene_FinalBoss::Exit()
{
}


