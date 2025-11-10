#include "pch.h"
#include "CWing.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CPlayerMgr.h"

CWing::CWing()
	:m_iDir(1)
	,m_iPrevDir(1)
	,i_Count(0)
{
	CreateAnimator();


	//애니메이션 원래 코드 
	CTexture* m_pWingEffectTex = CResMgr::GenInst()->LoadTexture(L"Wing", L"texture\\Player\\Knight_Wing2.bmp");

	GetAnimator()->CreateAnimation(L"WING_LEFT_EFFECT",  m_pWingEffectTex, Vec2(0.f, 0.f), Vec2(191.f, 178.f), Vec2(191.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WING_RIGHT_EFFECT", m_pWingEffectTex, Vec2(0.f, 178.f), Vec2(191.f, 178.f), Vec2(191.f, 0.f), 0.1f, 6);

}

CWing::~CWing()
{

}

void CWing::update()
{
	update_state();
	update_animation();


	if (m_iDir == -1)
	{
		SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x , CPlayerMgr::GenInst()->GetCurPlayerPos().y)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x , CPlayerMgr::GenInst()->GetCurPlayerPos().y));
	}

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
	{
		DeleteObject(this);
	}

}

void CWing::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}


void CWing::update_state()
{
}

void CWing::update_animation()
{
	if (m_iDir == -1)
	{
		GetAnimator()->Play(L"WING_LEFT_EFFECT", false);
	}
	else
	{
		GetAnimator()->Play(L"WING_RIGHT_EFFECT", false);
	}
}


void CWing::OnCollision(CCollider* _pOther)
{

}