#include "pch.h"
#include "CItem.h"
#include "CPlayerMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CSound.h"


CItem::CItem()
{

	CreateAnimator();
	CreateCollider();

	CreateRigidBody();
	CreateGravity();
	

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(30.f, 30.f));


	CTexture* m_pitemTex = CResMgr::GenInst()->LoadTexture(L"Item", L"texture\\geomove2.bmp");
	GetAnimator()->CreateAnimation(L"Item_Geo", m_pitemTex, Vec2(0.f, 0.f), Vec2(28.f, 41.f), Vec2(28.f, 0.f), 0.05f, 6);
	

	GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -200.f));
	GetAnimator()->Play(L"Item_Geo", true);

	CResMgr::GenInst()->LoadSound(L"Item_Gain", L"sound\\ui_button_confirm.wav");
	
}

CItem::~CItem()
{

}

void CItem::update()
{
	////Å¸°ÙÆÃ µÈ Player¸¦ ÂÑ¾Æ°£´Ù.
	//Vec2 vPlayerPos = CPlayerMgr::GenInst()->GetCurPlayerPos();
	//Vec2 ItemPos = GetPos();

	//
	//Vec2 vitemDir = vPlayerPos - ItemPos; // ¹æÇâº¤ÅÍ ±¸ÇÏ±â 

	//if (vitemDir != Vec2(0.f, 0.f))
	//{
	//	vitemDir.Normalize(); // ¹æÇâº¤ÅÍ¸¦ ´ÜÀ§º¤ÅÍ·Î ³ªÅ¸³¿
	//}

	//ItemPos += vitemDir * 150.f * fDT;

	//SetPos(ItemPos);
}

void CItem::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}



void CItem::update_move()
{

}

void CItem::update_state()
{

}

void CItem::update_animation()
{

}

void CItem::SetGravityXgive(float _f)
{
	GetRigidBody()->SetVelocity(Vec2(_f, -200.f));
}

void CItem::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pItemGain = CResMgr::GenInst()->FindSound(L"Item_Gain");
	


	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		
		pItemGain->Play(false);
		CPlayerMgr::GenInst()->IncreaseGeo(100);
		DeleteObject(this);
	}
}