#include "pch.h"
#include "CScene_Stage2.h"
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
#include "CBtnUI.h"
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
#include "CNpc.h"
#include "CNpcreaction.h"
#include "CElderBugQuest.h"

#include "CInventory.h"
#include "CScene_Tool.h"
#include "Cclock_Item.h"
#include "CItemCusor.h"
#include "CWing_item.h"
#include "CStage2.h"
#include "CMushRoom.h"

CScene_Stage2::CScene_Stage2()
	:m_iCount(0)
{

}

CScene_Stage2::~CScene_Stage2()
{

}


void CScene_Stage2::update()
{
	CScene::update();
	if (KEY_TAP(KEY::Q))
	{

		ChangeScene(SCENE_TYPE::THIRD);


	}
}

void CScene_Stage2::Enter()
{
	
	//CCamera::GenInst()->FadeIn(4.f);

	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(1206.f, 3220.f)); // x좌표 500 y좌표 1000 이였음 //중간 7000,2500
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

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

	CUI* pGeo = new CGeo;
	pGeo->SetName(L"GEO");
	pGeo->SetPos(Vec2(100.f, 200.f));
	AddObject(pGeo, GROUP_TYPE::UI);


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


	//몬스터 부분 
	//================================
	CObject* pMushRoomMonster1 = new CMushRoom;
	pMushRoomMonster1->SetName(L"MushRoom");
	pMushRoomMonster1->SetPos(Vec2(1900.f, 3130.f));
	AddObject(pMushRoomMonster1, GROUP_TYPE::MONSTER);

	CObject* pMushRoomMonster2 = new CMushRoom;
	pMushRoomMonster2->SetName(L"MushRoom");
	pMushRoomMonster2->SetPos(Vec2(2096.f, 2682.f));
	AddObject(pMushRoomMonster2, GROUP_TYPE::MONSTER);

	CObject* pMushRoomMonster3 = new CMushRoom;
	pMushRoomMonster3->SetName(L"MushRoom");
	pMushRoomMonster3->SetPos(Vec2(1258.f, 2500.f));
	AddObject(pMushRoomMonster3, GROUP_TYPE::MONSTER);

	CObject* pMushRoomMonster4 = new CMushRoom;
	pMushRoomMonster4->SetName(L"MushRoom");
	pMushRoomMonster4->SetPos(Vec2(2189.f, 2170.f));
	AddObject(pMushRoomMonster4, GROUP_TYPE::MONSTER);

	CObject* pMushRoomMonster5 = new CMushRoom;
	pMushRoomMonster5->SetName(L"MushRoom");
	pMushRoomMonster5->SetPos(Vec2(1270.f, 1910.f));
	AddObject(pMushRoomMonster5, GROUP_TYPE::MONSTER);




	CObject* pStage2_Ground1 = new CGround;
	pStage2_Ground1->SetName(L"Ground");
	pStage2_Ground1->SetPos(Vec2(1206.f, 3247.f));
	pStage2_Ground1->SetScale(Vec2(312.f, 5.f));
	AddObject(pStage2_Ground1, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground2 = new CGround;
	pStage2_Ground2->SetName(L"Ground");
	pStage2_Ground2->SetPos(Vec2(1787.f, 3345.f));
	pStage2_Ground2->SetScale(Vec2(885.f, 5.f));
	AddObject(pStage2_Ground2, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground3 = new CGround;
	pStage2_Ground3->SetName(L"Ground");
	pStage2_Ground3->SetPos(Vec2(2285.f, 3298.f));
	pStage2_Ground3->SetScale(Vec2(95.f, 5.f));
	AddObject(pStage2_Ground3, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground4 = new CGround;
	pStage2_Ground4->SetName(L"Ground");
	pStage2_Ground4->SetPos(Vec2(2408.f, 3350.f));
	pStage2_Ground4->SetScale(Vec2(116.f, 5.f));
	AddObject(pStage2_Ground4, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground5 = new CGround;
	pStage2_Ground5->SetName(L"Ground");
	pStage2_Ground5->SetPos(Vec2(2525.f, 3062.f));
	pStage2_Ground5->SetScale(Vec2(90.f, 5.f));
	AddObject(pStage2_Ground5, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground6 = new CGround;
	pStage2_Ground6->SetName(L"Ground");
	pStage2_Ground6->SetPos(Vec2(2702.f, 3302.f));
	pStage2_Ground6->SetScale(Vec2(123.f, 5.f));
	AddObject(pStage2_Ground6, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground7 = new CGround;
	pStage2_Ground7->SetName(L"Ground");
	pStage2_Ground7->SetPos(Vec2(3261.f, 3345.f));
	pStage2_Ground7->SetScale(Vec2(910.f, 5.f));
	AddObject(pStage2_Ground7, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground8 = new CGround;
	pStage2_Ground8->SetName(L"Ground");
	pStage2_Ground8->SetPos(Vec2(1621.f, 3061.f));
	pStage2_Ground8->SetScale(Vec2(99.f, 5.f));
	AddObject(pStage2_Ground8, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground9 = new CGround;
	pStage2_Ground9->SetName(L"Ground");
	pStage2_Ground9->SetPos(Vec2(2101.f, 2825.f));
	pStage2_Ground9->SetScale(Vec2(470.f, 5.f));
	AddObject(pStage2_Ground9, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground10 = new CGround;
	pStage2_Ground10->SetName(L"Ground");
	pStage2_Ground10->SetPos(Vec2(2541.f, 2652.f));
	pStage2_Ground10->SetScale(Vec2(78.f, 5.f));
	AddObject(pStage2_Ground10, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground11 = new CGround;
	pStage2_Ground11->SetName(L"Ground");
	pStage2_Ground11->SetPos(Vec2(1748.f, 2585.f));
	pStage2_Ground11->SetScale(Vec2(120.f, 5.f));
	AddObject(pStage2_Ground11, GROUP_TYPE::GROUND);


	CObject* pStage2_Ground12 = new CGround;
	pStage2_Ground12->SetName(L"Ground");
	pStage2_Ground12->SetPos(Vec2(1325.f, 2631.f));
	pStage2_Ground12->SetScale(Vec2(552.f, 5.f));
	AddObject(pStage2_Ground12, GROUP_TYPE::GROUND);
	
	CObject* pStage2_Ground13 = new CGround;
	pStage2_Ground13->SetName(L"Ground");
	pStage2_Ground13->SetPos(Vec2(2716.f, 2434.f));
	pStage2_Ground13->SetScale(Vec2(67.f, 5.f));
	AddObject(pStage2_Ground13, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground14 = new CGround;
	pStage2_Ground14->SetName(L"Ground");
	pStage2_Ground14->SetPos(Vec2(2199.f, 2257.f));
	pStage2_Ground14->SetScale(Vec2(660.f, 5.f));
	AddObject(pStage2_Ground14, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground15 = new CGround;
	pStage2_Ground15->SetName(L"Ground");
	pStage2_Ground15->SetPos(Vec2(1700.f, 2127.f));
	pStage2_Ground15->SetScale(Vec2(77.f, 5.f));
	AddObject(pStage2_Ground15, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground16 = new CGround;
	pStage2_Ground16->SetName(L"Ground");
	pStage2_Ground16->SetPos(Vec2(1277.f, 2022.f));
	pStage2_Ground16->SetScale(Vec2(560.f, 5.f));
	AddObject(pStage2_Ground16, GROUP_TYPE::GROUND);


	CObject* pStage2_Ground17 = new CGround;
	pStage2_Ground17->SetName(L"Ground");
	pStage2_Ground17->SetPos(Vec2(1726.f, 1833.f));
	pStage2_Ground17->SetScale(Vec2(77.f, 5.f));
	AddObject(pStage2_Ground17, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground18 = new CGround;
	pStage2_Ground18->SetName(L"Ground");
	pStage2_Ground18->SetPos(Vec2(2038.f, 1740.f));
	pStage2_Ground18->SetScale(Vec2(380.f, 5.f));
	AddObject(pStage2_Ground18, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground19 = new CGround;
	pStage2_Ground19->SetName(L"Ground");
	pStage2_Ground19->SetPos(Vec2(1277.f, 1554.f));
	pStage2_Ground19->SetScale(Vec2(560.f, 5.f));
	AddObject(pStage2_Ground19, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground20 = new CGround;
	pStage2_Ground20->SetName(L"Ground");
	pStage2_Ground20->SetPos(Vec2(2830.f, 1644.f));
	pStage2_Ground20->SetScale(Vec2(134.f, 5.f));
	AddObject(pStage2_Ground20, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground21 = new CGround;
	pStage2_Ground21->SetName(L"Ground");
	pStage2_Ground21->SetPos(Vec2(3355.f, 1550.f));
	pStage2_Ground21->SetScale(Vec2(890.f, 5.f));
	AddObject(pStage2_Ground21, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground22 = new CGround;
	pStage2_Ground22->SetName(L"Ground");
	pStage2_Ground22->SetPos(Vec2(3704.f, 3050.f));
	pStage2_Ground22->SetScale(Vec2(5.f, 650.f));
	AddObject(pStage2_Ground22, GROUP_TYPE::GROUND);

	CObject* pStage2_Ground23 = new CGround;
	pStage2_Ground23->SetName(L"Ground");
	pStage2_Ground23->SetPos(Vec2(3704.f, 2869.f));
	pStage2_Ground23->SetScale(Vec2(670.f, 5.f));
	AddObject(pStage2_Ground23, GROUP_TYPE::GROUND);

	

	CObject* pStage2BackGround = new CStage2;
	pStage2BackGround ->SetName(L"Stage2_BackGround");
	pStage2BackGround ->SetPos(Vec2(0.f, 0.f));
	AddObject(pStage2BackGround, GROUP_TYPE::BACKGROUND);

	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::SKILLEFFECT);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::MONSTER);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::SKILLEFFECT, GROUP_TYPE::MONSTER);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::PLAYER);

	CResMgr::GenInst()->LoadSound(L"Stage_2_BackgroundBGM", L"sound\\S5 Green Path Bass.wav");
	CSound* pStag2backgroundBGM = CResMgr::GenInst()->FindSound(L"Stage_2_BackgroundBGM");

	pStag2backgroundBGM->SetVolume(80.f);
	pStag2backgroundBGM->PlayToBGM(true);

	
	CCamera::GenInst()->SetTarget(pObj);
	start();
}

void CScene_Stage2::Exit()
{
	CCamera::GenInst()->FadeIn(5.f);
	CCollisionMgr::GenInst()->Reset();
	DeleteAll();

}

void CScene_Stage2::CreateForce()
{
}

