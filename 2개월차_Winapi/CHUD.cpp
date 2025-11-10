#include "pch.h"
#include "CHUD.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"


CHUD::CHUD()
	:CUI(false)
{
	CreateAnimator(false);
	CTexture* m_pHpBaridleTex = CResMgr::GenInst()->LoadTexture(L"HUD_FRAMEBar", L"texture\\HUDFrame.bmp");
	GetAnimator()->CreateAnimation(L"HUD_FRAME", m_pHpBaridleTex, Vec2(0.f, 0.f), Vec2(257.f, 164.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->Play(L"HUD_FRAME", true);
}

CHUD::~CHUD()
{

}


void CHUD::update()
{

}

void CHUD::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

