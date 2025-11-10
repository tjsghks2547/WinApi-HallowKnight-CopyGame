#include "pch.h"
#include "CFlyBug.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CItem.h"
#include "CSound.h"


CFlyBug::CFlyBug()
	: m_iHP(2)
	, m_iDir(-1)
	, m_iCount(0)
	, m_eCurState(MON_STATE::IDLE)
	, m_ePreState(MON_STATE::IDLE)
{
	CreateCollider();
	CreateAnimator();
	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	//애니메이션 원래 코드 
	CTexture* m_pFlyBugLeftTex = CResMgr::GenInst()->LoadTexture(L"FlyBuglLeft", L"texture\\Monster\\FlyBug_Left2.bmp");
	CTexture* m_pFlyBugRightTex = CResMgr::GenInst()->LoadTexture(L"FlyBugRight", L"texture\\Monster\\FlyBug_Right2.bmp");

	//IDLE
	GetAnimator()->CreateAnimation(L"IDLE_LEFT_FLYBUG", m_pFlyBugLeftTex, Vec2(0.f, 0.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.2f, 5);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT_FLYBUG", m_pFlyBugRightTex, Vec2(0.f, 0.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.2f, 5);

	//Conigition
	GetAnimator()->CreateAnimation(L"CONIGITION_LEFT_FLYBUG", m_pFlyBugLeftTex, Vec2(0.f, 300.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"CONIGITION_RIGHT_FLYBUG", m_pFlyBugRightTex, Vec2(0.f, 300.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.1f, 5);

	//Chase
	GetAnimator()->CreateAnimation(L"CHASE_LEFT_FLYBUG", m_pFlyBugLeftTex, Vec2(0.f, 450.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.2f, 5);
	GetAnimator()->CreateAnimation(L"CHASE_RIGHT_FLYBUG", m_pFlyBugRightTex, Vec2(0.f, 450.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.2f, 5);
	
	//DEAD
	GetAnimator()->CreateAnimation(L"DEAD_LEFT_FLYBUG", m_pFlyBugLeftTex, Vec2(0.f, 600.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"DEAD_RIGHT_FLYBUG", m_pFlyBugRightTex, Vec2(200.f, 600.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), 0.1f, 4);

	//사운드
	CResMgr::GenInst()->LoadSound(L"Enemy_Damage3", L"sound\\enemy_damage.wav");
	CResMgr::GenInst()->LoadSound(L"Enemy_Death3", L"sound\\enemy_death_sword.wav");
	CResMgr::GenInst()->LoadSound(L"FlyBug_Fly", L"sound\\fly_flying.wav");
}

CFlyBug::~CFlyBug()
{
}
void CFlyBug::update()
{
	update_move();

	update_state();

	update_animation();

}

void CFlyBug::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}


void CFlyBug::update_move()
{
	//타겟팅 된 Player를 쫓아간다.
	Vec2 vPlayerPos = CPlayerMgr::GenInst()->GetCurPlayerPos();
	Vec2 vPos = GetPos();
	
	if (vPos.x - 400 < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.y + 400 > CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& vPos.y - 400 < CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& m_eCurState == MON_STATE::IDLE)
	{
		if (m_eCurState != MON_STATE::DEAD)
		{
			m_iDir = -1;
			CSound* pFlySound = CResMgr::GenInst()->FindSound(L"FlyBug_Fly");
			pFlySound->SetVolume(85.f);
			pFlySound->Play(false);

			m_eCurState = MON_STATE::STARTLE;

		}
	}

	else if (vPos.x + 400 > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.y + 400 > CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& vPos.y - 400 < CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& m_eCurState == MON_STATE::IDLE)
	{
		if (m_eCurState != MON_STATE::DEAD)
		{
			m_iDir = 1;
			CSound* pFlySound = CResMgr::GenInst()->FindSound(L"FlyBug_Fly");
			pFlySound->Play(false);
		
			m_eCurState = MON_STATE::STARTLE;
		}
	}

	

	if(m_eCurState == MON_STATE::TRACE)
	{
		
		Vec2 vitemDir = vPlayerPos - vPos; // 방향벡터 구하기 

		if (vitemDir != Vec2(0.f, 0.f))
		{
			vitemDir.Normalize(); // 방향벡터를 단위벡터로 나타냄
		}

		vPos += vitemDir * 250.f * fDT;
	}

	

	m_ePreState = m_eCurState;

	SetPos(vPos);
}

void CFlyBug::update_state()
{

}

void CFlyBug::update_animation()
{
	if (m_iDir == -1 && (m_eCurState == MON_STATE::IDLE))
	{
		GetAnimator()->Play(L"IDLE_LEFT_FLYBUG", true);

	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::IDLE))
	{
		GetAnimator()->Play(L"IDLE_RIGHT_FLYBUG", true);
	}

	// 여기가 공격 시작 부분 
	if (m_iDir == -1 && (m_eCurState == MON_STATE::STARTLE))
	{
		GetAnimator()->Play(L"CONIGITION_LEFT_FLYBUG", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"CONIGITION_LEFT_FLYBUG", 0);
				m_eCurState = MON_STATE::TRACE;
			}
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::STARTLE))
	{
		GetAnimator()->Play(L"CONIGITION_RIGHT_FLYBUG", false);

		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"CONIGITION_RIGHT_FLYBUG", 0);
			m_eCurState = MON_STATE::TRACE;
		}
		//GetAnimator()->GetAnimation()->IsFinish();
	}

	if (m_iDir == -1 && (m_eCurState == MON_STATE::TRACE))
	{
		GetAnimator()->Play(L"CHASE_LEFT_FLYBUG", true);
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::TRACE))
	{
		GetAnimator()->Play(L"CHASE_RIGHT_FLYBUG", true);

	}


	if (m_iDir == -1 && (m_eCurState == MON_STATE::DEAD))
	{
		GetAnimator()->Play(L"DEAD_LEFT_FLYBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			Create_item();
			DeleteObject(this);
			
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::DEAD))
	{
		GetAnimator()->Play(L"DEAD_RIGHT_FLYBUG", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			Create_item();
			DeleteObject(this);

		}

	}


}


void CFlyBug::OnCollision(CCollider* _pOther)
{
}

void CFlyBug::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pDamagedSound2 = CResMgr::GenInst()->FindSound(L"Enemy_Damage3");
	CSound* pDeathSound2 = CResMgr::GenInst()->FindSound(L"Enemy_Death3");

	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"SLASH"
		|| pOtherObj->GetName() == L"UP_SLASH_Effect")
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
				GetAnimator()->Play(L"DEAD_LEFT_FLYBUG", false);
				pDeathSound2->Play(false);
				break;

			case -1:

				GetAnimator()->Play(L"DEAD_RIGHT_FLYBUG", false);
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
				GetAnimator()->Play(L"DEAD_LEFT_FLYBUG", false);
				pDeathSound2->Play(false);
				break;

			case -1:

				GetAnimator()->Play(L"DEAD_RIGHT_FLYBUG", false);
				pDeathSound2->Play(false);
				break;
			}

		}
	}
}

void CFlyBug::OnCollisionExit(CCollider* _pOther)
{
}


void CFlyBug::Create_item()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // 몬스터의 좌표 받아옴
	pitem->SetName(L"Item_Geo");

	CreateObject(pitem, GROUP_TYPE::ITEM);
}
