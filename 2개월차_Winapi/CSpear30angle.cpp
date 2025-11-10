#include "pch.h"
#include "CSpear30angle.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"

CSpear30angle::CSpear30angle()
	:m_iDir(-1)
	, m_iPrevDir(-1)
	, i_Count(0)
{
	CreateAnimator();
	CreateCollider();

	GetCollider()->SetScale(Vec2(100.f, 50.f));

	CTexture* m_pSpear30AngleTex = CResMgr::GenInst()->LoadTexture(L"30AngleSpear", L"texture\\PureVessel\\30angle.bmp");


	GetAnimator()->CreateAnimation(L"Spear_30Angle_Left",  m_pSpear30AngleTex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"Spear_30Angle_Right", m_pSpear30AngleTex, Vec2(0.f, 300.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);

	dwtime = GetTickCount64();
}

CSpear30angle::~CSpear30angle()
{
}

void CSpear30angle::update()
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

void CSpear30angle::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}


void CSpear30angle::update_move()
{
	Vec2 vPos = GetPos();

	// 30µµ ¹æÇâº¤ÅÍ
	float dir30_x = 0.8660;
	float dir30_y = 0.5;


	if (m_iDir == -1)
	{
		vPos.x += 1000 * -dir30_x * fDT;
		vPos.y += 1000 * -dir30_y * fDT;
	}

	else
	{
		vPos.x += 1000 * dir30_x * fDT;
		vPos.y += 1000 * -dir30_y * fDT;
	}

	SetPos(vPos);
}

void CSpear30angle::update_state()
{

}

void CSpear30angle::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"Spear_30Angle_Left", true);
	}
	else
	{
		GetAnimator()->Play(L"Spear_30Angle_Right", true);
	}
}

void CSpear30angle::OnCollision(CCollider* _pOther)
{
}