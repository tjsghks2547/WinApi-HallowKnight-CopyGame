#include "pch.h"
#include "CFinalBossRoom.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"

CFinalBossRoom::CFinalBossRoom()
	:m_pTex(nullptr)
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"PureVessel_boss_room", L"texture\\Map\\PureVessel_realMap.bmp");


}

CFinalBossRoom::~CFinalBossRoom()
{

}

void CFinalBossRoom::update()
{

}	

void CFinalBossRoom::render(HDC _dc)
{

	
	Vec2 vPlayerPos = CPlayerMgr::GenInst()->GetCurPlayerPos();
	CCamera::GenInst()->SetTarget(nullptr);
	CCamera::GenInst()->SetLookAt(Vec2(vPlayerPos.x, vPlayerPos.y - 200));

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


