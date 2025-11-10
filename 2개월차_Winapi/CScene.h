#pragma once

#include "CMonFactory.h"

class CObject; // 헤더가 헤더를 참조하는걸 방지하기 위해 단, 실체타입에 대한 구체적인 정보가 없음
// 그래서 포인터 타입만 사용 가능



class CScene
{

private:
	//오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	vector<CObject*>	 m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				 m_strName;  // Scene 이름 

	UINT				 m_iTileX; // 타일 가로 개수
	UINT				 m_iTileY; // 타일 세로 개수 

	CObject*			m_pPlayer; // Player  

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


	UINT  GetTileX() { return m_iTileX; }
	UINT  GetTileY() { return m_iTileY; }

	//플레이어 포인터 가져오기
	CObject* GetPlayer() { return m_pPlayer; }

	virtual void start();
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void render_tile(HDC _dc);

	virtual void Enter() = 0 ; // 해당 Scene 에 진입 시 호출
	virtual void Exit() = 0; // 해당 Scene 을 탈출 시 호출

	
public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType){m_arrObj[(UINT)_eType].push_back(_pObj);}
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType){return m_arrObj[(UINT)_eType];}
	void RegisterPlayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }


	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	//타일을 위한 함수
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI];}


public:
	CScene();
	virtual ~CScene(); // 부모 클래스에서 소멸자에 항상 virtual 넣어주는거 잊지말기
	// 왜냐하면 소멸자의 주기가 부모 생성-> 자식 생성 -> 자식 소멸 -> 부모 소멸 이므로.
	// 안만들면 부모만 되므로 부모생성->자식생성->부모소멸 하고 끝남. 

};

