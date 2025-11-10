#include "pch.h"
#include "CBeetle_New.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CItem.h"
#include "CSound.h"




CBeetle_New::CBeetle_New()
	:m_iHP(5)
	,m_iDir(0)
	,m_iCount(0)
	,m_eCurState(MON_STATE::IDLE)
	,m_ePreState(MON_STATE::IDLE)
{
	CreateCollider();
	CreateAnimator();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(-25.f, 20.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	//애니메이션 원래 코드 
	CTexture* m_pIdileTex2 = CResMgr::GenInst()->LoadTexture(L"MonsterIdle", L"texture\\beetle\\idle_3.bmp");
	CTexture* m_pRushTex = CResMgr::GenInst()->LoadTexture(L"BeetleRush", L"texture\\beetle\\attackinit_plz22.bmp");
	CTexture* m_pAttackTex = CResMgr::GenInst()->LoadTexture(L"BeetleAttack", L"texture\\beetle\\attackwhy.bmp");
	CTexture* m_pDeadTex = CResMgr::GenInst()->LoadTexture(L"BeetleDead", L"texture\\beetle\\death_real.bmp");
	

	GetAnimator()->CreateAnimation(L"Idle_LEFT_BEETLE", m_pIdileTex2, Vec2(0.f, 0.f), Vec2(118.f, 192.f), Vec2(118.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"Idle_RIGHT_BEETLE", m_pIdileTex2, Vec2(0.f, 192.f), Vec2(118.f, 192.f), Vec2(118.f, 0.f), 0.2f, 4);

	GetAnimator()->CreateAnimation(L"BeetleLeftAttack", m_pRushTex, Vec2(0.f, 0.f), Vec2(171.f, 190.f), Vec2(171.f, 0.f), 0.5f, 5);
	GetAnimator()->CreateAnimation(L"BeetleRightAttack", m_pRushTex, Vec2(0.f, 190.f), Vec2(171.f, 190.f), Vec2(171.f, 0.f), 0.5f, 5);

	GetAnimator()->CreateAnimation(L"BeetleLeftRush", m_pAttackTex, Vec2(0.f, 0.f), Vec2(200.f, 120.f), Vec2(200.f, 0.f), 0.5f, 4);
	GetAnimator()->CreateAnimation(L"BeetleRightRush", m_pAttackTex, Vec2(0.f, 120.f), Vec2(200.f, 120.f), Vec2(200.f, 0.f), 0.5f, 4);

	GetAnimator()->CreateAnimation(L"BeetleLeftDead", m_pDeadTex, Vec2(190.f, 0.f), Vec2(190.f, 131.f), Vec2(190.f, 0.f), 0.2f, 8);
	GetAnimator()->CreateAnimation(L"BeetleRightDead", m_pDeadTex, Vec2(190.f, 131.f), Vec2(190.f, 131.f), Vec2(190.f, 0.f), 0.2f, 8);
	GetAnimator()->Play(L"Idle_LEFT_BEETLE", true);

	//사운드 부분 
	CResMgr::GenInst()->LoadSound(L"Enemy_Damage", L"sound\\enemy_damage.wav");
	CResMgr::GenInst()->LoadSound(L"Enemy_Death", L"sound\\enemy_death_sword.wav");

}

CBeetle_New::~CBeetle_New()
{

}

void CBeetle_New::update()
{


	update_move();

	update_state();

	update_animation();

	if (GetAnimator()->GetAnimation()->IsFinish())
	{
		Create_item();
		DeleteObject(this);
	
	}

}

void CBeetle_New::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}



void CBeetle_New::OnCollision(CCollider* _pOther)
{
}

void CBeetle_New::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pDamagedSound = CResMgr::GenInst()->FindSound(L"Enemy_Damage");
	CSound* pDeathSound = CResMgr::GenInst()->FindSound(L"Enemy_Death");

	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"SLASH"
		|| pOtherObj->GetName() == L"DOWN_SLASH_Effect")
	{
		m_iHP--;
		pDamagedSound->Play(false);

		if(CPlayerMgr::GenInst()->GetPlayerMp()<6)
		{
			CPlayerMgr::GenInst()->IncreaseMp(1);
		}
		

		Vec2 vPos = GetPos();
		switch (m_iDir)
		{
		case 1:
			vPos.x -= 100.f;
			break;

		case -1:

			vPos.x += 100.f;
			break;
		}
		
		SetPos(vPos);

		if (m_iHP < 1)
		{
			m_eCurState = MON_STATE::DEAD;
			
			
			switch (m_iDir)
			{
			case 1:
				GetAnimator()->Play(L"BeetleLeftDead", false);
				pDeathSound->Play(false);
				break;

			case -1:
				
				GetAnimator()->Play(L"BeetleRightDead", false);
				pDeathSound->Play(false);
				break;
			}

		}
	}


	if (pOtherObj->GetName() == L"FireBall")
	{
		m_iHP--;
		pDamagedSound->Play(false);
		DeleteObject(pOtherObj);

		Vec2 vPos = GetPos();
		switch (m_iDir)
		{
		case 1:
			vPos.x -= 100.f;
			break;

		case -1:

			vPos.x += 100.f;
			break;
		}

		SetPos(vPos);

		if (m_iHP < 1)
		{
			m_eCurState = MON_STATE::DEAD;

			switch (m_iDir)
			{
			case 1:
				GetAnimator()->Play(L"BeetleLeftDead", false);
				pDeathSound->Play(false);
				break;

			case -1:

				GetAnimator()->Play(L"BeetleRightDead", false);
				pDeathSound->Play(false);
				break;
			}

		}
	}
}

