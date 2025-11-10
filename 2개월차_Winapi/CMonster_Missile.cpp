#include "pch.h"
#include "CMonster_Missile.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CResMgr.h"

CMonster_Missile::CMonster_Missile()
	:m_fTheta(PI / 2.F)
	,m_vDir(Vec2(1.f, 1.f))
	,m_pTex(nullptr)
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"MonsterMissile", L"texture\\Monster_bullet1_1.bmp");
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CMonster_Missile::~CMonster_Missile()
{

}


void CMonster_Missile::update()
{
	Vec2 vPos = GetPos();

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;

	SetPos(vPos);

}

void CMonster_Missile::render(HDC _dc)
{

	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();

	//Ellipse(_dc,
	//	(int)(vPos.x - vScale.x / 2.f),  // 왼쪽 상단 x
	//	(int)(vPos.y - vScale.y / 2.f),  // 왼쪽 상단 y
	//	(int)(vPos.x + vScale.x / 2.f),  // 오른쪽 하단 x
	//	(int)(vPos.y + vScale.y / 2.f)); // 오른쪽 하단 y

	TransparentBlt(_dc
		, (int)((vPos.x - (float)(iWidth / 2)))
		, (int)((vPos.y - (float)(iHeight / 2)))
		, iWidth
		, iHeight
		, m_pTex->GetDc()
		, 0, 0, iWidth, iHeight, RGB(255, 255, 255));


	// 컴포넌트 (충돌체, etc ..)가 있는 경우 출력.
	//component_render(_dc);

}

void CMonster_Missile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOhterObj = _pOther->GetObj();
	if(pOhterObj->GetName() == L"Player")
	{
		DeleteObject(this);
	}
}


