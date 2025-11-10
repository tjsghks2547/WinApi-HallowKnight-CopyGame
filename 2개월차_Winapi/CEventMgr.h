#pragma once

struct tEvent
{
	EVENT_TYPE	eEven; 
	DWORD_PTR	lParam; // 어떤 오브젝트의 주소값.
	DWORD_PTR   wParam; // 오브젝트 타입
};

class CEventMgr
{
	SINGLE(CEventMgr);

private:

	vector<tEvent> m_vecEvent; 

	//삭제 오브젝트 관리
	
	vector<CObject*> m_vecDead; 


public:

	void update(); 

private:
	void Excute(const tEvent& _eve);

public:

	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }




};

