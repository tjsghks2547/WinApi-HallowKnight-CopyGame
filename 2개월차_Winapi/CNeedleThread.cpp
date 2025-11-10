#include "pch.h"
#include "CNeedleThread.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"

CNeedleThread::CNeedleThread()
	:m_iDir(1)
	, m_iPrevDir(1)
	, i_Count(0)
	, m_eCurState(THREAD_STATE::THROW_THREAD)
{
	CreateAnimator();
	CTexture* m_pThreadEffectTex = CResMgr::GenInst()->LoadTexture(L"ThrowThreadEffect", L"texture\\Hornet\\Needle_Thread2.bmp");
	//CTexture* m_pSlashHitEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashHitEffect2", L"texture\\Player\\hit_effect.bmp");
	GetAnimator()->CreateAnimation(L"LEFT_THREAD_EFFECT",  m_pThreadEffectTex, Vec2(0.f, 0.f), Vec2(400.f, 27.f), Vec2(400.f, 0.f), 0.075f, 6);
	GetAnimator()->CreateAnimation(L"RIGHT_THREAD_EFFECT", m_pThreadEffectTex, Vec2(0.f, 27.f), Vec2(400.f, 27.f), Vec2(400.f, 0.f), 0.075f, 6);


	//¿ªÀç»ý 
	GetAnimator()->CreateAnimation(L"REVERSE_LEFT_THREAD_EFFECT",  m_pThreadEffectTex, Vec2(2000.f, 0.f), Vec2(400.f, 27.f), Vec2(-400.f, 0.f), 0.0325f, 6);
	GetAnimator()->CreateAnimation(L"REVERSE_RIGHT_THREAD_EFFECT", m_pThreadEffectTex, Vec2(2000.f, 27.f), Vec2(400.f, 27.f), Vec2(-400.f, 0.f), 0.0325f, 6);

}

CNeedleThread::~CNeedleThread()
{
}

void CNeedleThread::update()
{
	update_state();
	update_animation();
}

void CNeedleThread::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CNeedleThread::update_state()
{
	Vec2 vPos = GetPos();
	if (m_iDir == -1 && m_eCurState == THREAD_STATE::THROW_THREAD)
	{
		vPos.x -= 750 * fDT;
	}

	else if (m_iDir == 1 && m_eCurState == THREAD_STATE::THROW_THREAD)
	{
		vPos.x += 750 * fDT;
	}

	else if (m_iDir == -1 && m_eCurState == THREAD_STATE::GETBACK_THREAD)
	{
		vPos.x += 750 * fDT;
	}

	else if (m_iDir == 1 && m_eCurState == THREAD_STATE::GETBACK_THREAD)
	{
		vPos.x -= 750 * fDT;
	}

	SetPos(vPos);
}

void CNeedleThread::update_animation()
{
	if (m_iDir == -1 && m_eCurState == THREAD_STATE::THROW_THREAD)
	{
		GetAnimator()->Play(L"LEFT_THREAD_EFFECT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				m_eCurState = THREAD_STATE::GETBACK_THREAD;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == THREAD_STATE::THROW_THREAD)
	{
		GetAnimator()->Play(L"RIGHT_THREAD_EFFECT", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			m_eCurState = THREAD_STATE::GETBACK_THREAD;
		}

	}

	if (m_iDir == -1 && m_eCurState == THREAD_STATE::GETBACK_THREAD)
	{

		GetAnimator()->Play(L"REVERSE_LEFT_THREAD_EFFECT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				DeleteObject(this);
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == THREAD_STATE::GETBACK_THREAD)
	{

		GetAnimator()->Play(L"REVERSE_RIGHT_THREAD_EFFECT", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			DeleteObject(this);
		}

	}
}
