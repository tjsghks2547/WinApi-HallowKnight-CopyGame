#include "pch.h"
#include "CPlayerStunEffect.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayerStunEffect::CPlayerStunEffect()
	:i_Count(0)
{
	CreateAnimator();

	CTexture* m_pStunEffect = CResMgr::GenInst()->LoadTexture(L"PlayerStunEffect", L"texture\\Player\\Player_Stun_Effect2.bmp");
	GetAnimator()->CreateAnimation(L"PLAYER_STUN2_EFFECT", m_pStunEffect, Vec2(0.f, 0.f), Vec2(308.f, 270.f), Vec2(308.f, 0.f), 0.1f, 6);
}

CPlayerStunEffect::~CPlayerStunEffect()
{

}

void CPlayerStunEffect::update()
{
	update_state();
	update_animation();

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
	{
		i_Count++;
		if (i_Count < 2)
		{
			DeleteObject(this);
		}
	}
}

void CPlayerStunEffect::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CPlayerStunEffect::update_state()
{

}

void CPlayerStunEffect::update_animation()
{
	GetAnimator()->Play(L"PLAYER_STUN2_EFFECT", true);
}
