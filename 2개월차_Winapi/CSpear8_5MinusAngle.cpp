#include "pch.h"
#include "CSpear8_5MinusAngle.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"

CSpear8_5MinusAngle::CSpear8_5MinusAngle()
	:m_iDir(-1)
	, m_iPrevDir(-1)
	, i_Count(0)
{
	CreateAnimator();
	CreateCollider();

	GetCollider()->SetScale(Vec2(100.f, 50.f));

	CTexture* m_pSpear8_5AngleTex = CResMgr::GenInst()->LoadTexture(L"8_5AngleSpear", L"texture\\PureVessel\\Minus8_5angle.bmp");


	GetAnimator()->CreateAnimation(L"Spear8_5Angle_Left",  m_pSpear8_5AngleTex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"Spear8_5Angle_Right", m_pSpear8_5AngleTex, Vec2(0.f, 300.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);

	dwtime = GetTickCount64();
}

CSpear8_5MinusAngle::~CSpear8_5MinusAngle()
{
}

void CSpear8_5MinusAngle::update()
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

void CSpear8_5MinusAngle::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}



void CSpear8_5MinusAngle::update_move()
{
	Vec2 vPos = GetPos();

	float dir8_5_x = 0.9890;
	float dir8_5_y = 0.1490;


	if (m_iDir == -1)
	{
		vPos.x += 1000 * -dir8_5_x * fDT;
		vPos.y += 1000 * dir8_5_y * fDT;
	}

	else
	{
		vPos.x += 1000 * dir8_5_x * fDT;
		vPos.y += 1000 * dir8_5_y * fDT;
	}

	SetPos(vPos);
}

void CSpear8_5MinusAngle::update_state()
{
}

void CSpear8_5MinusAngle::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"Spear8_5Angle_Left", true);
	}
	else
	{
		GetAnimator()->Play(L"Spear8_5Angle_Right", true);
	}
}

void CSpear8_5MinusAngle::OnCollision(CCollider* _pOther)
{
}