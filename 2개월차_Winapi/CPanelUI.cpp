#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	:CUI(false) // "이 UI 는 카메라의 영향을 받지 않는다 " 라는 의미
{

}

CPanelUI::~CPanelUI()
{

}


void CPanelUI::update()
{

}

void CPanelUI::render(HDC _dc)
{
	CUI::render(_dc);
}

void CPanelUI::MouseOn()
{
	if(IsLbtnDown())
	{
		Vec2 vDiff = MOUSE_POS - m_vDragStatrt;

		Vec2 vCurPos = GetPos();
		//차이값 만큼 이동
		vCurPos += vDiff;

		SetPos(vCurPos);

		m_vDragStatrt = MOUSE_POS;

	}
}

void CPanelUI::MouseLbtnDown()
{
	m_vDragStatrt = MOUSE_POS;

}

void CPanelUI::MouseLbtnUp()
{

}
