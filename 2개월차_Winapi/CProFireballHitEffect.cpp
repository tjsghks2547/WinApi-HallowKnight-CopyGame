#include "pch.h"
#include "CProFireballHitEffect.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"


CProFireballHitEffect::CProFireballHitEffect()
	:m_iDir(1)
	, m_iPrevDir(1)
	, i_Count(0)
{
	//애니메이션 원래 코드 

	CreateAnimator();

	CTexture* m_pProFireBallHitEffectTex = CResMgr::GenInst()->LoadTexture(L"PlayerFireBallHit2", L"texture\\Player\\fireballEffect.bmp");

	GetAnimator()->CreateAnimation(L"PROFIREBALL_LEFT_HIT_EFFECT",  m_pProFireBallHitEffectTex, Vec2(0.f, 0.f), Vec2(151.f, 205.f), Vec2(151.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"PROFIREBALL_RIGHT_HIT_EFFECT", m_pProFireBallHitEffectTex, Vec2(0.f, 205.f), Vec2(151.f, 205.f), Vec2(151.f, 0.f), 0.1f, 7);
}

CProFireballHitEffect::~CProFireballHitEffect()
{

}

void CProFireballHitEffect::update()
{
	update_state();
	update_animation();
	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 6)
	{
		i_Count++;
		if (i_Count < 2)
		{
			DeleteObject(this);
		}
	}

}

void CProFireballHitEffect::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CProFireballHitEffect::OnCollision(CCollider* _pOther)
{

}

void CProFireballHitEffect::update_state()
{

}

void CProFireballHitEffect::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"PROFIREBALL_LEFT_HIT_EFFECT", false);
	}
	else
	{
		GetAnimator()->Play(L"PROFIREBALL_RIGHT_HIT_EFFECT", false);
	}
}
