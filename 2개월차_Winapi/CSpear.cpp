#include "pch.h"
#include "CSpear.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"


CSpear::CSpear()
	:m_iDir(-1)
	,m_iPrevDir(-1)
	,i_Count(0)
{
	CreateAnimator();
	CreateCollider();

	GetCollider()->SetScale(Vec2(100.f, 50.f));

	CTexture* m_pSpearMinus45Tex = CResMgr::GenInst()->LoadTexture(L"Minus45spear", L"texture\\PureVessel\\minus45angle.bmp");

	// 마이너스 45도
	GetAnimator()->CreateAnimation(L"Spear_45_Left_Minus",  m_pSpearMinus45Tex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"Spear_45_Right_Minus", m_pSpearMinus45Tex, Vec2(0.f, 300.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.3f, 4);

	dwtime = GetTickCount64();
}

CSpear::~CSpear()
{

}

void CSpear::update()
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

void CSpear::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}



void CSpear::update_move()
{
	Vec2 vPos = GetPos();

	float dir135_x = sqrt(2) / 2;
	float dir135_y = sqrt(2) / 2;


	if(m_iDir ==-1)
	{
		vPos.x += 1000 * -dir135_x * fDT;
		vPos.y += 1000 * dir135_y * fDT;
	}

	else
	{
		vPos.x += 1000 * dir135_x * fDT;
		vPos.y += 1000 * dir135_y * fDT;
	}

	SetPos(vPos);
}

void CSpear::update_state()
{

}

void CSpear::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"Spear_45_Left_Minus", true);
	}
	else
	{
		GetAnimator()->Play(L"Spear_45_Right_Minus", true);
	}
}


void CSpear::OnCollision(CCollider* _pOther)
{

}