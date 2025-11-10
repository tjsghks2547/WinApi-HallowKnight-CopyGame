#include "pch.h"
#include "CScene_Second.h"
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
#include "CTown.h"


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
#include "CTrump.h"
#include "CStore.h"
#include "CStoreCusor.h"
#include "CStoreItemlist.h"



CScene_Second::CScene_Second()
	:m_iCount(0)
{

}

CScene_Second::~CScene_Second()
{

}

void CScene_Second::update()
{
	/*if (KEY_TAP(KEY::Q))
	{
		
		ChangeScene(SCENE_TYPE::THIRD);
		

	}*/

	if (KEY_TAP(KEY::Y))
	{

		//ChangeScene(SCENE_TYPE::FINAL);
		ChangeScene(SCENE_TYPE::FINAL_BOSS_CUT_SCENE);


	}

	if (KEY_TAP(KEY::O))
	{

		ChangeScene(SCENE_TYPE::STAGE_02);

	}

	CScene::update();
	

	
	//if (KEY_TAP(KEY::ENTER))
	//{
	//	//이벤트 매니저를 통해서 호출하고 그 다음 SceneMgr의 Change
	//	ChangeScene(SCENE_TYPE::TOOL);
	//}
}

void CScene_Second::Enter()
{
	//Player 추가 
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	if (CPlayerMgr::GenInst()->GetChangeSceneCount() == 0)
	{

		
		pObj->SetPos(Vec2(500.f, 1000.f)); // x좌표 500 y좌표 1000 이였음 //중간 7000,2500
		pObj->SetScale(Vec2(100.f, 100.f));
	}

	else if(CPlayerMgr::GenInst()->GetChangeSceneCount() == 1)
	{
		
		pObj->SetPos(Vec2(8008.f, 2550.f));
		pObj->SetScale(Vec2(100.f, 100.f));
	}
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


	CUI* pGeo = new CGeo;
	pGeo->SetName(L"GEO");
	pGeo->SetPos(Vec2(100.f, 200.f));
	AddObject(pGeo, GROUP_TYPE::UI);

	CUI* pSoulUI = new CSoulUI;
	pSoulUI->SetName(L"SOUL_UI");
	pSoulUI->SetPos(Vec2(100.f, 100.f));
	AddObject(pSoulUI, GROUP_TYPE::UI);

	//인벤토리 넣기 
	//==================================
	
	

	CUI* pInventory = new CInventory;
	pInventory->SetName(L"Inventory");
	pInventory->SetPos(Vec2(640.f, 360.f));
	AddObject(pInventory, GROUP_TYPE::UI);

	
	CUI* pClcok_item1 = new Cclock_Item;
	pClcok_item1->SetName(L"Clock_item1");
	AddObject(pClcok_item1, GROUP_TYPE::UI);

	/*CUI* pClcok_item2 = new Cclock_Item;
	pClcok_item2->SetName(L"Clock_item2");
	AddObject(pClcok_item2, GROUP_TYPE::UI);*/

	CUI* pWing_item1 = new CWing_item;
	pWing_item1->SetName(L"Wing_item1");
	AddObject(pWing_item1, GROUP_TYPE::UI);

	

	//맨밑에 아이템 커서 오브젝트 추가하면 
	//제일 위에 그려져서 ok입니다.

	CUI* pItem_Cusor = new CItemCusor;
	pItem_Cusor->SetName(L"Item_Cusor");
	AddObject(pItem_Cusor, GROUP_TYPE::UI);


	//===============================
	
	
	// Elder Bug Npc
	CObject* pElderBug = new CNpc;
	pElderBug->SetName(L"Elder_Bug_Npc");
	pElderBug->SetPos(Vec2(5496.f, 2500.f));
	AddObject(pElderBug, GROUP_TYPE::NPC);

	// Trump Npc
	CObject* pTrumpNpc = new CTrump;
	pTrumpNpc->SetName(L"Trump_Npc");
	pTrumpNpc->SetPos(Vec2(6500.f, 2500.f));
	AddObject(pTrumpNpc, GROUP_TYPE::NPC);
	
	CObject* pNpcReaction = new CNpcreaction;
	pNpcReaction->SetName(L"Elder_Bug_Npc");
	//pNpcReaction->SetPos(Vec2(5495.f, 2380.f));
	AddObject(pNpcReaction, GROUP_TYPE::NPC);

	//Npc 퀘스트 
	CUI* pQuestChatUI = new CElderBugQuest;
	pQuestChatUI->SetName(L"QuestChatUI");
	pQuestChatUI->SetPos(Vec2(640.f, 200.f));
	AddObject(pQuestChatUI, GROUP_TYPE::UI);

	
	

	//상점 부분 
	CStore* pStroeUI = new CStore;
	pStroeUI->SetName(L"StoreUI");
	pStroeUI->SetPos(Vec2(640.f, 300.f));
	AddObject(pStroeUI, GROUP_TYPE::UI);

	
	//상점 커서 부분 
	CStoreCusor* pStroeCusorUI = new CStoreCusor;
	pStroeCusorUI->SetName(L"StoreCusorUI");
	pStroeCusorUI->SetPos(Vec2(-100.f, -100.f));
	AddObject(pStroeCusorUI, GROUP_TYPE::UI);

	//상점 아이템 부분 
	CStoreItemlist* pStroeItemUI = new CStoreItemlist;
	pStroeItemUI->SetName(L"StroeItemlist");
	//pStroeCusorUI->SetPos(Vec2(-100.f, -100.f));
	AddObject(pStroeItemUI, GROUP_TYPE::UI);

	// 타일 설치 
	// 

	CObject* pSecond_Ground = new CGround;
	pSecond_Ground->SetName(L"Ground");
	pSecond_Ground->SetPos(Vec2(593.f, 1110.f));
	pSecond_Ground->SetScale(Vec2(300.f, 5.f));

	AddObject(pSecond_Ground, GROUP_TYPE::GROUND);

	CObject* pSecond_Ground2 = new CGround;
	pSecond_Ground2->SetName(L"Ground");
	pSecond_Ground2->SetPos(Vec2(3950.f, 2570.f));
	pSecond_Ground2->SetScale(Vec2(6623.f, 5.f));

	AddObject(pSecond_Ground2, GROUP_TYPE::GROUND);

	CObject* pSecond_Ground3 = new CGround;
	pSecond_Ground3->SetName(L"Ground");
	pSecond_Ground3->SetPos(Vec2(7392.f, 2617.f));
	pSecond_Ground3->SetScale(Vec2(165.f, 5.f));

	AddObject(pSecond_Ground3, GROUP_TYPE::GROUND);


	CObject* pSecond_Ground4 = new CGround;
	pSecond_Ground4->SetName(L"Ground");
	pSecond_Ground4->SetPos(Vec2(7571.f, 2662.f));
	pSecond_Ground4->SetScale(Vec2(175.f, 5.f));

	AddObject(pSecond_Ground4, GROUP_TYPE::GROUND);

	CObject* pSecond_Ground5 = new CGround;
	pSecond_Ground5->SetName(L"Ground");
	pSecond_Ground5->SetPos(Vec2(7818.f, 2700.f));
	pSecond_Ground5->SetScale(Vec2(265.f, 5.f));

	AddObject(pSecond_Ground5, GROUP_TYPE::GROUND);


	CObject* pSecond_Ground6 = new CGround;
	pSecond_Ground6->SetName(L"Ground");
	pSecond_Ground6->SetPos(Vec2(8008.f, 2664.f));
	pSecond_Ground6->SetScale(Vec2(158.f, 5.f));

	AddObject(pSecond_Ground6, GROUP_TYPE::GROUND);
	

	CObject* pTownBackGround = new CTown;
	pTownBackGround->SetName(L"Town_BackGround");
	pTownBackGround->SetPos(Vec2(0.f, 0.f));
	AddObject(pTownBackGround, GROUP_TYPE::BACKGROUND);

	// 타운 브금 깔아주기 
	CResMgr::GenInst()->LoadSound(L"BGM_TOWN", L"sound\\Dirtmouth 1.wav");
	CSound* pTownBgm = CResMgr::GenInst()->FindSound(L"BGM_TOWN");

	//pNewSound -> Play();
	//pNewSound -> SetPosition(50.f); // 백분률로 소리위치설정

	//pTownBgm->SetVolume(80.f);
	pTownBgm->PlayToBGM(true);

	// 플레이어를 기준으로 카메라가 움직임.
	CCamera::GenInst()->SetTarget(pObj);

	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::SKILLEFFECT, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::NPC);

	if(CPlayerMgr::GenInst()->GetChangeSceneCount() == 1)
	{
		CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
		CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::NPC);
	}
	

	CCamera::GenInst()->FadeIn(1.f);
	

	start();
}

void CScene_Second::Exit()
{
	CSound* pTownBgm = CResMgr::GenInst()->FindSound(L"BGM_TOWN");
	pTownBgm->Stop(true);

	CCamera::GenInst()->FadeIn(5.f);
	CCollisionMgr::GenInst()->Reset();
	DeleteAll();

	
	
}

void CScene_Second::CreateForce()
{

}


