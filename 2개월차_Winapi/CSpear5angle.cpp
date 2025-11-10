#include "pch.h"
#include "CSpear5angle.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"

CSpear5angle::CSpear5angle()
	:m_iDir(-1)
	, m_iPrevDir(-1)
	, i_Count(0)
{
	CreateAnimator();
	CreateCollider();

	GetCollider()->SetScale(Vec2(100.f, 50.f));

	CTexture* m_pSpear5AngleTex = CResMgr::GenInst()->LoadTexture(L"5AngleSpear", L"texture\\PureVessel\\5angle.bmp");

	
	GetAnimator()->CreateAnimation(L"Spear_5Angle_Left",  m_pSpear5AngleTex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"Spear_5Angle_Right", m_pSpear5AngleTex, Vec2(0.f, 300.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);

	dwtime = GetTickCount64();
}

CSpear5angle::~CSpear5angle()
{

}

void CSpear5angle::update()
{
	update_move();
	update_state();
	update_animation();

	if (dwtime + 2000 < GetTickCount64())
	{
		DeleteObject(this);
		dwtime = GetTickCount64();
	}
}

void CSpear5angle::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CSpear5angle::update_move()
{
	Vec2 vPos = GetPos();

	// 5µµ ¹æÇâº¤ÅÍ
	float dir5_x = 0.9962;
	float dir5_y = 0.0872;


	if (m_iDir == -1)
	{
		vPos.x += 1000 * -dir5_x * fDT;
		vPos.y += 1000 * -dir5_y * fDT;
	}

	else
	{
		vPos.x += 1000 * dir5_x * fDT;
		vPos.y += 1000 * -dir5_y * fDT;
	}

	//float dir5_x = 0.9890;
	//float dir5_y = 0.1490;


	//if (m_iDir == -1)
	//{
	//	vPos.x += 1000 * -dir5_x * fDT;
	//	vPos.y += 1000 * dir5_y * fDT;
	//}

	//else
	//{
	//	vPos.x += 1000 * dir5_x * fDT;
	//	vPos.y += 1000 * dir5_y * fDT;
	//}

	SetPos(vPos);
}

void CSpear5angle::update_state()
{
}

void CSpear5angle::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"Spear_5Angle_Left", true);
	}
	else
	{
		GetAnimator()->Play(L"Spear_5Angle_Right", true);
	}
}


void CSpear5angle::OnCollision(CCollider* _pOther)
{

}