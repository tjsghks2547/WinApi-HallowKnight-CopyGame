#include "pch.h"
#include "CNpc.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"

CNpc::CNpc()
{
	CreateCollider();
	CreateAnimator();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	CTexture* m_pNpcIdleTex = CResMgr::GenInst()->LoadTexture(L"NpcIdle", L"texture\\Npc\\Elderbug2.bmp");
	GetAnimator()->CreateAnimation(L"ElderBug_idle", m_pNpcIdleTex, Vec2(0.f, 160.f), Vec2(110.f, 160.f), Vec2(110.f, 0.f), 0.5f, 6);
}

CNpc::~CNpc()
{

}

void CNpc::update()
{
	update_animation();

}

void CNpc::render(HDC _dc)
{
	GetAnimator()->render(_dc);
}

void CNpc::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == _pOther->GetObj()->GetName())
	{
		
	}
}

void CNpc::update_animation()
{
	GetAnimator()->Play(L"ElderBug_idle", true);
}
