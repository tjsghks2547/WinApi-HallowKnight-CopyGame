#include "pch.h"
#include "CProFireBall.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CProFireballHitEffect.h"

CProFireBall::CProFireBall()
	:m_iDir(1)
	,m_iPrevDir(1)
	,i_Count(0)
{
	CreateCollider();
	CreateAnimator();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(30.f, 30.f));

	//애니메이션 원래 코드 
	CTexture* m_pProFireBallEffectTex = CResMgr::GenInst()->LoadTexture(L"PlayerFireBall", L"texture\\Player\\FireballProEffect.bmp");

	GetAnimator()->CreateAnimation(L"PROFIREBALL_LEFT_EFFECT", m_pProFireBallEffectTex, Vec2(0.f, 0.f), Vec2(196.f, 85.f), Vec2(196.f, 0.f), 0.2f, 7);
	GetAnimator()->CreateAnimation(L"PROFIREBALL_RIGHT_EFFECT", m_pProFireBallEffectTex, Vec2(0.f, 85.f), Vec2(196.f, 85.f), Vec2(196.f, 0.f), 0.2f, 7);
}

CProFireBall::~CProFireBall()
{
}

void CProFireBall::update()
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

void CProFireBall::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CProFireBall::OnCollisionEnter(CCollider* _pOther)
{
	CreateFireBallHitEffect();
}

void CProFireBall::OnCollision(CCollider* _pOther)
{
	
}

void CProFireBall::update_state()
{
	Vec2 vPos = GetPos();
	if (m_iDir == -1)
	{
		vPos.x -= 500 * fDT; 
	}
	else
	{
		vPos.x += 500 * fDT;
	}

	SetPos(vPos);
	
}

void CProFireBall::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"PROFIREBALL_LEFT_EFFECT", false);
	}
	else
	{
		GetAnimator()->Play(L"PROFIREBALL_RIGHT_EFFECT", false);
	}


}

void CProFireBall::CreateFireBallHitEffect()
{
	CProFireballHitEffect* pFireBallHitEffect = new CProFireballHitEffect;
	pFireBallHitEffect->SetName(L"FireBallHitEffect2");
	pFireBallHitEffect->SetDir(m_iDir);
	
	pFireBallHitEffect->SetPos(GetPos());

	CreateObject(pFireBallHitEffect, GROUP_TYPE::SKILLEFFECT);

}
