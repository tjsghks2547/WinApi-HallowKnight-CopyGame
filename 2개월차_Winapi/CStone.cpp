#include "pch.h"
#include "CStone.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CSound.h"

CStone::CStone()
{
	CreateCollider();
	CreateAnimator();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	//애니메이션 원래 코드 
	CTexture* m_pStoneTex = CResMgr::GenInst()->LoadTexture(L"Stone", L"texture\\FalseKnight\\stone.bmp");

	GetAnimator()->CreateAnimation(L"FALL_STONE", m_pStoneTex, Vec2(0.f, 0.f), Vec2(154.f, 142.f), Vec2(154.f, 0.f), 0.2f, 5);

	dwtime = GetTickCount64();

}

CStone::~CStone()
{
}

void CStone::update()
{
	update_animation();
	update_move();

	if(dwtime+5000 < GetTickCount64())
	{
		DeleteObject(this);

		dwtime = GetTickCount64();
	}
	
}

void CStone::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CStone::OnCollisionEnter(CCollider* _pOther)
{
	CSound * pBarrelBroked = CResMgr::GenInst()->FindSound(L"BrokeBarrel");
	CObject* pOtherObj = _pOther->GetObj();
	if (L"UP_SLASH_Effect" == _pOther->GetObj()->GetName())
	{
		pBarrelBroked->Play(false);
		DeleteObject(this);
	}
}

void CStone::update_move()
{
	Vec2 vPos = GetPos();

	vPos.y += 500.f * fDT;

	SetPos(vPos);
}

void CStone::update_animation()
{
	GetAnimator()->Play(L"FALL_STONE", true);
}
