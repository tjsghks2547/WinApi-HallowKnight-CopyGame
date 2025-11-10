#include "pch.h"
#include "CMushRoom.h"
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

CMushRoom::CMushRoom()
	:m_iHP(3)
	, m_iDir(-1)
	, m_iCount(0)
	, m_eCurState(MON_STATE::WALK)
	, m_ePreState(MON_STATE::WALK)
	, m_fDistance(200.f)
	, m_fMoveDistance(0.f)
{
	CreateCollider();
	CreateAnimator();

	CreateRigidBody();
	CreateGravity();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, -15.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	//애니메이션  코드 
	CTexture* m_pMushRoomWalkLeftTex  = CResMgr::GenInst()->LoadTexture(L"MushRoomWalk_Left", L"texture\\Monster\\Mushroom_Walk_Left.bmp");
	CTexture* m_pMushRoomWalkRightTex = CResMgr::GenInst()->LoadTexture(L"MushRoomWalk_Right", L"texture\\Monster\\Mushroom_Walk_Right.bmp");

	CTexture* m_pMushRoomTurnLeftTex = CResMgr::GenInst()->LoadTexture(L"MushRoomTurn_Left", L"texture\\Monster\\Mushroom_Turn_Left.bmp");
	CTexture* m_pMushRoomTurnRightTex = CResMgr::GenInst()->LoadTexture(L"MushRoomTurn_Right", L"texture\\Monster\\Mushroom_Turn_Right.bmp");

	CTexture* m_pMushRoomDeadLeftTex  = CResMgr::GenInst()->LoadTexture(L"MushRoomDead_Left", L"texture\\Monster\\MushRoom_Dead_Left.bmp");
	CTexture* m_pMushRoomDeadRightTex = CResMgr::GenInst()->LoadTexture(L"MushRoomDead_Right", L"texture\\Monster\\MushRoom_Dead_Right.bmp");

	GetAnimator()->CreateAnimation(L"WALK_LEFT_MUSHROOM",  m_pMushRoomWalkLeftTex,  Vec2(0.f, 0.f), Vec2(127.f, 114.f), Vec2(127.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT_MUSHROOM", m_pMushRoomWalkRightTex, Vec2(381.f, 0.f), Vec2(127.f, 114.f), Vec2(-127.f, 0.f), 0.3f, 4);

	GetAnimator()->CreateAnimation(L"TURN_LEFT_MUSHROOM",  m_pMushRoomTurnLeftTex  , Vec2(0.f, 0.f), Vec2(121.5f, 108.f), Vec2(121.5f, 0.f), 0.3f, 2);
	GetAnimator()->CreateAnimation(L"TURN_RIGHT_MUSHROOM", m_pMushRoomTurnRightTex , Vec2(121.5f, 0.f), Vec2(121.5f, 108.f), Vec2(-121.5f, 0.f), 0.3f, 2);

	GetAnimator()->CreateAnimation(L"Dead_LEFT_MUSHROOM",  m_pMushRoomDeadLeftTex, Vec2(306.f, 0.f), Vec2(153.5f, 114.f), Vec2(153.5f, 0.f), 0.3f, 2);
	GetAnimator()->CreateAnimation(L"Dead_RIGHT_MUSHROOM", m_pMushRoomDeadRightTex, Vec2(0.f, 0.f), Vec2(153.f, 114.f), Vec2(153.f, 0.f), 0.3f, 2);

	CResMgr::GenInst()->LoadSound(L"Enemy_Damage4", L"sound\\enemy_damage.wav");
	CResMgr::GenInst()->LoadSound(L"Enemy_Death4", L"sound\\enemy_death_sword.wav");

}

CMushRoom::~CMushRoom()
{

}

void CMushRoom::update()
{
	update_move();

	update_state();


	update_animation();

	update_sound();



	m_ePreState = m_eCurState;

}

void CMushRoom::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}



void CMushRoom::update_move()
{
	Vec2 vPos = GetPos();


	if (vPos.x - 250 < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.y + 50 > CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& vPos.y - 50 < CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& (m_eCurState == MON_STATE::IDLE || m_eCurState == MON_STATE::WALK
			|| m_eCurState == MON_STATE::TURN || m_eCurState == MON_STATE::ATTACK)
		)
	{
		if (m_eCurState != MON_STATE::DEAD)
		{
			m_iDir = -1;

			if(m_eCurState != MON_STATE::ATTACK)
			m_eCurState = MON_STATE::ATTACK;
			


		}
	}

	else if (vPos.x + 250 > CPlayerMgr::GenInst()->GetCurPlayerPos().x
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
			m_eCurState = MON_STATE::ATTACK;
			

		}
	}

	//WALK 부분 이동관련 코드 
	if (m_iDir == -1 && (m_eCurState == MON_STATE::WALK))
	{
		if (m_fMoveDistance > m_fDistance)
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

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::WALK))
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

