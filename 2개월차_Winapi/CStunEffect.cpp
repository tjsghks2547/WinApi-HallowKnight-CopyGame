#include "pch.h"
#include "CStunEffect.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"


CStunEffect::CStunEffect()
	:m_iDir(1)
	,m_iPrevDir(1)
	,i_Count(0)
{
	CreateAnimator();
	CTexture* m_pStunEffectTex = CResMgr::GenInst()->LoadTexture(L"Stun_Damge_Effect", L"texture\\Hornet\\Stun_Effect_Effect.bmp");
	//CTexture* m_pSlashHitEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashHitEffect2", L"texture\\Player\\hit_effect.bmp");
	GetAnimator()->CreateAnimation(L"STUN_DAMAGE_EFFECT", m_pStunEffectTex, Vec2(0.f, 0.f), Vec2(308.f, 207.f), Vec2(308.f, 0.f), 0.075f, 7);
}

CStunEffect::~CStunEffect()
{
}

void CStunEffect::update()
{
	

	update_animation();

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 6)
	{
		DeleteObject(this);
	}
}

void CStunEffect::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CStunEffect::update_state()
{
}

void CStunEffect::update_animation()
{
	
	GetAnimator()->Play(L"STUN_DAMAGE_EFFECT", false);
	
}
