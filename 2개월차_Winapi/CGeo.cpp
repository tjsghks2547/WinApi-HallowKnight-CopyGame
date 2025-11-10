#include "pch.h"
#include "CGeo.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"


CGeo::CGeo()
	:CUI(false)
{
	CTexture* m_pGeoTex = CResMgr::GenInst()->LoadTexture(L"GEO", L"texture\\UI_geo.bmp");
	CreateAnimator(false);

	GetAnimator()->CreateAnimation(L"GEO", m_pGeoTex, Vec2(0.f, 0.f), Vec2(52.f, 54.f), Vec2(52.f, 0.f), 1.f, 1);
	GetAnimator()->Play(L"GEO", true);
}

CGeo::~CGeo()
{
}


void CGeo::update()
{
}

void CGeo::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

