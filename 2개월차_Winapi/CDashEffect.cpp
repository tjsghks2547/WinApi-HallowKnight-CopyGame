#include "pch.h"
#include "CDashEffect.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"

CDashEffect::CDashEffect()
	:m_iDir(1)
	,m_iPrevDir(1)
	,i_Count(0)
{
	CreateAnimator();
	CTexture* m_pDashEffectTex = CResMgr::GenInst()->LoadTexture(L"PlayerDashEffect", L"texture\\Player\\dash_test11.bmp");
	//CTexture* m_pSlashHitEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashHitEffect2", L"texture\\Player\\hit_effect.bmp");
	GetAnimator()->CreateAnimation(L"RIGHT_DASH_EFFECT", m_pDashEffectTex, Vec2(0.f, 0.f), Vec2(200.f, 100.f), Vec2(200.f, 0.f), 0.025f, 2);
	GetAnimator()->CreateAnimation(L"LEFT_DASH_EFFECT", m_pDashEffectTex, Vec2(600.f, 100.f), Vec2(200.f, 100.f), Vec2(-200.f, 0.f), 0.025f, 2);

	
}

CDashEffect::~CDashEffect()
{

}

void CDashEffect::update()
{

	if (m_iDir == -1)
	{
		SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x + 80.f, CPlayerMgr::GenInst()->GetCurPlayerPos().y)); // ÇÃ·¹ÀÌ¾îÀÇ ÁÂÇ¥ ¹Þ¾Æ¿È
	}

	else if (m_iDir == 1)
	{
		SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x - 80.f, CPlayerMgr::GenInst()->GetCurPlayerPos().y));
	}
	

	update_animation();

	if(GetAnimator()->GetAnimation()->GetCurrentFrm()==1)
	{
		DeleteObject(this);
	}

}

void CDashEffect::render(HDC _dc)
{

	GetAnimator()->render(_dc);
}

void CDashEffect::update_state()
{
	
}

void CDashEffect::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"LEFT_DASH_EFFECT", false);
	}
	else
	{
		GetAnimator()->Play(L"RIGHT_DASH_EFFECT", false);
	}

}
