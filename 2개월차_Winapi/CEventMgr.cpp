#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUIMgr.h"

#include "AI.h"
#include "CState.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// ================================================
	//이전 프레임에서 등로해둔 Dead Object들을 삭제한다.
	// ================================================

	for(size_t i =0; i<m_vecDead.size(); ++i)
	{
		
		
		delete m_vecDead[i];
		
		
	}
	m_vecDead.clear();


	// ============
	// Event 처리 
	// ============

	for(size_t i = 0; i< m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear(); //이거 안하면 미사일 한번에 몇백개씩 생김

}

void CEventMgr::Excute(const tEvent& _eve)
{

	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{	// lParam : Object의 주소 
		// wParam : Group TYPE을 의미  

		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;


		CSceneMgr::GenInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{	// lParam : Object의 주소 
		// Object 를 Dead 상태로 변경하고
		// 삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();

		m_vecDead.push_back(pDeadObj);

	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		//SCENE_CHANGE가 되면 나머지 이벤트들은 있더라도 처리하지 않는
		// 방법을 생각해야함 아니면 같은프레임내에서 
		// 신체인지 후에 오브젝트 생성 및 다른 AI_state 변경이 발생하면
		// 오류가 발생하므로 이 부분에 대해 고민해보자 
		
		// lparam : Next Scene Type
		// Scene 변경 
		CSceneMgr::GenInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		// 포커스 UI 해제 ( 이전 Scene 의 UI를 가리키고 있기 때문) ) 
		CUIMgr::GenInst()->SetFocusedUI(nullptr);
	}
		break;

	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		// lparam : AI
		// wParam : Next Type 
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;

		pAI->ChangeState(eNextState);
	}
		break;
	}
}
