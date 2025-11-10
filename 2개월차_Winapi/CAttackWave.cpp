#include "pch.h"
#include "CAttackWave.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"

CAttackWave::CAttackWave()
	:m_iCount(0)
{
	dwtime = GetTickCount64();

	CreateAnimator();
	CreateCollider();
	
	GetCollider()->SetOffsetPos(Vec2(0.f, 50.f));
	GetCollider()->SetScale(Vec2(60.f, 180.f));
	

	CTexture* m_pAttackWaveEffect = CResMgr::GenInst()->LoadTexture(L"AttackWaveEffect", L"texture\\FalseKnight\\false_knight_attack_wave2.bmp");
	GetAnimator()->CreateAnimation(L"LEFT_WAVE_EFFECT", m_pAttackWaveEffect, Vec2(0.f, 0.f), Vec2(120.f, 250.f), Vec2(120.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"RIGHT_WAVE_EFFECT", m_pAttackWaveEffect, Vec2(0.f, 250.f), Vec2(120.f, 250.f), Vec2(120.f, 0.f), 0.25f, 3);
}

CAttackWave::~CAttackWave()
{ 

}

void CAttackWave::update()
{
	update_state();
	update_animation();

	if(dwtime + 1000 < GetTickCount64())
	{
		DeleteObject(this);
	}
	/*if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 2)
	{
		m_iCount++;
		if (m_iCount < 2)
		{
			DeleteObject(this);
		}
	}*/
}

void CAttackWave::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CAttackWave::update_state()
{
	Vec2 vPos = GetPos();
	if (m_iDir == -1)
	{
		vPos.x -= 700 * fDT;
	}
	else
	{
		vPos.x += 700 * fDT;
	}

	SetPos(vPos);

}

void CAttackWave::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"LEFT_WAVE_EFFECT", false);
	}
	else
	{
		GetAnimator()->Play(L"RIGHT_WAVE_EFFECT", false);
	}
}
