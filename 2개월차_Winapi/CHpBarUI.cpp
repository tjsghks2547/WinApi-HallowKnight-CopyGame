#include "pch.h"
#include "CHpBarUI.h"

// Hp바 이미지넣기 위해 넣은 헤더 
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"




CHpBarUI::CHpBarUI()
	:CUI(false)
{

	CTexture* m_pHpBaridleTex = CResMgr::GenInst()->LoadTexture(L"PlayerHpBar", L"texture\\Health\\Hp_idle.bmp");
	CTexture* m_pHpBarBreakTex = CResMgr::GenInst()->LoadTexture(L"PlayerBreakHpBar", L"texture\\Health\\Hp_break.bmp");
	CTexture* m_pHpBarEmptyTex = CResMgr::GenInst()->LoadTexture(L"PlayerEmptyHpBar", L"texture\\Health\\Hp_Empty2.bmp");
	CTexture* m_pHpBarRefillTex = CResMgr::GenInst()->LoadTexture(L"PlayerRefillHpBar", L"texture\\Health\\Hp_Refill.bmp");


	CreateAnimator(false);
	GetAnimator()->CreateAnimation(L"Hp_Idle", m_pHpBaridleTex, Vec2(0.f, 0.f), Vec2(57.f, 70.f), Vec2(57.f, 0.f), 0.1f, 45);
	GetAnimator()->CreateAnimation(L"Hp_break", m_pHpBarBreakTex, Vec2(0.f, 0.f), Vec2(75.f, 164.f), Vec2(75.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"Hp_Empty", m_pHpBarEmptyTex, Vec2(0.f, 0.f), Vec2(58.f, 115.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"Hp_Refill", m_pHpBarRefillTex, Vec2(0.f, 0.f), Vec2(119.f, 130.f), Vec2(119.f, 0.f), 0.1f, 6);
	//GetAnimator()->Play(L"Hp_Idle", true);

}

CHpBarUI::~CHpBarUI()
{

}


void CHpBarUI::update()
{
	
}

void CHpBarUI::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}
