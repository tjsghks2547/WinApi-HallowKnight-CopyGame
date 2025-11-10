#include "pch.h"
#include "CThrowEffect.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"

CThrowEffect::CThrowEffect()
	:m_iDir(1)
	, m_iPrevDir(1)
	, i_Count(0)
{
	CreateAnimator();
	CTexture* m_pHornetThrowEffectTex = CResMgr::GenInst()->LoadTexture(L"HornetThrowEffect", L"texture\\Hornet\\Throw_Effect.bmp");
	//CTexture* m_pSlashHitEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashHitEffect2", L"texture\\Player\\hit_effect.bmp");
	GetAnimator()->CreateAnimation(L"HORNET_LEFT_THROW_EFFECT",  m_pHornetThrowEffectTex, Vec2(0.f, 0.f), Vec2(269.f, 87.5f), Vec2(269.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"HORNET_RIGHT_THROW_EFFECT", m_pHornetThrowEffectTex, Vec2(0.f, 87.5f), Vec2(269.f, 87.5f), Vec2(269.f, 0.f), 0.05f, 3);
}

CThrowEffect::~CThrowEffect()
{

}

void CThrowEffect::update()
{
	update_animation();

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 2)
	{
		DeleteObject(this);
	}
}

void CThrowEffect::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CThrowEffect::update_state()
{

}

void CThrowEffect::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"HORNET_RIGHT_THROW_EFFECT", false);
	}
	else
	{
		GetAnimator()->Play(L"HORNET_LEFT_THROW_EFFECT", false);
	}
}
