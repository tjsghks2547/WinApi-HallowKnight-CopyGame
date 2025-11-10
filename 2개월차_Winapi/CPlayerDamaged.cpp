#include "pch.h"
#include "CPlayerDamaged.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"

CPlayerDamaged::CPlayerDamaged()
	:m_iCount(0)
{
	CreateAnimator();
	CTexture* m_pPlayerDamagedTex = CResMgr::GenInst()->LoadTexture(L"PlayerDamaged", L"texture\\Player\\hit_effect.bmp");
	GetAnimator()->CreateAnimation(L"Player_Damaged_Effect", m_pPlayerDamagedTex, Vec2(0.f, 0.f), Vec2(699.f, 140.f), Vec2(699.f, 0.f), 0.1f, 3);
}

CPlayerDamaged::~CPlayerDamaged()
{

}

void CPlayerDamaged::update()
{
	update_animation();

	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 2)
	{
		m_iCount++;
		if (m_iCount < 2)
		{
			DeleteObject(this);
		}
	}
}

void CPlayerDamaged::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CPlayerDamaged::update_state()
{

}

void CPlayerDamaged::update_animation()
{
	GetAnimator()->Play(L"Player_Damaged_Effect",false);
}
