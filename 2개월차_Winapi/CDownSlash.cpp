#include "pch.h"
#include "CDownSlash.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CSound.h"
#include "CPlayerMgr.h"
#include "CSlashHitEffect.h"

CDownSlash::CDownSlash()
	:m_iCount(0)
{
	CreateCollider();
	CreateAnimator();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, +30.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));
	CTexture* m_pDownSlashEffectTex = CResMgr::GenInst()->LoadTexture(L"Down_Slash_Effect", L"texture\\Player\\DownSlashEffect.bmp");

	GetAnimator()->CreateAnimation(L"SLASH_DOWN_EFFECT", m_pDownSlashEffectTex, Vec2(0.f, 0.f), Vec2(162.f, 162.f), Vec2(162.f, 0.f), 0.05f, 6);
}

CDownSlash::~CDownSlash()
{
}

void CDownSlash::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == _pOther->GetObj()->GetName())
	{
		CreateHitEffect();
		CPlayerMgr::GenInst()->SetGroundHit(true);
		CResMgr::GenInst()->LoadSound(L"Reject_WallorGround", L"sound\\Player\\sword_hit_reject.wav");
		
		CSound* pWallorGroundRejectSound = CResMgr::GenInst()->FindSound(L"Reject_WallorGround");
		pWallorGroundRejectSound->SetVolume(85.f);
		pWallorGroundRejectSound->Play(false);
	}
}

void CDownSlash::update()
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

void CDownSlash::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CDownSlash::update_state()
{
}

void CDownSlash::update_animation()
{
	GetAnimator()->Play(L"SLASH_DOWN_EFFECT", true);
}

void CDownSlash::CreateHitEffect()
{
	CSlashHitEffect* pDown_Slash_Hit_Effect = new CSlashHitEffect;

	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 

	pDown_Slash_Hit_Effect->SetPos(Vec2(GetPos().x,GetPos().y+30.f)); // 좌표 받아옴
	

	CreateObject(pDown_Slash_Hit_Effect, GROUP_TYPE::SKILLEFFECT);
}
