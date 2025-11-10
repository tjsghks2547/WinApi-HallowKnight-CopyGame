#include "pch.h"
#include "CHornetBossRoom.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CTexture.h"





CHornetBossRoom::CHornetBossRoom()
	:m_pTex(nullptr)
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"Hornet_boss_room", L"texture\\Map\\greenpath_hornet_room.bmp");
}

CHornetBossRoom::~CHornetBossRoom()
{

}

void CHornetBossRoom::update()
{

}

void CHornetBossRoom::render(HDC _dc)
{
	
	CCamera::GenInst()->SetTarget(nullptr);
	CCamera::GenInst()->SetLookAt(Vec2(640.f, 380.f));

	Vec2 vPos = CCamera::GenInst()->GetLookAt();

	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	BitBlt(_dc
		, 0
		, 0
		, 1500
		, 1500
		, m_pTex->GetDc()
		, (int)(vPos.x - 640)
		, (int)(vPos.y - 380)
		, SRCCOPY);
}


