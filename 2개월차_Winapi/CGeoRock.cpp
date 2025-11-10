#include "pch.h"
#include "CGeoRock.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CItem.h"
#include "CSound.h"
#include "CAnimator.h"
#include "CAnimation.h"


CGeoRock::CGeoRock()
	:m_iHP(4)
	,m_pTex(nullptr)
{
	CreateCollider();
	CreateAnimator();

	m_pTex = CResMgr::GenInst()->LoadTexture(L"GEOROCK2", L"texture\\Monster\\Geo_Deposit_NoBroken.bmp");

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	GetAnimator()->CreateAnimation(L"IDLE_test", m_pTex, Vec2(0.f, 0.f), Vec2(125.f, 107.f), Vec2(125.f, 0.f), 5.f, 1);

	GetAnimator()->Play(L"IDLE_test", true);

	CResMgr::GenInst()->LoadSound(L"mine_Damage", L"sound\\Player\\sword_hit_reject.wav");
}

CGeoRock::~CGeoRock()
{

}
void CGeoRock::update()
{
}

void CGeoRock::render(HDC _dc)
{
	
	if(m_iHP >0)
	{
		GetAnimator()->render(_dc);
	}

	if(m_iHP <0)
	{
		DeleteObject(this);
	}
	
}

void CGeoRock::OnCollision(CCollider* _pOther)
{
}

void CGeoRock::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pHitRock = CResMgr::GenInst()->FindSound(L"mine_Damage");
	pHitRock->SetVolume(90.f);

	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"SLASH"
		|| pOtherObj->GetName() == L"DOWN_SLASH_Effect")
	{
		m_iHP--;
		pHitRock->Play(false);
		m_iCount++;

		switch (m_iCount)
		{
		case 1:
			Create_item();
			break;

		case 2:
			Create_item();
			Create_item1();
			Create_item2();
			break;

		case 3:
			Create_item1();
			Create_item3();
			Create_item4();
			break;

		case 4:
			Create_item();
			Create_item1();
			Create_item2();
			Create_item3();
			Create_item4();
			break;

		case 5:
			break;
		}
	}
}

void CGeoRock::OnCollisionExit(CCollider* _pOther)
{
}

void CGeoRock::Create_item()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // ¸ó½ºÅÍÀÇ ÁÂÇ¥ ¹Þ¾Æ¿È
	pitem->SetName(L"Item_Geo");

	CreateObject(pitem, GROUP_TYPE::ITEM);
}

void CGeoRock::Create_item1()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // ¸ó½ºÅÍÀÇ ÁÂÇ¥ ¹Þ¾Æ¿È
	pitem->SetName(L"Item_Geo");
	pitem->SetGravityXgive(50.f);

	CreateObject(pitem, GROUP_TYPE::ITEM);
}

void CGeoRock::Create_item2()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // ¸ó½ºÅÍÀÇ ÁÂÇ¥ ¹Þ¾Æ¿È
	pitem->SetName(L"Item_Geo");
	pitem->SetGravityXgive(-50.f);

	CreateObject(pitem, GROUP_TYPE::ITEM);
}

void CGeoRock::Create_item3()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // ¸ó½ºÅÍÀÇ ÁÂÇ¥ ¹Þ¾Æ¿È
	pitem->SetName(L"Item_Geo");
	pitem->SetGravityXgive(-100.f);

	CreateObject(pitem, GROUP_TYPE::ITEM);

}

void CGeoRock::Create_item4()
{
	CItem* pitem = new CItem;

	pitem->SetPos(Vec2(GetPos())); // ¸ó½ºÅÍÀÇ ÁÂÇ¥ ¹Þ¾Æ¿È
	pitem->SetName(L"Item_Geo");
	pitem->SetGravityXgive(100.f);

	CreateObject(pitem, GROUP_TYPE::ITEM);
}
