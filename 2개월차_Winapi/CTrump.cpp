#include "pch.h"
#include "CTrump.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"


CTrump::CTrump()
{
	CreateCollider();
	CreateAnimator();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	CTexture* m_pTrumpIdleTex = CResMgr::GenInst()->LoadTexture(L"TrumpNpcIdle", L"texture\\Npc\\Trump_Npc_real.bmp");
	GetAnimator()->CreateAnimation(L"TrumpNpcIdle", m_pTrumpIdleTex, Vec2(0.f, 0.f), Vec2(164.f, 172.f), Vec2(164.f, 0.f), 0.25f, 11);

	
}

CTrump::~CTrump()
{
}

void CTrump::update()
{
	update_animation();
}

void CTrump::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CTrump::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == _pOther->GetObj()->GetName())
	{

	}
}

void CTrump::update_animation()
{
	GetAnimator()->Play(L"TrumpNpcIdle", true);
}
