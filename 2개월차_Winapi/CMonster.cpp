#include "pch.h"
#include "CMonster.h"
#include "AI.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CMonster_Missile.h"
#include "CResMgr.h"
#include "CTexture.h"

//6월 21일 이후 작성한 코드 ( 카메라)
#include "CCamera.h"


CMonster::CMonster()
	:m_tInfo{}

{

	m_pTex = CResMgr::GenInst()->LoadTexture(L"MonsterTex", L"texture\\player3.bmp");
	//dwTime = GetTickCount();
	CreateCollider();
	GetCollider()->SetScale(Vec2(55.f, 55.f));
	//DirChange = { -1.f,0.f };
}

CMonster::~CMonster()
{
	if(nullptr != m_pAI)
	{
		delete m_pAI;
	}
}


void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::update()
{
	if (m_pAI != nullptr)
	{
		m_pAI->update();
	}
}

void CMonster::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	vPos = CCamera::GenInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)((vPos.x - (float)(iWidth / 2)))
		, (int)((vPos.y - (float)(iHeight / 2)))
		, iWidth
		, iHeight
		, m_pTex->GetDc()
		, 0, 0, iWidth, iHeight, RGB(153,255,255));

	// 컴포넌트 (충돌체, etc ..)가 있는 경우 출력.
	component_render(_dc);

}


void CMonster::OnCollision(CCollider* _pOther)
{
}

void CMonster::OnCollisionEnter(CCollider* _pOther) //매개변수는 나랑 충돌한 오브젝트의 주소
{
	CObject* pOtherObj = _pOther->GetObj();
	if(pOtherObj->GetName() == L"Missile_Player")
	{
		//m_iHP -= 1;
		DeleteObject(this);
		
	}

}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
}

void CMonster::CreateMissile()
{
	//몬스터 좌표 가져오기
	Vec2 vMissilePos = GetPos();
	 
	//6월 16일 16시 생각
	//turn bullte 저거 int해서 상태 1,2,3, 주는게 편할듯 2개니깐 진행이 안되네

	CMonster_Missile* p_Monster_missile = new CMonster_Missile;
	p_Monster_missile->SetName(L"Monster_Missile");
	p_Monster_missile->SetPos(vMissilePos);
	p_Monster_missile->SetScale(Vec2(25.f, 25.f));


	//if (turn_bullet == 1 && DirChange.x > -1.f && DirChange.y < 0.35f)
	//{
	//	turn_bullet = 2;
	//	DirChange = { -1.f,0.f };

	//}

	//if (turn_bullet == 1 && DirChange.x > -1.f && DirChange.y >= 0.35f)
	//{

	//	DirChange.x -= 0.1f;
	//	DirChange.y -= 0.05f;
	//	p_Monster_missile->SetDir(Vec2(DirChange.x, DirChange.y));
	//	CreateObject(p_Monster_missile, GROUP_TYPE::PROJ_MONSTER);
	//	
	//	//DirChange = { -1.0f,0.f };
	//}
	//
	//if (DirChange.x <= 1.f && DirChange.y <= 1.f && turn_bullet ==0 )
	//{
	//	p_Monster_missile->SetDir(Vec2(DirChange.x, DirChange.y));
	//	DirChange.x += 0.1f;
	//	DirChange.y += 0.05f;
	//	CreateObject(p_Monster_missile, GROUP_TYPE::PROJ_MONSTER);
	//}

	//if (DirChange.x > 1.f && DirChange.y > 1.f)
	//{	
	//	turn_bullet = 1;
	//}

	//// -1.f,0.f
	
	//플레이어의 onCollisionEnter에 이거 써주기

}
//
//void CMonster::CreateMissile2()
//{
//	//몬스터 좌표 가져오기
//	Vec2 vMissilePos = GetPos();
//
//
//	CMonster_Missile* p_Monster_missile = new CMonster_Missile;
//	p_Monster_missile->SetName(L"Monster_Missile");
//	p_Monster_missile->SetPos(vMissilePos);
//	p_Monster_missile->SetScale(Vec2(25.f, 25.f));
//	p_Monster_missile->SetDir(Vec2(1.f, 1.f));
//
//	CreateObject(p_Monster_missile, GROUP_TYPE::PROJ_MONSTER);
//
//	//플레이어의 onCollisionEnter에 이거 써주기
//
//}
//
//void CMonster::CreateMissile3()
//{
//	//몬스터 좌표 가져오기
//	Vec2 vMissilePos = GetPos();
//
//
//	CMonster_Missile* p_Monster_missile = new CMonster_Missile;
//	p_Monster_missile->SetName(L"Monster_Missile");
//	p_Monster_missile->SetPos(vMissilePos);
//	p_Monster_missile->SetScale(Vec2(25.f, 25.f));
//	p_Monster_missile->SetDir(Vec2(-1.f, 1.f));
//
//	CreateObject(p_Monster_missile, GROUP_TYPE::PROJ_MONSTER);
//
//	//플레이어의 onCollisionEnter에 이거 써주기
//
//}
