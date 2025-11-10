#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CScene_Tool.h"
#include "CEventMgr.h"
#include "CScene_Second.h"
#include "CScene_Thrid.h"
#include "CScene_Game_Start.h"
#include "CScene_FinalBoss.h"
#include "CScene_Stage2.h"
#include "CScene_End.h"
#include "CSceneFinalbossVideo.h"




CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// 씬 전부삭제
	for (UINT i = 0 ; i<(UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::GAME_START] = new CScene_Game_Start();
	m_arrScene[(UINT)SCENE_TYPE::GAME_START]->SetName(L"Game_Start");

	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start(); //CScene 의 포인터 m_arrScene
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOWN] = new CScene_Second();
	m_arrScene[(UINT)SCENE_TYPE::TOWN]->SetName(L"Second Scene");

	m_arrScene[(UINT)SCENE_TYPE::THIRD] = new CScene_Thrid();
	m_arrScene[(UINT)SCENE_TYPE::THIRD]->SetName(L"Third Scene");

	m_arrScene[(UINT)SCENE_TYPE::FINAL] = new CScene_FinalBoss();
	m_arrScene[(UINT)SCENE_TYPE::FINAL]->SetName(L"Final_Boss_Scene");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage2();
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02]->SetName(L"Stage2");

	m_arrScene[(UINT)SCENE_TYPE::END_SCEEN] = new CScene_End();
	m_arrScene[(UINT)SCENE_TYPE::END_SCEEN]->SetName(L"End");

	m_arrScene[(UINT)SCENE_TYPE::FINAL_BOSS_CUT_SCENE] = new CSceneFinalbossVideo();
	m_arrScene[(UINT)SCENE_TYPE::FINAL_BOSS_CUT_SCENE]->SetName(L"FINAL_BOSS_CUT_SCENE");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool();
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");


	
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01();
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02();

	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TOWN];
	m_pCurScene->Enter();

}

void CSceneMgr::update()
{
	// 여기다가 m_pCurScene값을 변경하면 화면 변환에 따른 그 화면에 대한
	// 오브젝트애들이 생성될듯함. 


	m_pCurScene->update();
	
	m_pCurScene->finalupdate();

}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	//이벤트 매니저에서 처리후 이거 발동 
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	m_pCurScene->Enter();

}

