#include "pch.h"
#include "CScene_Start.h"
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
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CKeyMgr.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CGround.h"
#include "CBackGround.h"

#include "CBeetle_New.h"

#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CHpBarUI.h"
#include "CFalseKnight.h"
#include "CGeo.h"
#include "CSoulUI.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CResMgr.h"
#include "CLiquidUI.h"
#include "CBlackFilter.h"
#include "CHUD.h"
#include "CPlayerMgr.h"
#include "CCrawlBug.h"
#include "CFlyBug.h"
#include "CDashBug.h"

#include "CGeoRock.h"


CScene_Start::CScene_Start()
	:m_bUseForce(false)
	,m_fForceRadius(500.f)
	,m_fCurRadius(0.f)
	,m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}


void CScene_Start::update()
{
	CScene::update();
	//if(KEY_TAP(KEY::ENTER))
	//{
	//	//이벤트 매니저를 통해서 호출하고 그 다음 SceneMgr의 Change
	//	ChangeScene(SCENE_TYPE::TOOL);
	//}

	if(CPlayerMgr::GenInst()->GetCurPlayerPos().x > 10860.f
		&& CPlayerMgr::GenInst()->GetCurPlayerPos().y == 2162.5f)
	{
		ChangeScene(SCENE_TYPE::TOWN);
	}

	//if(KEY_TAP(KEY::LBTN))
	//{
	//	Vec2 vLookAt = CCamera::GenInst()->GetRealPos(MOUSE_POS);
	//	CCamera::GenInst()->SetLookAt(vLookAt);
	//}

	//Vec2 CameraPos = Vec2(GetPlayer()->GetPos().x, GetPlayer()->GetPos().y - 300.f);
	//
	//CCamera::GenInst()->SetLookAt(CameraPos);

}



