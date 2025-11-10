#include "pch.h"
#include "COrb.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSound.h"

COrb::COrb()
{
	CreateAnimator();

	CTexture* m_CircleObjEffectTex = CResMgr::GenInst()->LoadTexture(L"CirCleEffect", L"texture\\PureVessel\\CircleObj.bmp");

	GetAnimator()->CreateAnimation(L"CirCleEffect", m_CircleObjEffectTex, Vec2(0.f, 0.f), Vec2(707.f, 608.f), Vec2(707.f, 0.f), 0.1f, 6);
	
	
}

COrb::~COrb()
{

}

void COrb::update()
{
	

	update_state();
	update_animation();

	

	if(GetAnimator()->GetAnimation()->GetCurrentFrm()>5)
	{
		
		DeleteObject(this);
	}
}

void COrb::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void COrb::update_state()
{

}

void COrb::update_sound()
{

}

void COrb::update_animation()
{
	GetAnimator()->Play(L"CirCleEffect", false);
}
