#include "pch.h"
#include "CSLASH.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CSlashHitEffect.h"


CSLASH::CSLASH()
	:m_iDir(1)
	,m_iPrevDir(1)
	,i_Count(0)
{

	CreateCollider();
	CreateAnimator();
	
	//충돌체 크기조정
	GetCollider()->SetScale(Vec2(100.f, 80.f));
	
	//애니메이션 원래 코드 
	CTexture* m_pSlashEffectText = CResMgr::GenInst()->LoadTexture(L"PlayerSlashEffect", L"texture\\Player\\New_Slash4.bmp");
	

	//GetAnimator()->CreateAnimation(L"SLASH_LEFT_EFFECT", m_pSlashEffectText, Vec2(0.f, 0.f), Vec2(151.f, 129.f), Vec2(151.f, 0.f), 0.2f, 2);
	//GetAnimator()->CreateAnimation(L"SLASH_RIGHT_EFFECT", m_pSlashEffectText, Vec2(0.f, 129.f), Vec2(151.f, 129.f), Vec2(151.f, 0.f), 0.2f, 2);
	//GetAnimator()->CreateAnimation(L"SLASH_LEFT_EFFECT", m_pSlashEffectText, Vec2(0.f, 0.f), Vec2(220.f, 110.f), Vec2(220.f, 0.f), 0.025f, 6);
	//GetAnimator()->CreateAnimation(L"SLASH_RIGHT_EFFECT", m_pSlashEffectText, Vec2(0.f, 110.f), Vec2(220.f, 110.f), Vec2(220.f, 0.f), 0.025f, 6);

	GetAnimator()->CreateAnimation(L"SLASH_LEFT_EFFECT", m_pSlashEffectText, Vec2(0.f, 0.f), Vec2(349.f, 186.f), Vec2(349.f, 0.f), 0.025f, 6);
	GetAnimator()->CreateAnimation(L"SLASH_RIGHT_EFFECT", m_pSlashEffectText, Vec2(0.f, 186.f), Vec2(349.f, 186.f), Vec2(349.f, 0.f), 0.025f, 6);
	
}

CSLASH::~CSLASH()
{
}

void CSLASH::update()
{
	update_state();
	update_animation();
	

	//아 이게 애니메이션의 주기가 빠르게 도니깐 델타타임보다 그래서 그런듯  (진짜임;; 0.05F 에서 5F로 바꾸니깐 여러번 돌아버림)
	if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
	{
		i_Count++;
		if (i_Count < 2)
		{
			DeleteObject(this);
		}
	}
}

void CSLASH::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}



void CSLASH::update_state()
{

	
}

void CSLASH::update_animation()
{
	if (m_iDir == -1)
	{
		GetCollider()->SetOffsetPos(Vec2(-70.f, 15.f));
		GetAnimator()->Play(L"SLASH_LEFT_EFFECT", false);
	}
	else
	{
		GetCollider()->SetOffsetPos(Vec2(-50.f, 15.f));
		GetAnimator()->Play(L"SLASH_RIGHT_EFFECT", false);
	}
	

}



void CSLASH::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Beetle" 
		|| pOtherObj->GetName() == L"FalseKnight"
		|| pOtherObj->GetName() == L"Hornet"
		|| pOtherObj->GetName() == L"Pure_Vessel"
		|| pOtherObj->GetName() == L"MushRoom"
		|| pOtherObj->GetName() == L"Crawl"
		|| pOtherObj->GetName() == L"Fly_Bug")
	{
		CreateHitEffect();
	}
}

void CSLASH::CreateHitEffect()
{
	CSlashHitEffect* pSlash_Hit_Effect = new CSlashHitEffect;

	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 
	pSlash_Hit_Effect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pSlash_Hit_Effect->SetPos(GetPos()); // 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pSlash_Hit_Effect->SetPos(GetPos());
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pSlash_Hit_Effect->SetName(L"SLASH_HIT_EFFECT");

	CreateObject(pSlash_Hit_Effect, GROUP_TYPE::SKILLEFFECT);

}
