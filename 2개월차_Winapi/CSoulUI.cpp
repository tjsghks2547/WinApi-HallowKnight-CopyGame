#include "pch.h"
#include "CSoulUI.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CPlayerMgr.h"

CSoulUI::CSoulUI()
	:CUI(false)
	, m_pSoulUiTex(nullptr)
{
	// 원래 것들
	// =================
	m_pTex = CResMgr::GenInst()->LoadTexture(L"Soul_full", L"texture\\Soul.bmp");
	CTexture* m_pSoulUiTex = CResMgr::GenInst()->LoadTexture(L"SOULUI", L"texture\\Soul2.bmp");

	CreateAnimator(false);
	GetAnimator()->CreateAnimation(L"SOUL_UI", m_pSoulUiTex, Vec2(0.f, 0.f), Vec2(129.f, 126.f), Vec2(0.f, 0.f), 1.f, 1);
	//GetAnimator()->Play(L"SOUL_UI", true);
	// =========================

	//m_pSoulUiTex = CResMgr::GenInst()->LoadTexture(L"SOULUI", L"texture\\Soul_UI_Test.bmp");
}

CSoulUI::~CSoulUI()
{
}


void CSoulUI::update()
{

}

void CSoulUI::render(HDC _dc)
{

	if(CPlayerMgr::GenInst()->GetPlayerMp()>5)
	{
		
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();

		int iWidth = (int)m_pTex->Width();
		int iHeight = (int)m_pTex->Height();
	

		TransparentBlt(_dc
			, (int)((vPos.x - (float)(iWidth / 2)))
			, (int)((vPos.y - (float)(iHeight / 2)))
			, iWidth
			, iHeight
			, m_pTex->GetDc()
			, 0, 0, iWidth, iHeight, RGB(0, 0, 0));
	
	}

	else if(CPlayerMgr::GenInst()->GetPlayerMp()>= 0 
			&& CPlayerMgr::GenInst()->GetPlayerMp() <= 5)
	{
		GetAnimator()->render(_dc);
	}
	

}


