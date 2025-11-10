#include "pch.h"
#include "CStoreItemlist.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"
#include "CSound.h"


CStoreItemlist::CStoreItemlist()
	:CUI(false)
{
	m_pSoulBallTex = CResMgr::GenInst()->LoadTexture(L"Store_Soulball_itme", L"texture\\UI\\soulball_store_real.bmp");
	m_pFocusTex    = CResMgr::GenInst()->LoadTexture(L"Store_Focus_itme", L"texture\\UI\\focus_store_real.bmp");
	
}

CStoreItemlist::~CStoreItemlist()
{
}

void CStoreItemlist::update()
{
}

void CStoreItemlist::render(HDC _dc)
{
	if (CPlayerMgr::GenInst()->GetStoreOnOff())
	{
		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = 240; // 전역적으로 적용되는 알파값  (투명도) 

		float width = (float)m_pSoulBallTex->Width();
		float height = (float)m_pSoulBallTex->Height();
		Vec2 vPos = Vec2(525.f, 250.f);

		

		AlphaBlend(_dc
			, (int)(vPos.x - width / 2.f)
			, (int)(vPos.y - height / 2.f)
			, (int)(width)
			, (int)(height)
			, m_pSoulBallTex->GetDc()
			, 0
			, 0
			, (int)width
			, (int)height
			, bf);



		float width2 = (float)m_pFocusTex->Width();
		float height2 = (float)m_pFocusTex->Height();
		vPos = Vec2(525.f, 350.f);


		AlphaBlend(_dc
			, (int)(vPos.x - width2 / 2.f)
			, (int)(vPos.y - height2 / 2.f)
			, (int)(width2)
			, (int)(height2)
			, m_pFocusTex->GetDc()
			, 0
			, 0
			, (int)width2
			, (int)height2
			, bf);


	}
}


