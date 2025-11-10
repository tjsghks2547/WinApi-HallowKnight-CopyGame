#include "pch.h"
#include "CSpear20minusAngle.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"

CSpear20minusAngle::CSpear20minusAngle()
	:m_iDir(-1)
	, m_iPrevDir(-1)
	, i_Count(0)
{
	CreateAnimator();
	CreateCollider();

	GetCollider()->SetScale(Vec2(100.f, 50.f));

	CTexture* m_pSpearMinus45Tex = CResMgr::GenInst()->LoadTexture(L"Minus20spear", L"texture\\PureVessel\\minus20angle.bmp");

	// 마이너스 45도
	GetAnimator()->CreateAnimation(L"Spear_20_Left_Minus", m_pSpearMinus45Tex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"Spear_20_Right_Minus", m_pSpearMinus45Tex, Vec2(0.f, 300.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);

	dwtime = GetTickCount64();
}

CSpear20minusAngle::~CSpear20minusAngle()
{

}

void CSpear20minusAngle::update()
{
	update_move();
	update_state();
	update_animation();

	if (dwtime + 2000 < GetTickCount64())
	{
		DeleteObject(this);
		dwtime = GetTickCount64();
	}

}

void CSpear20minusAngle::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}


void CSpear20minusAngle::update_move()
{
	Vec2 vPos = GetPos();

	// 105도 방향벡터
	float dir20_x = 0.9397;
	float dir20_y = 0.3420;


	if (m_iDir == -1)
	{
		vPos.x += 1000 * -dir20_x * fDT;
		vPos.y += 1000 * dir20_y * fDT;
	}

	else
	{
		vPos.x += 1000 * dir20_x * fDT;
		vPos.y += 1000 * dir20_y * fDT;
	}

	SetPos(vPos);
}

void CSpear20minusAngle::update_state()
{

}

void CSpear20minusAngle::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"Spear_20_Left_Minus", true);
	}
	else
	{
		GetAnimator()->Play(L"Spear_20_Right_Minus", true);
	}
}

void CSpear20minusAngle::OnCollision(CCollider* _pOther)
{

}
