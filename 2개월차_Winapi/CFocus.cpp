#include "pch.h"
#include "CFocus.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

CFocus::CFocus()
	:i_Count(0)
{
	CreateAnimator();
	
	CTexture* m_pFocusEffect = CResMgr::GenInst()->LoadTexture(L"FocusEffect", L"texture\\Player\\FocusEffect_real.bmp");
	GetAnimator()->CreateAnimation(L"FOCUS_EFFECT", m_pFocusEffect, Vec2(0.f, 0.f), Vec2(91.f, 182.f), Vec2(91.f, 0.f), 0.05f, 13);
}

CFocus::~CFocus()
{
}

void CFocus::update()
{
	update_state();
	update_animation();

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 12)
	{
		i_Count++;
		if (i_Count < 2)
		{
			DeleteObject(this);
		}
	}

}

void CFocus::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CFocus::update_state()
{
}

void CFocus::update_animation()
{
	GetAnimator()->Play(L"FOCUS_EFFECT", true);
}
