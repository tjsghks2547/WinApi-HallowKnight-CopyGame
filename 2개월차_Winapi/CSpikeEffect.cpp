#include "pch.h"
#include "CSpikeEffect.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CSound.h"


CSpikeEffect::CSpikeEffect()
	:i_Count(0)
	,m_eCurState(SPIKE_STATE::SPIKE_EFFECT_ANTICIPATE)
	,m_bSoundPlayed(false)

{
	CreateAnimator();
	CreateCollider();

	

	CTexture* m_SpikeAnticipateEffectTex = CResMgr::GenInst()->LoadTexture(L"SpikeEffectAnticipate", L"texture\\PureVessel\\Spike_Effect_Anticipate2.bmp");
	CTexture* m_SpikeAttackEffectTex = CResMgr::GenInst()->LoadTexture(L"SpikeAttackEffect", L"texture\\PureVessel\\Spike_Attack_Effect.bmp");

	GetAnimator()->CreateAnimation(L"SPIKE_EFFECT_ANTICIPATE", m_SpikeAnticipateEffectTex, Vec2(0.f, 0.f), Vec2(262.f, 839.f), Vec2(262.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"SPIKE_EFFECT_ATTACK", m_SpikeAttackEffectTex, Vec2(0.f, 0.f), Vec2(262.f, 839.f), Vec2(262.f, 0.f), 0.1f, 15);
	
	//사운드 
	
	CResMgr::GenInst()->LoadSound(L"Ground_Sword_Appear", L"sound\\Vessel_Sound\\gg_pure_vessel_ground_swords_appear.wav");
	CResMgr::GenInst()->LoadSound(L"Ground_Sword_PrePare", L"sound\\Vessel_Sound\\gg_pure_vessel_ground_swords_prepare.wav");

}

CSpikeEffect::~CSpikeEffect()
{
}

void CSpikeEffect::update()
{
	update_state();
	update_sound();
	update_animation();

	/*if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 6)
	{
		i_Count++;
		if (i_Count < 2)
		{
			DeleteObject(this);
		}
	}*/

	m_ePreState = m_eCurState;
}

void CSpikeEffect::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CSpikeEffect::update_state()
{
}

void CSpikeEffect::update_sound()
{
	CSound* pGroundSwordAppearSound = CResMgr::GenInst()->FindSound(L"Ground_Sword_Appear");
	CSound* pGroundSwordPrePareSound = CResMgr::GenInst()->FindSound(L"Ground_Sword_PrePare");

	switch(m_eCurState)
	{
	case SPIKE_STATE::SPIKE_EFFECT_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pGroundSwordPrePareSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;

	case SPIKE_STATE::SPIKE_EFFECT_ATTACK:
		if (!m_bSoundPlayed)
		{
			GetCollider()->SetScale(Vec2(100.f, 1200.f));
			pGroundSwordAppearSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	}
}

void CSpikeEffect::update_animation()
{
	if (m_eCurState == SPIKE_STATE::SPIKE_EFFECT_ANTICIPATE)
	{
		GetAnimator()->Play(L"SPIKE_EFFECT_ANTICIPATE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SPIKE_EFFECT_ANTICIPATE", 0);
				m_eCurState = SPIKE_STATE::SPIKE_EFFECT_ATTACK;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}


	if (m_eCurState == SPIKE_STATE::SPIKE_EFFECT_ATTACK)
	{

		GetAnimator()->Play(L"SPIKE_EFFECT_ATTACK", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SPIKE_EFFECT_ATTACK", 0);
				m_bSoundPlayed = false;
				DeleteObject(this);
			}
		}
	}

}