void CMushRoom::update_state()
{
}

void CMushRoom::update_animation()
{
	//WALK
	// ===========================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::WALK))
	{
		GetAnimator()->Play(L"WALK_LEFT_MUSHROOM", true);
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::WALK))
	{
		GetAnimator()->Play(L"WALK_RIGHT_MUSHROOM", true);
	}

	//TURN
	//======================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::TURN))
	{
		GetAnimator()->Play(L"TURN_RIGHT_MUSHROOM", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"TURN_RIGHT_MUSHROOM", 0);

			m_eCurState = MON_STATE::WALK;
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::TURN))
	{
		GetAnimator()->Play(L"TURN_LEFT_MUSHROOM", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"TURN_LEFT_MUSHROOM", 0);

			m_eCurState = MON_STATE::WALK;
		}
	}

	// 여기가 공격 시작 부분 
	// 
	// ATTACK ANTICIPATE
	// ===========================================================

	// ATTACK
	// ===========================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::ATTACK))
	{
		GetAnimator()->Play(L"WALK_LEFT_MUSHROOM", true);
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::ATTACK))
	{
		GetAnimator()->Play(L"WALK_RIGHT_MUSHROOM", true);
	}


	// DEAD
	// ===========================================================
	if (m_iDir == -1 && (m_eCurState == MON_STATE::DEAD))
	{
		GetAnimator()->Play(L"Dead_LEFT_MUSHROOM", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			Create_item();
			DeleteObject(this);
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::DEAD))
	{
		GetAnimator()->Play(L"Dead_RIGHT_MUSHROOM", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			Create_item();
			DeleteObject(this);
		}
	}
}

void CMushRoom::update_sound()
{
}


void CMushRoom::OnCollision(CCollider* _pOther)
{
}

void CMushRoom::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pDamagedSound2 = CResMgr::GenInst()->FindSound(L"Enemy_Damage4");
	CSound* pDeathSound2 = CResMgr::GenInst()->FindSound(L"Enemy_Death4");

	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"SLASH"
		|| pOtherObj->GetName() == L"DOWN_SLASH_Effect")
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
				GetAnimator()->Play(L"Dead_LEFT_MUSHROOM", false);
				pDeathSound2->Play(false);
				break;

			case -1:

				GetAnimator()->Play(L"Dead_RIGHT_MUSHROOM", false);
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
				GetAnimator()->Play(L"Dead_LEFT_MUSHROOM", false);
				pDeathSound2->Play(false);
				break;

			case -1:

				GetAnimator()->Play(L"Dead_RIGHT_MUSHROOM", false);
				pDeathSound2->Play(false);
				break;
			}

		}
	}
}

void CMushRoom::OnCollisionExit(CCollider* _pOther)
{
}

void CMushRoom::Create_item()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // 몬스터의 좌표 받아옴
	pitem->SetName(L"Item_Geo");

	CreateObject(pitem, GROUP_TYPE::ITEM);
}