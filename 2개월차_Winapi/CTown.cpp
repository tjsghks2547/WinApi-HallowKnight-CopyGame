#include "pch.h"
#include "CTown.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "C_Core.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CTown::CTown()
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"BackGround_2", L"texture\\Map\\stage2_town_real.bmp");
}

CTown::~CTown()
{

}

void CTown::update()
{


}

void CTown::render(HDC _dc)
{
	
	

	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();
	
	
	if(CPlayerMgr::GenInst()->GetCurPlayerPos().x <1000.f)
	{
		CCamera::GenInst()->SetOffSet(Vec2(300.f, 0.f));
		
		Vec2 vPos = CCamera::GenInst()->GetLookAt();

		BitBlt(_dc
			, 0
			, 0
			, 1500
			, 1500
			, m_pTex->GetDc()
			, (int)(vPos.x - 760)
			, (int)(vPos.y - 380)
			, SRCCOPY);

		
	}
	
	else if (CPlayerMgr::GenInst()->GetCurPlayerPos().x >= 1000.f)
	{
		CCamera::GenInst()->SetOffSet(Vec2(0.f, -250.f));

		Vec2 vPos = CCamera::GenInst()->GetLookAt();

		BitBlt(_dc
			, 0
			, 0
			, 1500
			, 1500
			, m_pTex->GetDc()
			, (int)(vPos.x - 760)
			, (int)(vPos.y - 380)
			, SRCCOPY);


	}
	
}


