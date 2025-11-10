#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CResMgr.h"




CMissile::CMissile()
	:m_fTheta(PI/2.F)
	,m_vDir(Vec2(1.f,1.f))
	,m_pTex(nullptr)
{

	m_pTex = CResMgr::GenInst()->LoadTexture(L"Player_Bullet_Tex", L"texture\\bullet1_1.bmp");
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));

}

CMissile::~CMissile()
{
}


void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;

	SetPos(vPos);

}

void CMissile::render(HDC _dc) // 총알 모양 구현 
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();
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
		, 0, 0, iWidth, iHeight, RGB(0, 255, 0));

	// 컴포넌트 (충돌체, etc ..)가 있는 경우 출력.
	//component_render(_dc);
}

//void CMissile::OnCollision(CCollider* _pOther)
//{
//
//}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if(pOtherObj->GetName() == L"Monster") // 여기 몬스터 이름 같아서 몬스터 2마리 동시에 맞으면 총알 삭제 2번 되서 문제 생김 실제 총알은 1개인데
	{
		DeleteObject(this);
	}
}

//void CMissile::OnCollisionExit(CCollider* _pOther)
//{
//
//}
