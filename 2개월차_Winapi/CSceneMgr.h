#pragma once


class CScene;  //전방 선언


class CSceneMgr
{

	SINGLE(CSceneMgr);

private:

	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; // 모든 장면을 관리하기 위해서 선언
	CScene* m_pCurScene;                       // 현재 씬


public:
	void init();
	void update();
	void render(HDC _dc);



public:
	CScene* GetCurScene() { return m_pCurScene; }


private:

	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;

	
};

