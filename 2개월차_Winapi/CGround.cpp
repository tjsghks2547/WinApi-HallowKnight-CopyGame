#include "pch.h"
#include "CGround.h"
#include "CCollider.h"
#include "CGravity.h"


CGround::CGround()

{
	CreateCollider();
}

CGround::~CGround()
{

}


void CGround::start()
{
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CGround::update()
{

}



void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	//상 충돌 
	
	//L"MushRoom"
	//하충돌 
 	if (pOtherObj->GetPos().y < (GetPos().y - GetScale().y / 2.f))
	{
	 	if (pOtherObj->GetName() == L"Player" 
			|| pOtherObj->GetName() == L"Falseknight"
			|| pOtherObj->GetName() == L"Hornet"
			|| pOtherObj->GetName() == L"Crawl"
			|| pOtherObj->GetName() == L"Item_Geo"
			|| pOtherObj->GetName() == L"Dash_Bug"
			|| pOtherObj->GetName() == L"Pure_Vessel"
			|| pOtherObj->GetName() == L"MushRoom")
		{
			pOtherObj->GetGravity()->SetGround(true);

			Vec2 vObjPos = _pOther->GetFinalPos();
			Vec2 vObjScale = _pOther->GetScale();

			Vec2 vPos = GetCollider()->GetFinalPos();
			Vec2 vScale = GetCollider()->GetScale();

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;


			vObjPos = pOtherObj->GetPos();
			vObjPos.y -= fValue;

			pOtherObj->SetPos(vObjPos);

		
		}
	}


	//벽과 오른쪽에서 충돌시
	// x 좌표가 더 크고, y 좌표는 더 작다 
	if (pOtherObj->GetPos().x > GetPos().x && pOtherObj->GetPos().y > (GetPos().y - GetScale().y / 2.f))
	{
		if (pOtherObj->GetName() == L"Player"
			|| pOtherObj->GetName() == L"Hornet"
			|| pOtherObj->GetName() == L"Pure_Vessel")
		{
			Vec2 vObjPos = _pOther->GetFinalPos();
			Vec2 vObjScale = _pOther->GetScale();

			Vec2 vPos = GetCollider()->GetFinalPos();
			Vec2 vScale = GetCollider()->GetScale();

			float fLen = abs(vObjPos.x - vPos.x);
			float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;


			vObjPos = pOtherObj->GetPos();
			vObjPos.x += fValue;

			pOtherObj->SetPos(vObjPos);
		}
	}


	//벽과 왼쪽에서 충돌시
	// x 좌표가 더 작고, y 좌표는 더 작다 
	if (pOtherObj->GetPos().x < GetPos().x && pOtherObj->GetPos().y >(GetPos().y - GetScale().y / 2.f))
	{
		if (pOtherObj->GetName() == L"Player"
			|| pOtherObj->GetName() == L"Hornet"
			|| pOtherObj->GetName() == L"Pure_Vessel")
		{
			Vec2 vObjPos = _pOther->GetFinalPos();
			Vec2 vObjScale = _pOther->GetScale();

			Vec2 vPos = GetCollider()->GetFinalPos();
			Vec2 vScale = GetCollider()->GetScale();

			float fLen = abs(vObjPos.x - vPos.x);
			float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;


			vObjPos = pOtherObj->GetPos();
			vObjPos.x -= fValue;

			pOtherObj->SetPos(vObjPos);
		}
	}
}

void CGround::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	
	// 하 충돌
	if (pOtherObj->GetPos().y < (GetPos().y - GetScale().y / 2.f) )
	{
		if (pOtherObj->GetName() == L"Player" 
			|| pOtherObj->GetName() == L"FalseKnight"
			|| pOtherObj->GetName() == L"Hornet"
			|| pOtherObj->GetName() == L"Crawl"
			|| pOtherObj->GetName() == L"Item_Geo"
			|| pOtherObj->GetName() == L"Dash_Bug"
			|| pOtherObj->GetName() == L"Pure_Vessel"
			|| pOtherObj->GetName() == L"MushRoom")
		{
 			pOtherObj->GetGravity()->SetGround(true);

			Vec2 vObjPos = _pOther->GetFinalPos();
			Vec2 vObjScale = _pOther->GetScale();

			Vec2 vPos = GetCollider()->GetFinalPos();
			Vec2 vScale = GetCollider()->GetScale();

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;


			vObjPos = pOtherObj->GetPos();
			vObjPos.y -= fValue;

			pOtherObj->SetPos(vObjPos);
		}
	}

	//벽과 오른쪽에서 충돌시
	// x 좌표가 더 크고, y 좌표는 더 작다 
	if (pOtherObj->GetPos().x > GetPos().x && pOtherObj->GetPos().y > (GetPos().y - GetScale().y / 2.f))
	{
		if (pOtherObj->GetName() == L"Player"
			|| pOtherObj->GetName() == L"Beetle"
			|| pOtherObj->GetName() == L"Hornet"
			|| pOtherObj->GetName() == L"Pure_Vessel"
			)
		{
			Vec2 vObjPos = _pOther->GetFinalPos();
			Vec2 vObjScale = _pOther->GetScale();

			Vec2 vPos = GetCollider()->GetFinalPos();
			Vec2 vScale = GetCollider()->GetScale();

			float fLen = abs(vObjPos.x - vPos.x);
			float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;


			vObjPos = pOtherObj->GetPos();
			vObjPos.x += fValue;

			pOtherObj->SetPos(vObjPos);
		}
	}

	//벽과 왼쪽에서 충돌시
	// x 좌표가 더 작고, y 좌표는 더 작다 
	if (pOtherObj->GetPos().x < GetPos().x && pOtherObj->GetPos().y > (GetPos().y - GetScale().y / 2.f))
	{
		if (pOtherObj->GetName() == L"Player"
			|| pOtherObj->GetName() == L"Beetle"
			|| pOtherObj->GetName() == L"Hornet"
			|| pOtherObj->GetName() == L"Pure_Vessel")
		{
			Vec2 vObjPos = _pOther->GetFinalPos();
			Vec2 vObjScale = _pOther->GetScale();

			Vec2 vPos = GetCollider()->GetFinalPos();
			Vec2 vScale = GetCollider()->GetScale();

			float fLen = abs(vObjPos.x - vPos.x);
			float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;


			vObjPos = pOtherObj->GetPos();
			vObjPos.x -= fValue;

			pOtherObj->SetPos(vObjPos);
		}
	}
	
}


void CGround::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(false);
	}
}