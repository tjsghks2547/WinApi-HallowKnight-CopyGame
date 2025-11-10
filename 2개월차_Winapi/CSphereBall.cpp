#include "pch.h"
#include "CSphereBall.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

CSphereBall::CSphereBall()
{
	CreateAnimator();
	CreateCollider();

	GetCollider()->SetScale(Vec2(400.f, 400.f));

	CTexture* m_pSphereBallEffect = CResMgr::GenInst()->LoadTexture(L"SPHERE_Effect", L"texture\\Hornet\\Sphere_ball_real.bmp");
	GetAnimator()->CreateAnimation(L"SPHERE_BALL_EFFECT", m_pSphereBallEffect, Vec2(0.f, 0.f), Vec2(424.f, 447.f), Vec2(424.f, 0.f), 0.10f, 9);

}

CSphereBall::~CSphereBall()
{

}

void CSphereBall::update()
{
	update_state();
	update_animation();

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 8)
	{
		i_Count++;
		if (i_Count < 2)
		{
			DeleteObject(this);
		}
	}
}

void CSphereBall::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CSphereBall::update_state()
{
	
}

void CSphereBall::update_animation()
{
	GetAnimator()->Play(L"SPHERE_BALL_EFFECT", true);
}
