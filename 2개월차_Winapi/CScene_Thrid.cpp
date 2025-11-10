#include "pch.h"
#include "CScene_Thrid.h"
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
#include "CNpc.h"
#include "CNpcreaction.h"
#include "CElderBugQuest.h"

#include "CInventory.h"
#include "CScene_Tool.h"
#include "Cclock_Item.h"
#include "CItemCusor.h"
#include "CWing_item.h"
#include "CHornet.h"


CScene_Thrid::CScene_Thrid()
{
}

CScene_Thrid::~CScene_Thrid()
{
}


void CScene_Thrid::update()
{
	CScene::update();
	//CCamera::GenInst()->SetLookAt(Vec2(640.f, 360.f));

	if (KEY_TAP(KEY::Q))
	{
		CPlayerMgr::GenInst()->SetChangeSceneCount(1);
		ChangeScene(SCENE_TYPE::TOWN);
	}

}

void CScene_Thrid::Enter()
{
	//Player 추가 
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(100.f, 650.f)); // x좌표 500 y좌표 1000 이였음 //보스룸 7700,2200
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


	CObject* pHornet = new CHornet;
	pHornet->SetName(L"Hornet");
	pHornet->SetPos(Vec2(700.f, 625.f));
	AddObject(pHornet, GROUP_TYPE::MONSTER);

	CObject* pThird_Ground = new CGround;
	pThird_Ground->SetName(L"Ground");
	pThird_Ground->SetPos(Vec2(625.f, 678.f));
	pThird_Ground->SetScale(Vec2(1140.f, 5.f));
	AddObject(pThird_Ground, GROUP_TYPE::GROUND);

	// 세로벽 
	CObject* pThird_Ground1 = new CGround;
	pThird_Ground1->SetName(L"Ground");
	pThird_Ground1->SetPos(Vec2(50.f, 380.f));
	pThird_Ground1->SetScale(Vec2(5.f, 760.f));
	AddObject(pThird_Ground1, GROUP_TYPE::GROUND);

	CObject* pThird_Ground2 = new CGround;
	pThird_Ground2->SetName(L"Ground");
	pThird_Ground2->SetPos(Vec2(1159.f, 530.f));
	pThird_Ground2->SetScale(Vec2(5.f, 380.f));
	AddObject(pThird_Ground2, GROUP_TYPE::GROUND);

	CObject* pThird_Ground3 = new CGround;
	pThird_Ground3->SetName(L"Ground");
	pThird_Ground3->SetPos(Vec2(1259.f, 340.f));
	pThird_Ground3->SetScale(Vec2(200.f, 5.f));
	AddObject(pThird_Ground3, GROUP_TYPE::GROUND);



	CObject* pBossBackGround = new CHornetBossRoom;
	pBossBackGround->SetName(L"Hornet_Boss_Room");
	AddObject(pBossBackGround, GROUP_TYPE::BACKGROUND);

	//배경음 
	CResMgr::GenInst()->LoadSound(L"HORNET_BGM", L"sound\\Hornet\\S45 HORNET-110.wav");
	CSound* pHornetBgm = CResMgr::GenInst()->FindSound(L"HORNET_BGM");
	
	pHornetBgm->SetVolume(85.f);
	pHornetBgm->PlayToBGM(true);

	//카메라 설정 
	CCamera::GenInst()->SetTarget(pObj);
	

	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::SKILLEFFECT, GROUP_TYPE::MONSTER);
	

	start(); // 벽 scale 값 넣는 부분 
}

void CScene_Thrid::Exit()
{
	DeleteAll();
}

