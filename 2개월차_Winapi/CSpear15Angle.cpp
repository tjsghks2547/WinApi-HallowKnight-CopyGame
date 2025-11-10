#include "pch.h"
#include "CSpear15Angle.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"

CSpear15Angle::CSpear15Angle()
	:m_iDir(-1)
	, m_iPrevDir(-1)
	, i_Count(0)
{
	CreateAnimator();
	CreateCollider();

	GetCollider()->SetScale(Vec2(100.f, 50.f));

	CTexture* m_pSpear15AngleTex = CResMgr::GenInst()->LoadTexture(L"15AngleSpear", L"texture\\PureVessel\\15Angle.bmp");


	GetAnimator()->CreateAnimation(L"Spear_15Angle_Left",  m_pSpear15AngleTex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"Spear_15Angle_Right", m_pSpear15AngleTex, Vec2(0.f, 300.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);

	dwtime = GetTickCount64();
}

CSpear15Angle::~CSpear15Angle()
{
}

void CSpear15Angle::update()
{
	update_move();
	update_state();
	update_animation();

	if(dwtime +2000 < GetTickCount64())
	{
		DeleteObject(this);
		dwtime = GetTickCount64();
	}
}

void CSpear15Angle::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CSpear15Angle::update_move()
{
	Vec2 vPos = GetPos();

	// 30µµ ¹æÇâº¤ÅÍ
	float dir15_x = 0.9659;
	float dir15_y = 0.2588;


	if (m_iDir == -1)
	{
		vPos.x += 1000 * -dir15_x * fDT;
		vPos.y += 1000 * -dir15_y * fDT;
	}

	else
	{
		vPos.x += 1000 * dir15_x * fDT;
		vPos.y += 1000 * -dir15_y * fDT;
	}

	SetPos(vPos);
}

void CSpear15Angle::update_state()
{
}

void CSpear15Angle::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"Spear_15Angle_Left", true);
	}
	else
	{
		GetAnimator()->Play(L"Spear_15Angle_Right", true);
	}
}

void CSpear15Angle::OnCollision(CCollider* _pOther)
{
}
