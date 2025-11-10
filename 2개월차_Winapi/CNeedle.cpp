#include "pch.h"
#include "CNeedle.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"


CNeedle::CNeedle()
	:m_iDir(1)
	,m_iPrevDir(1)
	,i_Count(0)
	,m_eCurState(NEEDLE_STATE::THROW_NEEDLE)
{
	CreateAnimator();
	CreateCollider();

	GetCollider()->SetScale(Vec2(100.f, 50.f));
	
	CTexture* m_pNeedleEffectTex = CResMgr::GenInst()->LoadTexture(L"ThrowNeedleEffect", L"texture\\Hornet\\Needle.bmp");
	//CTexture* m_pSlashHitEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashHitEffect2", L"texture\\Player\\hit_effect.bmp");
	GetAnimator()->CreateAnimation(L"LEFT_NEEDLE_EFFECT", m_pNeedleEffectTex, Vec2(0.f, 0.f), Vec2(180.f, 11.f), Vec2(180.f, 0.f), 0.15f, 3);
	GetAnimator()->CreateAnimation(L"RIGHT_NEEDLE_EFFECT", m_pNeedleEffectTex, Vec2(0.f, 11.f), Vec2(180.f, 11.f), Vec2(180.f, 0.f), 0.15f, 3);


	//¿ªÀç»ý 
	GetAnimator()->CreateAnimation(L"REVERSE_LEFT_NEEDLE_EFFECT", m_pNeedleEffectTex, Vec2(360.f, 0.f), Vec2(180.f, 11.f), Vec2(-180.f, 0.f), 0.15f, 3);
	GetAnimator()->CreateAnimation(L"REVERSE_RIGHT_NEEDLE_EFFECT", m_pNeedleEffectTex, Vec2(360.f, 11.f), Vec2(180.f, 11.f), Vec2(-180.f, 0.f), 0.15f, 3);

}

CNeedle::~CNeedle()
{
}

void CNeedle::update()
{
	
	update_state();
	update_animation();

	
}

void CNeedle::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CNeedle::update_state()
{
	Vec2 vPos = GetPos();
	if (m_iDir == -1 && m_eCurState == NEEDLE_STATE::THROW_NEEDLE)
	{
		vPos.x -= 1500 * fDT;
	}
	
	else if (m_iDir == 1 && m_eCurState == NEEDLE_STATE::THROW_NEEDLE)
	{
		vPos.x += 1500 * fDT;
	}

	else if (m_iDir == -1 && m_eCurState == NEEDLE_STATE::GETBACK_NEEDLE)
	{
		vPos.x += 1500 * fDT;
	}

	else if (m_iDir == 1 && m_eCurState == NEEDLE_STATE::GETBACK_NEEDLE)
	{
		vPos.x -= 1500 * fDT;
	}

	SetPos(vPos);
}

void CNeedle::update_animation()
{
	if (m_iDir == -1 && m_eCurState == NEEDLE_STATE::THROW_NEEDLE)
	{
		GetAnimator()->Play(L"LEFT_NEEDLE_EFFECT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				m_eCurState = NEEDLE_STATE::GETBACK_NEEDLE;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == NEEDLE_STATE::THROW_NEEDLE)
	{
		GetAnimator()->Play(L"RIGHT_NEEDLE_EFFECT", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			m_eCurState = NEEDLE_STATE::GETBACK_NEEDLE;
		}

	}

	if (m_iDir == -1 && m_eCurState == NEEDLE_STATE::GETBACK_NEEDLE)
	{

		GetAnimator()->Play(L"REVERSE_LEFT_NEEDLE_EFFECT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				DeleteObject(this);
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == NEEDLE_STATE::GETBACK_NEEDLE)
	{

		GetAnimator()->Play(L"REVERSE_RIGHT_NEEDLE_EFFECT", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			DeleteObject(this);
		}

	}
}
