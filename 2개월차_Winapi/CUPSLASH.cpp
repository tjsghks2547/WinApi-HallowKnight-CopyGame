#include "pch.h"
#include "CUPSLASH.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

CUPSLASH::CUPSLASH()
	:m_iCount(0)
{
	CreateCollider();
	CreateAnimator();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, -30.f));
	GetCollider()->SetScale(Vec2(100.f, 50.f));
	CTexture* m_pUpSlashEffectTex = CResMgr::GenInst()->LoadTexture(L"Up_Slash_Effect", L"texture\\Player\\Up_Slash_Effect_real.bmp");

	GetAnimator()->CreateAnimation(L"SLASH_UP_EFFECT", m_pUpSlashEffectTex, Vec2(0.f, 0.f), Vec2(162.f, 162.f), Vec2(162.f, 0.f), 0.05f, 6);

}

CUPSLASH::~CUPSLASH()
{

}

void CUPSLASH::update()
{
	update_state();
	update_animation();


	//아 이게 애니메이션의 주기가 빠르게 도니깐 델타타임보다 그래서 그런듯  (진짜임;; 0.05F 에서 5F로 바꾸니깐 여러번 돌아버림)
	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
	{
		m_iCount++;
		if (m_iCount < 2)
		{
			DeleteObject(this);
		}
	}
}

void CUPSLASH::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CUPSLASH::update_state()
{

}

void CUPSLASH::update_animation()
{
	GetAnimator()->Play(L"SLASH_UP_EFFECT", true);
}
