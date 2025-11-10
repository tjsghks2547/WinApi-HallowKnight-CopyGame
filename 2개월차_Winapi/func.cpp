#include "pch.h"
#include "func.h"

#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	
	tEvent evn = { };

	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj; // 상황에따라 32비트로 하면 _pObj는 4바이트로 64비트로 하면 8바이트로 바뀐다.
		//현재 윈도우는 64비트 기준으로 되므로 지금은 unsinged __int64 자료형을 갖고 32비트면 unsigned int형을 갖는다.

	evn.wParam = (DWORD_PTR)_eGroup;


	CEventMgr::GenInst()->AddEvent(evn);

}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GenInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GenInst()->AddEvent(evn);

}

void ChangeAIState(AI* _pAI, MON_STATE _eNextState)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)_pAI;
	evn.wParam = (DWORD_PTR)_eNextState;

	CEventMgr::GenInst()->AddEvent(evn);
}
