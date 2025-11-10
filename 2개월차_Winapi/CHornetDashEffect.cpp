#include "pch.h"
#include "CHornetDashEffect.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"


CHornetDashEffect::CHornetDashEffect()
	:m_iDir(1)
	,m_iPrevDir(1)
	,i_Count(0)
{
	CreateAnimator();
	CTexture* m_pHornetDashEffectTex = CResMgr::GenInst()->LoadTexture(L"HornetDashEffect", L"texture\\Hornet\\Rush_Effect.bmp");
	//CTexture* m_pSlashHitEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashHitEffect2", L"texture\\Player\\hit_effect.bmp");
	GetAnimator()->CreateAnimation(L"HORNET_LEFT_DASH_EFFECT", m_pHornetDashEffectTex, Vec2(0.f, 0.f), Vec2(302.f, 284.f), Vec2(302.f, 0.f), 0.05f, 5);
	GetAnimator()->CreateAnimation(L"HORNET_RIGHT_DASH_EFFECT",  m_pHornetDashEffectTex, Vec2(0.f, 284.f), Vec2(302.f, 284.f), Vec2(302.f, 0.f), 0.05f, 5);

	
}

CHornetDashEffect::~CHornetDashEffect()
{

}

void CHornetDashEffect::update()
{

	update_animation();

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 4)
	{
		DeleteObject(this);
	}

}

void CHornetDashEffect::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CHornetDashEffect::update_state()
{

}

void CHornetDashEffect::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"HORNET_LEFT_DASH_EFFECT", false);
	}
	else
	{	
		GetAnimator()->Play(L"HORNET_RIGHT_DASH_EFFECT", false);
	}
}

