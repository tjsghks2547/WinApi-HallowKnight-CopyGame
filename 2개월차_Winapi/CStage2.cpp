#include "pch.h"
#include "CStage2.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "C_Core.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CStage2::CStage2()
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"Stage2_Background_2", L"texture\\Map\\Stage2_Map3.bmp");
	

}

CStage2::~CStage2()
{
}


void CStage2::update()
{
}

void CStage2::render(HDC _dc)
{

	

	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = CCamera::GenInst()->GetLookAt();
	CCamera::GenInst()->SetOffSet(Vec2(-50.f, 0.f));

	BitBlt(_dc
		, 0
		, 0
		, 1500
		, 1500
		, m_pTex->GetDc()
		, (int)(vPos.x - 760)
		, (int)(vPos.y - 380)
		, SRCCOPY);
	

	/*if (CPlayerMgr::GenInst()->GetCurPlayerPos().x < 589.f)
	{
		CCamera::GenInst()->SetOffSet(Vec2(420.f, -200.f));

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

	else if (CPlayerMgr::GenInst()->GetCurPlayerPos().x >= 589.f)
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


	}*/
}

