#include "pch.h"
#include "CTraceState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"

#include "CMonster.h"
#include "CTimeMgr.h"

CTraceState::CTraceState()
	:CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}


void CTraceState::update()
{
	//Å¸°ÙÆÃ µÈ Player¸¦ ÂÑ¾Æ°£´Ù.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GenInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos; // ¹æÇâº¤ÅÍ ±¸ÇÏ±â 

	if (vMonDir != Vec2(0.f, 0.f))
	{
		vMonDir.Normalize(); // ¹æÇâº¤ÅÍ¸¦ ´ÜÀ§º¤ÅÍ·Î ³ªÅ¸³¿
	}
	
	vMonPos += vMonDir * GetMonster()->GetInfo().fSpeed * fDT;


	GetMonster()->SetPos(vMonPos);

}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}