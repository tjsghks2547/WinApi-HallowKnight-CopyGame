#include "pch.h"
#include "Cclock_Item.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"



Cclock_Item::Cclock_Item()
	:CUI(false)
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"clock_item", L"texture\\UI\\cloak2.bmp");
	
	CPlayerMgr::GenInst()->GetItemList().push_back(this);
	
}

Cclock_Item::~Cclock_Item()
{

}


void Cclock_Item::update()
{

}

void Cclock_Item::render(HDC _dc)
{
	if(CPlayerMgr::GenInst()->GetInventoryStatus())
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
			, 0, 0, iWidth, iHeight, RGB(0, 0, 0));
	}
	
}


