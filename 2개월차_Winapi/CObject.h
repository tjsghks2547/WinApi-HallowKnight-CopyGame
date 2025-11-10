#pragma once

#include  "CCamera.h"


class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CObject
{
private: 
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale; 


	// Component
	CCollider*  m_pCollider;  // 필요없으면 nullptr 로 하면됨. 
	CAnimator*  m_pAnimator;
	CRigidBody* m_pRigidBody;
	CGravity*   m_pGravity; 

	bool		m_bAlive;    //자기 자신이 살아있는 오브젝트인지 아닌지를 체크하는 맴버변수
	bool		m_bCamAffect;


public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

public:
	virtual void start() {}; // Scene 이 시작되기 직전에 호출되는 함수
	virtual void update() = 0;
	virtual void render(HDC _dc);
	virtual void finalupdate(); // 오버라이딩을 막아주는것
	void component_render(HDC _dc);
	virtual CObject* Clone();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; } // 값을 얻어오기 위한 함수
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; } // 값을 얻어오기 위한 함수

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	
	void  SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider*  GetCollider()  { return m_pCollider; }
	CAnimator*  GetAnimator()  { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity* GetGravity()	   { return m_pGravity; }
	
	void CreateCollider();
	void CreateAnimator();
	void CreateAnimator(bool _CamAffect);
	void CreateRigidBody();
	void CreateGravity();

	

	bool IsDead() { return !m_bAlive; } // false면 true니깐. 죽었으면 true를 보냄
	
	bool GetCamAff() { return m_bCamAffect; }
	void SetCamAff(bool _bAff) { m_bCamAffect = _bAff; }


private:
	void  SetDead() { m_bAlive = false; }

public:
	friend class CEventMgr;  // SetDead를 이벤트매니저에서  사용하기 위해 


public:


	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};



//6월 21일 이후 내가 추가한 코드 



public:
	
	void CreateAnimator_using_vector();
	vector<CAnimator*> GetAnimator_using_vector() { return m_vecAnimator; }

protected: 

	vector<CAnimator*> m_vecAnimator; 
	
	//걷는 상태 추가 
	int   type_of_animation; // 여기서 어느것으로 걸을지 걸정하기

	
};

