#include "pch.h"
#include "CDashBug.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CItem.h"
#include "CSound.h"
#include "CRigidBody.h"
#include "CGravity.h"


CDashBug::CDashBug()
	:m_iHP(2)
	,m_iDir(-1)
	,m_iCount(0)
	,m_eCurState(MON_STATE::IDLE)
	,m_ePreState(MON_STATE::IDLE)
	,m_fDistance(300.f)
	,m_fMoveDistance(0.f)
{
	CreateCollider();
	CreateAnimator();

	CreateRigidBody();
	CreateGravity();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, -15.f));
	GetCollider()->SetScale(Vec2(50.f, 35.f));

	//애니메이션  코드 
	CTexture* m_pDashBugLeftTex = CResMgr::GenInst()->LoadTexture(L"DashBugLeft", L"texture\\Monster\\DashBug_LEFT.bmp");
	CTexture* m_pDashBugRightTex = CResMgr::GenInst()->LoadTexture(L"DashBugRight", L"texture\\Monster\\DashBug_Right.bmp");

	//IDLE
	GetAnimator()->CreateAnimation(L"IDLE_LEFT_DASHBUG", m_pDashBugLeftTex, Vec2(0.f, 0.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.15f, 5);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT_DASHBUG", m_pDashBugRightTex, Vec2(0.f, 0.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.15f, 5);

	//WALK
	GetAnimator()->CreateAnimation(L"WALK_LEFT_DASHBUG", m_pDashBugLeftTex, Vec2(0.f, 150.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.3f, 5);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT_DASHBUG", m_pDashBugRightTex, Vec2(0.f, 150.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.3f, 5);

	//TURN
	GetAnimator()->CreateAnimation(L"TURN_RIGHT_DASHBUG", m_pDashBugLeftTex, Vec2(0.f, 300.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"TURN_LEFT_DASHBUG", m_pDashBugRightTex, Vec2(800.f, 300.f), Vec2(200.f, 150.f), Vec2(-200.f, 0.f), 0.1f, 5);

	//ATTACK ANTICIPATE
	GetAnimator()->CreateAnimation(L"ATTACK_ANTICIPATE_LEFT_DASHBUG",  m_pDashBugLeftTex, Vec2(0.f, 450.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.15f, 5);
	GetAnimator()->CreateAnimation(L"ATTACK_ANTICIPATE_RIGHT_DASHBUG", m_pDashBugRightTex, Vec2(0.f, 450.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.15f, 5);

	//ATTACK 
	GetAnimator()->CreateAnimation(L"ATTACK_LEFT_DASHBUG", m_pDashBugLeftTex, Vec2(0.f, 600.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.15f, 5);
	GetAnimator()->CreateAnimation(L"ATTACK_RIGHT_DASHBUG", m_pDashBugRightTex, Vec2(0.f, 600.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.15f, 5);

	//DEAD
	GetAnimator()->CreateAnimation(L"DEAD_LEFT_DASHBUG", m_pDashBugLeftTex, Vec2(0.f, 750.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"DEAD_RIGHT_DASHBUG", m_pDashBugRightTex, Vec2(0.f, 750.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.1f, 5);

	//SOUND
	CResMgr::GenInst()->LoadSound(L"Enemy_Damage3", L"sound\\enemy_damage.wav");
	CResMgr::GenInst()->LoadSound(L"Enemy_Death3", L"sound\\enemy_death_sword.wav");

	CResMgr::GenInst()->LoadSound(L"Dash_Bug_startle", L"sound\\DashBugAttack.wav");
	CResMgr::GenInst()->LoadSound(L"Dash_Bug_Run_Sound", L"sound\\moss_walker_footstep_loop.wav");

}

CDashBug::~CDashBug()
{

}

void CDashBug::update()
{
	update_move();

	update_state();


	update_animation();

	update_sound();

	

	m_ePreState = m_eCurState;

}


void CDashBug::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CDashBug::update_move()
{
	Vec2 vPos = GetPos();

	
	if (vPos.x - 500 < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.y + 50 > CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& vPos.y - 50 < CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& (m_eCurState == MON_STATE::IDLE || m_eCurState == MON_STATE::WALK
		|| m_eCurState == MON_STATE::TURN  || m_eCurState == MON_STATE::ATTACK)
		)
	{
		if (m_eCurState != MON_STATE::DEAD)
		{
			m_iDir = -1;

			if(m_eCurState != MON_STATE::ATTACK)
			{
				m_eCurState = MON_STATE::ATTACK_ANTICIAPTE;
			}
			
			
		}
	}

	else if (vPos.x + 500 > CPlayerMgr::GenInst()->GetCurPlayerPos().x
			 && vPos.x < CPlayerMgr::GenInst()->GetCurPlayerPos().x
			 && vPos.y + 50 > CPlayerMgr::GenInst()->GetCurPlayerPos().y
			 && vPos.y - 50 < CPlayerMgr::GenInst()->GetCurPlayerPos().y
			 && (m_eCurState == MON_STATE::IDLE || m_eCurState == MON_STATE::WALK
			  || m_eCurState == MON_STATE::TURN || m_eCurState == MON_STATE::ATTACK)
		      )
	 {
		 if (m_eCurState != MON_STATE::DEAD)
		 {
			m_iDir = 1;
			
			if (m_eCurState != MON_STATE::ATTACK)
			{
				m_eCurState = MON_STATE::ATTACK_ANTICIAPTE;
			}

		 }
	 }

	//WALK 부분 이동관련 코드 
	if (m_iDir == -1 && (m_eCurState == MON_STATE::WALK))
	{
		if(m_fMoveDistance > m_fDistance)
		{
			m_iDir = 1; 
			m_fMoveDistance = 0.f;
			m_eCurState = MON_STATE::TURN;
		}

		else
		{
			vPos.x -= 100.f * fDT;
			m_fMoveDistance += 100 * fDT;
		}
	}

	else if(m_iDir == 1 && (m_eCurState == MON_STATE::WALK))
	{
		if (m_fMoveDistance > m_fDistance)
		{
			m_iDir = -1;
			m_fMoveDistance = 0.f;
			m_eCurState = MON_STATE::TURN;
		}

		else
		{
			vPos.x += 100.f * fDT;
			m_fMoveDistance += 100 * fDT;
		}
	}


	//ATTACK 부분 

	if (m_iDir == -1 && (m_eCurState == MON_STATE::ATTACK))
	{
		vPos.x -= 300 * fDT; 
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::ATTACK))
	{
		vPos.x += 300 * fDT;
	}


	

	SetPos(vPos);
}

void CDashBug::update_state()
{

}

void CDashBug::update_animation()
{
	// IDLE
	// ===========================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::IDLE))
	{
		GetAnimator()->Play(L"IDLE_LEFT_DASHBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"IDLE_LEFT_DASHBUG", 0);
			m_eCurState = MON_STATE::WALK;
		}

	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::IDLE))
	{
		GetAnimator()->Play(L"IDLE_RIGHT_DASHBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"IDLE_RIGHT_DASHBUG", 0);
			m_eCurState = MON_STATE::WALK;
		}

	}

	//WALK
	// ===========================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::WALK))
	{
		GetAnimator()->Play(L"WALK_LEFT_DASHBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"WALK_LEFT_DASHBUG", 0);
			m_eCurState = MON_STATE::IDLE;
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::WALK))
	{
		GetAnimator()->Play(L"WALK_RIGHT_DASHBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"WALK_RIGHT_DASHBUG", 0);
			m_eCurState = MON_STATE::IDLE;
		}
	}

	//TURN
	//======================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::TURN))
	{
		GetAnimator()->Play(L"TURN_RIGHT_DASHBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"TURN_RIGHT_DASHBUG", 0);
		
			m_eCurState = MON_STATE::IDLE;
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::TURN))
	{
		GetAnimator()->Play(L"TURN_LEFT_DASHBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"TURN_LEFT_DASHBUG", 0);
		
			m_eCurState = MON_STATE::IDLE;
		}
	}

	// 여기가 공격 시작 부분 
	// 
	// ATTACK ANTICIPATE
	// ===========================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::ATTACK_ANTICIAPTE))
	{
		GetAnimator()->Play(L"ATTACK_ANTICIPATE_LEFT_DASHBUG", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"ATTACK_ANTICIPATE_LEFT_DASHBUG", 0);
				m_eCurState = MON_STATE::ATTACK;
			}
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::ATTACK_ANTICIAPTE))
	{
		GetAnimator()->Play(L"ATTACK_ANTICIPATE_RIGHT_DASHBUG", false);

		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"ATTACK_ANTICIPATE_RIGHT_DASHBUG", 0);
			m_eCurState = MON_STATE::ATTACK;
		}
		//GetAnimator()->GetAnimation()->IsFinish();
	}

	// ATTACK
	// ===========================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::ATTACK))
	{
		GetAnimator()->Play(L"ATTACK_LEFT_DASHBUG", true);
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::ATTACK))
	{
		GetAnimator()->Play(L"ATTACK_RIGHT_DASHBUG", true);
	}


	// DEAD
	// ===========================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::DEAD))
	{
		GetAnimator()->Play(L"DEAD_LEFT_DASHBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			Create_item();
			DeleteObject(this);
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::DEAD))
	{
		GetAnimator()->Play(L"DEAD_RIGHT_DASHBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			Create_item();
			DeleteObject(this);
		}
	}
}

void CDashBug::update_sound()
{
	CSound* pDashBugAttackAnticipate = CResMgr::GenInst()->FindSound(L"Dash_Bug_startle");
	CSound* pDashBugAttackWalk = CResMgr::GenInst()->FindSound(L"Dash_Bug_Run_Sound");

	switch(m_eCurState)
	{
	case MON_STATE::ATTACK_ANTICIAPTE:
		if (m_eCurState != m_ePreState)
		{
			pDashBugAttackAnticipate->Play(false);
			
		}
		break;

	case MON_STATE::ATTACK:
		if (m_eCurState != m_ePreState)
		{
			pDashBugAttackWalk->Play(false);
		}
		break;
	}
}

void CDashBug::OnCollision(CCollider* _pOther)
{

}

void CDashBug::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pDamagedSound2 = CResMgr::GenInst()->FindSound(L"Enemy_Damage3");
	CSound* pDeathSound2 = CResMgr::GenInst()->FindSound(L"Enemy_Death3");

	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"SLASH"
		||pOtherObj->GetName() ==L"DOWN_SLASH_Effect")
	{
		m_iHP--;
		pDamagedSound2->Play(false);

		if (CPlayerMgr::GenInst()->GetPlayerMp() < 6)
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
				GetAnimator()->Play(L"DEAD_LEFT_DASHBUG", false);
				pDeathSound2->Play(false);
				break;

			case -1:

				GetAnimator()->Play(L"DEAD_RIGHT_DASHBUG", false);
				pDeathSound2->Play(false);
				break;
			}

		}
	}


	if (pOtherObj->GetName() == L"FireBall")
	{
		m_iHP--;
		pDamagedSound2->Play(false);
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
				GetAnimator()->Play(L"DEAD_LEFT_DASHBUG", false);
				pDeathSound2->Play(false);
				break;

			case -1:

				GetAnimator()->Play(L"DEAD_RIGHT_DASHBUG", false);
				pDeathSound2->Play(false);
				break;
			}

		}
	}
}

void CDashBug::OnCollisionExit(CCollider* _pOther)
{

}



void CDashBug::Create_item()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // 몬스터의 좌표 받아옴
	pitem->SetName(L"Item_Geo");

	CreateObject(pitem, GROUP_TYPE::ITEM);
}