void CBeetle_New::OnCollisionExit(CCollider* _pOther)
{
}

void CBeetle_New::update_move()
{

	Vec2 vPos = GetPos();

	if (vPos.x - 400 < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.y + 50 > CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& vPos.y - 50 < CPlayerMgr::GenInst()->GetCurPlayerPos().y)
	{
		if (m_eCurState != MON_STATE::DEAD)
		{
			m_iDir = -1;
			if (m_eCurState != MON_STATE::RUSH)
			{
				m_eCurState = MON_STATE::ATTACK;
			}

			if (m_eCurState == MON_STATE::ATTACK || m_eCurState == MON_STATE::IDLE)
			{
				vPos.x -= 100 * fDT;
			}

			if(m_eCurState == MON_STATE::RUSH)
			{
				vPos.x -= 250 * fDT;
			}
			
		}
	}

	else if (vPos.x + 400 > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.y + 50 > CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& vPos.y - 50 < CPlayerMgr::GenInst()->GetCurPlayerPos().y)
	{
		if (m_eCurState != MON_STATE::DEAD)
		{
			m_iDir = 1;
			if(m_eCurState!=MON_STATE::RUSH)
			{
				m_eCurState = MON_STATE::ATTACK;
			}
			
			if (m_eCurState == MON_STATE::ATTACK || m_eCurState == MON_STATE::IDLE)
			{
				vPos.x += 100 * fDT;
			}

			if (m_eCurState == MON_STATE::RUSH)
			{
				vPos.x += 250 * fDT;
			}
		}
	}

	else
	{
		if (m_eCurState != MON_STATE::DEAD)
		{
			m_eCurState = MON_STATE::IDLE;
		}
	}

	m_ePreState = m_eCurState;

	SetPos(vPos);
}

void CBeetle_New::update_state()
{

}

void CBeetle_New::update_animation()
{

	// 여기가 공격 시작 부분 
	if (m_iDir == -1 && (m_eCurState == MON_STATE::ATTACK||m_eCurState == MON_STATE::RUSH))
	{
		GetAnimator()->Play(L"BeetleRightAttack", false);
		{
			if(GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->Play(L"BeetleRightRush", true);
				m_eCurState = MON_STATE::RUSH;

			}
		}
	}

	else if(m_iDir == 1 && (m_eCurState == MON_STATE::ATTACK || m_eCurState == MON_STATE::RUSH))
	{
		GetAnimator()->Play(L"BeetleLeftAttack", false);

		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->Play(L"BeetleLeftRush", true);
			m_eCurState = MON_STATE::RUSH;
		}
		//GetAnimator()->GetAnimation()->IsFinish();
	}





	if(m_iDir == 1 && m_eCurState == MON_STATE::IDLE)
	{
		GetAnimator()->Play(L"Idle_LEFT_BEETLE", true);
	}

	else if (m_iDir == -1 && m_eCurState == MON_STATE::IDLE)
	{
		GetAnimator()->Play(L"Idle_RIGHT_BEETLE", true);
	}

}

void CBeetle_New::Create_item()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // 몬스터의 좌표 받아옴
	pitem->SetName(L"Item_Geo");

	CreateObject(pitem, GROUP_TYPE::ITEM);
}
