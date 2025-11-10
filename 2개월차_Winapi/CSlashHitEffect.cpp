#include "pch.h"
#include "CSlashHitEffect.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"


CSlashHitEffect::CSlashHitEffect()
	:m_iDir(1)
	,m_iPrevDir(1)
	,i_Count(0)
{
	CreateAnimator();
	CTexture* m_pSlashHitEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashHitEffect", L"texture\\Player\\Nail_hit.bmp");
	//CTexture* m_pSlashHitEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashHitEffect2", L"texture\\Player\\hit_effect.bmp");
	GetAnimator()->CreateAnimation(L"SLASH_LEFT_HIT_EFFECT", m_pSlashHitEffectText, Vec2(0.f, 0.f), Vec2(153.f, 114.f), Vec2(153.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"SLASH_RIGHT_HIT_EFFECT", m_pSlashHitEffectText, Vec2(0.f, 114.f), Vec2(153.f, 114.f), Vec2(153.f, 0.f), 0.1f, 4);

	//GetAnimator()->CreateAnimation(L"SLASH_RIGHT_HIT_EFFECT", m_pSlashHitEffectText, Vec2(0.f, 0.f), Vec2(699.f, 140.f), Vec2(699.f, 0.f), 0.1f, 3);
}

CSlashHitEffect::~CSlashHitEffect()
{
}

void CSlashHitEffect::update()
{
	update_state();
	update_animation();


	//아 이게 애니메이션의 주기가 빠르게 도니깐 델타타임보다 그래서 그런듯  (진짜임;; 0.05F 에서 5F로 바꾸니깐 여러번 돌아버림)
	/*if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 2)
	{
		i_Count++;
		if (i_Count < 2)
		{
			DeleteObject(this);
		}
	}*/
}

void CSlashHitEffect::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}



void CSlashHitEffect::update_state()
{
}

void CSlashHitEffect::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"SLASH_LEFT_HIT_EFFECT", false);
	}
	else
	{
		GetAnimator()->Play(L"SLASH_RIGHT_HIT_EFFECT", false);
	}

}

void CSlashHitEffect::OnCollisionEnter(CCollider* _pOther)
{
}
