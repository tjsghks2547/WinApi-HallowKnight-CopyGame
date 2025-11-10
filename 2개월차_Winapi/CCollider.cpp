#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "C_Core.h"
#include "SelectGDI.h"
#include "CCamera.h"



UINT CCollider::g_iNextID = 0;


CCollider::CCollider() 
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
	, m_bActive(true)
{
}

CCollider::CCollider(const CCollider& _origin)
	:m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
	, m_bActive(_origin.m_bActive)
{	

}

CCollider::~CCollider()
{
}


void CCollider::finalupdate()
{
	//object의 위치를 따라가는 곳
	
	
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
	

	assert(0 <= m_iCol);
}

void CCollider::render(HDC _dc)
{

	

	//HPEN hGreenPen = CCore::GenInst()->GetPen(PEN_TYPE::GREEN);
	//HPEN hDefaultPen = (HPEN)SelectObject(_dc, hGreenPen);

	//HBRUSH hHollowBrush = CCore::GenInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	//HBRUSH hDefaultBrush = (HBRUSH)SelectObject(_dc, hHollowBrush);


	//이 함수가 종료되면 임시객체니깐 소멸자를 호출할거니 알아서 사라짐 

	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if(m_iCol) // 0만 아니면 다 true (m_iCol > 0 ) 과 같음.
	{
		ePen = PEN_TYPE::RED;
	}

	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	


	Vec2 vRenderPos = CCamera::GenInst()->GetRenderPos(m_vFinalPos);


	
	
	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f)
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f));

	//// 원래 기본펜으로 다시 변경 
	//SelectObject(_dc, hDefaultPen);
	//SelectObject(_dc, hDefaultBrush);

}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{

	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
	
	//m_iCol = true; 이때는 플레이어가 2개의 충돌체와 접촉했을 때 1개의 충돌체가 떨어지면 플레이어가 충돌이 아닌 상태로 초록색으로 색칠됨 그래서 안됨.
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
	/*m_iCol = false;*/
}
