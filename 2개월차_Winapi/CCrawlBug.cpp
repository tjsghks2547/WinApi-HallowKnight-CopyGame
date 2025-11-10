#include "pch.h"
#include "CCrawlBug.h"
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

CCrawlBug::CCrawlBug()
	:m_iHP(2)
	,m_iDir(-1)
	,m_iCount(0)
	,m_eCurState(MON_STATE::IDLE)
	,m_ePreState(MON_STATE::IDLE)
{
	CreateCollider();
	CreateAnimator();

	CreateRigidBody();
	CreateGravity();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	//애니메이션 원래 코드 
	CTexture* m_pCrawlLeftTex = CResMgr::GenInst()->LoadTexture(L"CrawlLeft", L"texture\\Monster\\CrawlBug_Left2.bmp");
	CTexture* m_pCrawlRightTex = CResMgr::GenInst()->LoadTexture(L"CrawlRight", L"texture\\Monster\\CrawlBug_Right2.bmp");


	//IDLE
	GetAnimator()->CreateAnimation(L"IDLE_LEFT_CRAWL", m_pCrawlLeftTex, Vec2(125.f, 0.f), Vec2(125.f, 125.f), Vec2(125.f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT_CRAWL", m_pCrawlRightTex, Vec2(125.f, 0.f), Vec2(125.f, 125.f), Vec2(125.f, 0.f), 0.3f, 1);

	//WALK
	GetAnimator()->CreateAnimation(L"WALK_LEFT_CRAWL", m_pCrawlLeftTex, Vec2(125.f, 0.f), Vec2(125.f, 125.f), Vec2(125.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT_CRAWL", m_pCrawlRightTex, Vec2(125.f, 0.f), Vec2(125.f, 125.f), Vec2(125.f, 0.f), 0.3f, 4);

	//DEAD
	GetAnimator()->CreateAnimation(L"DEAD_LEFT_CRAWL", m_pCrawlLeftTex, Vec2(125.f, 250.f), Vec2(125.f, 125.f), Vec2(-125.f, 0.f), 0.4f, 2);
	GetAnimator()->CreateAnimation(L"DEAD_RIGHT_CRAWL", m_pCrawlRightTex, Vec2(375.f, 250.f), Vec2(125.f, 125.f), Vec2(125.f, 0.f), 0.4f, 2);

	//사운드
	CResMgr::GenInst()->LoadSound(L"Enemy_Damage2", L"sound\\enemy_damage.wav");
	CResMgr::GenInst()->LoadSound(L"Enemy_Death2", L"sound\\enemy_death_sword.wav");
}

CCrawlBug::~CCrawlBug()
{

}

void CCrawlBug::update()
{
	update_move();

	update_state();

	update_animation();

	//if (GetAnimator()->GetAnimation()->IsFinish())
	//{
	//	//Create_item();
	//	DeleteObject(this);

	//}
}

void CCrawlBug::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}


void CCrawlBug::update_move()
{
	Vec2 vPos = GetPos();

	if (vPos.x - 400 < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.y + 50 > CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& vPos.y - 50 < CPlayerMgr::GenInst()->GetCurPlayerPos().y
		)
	{
		if (m_eCurState != MON_STATE::DEAD)
		{
			m_iDir = -1;
			
			m_eCurState = MON_STATE::WALK;

			if (m_eCurState == MON_STATE::WALK)
			{
				vPos.x -= 100 * fDT;
			}

			

		}
	}

	else if (vPos.x + 400 > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.y + 50 > CPlayerMgr::GenInst()->GetCurPlayerPos().y
		&& vPos.y - 50 < CPlayerMgr::GenInst()->GetCurPlayerPos().y
		)
	{
		if (m_eCurState != MON_STATE::DEAD)
		{
			m_iDir = 1;
			m_eCurState = MON_STATE::WALK;

			if (m_eCurState == MON_STATE::WALK)
			{
				vPos.x += 100 * fDT;
			}
		}
	}


	m_ePreState = m_eCurState;

	SetPos(vPos);
}

void CCrawlBug::update_state()
{

}

void CCrawlBug::update_animation()
{

	
	if (m_iDir == -1 && (m_eCurState == MON_STATE::IDLE))
	{
		GetAnimator()->Play(L"IDLE_LEFT_CRAWL", true);
		
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::IDLE))
	{
		GetAnimator()->Play(L"IDLE_RIGHT_CRAWL", true);
	}

	// 여기가 공격 시작 부분 
	if (m_iDir == -1 && (m_eCurState == MON_STATE::WALK))
	{
		GetAnimator()->Play(L"WALK_LEFT_CRAWL", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"WALK_LEFT_CRAWL", 0);
				m_eCurState = MON_STATE::IDLE;
			}
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::WALK))
	{
		GetAnimator()->Play(L"WALK_RIGHT_CRAWL", false);

		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"WALK_RIGHT_CRAWL", 0);
			m_eCurState = MON_STATE::IDLE;
		}
		//GetAnimator()->GetAnimation()->IsFinish();
	}

	if (m_iDir == -1 && (m_eCurState == MON_STATE::DEAD))
	{
		GetAnimator()->Play(L"DEAD_LEFT_CRAWL", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				Create_item();
				DeleteObject(this);
			}
		}
	}

	else if (m_iDir == 1 && (m_eCurState == MON_STATE::DEAD))
	{
		GetAnimator()->Play(L"DEAD_RIGHT_CRAWL", false);

		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			Create_item();
			DeleteObject(this);
		}
		
	}


}

void CCrawlBug::Create_item()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // 몬스터의 좌표 받아옴
	pitem->SetName(L"Item_Geo");

	CreateObject(pitem, GROUP_TYPE::ITEM);
}


void CCrawlBug::OnCollision(CCollider* _pOther)
{

}

void CCrawlBug::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pDamagedSound2 = CResMgr::GenInst()->FindSound(L"Enemy_Damage2");
	CSound* pDeathSound2 = CResMgr::GenInst()->FindSound(L"Enemy_Death2");

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
				GetAnimator()->Play(L"DEAD_LEFT_CRAWL", false);
				pDeathSound2->Play(false);
				break;

			case -1:

				GetAnimator()->Play(L"DEAD_RIGHT_CRAWL", false);
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
				GetAnimator()->Play(L"DEAD_LEFT_CRAWL", false);
				pDeathSound2->Play(false);
				break;

			case -1:

				GetAnimator()->Play(L"DEAD_RIGHT_CRAWL", false);
				pDeathSound2->Play(false);
				break;
			}

		}
	}

}

void CCrawlBug::OnCollisionExit(CCollider* _pOther)
{

}
