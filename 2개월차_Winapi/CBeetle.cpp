#include "pch.h"
#include "CBeetle.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPathMgr.h"
#include "AI.h"


CBeetle::CBeetle()
	:m_iDir(1)
	,m_iPrevDir(1)
	,m_eCurState(MON_STATE::IDLE)
	,m_ePreState(MON_STATE::IDLE)
{

	CreateCollider();
	CreateAnimator();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(25.f, 50.f));

	//애니메이션 원래 코드 
	CTexture* m_pIdileTex2 = CResMgr::GenInst()->LoadTexture(L"MonsterIdle", L"texture\\beetle\\idle_3.bmp");

	GetAnimator()->CreateAnimation(L"Idle_LEFT_BEETLE", m_pIdileTex2, Vec2(0.f, 0.f), Vec2(118.f, 192.f), Vec2(118.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"Idle_RIGHT_BEETLE", m_pIdileTex2, Vec2(0.f, 192.f), Vec2(118.f, 192.f), Vec2(118.f, 0.f), 0.2f, 4);
	GetAnimator()->Play(L"Idle_LEFT_BEETLE", true);

}

CBeetle::~CBeetle()
{
}



void CBeetle::update()
{

	update_move();

	update_state();

	update_animation();

	if (m_pAI != nullptr)
	{
		m_pAI->update();
	}

}

void CBeetle::update_state()
{
}

void CBeetle::update_move()
{
}

void CBeetle::update_animation()
{
	GetAnimator()->Play(L"Idle_RIGHT_BEETLE", true);
}


void CBeetle::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CBeetle::OnCollision(CCollider* _pOther)
{
}

void CBeetle::OnCollisionEnter(CCollider* _pOther)
{
}

void CBeetle::OnCollisionExit(CCollider* _pOther)
{
}
