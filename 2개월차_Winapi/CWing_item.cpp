#include "pch.h"
#include "CWing_item.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"



CWing_item::CWing_item()
	:CUI(false)
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"Wing_item", L"texture\\UI\\wing.bmp");

	CPlayerMgr::GenInst()->GetItemList().push_back(this);
}

CWing_item::~CWing_item()
{

}


void CWing_item::update()
{

}

void CWing_item::render(HDC _dc)
{
	if (CPlayerMgr::GenInst()->GetInventoryStatus())
	{


		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();

		int iWidth = (int)m_pTex->Width();
		int iHeight = (int)m_pTex->Height();
		//Ellipse(_dc,
		//	(int)(vPos.x - vScale.x / 2.f),  // 왼쪽 상단 x
		//	(int)(vPos.y - vScale.y / 2.f),  // 왼쪽 상단 y
		//	(int)(vPos.x + vScale.x / 2.f),  // 오른쪽 하단 x
		//	(int)(vPos.y + vScale.y / 2.f)); // 오른쪽 하단 y


		TransparentBlt(_dc
			, (int)((vPos.x - (float)(iWidth / 2)))
			, (int)((vPos.y - (float)(iHeight / 2)))
			, iWidth
			, iHeight
			, m_pTex->GetDc()
			, 0, 0, iWidth, iHeight, RGB(32, 34, 64));
	}
}

