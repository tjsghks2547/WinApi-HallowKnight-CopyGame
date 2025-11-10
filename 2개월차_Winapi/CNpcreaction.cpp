#include "pch.h"
#include "CNpcreaction.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayerMgr.h"

CNpcreaction::CNpcreaction()
	:i_Count(0)
{
	CreateAnimator();

	CTexture* m_pNpcReaction = CResMgr::GenInst()->LoadTexture(L"NpcReaction", L"texture\\Npc\\Npc_reaction.bmp");
	GetAnimator()->CreateAnimation(L"NPC_REACTION", m_pNpcReaction, Vec2(0.f, 0.f), Vec2(72.f, 99.f), Vec2(72.f, 0.f), 0.1f, 11);
}

CNpcreaction::~CNpcreaction()
{

}

void CNpcreaction::update()
{
	update_animation();

	/*if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 10)
	{
		i_Count++;
		if (i_Count < 2)
		{
			DeleteObject(this);
		}
	}*/
}

void CNpcreaction::render(HDC _dc)
{
	if(CPlayerMgr::GenInst()->GetCurPlayerPos().x >= 5406
		&& CPlayerMgr::GenInst()->GetCurPlayerPos().x <= 5596)
	{
		GetAnimator()->render(_dc);
	}

	else if (CPlayerMgr::GenInst()->GetCurPlayerPos().x >= 6400
		&& CPlayerMgr::GenInst()->GetCurPlayerPos().x <= 6600)
	{
		GetAnimator()->render(_dc);
	}
	
}

void CNpcreaction::update_animation()
{
	if (CPlayerMgr::GenInst()->GetCurPlayerPos().x >= 5406
		&& CPlayerMgr::GenInst()->GetCurPlayerPos().x <= 5596)
	{
		SetPos(Vec2(5495.f, 2380.f));
		GetAnimator()->Play(L"NPC_REACTION", true);
	}

	else if (CPlayerMgr::GenInst()->GetCurPlayerPos().x >= 6400
		&& CPlayerMgr::GenInst()->GetCurPlayerPos().x <= 6600)
	{
		SetPos(Vec2(6500.f, 2380.f));
		GetAnimator()->Play(L"NPC_REACTION", true);
	}
	
}
