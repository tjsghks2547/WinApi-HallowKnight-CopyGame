#include "pch.h"
#include "CFireBall.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

CFireBall::CFireBall()
	:m_iCount(0)
	,m_iDir(1)
	,m_iPrevDir(1)
{
	CreateAnimator();

	CTexture* m_pFireBallEffect = CResMgr::GenInst()->LoadTexture(L"FireBallEffect", L"texture\\Player\\fireballcastEffect2_real.bmp");
	GetAnimator()->CreateAnimation(L"FIREBALL_EFFECT_LEFT", m_pFireBallEffect, Vec2(0.f, 0.f), Vec2(205.f, 204.f), Vec2(205.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"FIREBALL_EFFECT_RIGHT", m_pFireBallEffect, Vec2(0.f, 204.f), Vec2(205.f, 204.f), Vec2(205.f, 0.f), 0.1f, 8);
}

CFireBall::~CFireBall()
{

}

void CFireBall::update()
{
	update_state();
	update_animation();

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 7)
	{
		m_iCount++;
		if (m_iCount < 2)
		{
			DeleteObject(this);
		}
	}
}

void CFireBall::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CFireBall::update_state()
{

}

void CFireBall::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"FIREBALL_EFFECT_LEFT", false);
	}
	else
	{
		GetAnimator()->Play(L"FIREBALL_EFFECT_RIGHT", false);
	}

}
