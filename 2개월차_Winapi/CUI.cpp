#include "pch.h"
#include "CUI.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"
#include "CAnimator.h"


CUI::CUI(bool _bCamAff)
	:m_pParentUI(nullptr)
	,m_bCamAffected(false)
	,m_bMouseOn(false)
	,m_bLbtnDown(false)
{
}

CUI::CUI(const CUI& _origin)
	:CObject(_origin) //부모쪽 복사생성자를 써라고 명시해준것 (default 복사 생성자를 쓰지 않기 때문에 이렇게 해줘야함)
	,m_pParentUI(nullptr)
	,m_bCamAffected(_origin.m_bCamAffected)
	,m_bMouseOn(false)
	,m_bLbtnDown(false)
	
{
	// 자식도 복사해주는것 
	for(size_t i = 0; i< _origin.m_vecChildUI.size(); i++)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);

}




void CUI::update()
{
	// child ui update 
	update_child();
}

void CUI::finalupdate()
{
	//자기 자신의 최종 위치를 결정하는 곳 
	CObject::finalupdate();

	// UI 의 최종 좌표를 구한다.
	m_vFinalPos = GetPos();

	if(GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalpos();
		m_vFinalPos += vParentPos ;
	}
	
	//UI 마우스 체크 
	MouseOnCheck();

	


	finalupdate_child();
	
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalpos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GenInst()->GetRenderPos(vPos);
	}

	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));

	}

	else
	{
		/*if (GetAnimator()->GetAnimation())
		{
			GetAnimator()->render(_dc);
		}*/
		//else
		{
			Rectangle(_dc
				, (int)(vPos.x)
				, (int)(vPos.y)
				, (int)(vPos.x + vScale.x)
				, (int)(vPos.y + vScale.y));

		}

		//child ui render 
		render_child(_dc);
	}


	
}



void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}



void CUI::MouseOn()
{

}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnUp()
{

}

void CUI::MouseLbtnClicked()
{

}

void CUI::MouseOnCheck()
{
	Vec2 vMousPos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if(m_bCamAffected)
	{
		vMousPos = CCamera::GenInst()->GetRealPos(vMousPos);
	}

	if(m_vFinalPos.x <= vMousPos.x && vMousPos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousPos.y && vMousPos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true; 
	}

	else
	{
		m_bMouseOn = false; 
	}

}
