#include "pch.h"
#include "CStartBackGround.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "C_Core.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"

CStartBackGround::CStartBackGround()
	:m_pTex(nullptr)

{

	m_pTex = CResMgr::GenInst()->LoadTexture(L"START_BG", L"texture\\Map\\background_test.bmp");
	
}

CStartBackGround::~CStartBackGround()
{

}


void CStartBackGround::update()
{

}

void CStartBackGround::render(HDC _dc)
{
	BitBlt(_dc
		, 0
		, 0
		, 1280
		, 760
		, m_pTex->GetDc()
		, (int)(0)
		, (int)(0)
		, SRCCOPY);


}

