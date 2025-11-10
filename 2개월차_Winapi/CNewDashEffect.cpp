#include "pch.h"
#include "CNewDashEffect.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"

CNewDashEffect::CNewDashEffect()
	:m_iDir(1)
	, m_iPrevDir(1)
	, i_Count(0)
{
	CreateAnimator();
	CTexture* m_pNewDashEffectTex = CResMgr::GenInst()->LoadTexture(L"PlayerNewDashEffect", L"texture\\Player\\New_Dash_Effect2.bmp");
	//CTexture* m_pSlashHitEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashHitEffect2", L"texture\\Player\\hit_effect.bmp");
	GetAnimator()->CreateAnimation(L"RIGHT_NEW_DASH_EFFECT", m_pNewDashEffectTex, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.075f, 6);
	GetAnimator()->CreateAnimation(L"LEFT_NEW_DASH_EFFECT",  m_pNewDashEffectTex, Vec2(0.f, 200.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.075f, 6);
}

CNewDashEffect::~CNewDashEffect()
{
}

void CNewDashEffect::update()
{
	if (m_iDir == -1)
	{
		SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x + 45.f, CPlayerMgr::GenInst()->GetCurPlayerPos().y)); // ÇÃ·¹ÀÌ¾îÀÇ ÁÂÇ¥ ¹Þ¾Æ¿È
	}

	else if (m_iDir == 1)
	{
		SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x - 45.f, CPlayerMgr::GenInst()->GetCurPlayerPos().y));
	}


	update_animation();

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
	{
		DeleteObject(this);
	}
}

void CNewDashEffect::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CNewDashEffect::update_state()
{
}

void CNewDashEffect::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"RIGHT_NEW_DASH_EFFECT", false);
	}
	else
	{
		GetAnimator()->Play(L"LEFT_NEW_DASH_EFFECT", false);
	}
}
