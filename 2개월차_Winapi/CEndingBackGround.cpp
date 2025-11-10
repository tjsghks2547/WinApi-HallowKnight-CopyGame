#include "pch.h"
#include "CEndingBackGround.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"

CEndingBackGround::CEndingBackGround()
	:m_pEndingTex(nullptr)
{
	m_pEndingTex = CResMgr::GenInst()->LoadTexture(L"Ending_BackGround", L"texture\\Map\\Ending.bmp");
}

CEndingBackGround::~CEndingBackGround()
{

}

void CEndingBackGround::update()
{

}

void CEndingBackGround::render(HDC _dc)
{

	int iWidth  = (int)m_pEndingTex->Width();
	int iHeight = (int)m_pEndingTex->Height();

	BitBlt(_dc
		, 0
		, 0
		, 1280
		, 760
		, m_pEndingTex->GetDc()
		, 0
		, 0
		, SRCCOPY);
	
}


