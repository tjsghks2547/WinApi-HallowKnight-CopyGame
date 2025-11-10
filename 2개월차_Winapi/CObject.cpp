#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CGravity.h"


CObject::CObject()
	:m_vPos{}
	,m_vScale{} // 초기화 
	,m_pCollider(nullptr)
	,m_pAnimator(nullptr)
	,m_pGravity(nullptr)
	,m_pRigidBody(nullptr)
	,m_bAlive(true)
	,m_bCamAffect(true)
	,type_of_animation(0)
{

}

CObject::CObject(const CObject& _origin)
	:m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pGravity(nullptr)
	, m_pRigidBody(nullptr)
	, m_bAlive(true)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}

	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this; 
	}

	if (_origin.m_pRigidBody)
	{
		m_pRigidBody = new CRigidBody(*_origin.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}

	if (_origin.m_pGravity)
	{
		m_pGravity = new CGravity(*_origin.m_pGravity);
		m_pGravity ->m_pOwner = this;
	}

}

CObject::~CObject()
{
	if(nullptr != m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr; 
 
	}

	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}

	if(nullptr != m_pRigidBody)
	{
		delete m_pRigidBody;
		m_pRigidBody = nullptr;
	}

	if (nullptr != m_pGravity)
	{
		delete m_pGravity;
		m_pGravity = nullptr;
	}
}

void CObject::update()
{

}

void CObject::finalupdate()
{
	
	if(m_pAnimator)
	{
		m_pAnimator->finalupdate();
	}

	if (m_pGravity)
	{
		m_pGravity->finalupdate();
	}

	if (m_pRigidBody)
	{
		m_pRigidBody->finalupdate();
	}

	// 이거 순서 중요함 지금 콜라이더 박스가 중력과 리지드 박스 처리 이후에 되야 충돌 처리가 2번안생겨서 점프 가능해짐 지형에 닿아도
	if (m_pCollider)
	{
		m_pCollider->finalupdate();
	}

}



void CObject::render(HDC _dc)
{
	//Vec2 vRenderPos = CCamera::GenInst()->GetRenderPos(m_vPos); 
	//
	//Rectangle(_dc,
	//	(int)(vRenderPos.x - m_vScale.x / 2.f),  // 왼쪽 상단 x
	//	(int)(vRenderPos.y - m_vScale.y / 2.f),  // 왼쪽 상단 y
	//	(int)(vRenderPos.x + m_vScale.x / 2.f),  // 오른쪽 하단 x
	//	(int)(vRenderPos.y + m_vScale.y / 2.f)); // 오른쪽 하단 y
	
	//Rectangle(_dc,
	//	(int)(m_vPos.x - m_vScale.x / 2.f),  // 왼쪽 상단 x
	//	(int)(m_vPos.y - m_vScale.y / 2.f),  // 왼쪽 상단 y
	//	(int)(m_vPos.x + m_vScale.x / 2.f),  // 오른쪽 하단 x
	//	(int)(m_vPos.y + m_vScale.y / 2.f)); // 오른쪽 하단 y

	//component_render(_dc);

}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this; //this를 넣은 이유가 오브젝트가 자기 자신의 주소를 콜라이더에게 알려주기 위해
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this; 

}

void CObject::CreateAnimator(bool _CamAffect)
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
	m_bCamAffect = _CamAffect;

}

void CObject::CreateRigidBody()
{
	m_pRigidBody= new CRigidBody;
	m_pRigidBody->m_pOwner = this;

}

void CObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;

}

void CObject::CreateAnimator_using_vector()
{
	m_vecAnimator.push_back(new CAnimator);
	m_vecAnimator.back()->m_pOwner = this; 
}




void CObject::component_render(HDC _dc)
{

	if (nullptr != m_pCollider)
	{
		m_pCollider->render(_dc);
	}


	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render(_dc);
	}
}

CObject* CObject::Clone()
{
	return nullptr;
}