void CScene_Start::Enter() // 오브젝트 추가하는 코드 구간
{
	//Player 추가 
	CObject* pObj = new CPlayer; 
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(2394.f,500.f)); // x좌표 2394 y좌표 500, 5000 이였음 //보스룸 7700,2200
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

	
	

	

	/*CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));
	AddObject(pPanelUI, GROUP_TYPE::UI);*/


	

	
	// 광석 배치 
	CObject* pGeoRock = new CGeoRock;
	pGeoRock->SetName(L"GEO_ROCK");
	pGeoRock->SetPos(Vec2(4037.f, 3369.f));
	AddObject(pGeoRock, GROUP_TYPE::MONSTER);

	CObject* pGeoRock1 = new CGeoRock;
	pGeoRock1->SetName(L"GEO_ROCK");
	pGeoRock1->SetPos(Vec2(3461.f, 2438.f));
	AddObject(pGeoRock1, GROUP_TYPE::MONSTER);


	////7월 2일 몬스터 배치

	CObject* pCrawlMonster1 = new CCrawlBug;
	pCrawlMonster1->SetName(L"Crawl");
	pCrawlMonster1->SetPos(Vec2(4300.f, 5130.f));
	AddObject(pCrawlMonster1, GROUP_TYPE::MONSTER);

	CObject* pCrawlMonster2 = new CCrawlBug;
	pCrawlMonster2->SetName(L"Crawl");
	pCrawlMonster2->SetPos(Vec2(5540.f, 5122.f));
	AddObject(pCrawlMonster2, GROUP_TYPE::MONSTER);


	CObject* pFlyMonster1 = new CFlyBug;
	pFlyMonster1->SetName(L"Fly_Bug");
	pFlyMonster1->SetPos(Vec2(8311.f, 4685.f));
	AddObject(pFlyMonster1, GROUP_TYPE::MONSTER);

	CObject* pFlyMonster2 = new CFlyBug;
	pFlyMonster2->SetName(L"Fly_Bug");
	pFlyMonster2->SetPos(Vec2(8824.f, 4550.f));
	AddObject(pFlyMonster2, GROUP_TYPE::MONSTER);

	CObject* pFlyMonster3 = new CFlyBug;
	pFlyMonster3->SetName(L"Fly_Bug");
	pFlyMonster3->SetPos(Vec2(5329.f, 3287.f));
	AddObject(pFlyMonster3, GROUP_TYPE::MONSTER);

	CObject* pFlyMonster4 = new CFlyBug;
	pFlyMonster4->SetName(L"Fly_Bug");
	pFlyMonster4->SetPos(Vec2(5089.f, 3625.f));
	AddObject(pFlyMonster4, GROUP_TYPE::MONSTER);


	CObject* pDashBugMonster1 = new CDashBug;
	pDashBugMonster1->SetName(L"Dash_Bug");
	pDashBugMonster1->SetPos(Vec2(7334.f, 5122.f));
	AddObject(pDashBugMonster1, GROUP_TYPE::MONSTER);

	CObject* pDashBugMonster2 = new CDashBug;
	pDashBugMonster2->SetName(L"Dash_Bug");
	pDashBugMonster2->SetPos(Vec2(5084.f, 4215.f));
	AddObject(pDashBugMonster2, GROUP_TYPE::MONSTER);


	CObject* pBeetleMonster1 = new CBeetle_New; 
	pBeetleMonster1->SetName(L"Beetle");
	pBeetleMonster1->SetPos(Vec2(8587.f, 5463.f));
	AddObject(pBeetleMonster1, GROUP_TYPE::MONSTER);

	CObject* pMonsterpBeetleMonster2 = new CBeetle_New;
	pMonsterpBeetleMonster2->SetName(L"Beetle");
	pMonsterpBeetleMonster2->SetPos(Vec2(6404.f, 3987.f));

	AddObject(pMonsterpBeetleMonster2, GROUP_TYPE::MONSTER);


	

	//CObject* pMonster3 = new CBeetle_New;
	//pMonster3->SetName(L"Beetle");
	//pMonster3->SetPos(Vec2(8903.f, 5440.f));

	//AddObject(pMonster3, GROUP_TYPE::MONSTER);


	//보스 몬스터 
	
	CObject* pFalseKnight = new CFalseKnight;
	pFalseKnight->SetName(L"FalseKnight");
	pFalseKnight->SetPos(Vec2(9152.f, 1900.f)); //2062

	AddObject(pFalseKnight, GROUP_TYPE::MONSTER);


	//몬스터 배치
	//Vec2 vResolution = CCore::GenInst()->GetResolution();
	//CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL,vResolution/2.f -Vec2(0.f,300.f));

	//AddObject(pMon, GROUP_TYPE::MONSTER);
	

	//CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL,Vec2(2300.f, 5100.f));
	//CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(2300.f, 5100.f));
	//AddObject(pMon, GROUP_TYPE::MONSTER);








	//땅 물체 배치 
	CObject* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(4020.f, 5165.f));
	pGround->SetScale(Vec2(5060.f, 5.f));
	AddObject(pGround, GROUP_TYPE::GROUND);

	
	CObject* pGround6 = new CGround;
	pGround6->SetName(L"Ground");
	pGround6->SetPos(Vec2(6800.f, 5230.f));
	pGround6->SetScale(Vec2(5.f, 80.f));
	AddObject(pGround6, GROUP_TYPE::GROUND);

	CObject* pGround2 = new CGround;
	pGround2->SetName(L"Ground");
	pGround2->SetPos(Vec2(6668.f, 5270.f));
	pGround2->SetScale(Vec2(243.f, 5.f));
	AddObject(pGround2, GROUP_TYPE::GROUND);

	CObject* pGround3 = new CGround;
	pGround3->SetName(L"Ground");
	pGround3->SetPos(Vec2(7294.f, 5165.f));
	pGround3->SetScale(Vec2(1000.f, 5.f));
	AddObject(pGround3, GROUP_TYPE::GROUND);


	//세로 
	CObject* pGround4 = new CGround;
	pGround4->SetName(L"Ground");
	pGround4->SetPos(Vec2(7805.f, 5300.f));
	pGround4->SetScale(Vec2(5.f, 250.f));
	AddObject(pGround4, GROUP_TYPE::GROUND);


	CObject* pGround5 = new CGround;
	pGround5->SetName(L"Ground");
	pGround5->SetPos(Vec2(7940.f, 5400.f));
	pGround5->SetScale(Vec2(300.f, 5.f));
	AddObject(pGround5, GROUP_TYPE::GROUND);


	//박스 
	CObject* pGround7 = new CGround;
	pGround7->SetName(L"Ground");
	pGround7->SetPos(Vec2(8141.f, 5153.f)); // 원래 Y좌표 5113 이였음
	pGround7->SetScale(Vec2(226.f, 100.f));
	AddObject(pGround7, GROUP_TYPE::GROUND);


	//박스
	CObject* pGround8 = new CGround;
	pGround8->SetName(L"Ground");
	pGround8->SetPos(Vec2(8470.f, 5035.f)); 
	pGround8->SetScale(Vec2(113.f, 100.f));
	AddObject(pGround8, GROUP_TYPE::GROUND);

	//박스
	CObject* pGround9 = new CGround;
	pGround9->SetName(L"Ground");
	pGround9->SetPos(Vec2(8690.f, 4784.f));
	pGround9->SetScale(Vec2(135.f, 50.f));
	AddObject(pGround9, GROUP_TYPE::GROUND);
	

	//가로
	CObject* pGround10 = new CGround;
	pGround10->SetName(L"Ground");
	pGround10->SetPos(Vec2(8553.f, 5506.f));
	pGround10->SetScale(Vec2(947.f, 5.f));
	AddObject(pGround10, GROUP_TYPE::GROUND);


	//박스
	CObject* pGround11 = new CGround;
	pGround11->SetName(L"Ground");
	pGround11->SetPos(Vec2(8797.f, 5294.f));
	pGround11->SetScale(Vec2(114.f, 120.f));
	AddObject(pGround11, GROUP_TYPE::GROUND);


	CObject* pGround12 = new CGround;
	pGround12->SetName(L"Ground");
	pGround12->SetPos(Vec2(8007.f, 4564.f));
	pGround12->SetScale(Vec2(100.f, 5.f));
	AddObject(pGround12, GROUP_TYPE::GROUND);

	CObject* pGround13 = new CGround;
	pGround13->SetName(L"Ground");
	pGround13->SetPos(Vec2(8386.f, 4516.f));
	pGround13->SetScale(Vec2(150.f, 5.f));
	AddObject(pGround13, GROUP_TYPE::GROUND);


	CObject* pGround14 = new CGround;
	pGround14->SetName(L"Ground");
	pGround14->SetPos(Vec2(7600.f, 4481.f));
	pGround14->SetScale(Vec2(270.f, 5.f));
	AddObject(pGround14, GROUP_TYPE::GROUND);

	CObject* pGround15 = new CGround;
	pGround15->SetName(L"Ground");
	pGround15->SetPos(Vec2(7369.f, 4255.f));
	pGround15->SetScale(Vec2(165.f, 5.f));
	AddObject(pGround15, GROUP_TYPE::GROUND);

	CObject* pGround16 = new CGround;
	pGround16->SetName(L"Ground");
	pGround16->SetPos(Vec2(6504.f, 4030.f));
	pGround16->SetScale(Vec2(1570.f, 5.f));
	AddObject(pGround16, GROUP_TYPE::GROUND);


	//가로
	CObject* pGround17 = new CGround;
	pGround17->SetName(L"Ground");
	pGround17->SetPos(Vec2(5150.f, 4258.f));
	pGround17->SetScale(Vec2(1200.f, 5.f));
	AddObject(pGround17, GROUP_TYPE::GROUND);

	CObject* pGround18 = new CGround;
	pGround18->SetName(L"Ground");
	pGround18->SetPos(Vec2(4150.f, 4324.f));
	pGround18->SetScale(Vec2(672.f, 5.f));
	AddObject(pGround18, GROUP_TYPE::GROUND);


	CObject* pGround19 = new CGround;
	pGround19->SetName(L"Ground");
	pGround19->SetPos(Vec2(4672.f, 4041.f));
	pGround19->SetScale(Vec2(150.f, 5.f));
	AddObject(pGround19, GROUP_TYPE::GROUND);


	CObject* pGround20 = new CGround;
	pGround20->SetName(L"Ground");
	pGround20->SetPos(Vec2(4946.f, 3819.f));
	pGround20->SetScale(Vec2(110.f, 5.f));
	AddObject(pGround20, GROUP_TYPE::GROUND);

	CObject* pGround21 = new CGround;
	pGround21->SetName(L"Ground");
	pGround21->SetPos(Vec2(5271.f, 3668.f));
	pGround21->SetScale(Vec2(120.f, 5.f));
	AddObject(pGround21, GROUP_TYPE::GROUND);

	CObject* pGround22 = new CGround;
	pGround22->SetName(L"Ground");
	pGround22->SetPos(Vec2(5512.f, 3488.f));
	pGround22->SetScale(Vec2(140.f, 5.f));
	AddObject(pGround22, GROUP_TYPE::GROUND);

	//세로 테스트 ( beetle 벽이랑 충돌된다 대박) 
	CObject* pGround23 = new CGround;
	pGround23->SetName(L"Ground");
	pGround23->SetPos(Vec2(8072.f, 5483.f));
	pGround23->SetScale(Vec2(5.f, 100.f));
	AddObject(pGround23, GROUP_TYPE::GROUND);


	CObject* pGround24 = new CGround;
	pGround24->SetName(L"Ground");
	pGround24->SetPos(Vec2(5110.f, 3330.f));
	pGround24->SetScale(Vec2(224.f, 5.f));
	AddObject(pGround24, GROUP_TYPE::GROUND);


	CObject* pGround25 = new CGround;
	pGround25->SetName(L"Ground");
	pGround25->SetPos(Vec2(4786.f, 3112.f));
	pGround25->SetScale(Vec2(221.f, 5.f));
	AddObject(pGround25, GROUP_TYPE::GROUND);

	CObject* pGround26 = new CGround;
	pGround26->SetName(L"Ground");
	pGround26->SetPos(Vec2(4593.f, 2996.f));
	pGround26->SetScale(Vec2(151.f, 5.f));
	AddObject(pGround26, GROUP_TYPE::GROUND);

	CObject* pGround27 = new CGround;
	pGround27->SetName(L"Ground");
	pGround27->SetPos(Vec2(4344.f, 2826.f));
	pGround27->SetScale(Vec2(262.f, 5.f));
	AddObject(pGround27, GROUP_TYPE::GROUND);

	CObject* pGround28 = new CGround;
	pGround28->SetName(L"Ground");
	pGround28->SetPos(Vec2(4152.f, 2594.f));
	pGround28->SetScale(Vec2(110.f, 5.f));
	AddObject(pGround28, GROUP_TYPE::GROUND);

	CObject* pGround29 = new CGround;
	pGround29->SetName(L"Ground");
	pGround29->SetPos(Vec2(3948.f, 2415.f));
	pGround29->SetScale(Vec2(283.f, 5.f));
	AddObject(pGround29, GROUP_TYPE::GROUND);

	CObject* pGround30 = new CGround;
	pGround30->SetName(L"Ground");
	pGround30->SetPos(Vec2(3452.f, 2481.f));
	pGround30->SetScale(Vec2(640.f, 5.f));
	AddObject(pGround30, GROUP_TYPE::GROUND);

	CObject* pGround31 = new CGround;
	pGround31->SetName(L"Ground");
	pGround31->SetPos(Vec2(4820.f, 2363.f));
	pGround31->SetScale(Vec2(615.f, 5.f));
	AddObject(pGround31, GROUP_TYPE::GROUND);

	CObject* pGround32 = new CGround;
	pGround32->SetName(L"Ground");
	pGround32->SetPos(Vec2(5331.f, 2256.f));
	pGround32->SetScale(Vec2(380.f, 5.f));
	AddObject(pGround32, GROUP_TYPE::GROUND);

	CObject* pGround33 = new CGround;
	pGround33->SetName(L"Ground");
	pGround33->SetPos(Vec2(8323.f, 2205.f));
	pGround33->SetScale(Vec2(5476.f, 5.f));
	AddObject(pGround33, GROUP_TYPE::GROUND);

	CObject* pGround34 = new CGround;
	pGround34->SetName(L"Ground");
	pGround34->SetPos(Vec2(3568.f, 4328.f));
	pGround34->SetScale(Vec2(407.f, 5.f));
	AddObject(pGround34, GROUP_TYPE::GROUND);

	CObject* pGround35 = new CGround;
	pGround35->SetName(L"Ground");
	pGround35->SetPos(Vec2(3592.f, 4114.f));
	pGround35->SetScale(Vec2(115.f, 5.f));
	AddObject(pGround35, GROUP_TYPE::GROUND);

	CObject* pGround36 = new CGround;
	pGround36->SetName(L"Ground");
	pGround36->SetPos(Vec2(3991.f, 3926.f));
	pGround36->SetScale(Vec2(176.f, 5.f));
	AddObject(pGround36, GROUP_TYPE::GROUND);

	CObject* pGround37 = new CGround;
	pGround37->SetName(L"Ground");
	pGround37->SetPos(Vec2(3698.f, 3671.f));
	pGround37->SetScale(Vec2(160.f, 5.f));
	AddObject(pGround37, GROUP_TYPE::GROUND);

	CObject* pGround38 = new CGround;
	pGround38->SetName(L"Ground");
	pGround38->SetPos(Vec2(4009.f, 3412.f));
	pGround38->SetScale(Vec2(211.f, 5.f));
	AddObject(pGround38, GROUP_TYPE::GROUND);



	
	CObject* pBackGround = new CBackGround; 
	pBackGround->SetName(L"BackGround");
	pBackGround->SetPos(Vec2(0.f, 0.f));

	AddObject(pBackGround, GROUP_TYPE::BACKGROUND);


	// 플레이어를 기준으로 카메라가 움직임.
	CCamera::GenInst()->SetTarget(pObj);
	

	// 타일 로딩 
	//LoadTile(L"Tile\\Start.tile");

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크를 하겠다라고 선언  
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::SKILLEFFECT, GROUP_TYPE::MONSTER);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::PLAYER);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::SKILLEFFECT, GROUP_TYPE::GROUND);
	CCollisionMgr::GenInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::GROUND);

	//Camera Look 지정 
	//Vec2 vResolution = CCore::GenInst()->GetResolution();
	//CCamera::GenInst()->SetLookAt(Vec2(-1200.f, 100.f)); // 해상도 절반 위치 

	//Camera 효과 지정 
	CCamera::GenInst()->FadeOut(1.f);
	CCamera::GenInst()->FadeIn(1.f);


	CResMgr::GenInst()->LoadSound(L"BGM_01", L"sound\\S19_Crossroads_Bass.wav");
	CSound* pNewSound = CResMgr::GenInst()->FindSound(L"BGM_01");
	
	//pNewSound -> Play();
	//pNewSound -> SetPosition(50.f); // 백분률로 소리위치설정
	pNewSound->SetVolume(80.f);
	pNewSound->PlayToBGM(true);
	//	pNewSound -> SetVolume(60.f);
	
	start();
}

void CScene_Start::Exit()
{

	//변경후 삭제를 위핸 함수 (06/15 추가) 
	DeleteAll();


	//다른 신으로 넘어갈 때 호출되는 함수
	//여기서는 충돌지정을 해제시켜야 다른 장면에서 충돌 지정 그룹이 달라지므로
	CCollisionMgr::GenInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GenInst()->GetRealPos(MOUSE_POS);
}
