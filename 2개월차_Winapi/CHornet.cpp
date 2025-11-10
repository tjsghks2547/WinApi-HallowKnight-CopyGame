#include "pch.h"
#include "CHornet.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"
#include "CRigidBody.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CHornetDashEffect.h"
#include "CNeedle.h"
#include "CNeedleThread.h"
#include "CThrowEffect.h"
#include "CSphereBall.h"
#include "CStunEffect.h"


//중력값 없애보는거 실험 
//GetRigidBody()->SetVelocity(Vec2(vV.x, 0.f));


CHornet::CHornet()
	:m_iHP(25)
	,m_iCount(0)
	,m_iPatternCount(0)
	,m_bSoundPlayed(false)
	,m_eCurState(HORNET_STATE::IDLE)
	,m_ePreState(HORNET_STATE::IDLE)
	,GroundOn(false)
{
	CreateCollider();
	CreateAnimator();

	CreateGravity();
	CreateRigidBody();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(75.f, 100.f));

	//애니메이션 원래 코드 
	CTexture* m_pHornetIdileTex = CResMgr::GenInst()->LoadTexture(L"HornetIdle", L"texture\\Hornet\\hornet_idle.bmp");
	CTexture* m_pHornetRushAnticipateTex = CResMgr::GenInst()->LoadTexture(L"HornetRushAnticipate", L"texture\\Hornet\\Rush_Anticipate3.bmp");
	CTexture* m_pHornetRushTex = CResMgr::GenInst()->LoadTexture(L"HornetRush", L"texture\\Hornet\\Rush.bmp");
	CTexture* m_pHornetRushRecoverTex = CResMgr::GenInst()->LoadTexture(L"HornetRushRecover", L"texture\\Hornet\\Rush_Recover.bmp");

	//투창 
	CTexture* m_pHornetThrowAnitcipateTex = CResMgr::GenInst()->LoadTexture(L"HornetThorwAnticipate", L"texture\\Hornet\\Throw_Anticipate.bmp");
	CTexture* m_pHornetThrowTex = CResMgr::GenInst()->LoadTexture(L"HornetThrow", L"texture\\Hornet\\Throw.bmp");
	CTexture* m_pHornetThrowRecoverTex = CResMgr::GenInst()->LoadTexture(L"HornetThrowRecover", L"texture\\Hornet\\Throw_Recover.bmp");

	//점프
	CTexture* m_pHornetJumpAnitcipateTex = CResMgr::GenInst()->LoadTexture(L"HornetJumpAnticipate", L"texture\\Hornet\\Jump_Anticipate.bmp");
	CTexture* m_pHornetJumpTex = CResMgr::GenInst()->LoadTexture(L"HornetJump", L"texture\\Hornet\\Jump_real.bmp");
	CTexture* m_pHornetJumpRushLeftTex  = CResMgr::GenInst()->LoadTexture(L"HornetJumpRushLeft", L"texture\\Hornet\\Jump_Rush_left.bmp");
	CTexture* m_pHornetJumpRushRightTex = CResMgr::GenInst()->LoadTexture(L"HornetJumpRushRight", L"texture\\Hornet\\Jump_Rush2_Right.bmp");
	CTexture* m_pHornetJumpLandTex = CResMgr::GenInst()->LoadTexture(L"HornetJumpLand", L"texture\\Hornet\\Jump_Land.bmp");

	//백스탭
	CTexture* m_pHornetEvadeAnticipateTex = CResMgr::GenInst()->LoadTexture(L"HornetEvadeAnticipate", L"texture\\Hornet\\Evade_Anticipate_real.bmp");
	CTexture* m_pHornetEvadeTex = CResMgr::GenInst()->LoadTexture(L"HornetEvade", L"texture\\Hornet\\Evade.bmp");

	//패링
	CTexture* m_pHornetCounterAnticipateTex = CResMgr::GenInst()->LoadTexture(L"HornetCounterAnticipate", L"texture\\Hornet\\Counter_Anticipate.bmp");
	CTexture* m_pHornetCounterStance = CResMgr::GenInst()->LoadTexture(L"HornetCounterStance", L"texture\\Hornet\\Counter_Stance.bmp");
	CTexture* m_pHornetCounterEnd = CResMgr::GenInst()->LoadTexture(L"HornetCounterEnd", L"texture\\Hornet\\Counter_End.bmp");

	//패링 성공시 
	CTexture* m_pHornetCounterAttackAnticipateTex = CResMgr::GenInst()->LoadTexture(L"HornetCounterAttackAnticipate", L"texture\\Hornet\\Counter_Attack_Anticipate.bmp");
	CTexture* m_pHornetCounterAttack = CResMgr::GenInst()->LoadTexture(L"HornetCounterAttack", L"texture\\Hornet\\Counter_Attack.bmp");
	CTexture* m_pHornetCounterRecover = CResMgr::GenInst()->LoadTexture(L"HornetCounterAttackRecover", L"texture\\Hornet\\Counter_Attack_Reocver.bmp");

	//원모양 범위 공격
	CTexture* m_pHornetSphereAnticipateTex = CResMgr::GenInst()->LoadTexture(L"HornetSphereAnticipate", L"texture\\Hornet\\Sphere_Anticipte.bmp");
	CTexture* m_pHornetSphereTex = CResMgr::GenInst()->LoadTexture(L"HornetSphere", L"texture\\Hornet\\Sphere.bmp");
	CTexture* m_pHornetSphereRecoverTex = CResMgr::GenInst()->LoadTexture(L"HornetSphereRecover", L"texture\\Hornet\\Sphere_Recover.bmp");

	//스턴상태
	CTexture* m_pHornetStunAnticipateTex = CResMgr::GenInst()->LoadTexture(L"HornetStunAnticipate", L"texture\\Hornet\\Stun_Anticipate.bmp");
	CTexture* m_pHornetStunTex = CResMgr::GenInst()->LoadTexture(L"HornetStun", L"texture\\Hornet\\Stun2.bmp");


	GetAnimator()->CreateAnimation(L"Idle_LEFT_HORNET",  m_pHornetIdileTex, Vec2(0.f, 0.f), Vec2(126.f, 108.f), Vec2(126.f, 0.f), 0.2f, 6);
	GetAnimator()->CreateAnimation(L"Idle_RIGHT_HORNET", m_pHornetIdileTex, Vec2(0.f, 108.f), Vec2(126.f, 108.f), Vec2(126.f, 0.f), 0.2f, 6);

	GetAnimator()->CreateAnimation(L"RUSH_ANTICIPATE_LEFT_HORNET",  m_pHornetRushAnticipateTex, Vec2(0.f, 0.f), Vec2(156.f, 96.f), Vec2(156.f, 0.f), 0.05f, 9);
	GetAnimator()->CreateAnimation(L"RUSH_ANTICIPATE_RIGHT_HORNET", m_pHornetRushAnticipateTex, Vec2(0.f, 96.f), Vec2(156.f, 96.f), Vec2(156.f, 0.f), 0.05f, 9);

	GetAnimator()->CreateAnimation(L"RUSH_LEFT_HORNET",  m_pHornetRushTex, Vec2(0.f, 0.f), Vec2(170.f, 68.5f), Vec2(170.f, 0.f), 0.2f, 2);
	GetAnimator()->CreateAnimation(L"RUSH_RIGHT_HORNET", m_pHornetRushTex, Vec2(0.f, 68.5f), Vec2(170.f, 68.5f), Vec2(170.f, 0.f), 0.2f, 2);

	GetAnimator()->CreateAnimation(L"RUSH_RECOVER_LEFT_HORNET", m_pHornetRushRecoverTex, Vec2(0.f, 0.f), Vec2(132.f, 103.f), Vec2(132.f, 0.f), 0.05f, 5);
	GetAnimator()->CreateAnimation(L"RUSH_RECOVER_RIGHT_HORNET", m_pHornetRushRecoverTex, Vec2(0.f, 103.f), Vec2(132.f, 103.f), Vec2(132.f, 0.f), 0.05f, 5);


	GetAnimator()->CreateAnimation(L"THROW_ANTICIPATE_LEFT_HORNET", m_pHornetThrowAnitcipateTex, Vec2(0.f, 0.f), Vec2(186.f, 107.f), Vec2(186.f, 0.f), 0.05f, 10);
	GetAnimator()->CreateAnimation(L"THROW_ANTICIPATE_RIGHT_HORNET", m_pHornetThrowAnitcipateTex, Vec2(0.f, 107.f), Vec2(186.f, 107.f), Vec2(186.f, 0.f), 0.05f, 10);

	GetAnimator()->CreateAnimation(L"THROW_LEFT_HORNET",  m_pHornetThrowTex, Vec2(0.f, 0.f), Vec2(102.f, 93.5f), Vec2(102.f, 0.f), 0.05f, 6);
	GetAnimator()->CreateAnimation(L"THROW_RIGHT_HORNET", m_pHornetThrowTex, Vec2(0.f, 93.5f), Vec2(102.f, 93.5f), Vec2(102.f, 0.f), 0.05f, 6);

	GetAnimator()->CreateAnimation(L"THROW_RECOVER_LEFT_HORNET",  m_pHornetThrowRecoverTex , Vec2(0.f, 0.f), Vec2(160.f, 94.5f), Vec2(160.f, 0.f), 0.05f, 6);
	GetAnimator()->CreateAnimation(L"THROW_RECOVER_RIGHT_HORNET", m_pHornetThrowRecoverTex , Vec2(0.f, 94.5f), Vec2(160.f, 94.5f), Vec2(160.f, 0.f), 0.05f, 6);

	
	GetAnimator()->CreateAnimation(L"JUMP_ANTICIPATE_LEFT_HORNET",  m_pHornetJumpAnitcipateTex, Vec2(0.f, 0.f), Vec2(138.f, 100.f), Vec2(138.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"JUMP_ANTICIPATE_RIGHT_HORNET", m_pHornetJumpAnitcipateTex, Vec2(0.f, 100.f), Vec2(138.f, 100.f), Vec2(138.f, 0.f), 0.1f, 4);

	GetAnimator()->CreateAnimation(L"JUMP_LEFT_HORNET",  m_pHornetJumpTex, Vec2(0.f, 0.f), Vec2(126.f, 114.5f), Vec2(126.f, 0.f), 0.075f, 9);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT_HORNET", m_pHornetJumpTex, Vec2(0.f, 114.5f), Vec2(126.f,114.5f), Vec2(126.f, 0.f), 0.075f, 9);

	GetAnimator()->CreateAnimation(L"JUMP_RUSH_LEFT_HORNET", m_pHornetJumpRushLeftTex, Vec2(0.f, 0.f), Vec2(170.f, 137.f), Vec2(170.f, 0.f), 0.3f, 2);
	GetAnimator()->CreateAnimation(L"JUMP_RUSH_RIGHT_HORNET", m_pHornetJumpRushRightTex, Vec2(0.f, 0.f), Vec2(170.f, 137.f), Vec2(170.f, 0.f), 0.3f, 2);

	
	GetAnimator()->CreateAnimation(L"JUMP_LAND_LEFT_HORNET",   m_pHornetJumpLandTex, Vec2(0.f, 0.f), Vec2(136.f, 109.f), Vec2(136.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"JUMP_LAND_RIGHT_HORNET",  m_pHornetJumpLandTex, Vec2(0.f, 109.f), Vec2(136.f, 109.f), Vec2(136.f, 0.f), 0.1f, 3);

	
	GetAnimator()->CreateAnimation(L"ANTICIPATE_EVADE_LEFT_HORNET",  m_pHornetEvadeAnticipateTex, Vec2(0.f, 0.f), Vec2(124.f, 109.f), Vec2(124.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"ANTICIPATE_EVADE_RIGHT_HORNET", m_pHornetEvadeAnticipateTex, Vec2(0.f, 109.f), Vec2(124.f, 109.f), Vec2(124.f, 0.f), 0.05f, 3);

	GetAnimator()->CreateAnimation(L"EVADE_LEFT_HORNET",  m_pHornetEvadeTex, Vec2(0.f, 0.f), Vec2(136.f, 106.f), Vec2(136.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"EVADE_RIGHT_HORNET", m_pHornetEvadeTex, Vec2(0.f, 106.f), Vec2(136.f, 106.f), Vec2(136.f, 0.f), 0.05f, 3);


	GetAnimator()->CreateAnimation(L"COUNTER_ANTICIPATE_LEFT_HORNET",  m_pHornetCounterAnticipateTex, Vec2(0.f, 0.f), Vec2(124.f, 107.5f), Vec2(124.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"COUNTER_ANTICIPATE_RIGHT_HORNET", m_pHornetCounterAnticipateTex, Vec2(0.f, 107.5f), Vec2(124.f, 107.5f), Vec2(124.f, 0.f), 0.05f, 3);
	
	GetAnimator()->CreateAnimation(L"COUNTER_STANCE_LEFT_HORNET",  m_pHornetCounterStance, Vec2(0.f, 0.f), Vec2(124.f, 72.f), Vec2(124.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"COUNTER_STANCE_RIGHT_HORNET", m_pHornetCounterStance, Vec2(0.f, 72.f), Vec2(124.f, 72.f), Vec2(124.f, 0.f), 0.3f, 4);

	GetAnimator()->CreateAnimation(L"COUNTER_END_LEFT_HORNET",  m_pHornetCounterEnd, Vec2(0.f, 0.f), Vec2(74.f, 106.5f), Vec2(74.f, 0.f), 0.05f, 2);
	GetAnimator()->CreateAnimation(L"COUNTER_END_RIGHT_HORNET", m_pHornetCounterEnd, Vec2(0.f, 106.5f), Vec2(74.f, 106.5f), Vec2(74.f, 0.f), 0.05f, 2);

	GetAnimator()->CreateAnimation(L"COUNTER_ATTACK_ANTICIPATE_LEFT_HORNET",  m_pHornetCounterAttackAnticipateTex, Vec2(0.f, 0.f), Vec2(172.f, 140.f), Vec2(172.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"COUNTER_ATTACK_ANTICIPATE_RIGHT_HORNET", m_pHornetCounterAttackAnticipateTex, Vec2(0.f, 140.f), Vec2(172.f, 140.f), Vec2(172.f, 0.f), 0.1f, 3);

	GetAnimator()->CreateAnimation(L"COUNTER_ATTACK_LEFT_HORNET",  m_pHornetCounterAttack, Vec2(0.f, 0.f), Vec2(398.f, 166.5f), Vec2(398.f, 0.f), 0.2f, 2);
	GetAnimator()->CreateAnimation(L"COUNTER_ATTACK_RIGHT_HORNET", m_pHornetCounterAttack, Vec2(0.f, 166.5f), Vec2(398.f, 166.5f), Vec2(398.f, 0.f), 0.2f, 2);

	GetAnimator()->CreateAnimation(L"COUNTER_ATTACK_RECOVER_LEFT_HORNET",  m_pHornetCounterRecover, Vec2(0.f, 0.f), Vec2(198.f, 99.5f), Vec2(198.f, 0.f), 0.05f, 2);
	GetAnimator()->CreateAnimation(L"COUNTER_ATTACK_RECOVER_RIGHT_HORNET", m_pHornetCounterRecover, Vec2(0.f, 99.5f), Vec2(198.f, 99.5f), Vec2(198.f, 0.f), 0.05f, 2);

	GetAnimator()->CreateAnimation(L"SPHERE_ANTICIPATE_LEFT_HORNET",  m_pHornetSphereAnticipateTex, Vec2(0.f, 0.f), Vec2(160.f, 102.f), Vec2(160.f, 0.f), 0.05f, 7);
	GetAnimator()->CreateAnimation(L"SPHERE_ANTICIPATE_RIGHT_HORNET", m_pHornetSphereAnticipateTex, Vec2(0.f, 102.f), Vec2(160.f, 102.f), Vec2(160.f, 0.f), 0.05f, 7);

	GetAnimator()->CreateAnimation(L"SPHERE_LEFT_HORNET",  m_pHornetSphereTex, Vec2(0.f, 0.f), Vec2(94.f, 92.f), Vec2(94.f, 0.f), 0.11f, 9);
	GetAnimator()->CreateAnimation(L"SPHERE_RIGHT_HORNET", m_pHornetSphereTex, Vec2(0.f, 92.f), Vec2(94.f, 92.f), Vec2(94.f, 0.f), 0.11f, 9);

	GetAnimator()->CreateAnimation(L"SPHERE_RECOVER_LEFT_HORNET",  m_pHornetSphereRecoverTex, Vec2(0.f, 0.f), Vec2(182.f, 105.5f), Vec2(182.f, 0.f), 0.075f, 2);
	GetAnimator()->CreateAnimation(L"SPHERE_RECOVER_RIGHT_HORNET", m_pHornetSphereRecoverTex, Vec2(0.f, 105.5f), Vec2(182.f, 105.5f), Vec2(182.f, 0.f), 0.075f, 2);

	//작업중 
	GetAnimator()->CreateAnimation(L"STUN_ANTICIPATE_LEFT_HORNET",  m_pHornetStunAnticipateTex, Vec2(0.f, 0.f), Vec2(142.f, 93.5f), Vec2(142.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"STUN_ANTICIPATE_RIGHT_HORNET", m_pHornetStunAnticipateTex, Vec2(0.f, 93.5f), Vec2(142.f, 93.5f), Vec2(142.f, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(L"STUN_LEFT_HORNET",  m_pHornetStunTex, Vec2(0.f, 0.f), Vec2(142.f, 93.5f), Vec2(142.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"STUN_RIGHT_HORNET", m_pHornetStunTex, Vec2(0.f, 93.5f), Vec2(142.f, 93.5f), Vec2(142.f, 0.f), 0.3f, 4);


	//애니메이션 오프셋 관련 코드 
	// 돌진 애니메이션 오프셋 조정 
	CAnimation* pCounterAttack_LEFT = GetAnimator()->FindAnimation(L"COUNTER_ATTACK_LEFT_HORNET");
	for (UINT i = 0; i < pCounterAttack_LEFT->GetMaxFrame(); i++)
	{
		pCounterAttack_LEFT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pCounterAttack_RIGHT = GetAnimator()->FindAnimation(L"COUNTER_ATTACK_RIGHT_HORNET");
	for (UINT i = 0; i < pCounterAttack_RIGHT->GetMaxFrame(); i++)
	{
		pCounterAttack_RIGHT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pCounterStance_LEFT = GetAnimator()->FindAnimation(L"COUNTER_STANCE_LEFT_HORNET");
	for (UINT i = 0; i < pCounterStance_LEFT->GetMaxFrame(); i++)
	{
		pCounterStance_LEFT->GetFrame(i).vOffset = Vec2(0.f, +25.f);
	}

	CAnimation* pCounterStance_RIGHT = GetAnimator()->FindAnimation(L"COUNTER_STANCE_RIGHT_HORNET");
	for (UINT i = 0; i < pCounterStance_RIGHT->GetMaxFrame(); i++)
	{
		pCounterStance_RIGHT->GetFrame(i).vOffset = Vec2(0.f, +25.f);
	}

	//사운드 관련 
	
	CResMgr::GenInst()->LoadSound(L"RUSH_HORNET", L"sound\\Hornet\\(Rush)_Hornet_Fight_Yell_06.wav");
	CResMgr::GenInst()->LoadSound(L"RUSH_HORNET_EFFECT_SOUND", L"sound\\Hornet\\hornet_dash.wav");

	CResMgr::GenInst()->LoadSound(L"THROW_HORNET", L"sound\\Hornet\\(Throw)Hornet_Fight_Yell_09.wav");
	CResMgr::GenInst()->LoadSound(L"THORW_HORNET_EFFECT_SOUND", L"sound\\Hornet\\(Throw_Effect)hornet_needle_throw_and_return.wav");
	CResMgr::GenInst()->LoadSound(L"Jump_Rush_SOUND", L"sound\\Hornet\\(Jump_Rush)Hornet_Fight_Yell_04.wav");
	CResMgr::GenInst()->LoadSound(L"Jump_SOUND", L"sound\\Hornet\\(Jump)Hornet_Fight_Yell_03.wav");
	CResMgr::GenInst()->LoadSound(L"Hornet_Damaged", L"sound\\enemy_damage.wav");
	CResMgr::GenInst()->LoadSound(L"Horent_Death_Sound", L"sound\\Hornet\\Hornet_Fight_Death_01.wav");

	CResMgr::GenInst()->LoadSound(L"Hornet_Parry_Anticipate_Sound", L"sound\\Hornet\\Hornet_Fight_Yell_05.wav");
	CResMgr::GenInst()->LoadSound(L"Hornet_Parry_PrePare_Sound", L"sound\\Hornet\\hornet_parry_prepare.wav");
	CResMgr::GenInst()->LoadSound(L"Hornet_Parry_Sound", L"sound\\Hornet\\hornet_parry.wav");
	CResMgr::GenInst()->LoadSound(L"Hornet_Sphere_Sound", L"sound\\Hornet\\Hornet_Fight_Flourish_02.wav");
	CResMgr::GenInst()->LoadSound(L"Hornet_Sphere_Effect_Sound", L"sound\\Hornet\\hornet_needle_thow.wav");
	CResMgr::GenInst()->LoadSound(L"Hornet_Count_Stance_Sound", L"sound\\Hornet\\Hornet_Greenpath_01.wav");
	CResMgr::GenInst()->LoadSound(L"Hornet_Stun_Sound", L"sound\\Hornet\\Hornet_Fight_Stun_03.wav");

	//CResMgr::GenInst()->LoadSound(L"hit_Ground", L"sound\\False_Knight\\false_knight_strike_ground.wav");
	dwtime = GetTickCount64();
}

CHornet::~CHornet()
{
}

void CHornet::update()
{
	update_move();
	update_state();
	update_sound();
	update_animation();

	HORNET_STATE patterns[] =
	{
		HORNET_STATE::RUSH_ANTICIPATE,
		HORNET_STATE::THROW_ANTICIPATE,
		HORNET_STATE::JUMP_ANTICIPATE,
		//HORNET_STATE::EVADE_ANTICIPATE,
		HORNET_STATE::COUNTER_ANTICIPATE,
		HORNET_STATE::SPHERE_ANTICIPATE,
	
	};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 6);

	////여기서 조건좀 수정해서 몇초에 한번씩 패턴주기.
	if (dwtime + 2000 < GetTickCount64() 
		&& m_eCurState != HORNET_STATE::STUN
		&& m_eCurState != HORNET_STATE::STUN_ANTICIPATE
		&& m_eCurState != HORNET_STATE::DEAD)
	{
		m_iPatternCount++;
		int randomIndex = dis(gen);
		m_eCurState = patterns[randomIndex];

		
		/*if (m_iPatternCount % 6 == 0)
		{
			m_eCurState = HORNET_STATE::RUSH_ANTICIPATE;
		}

		else if (m_iPatternCount % 6 == 1)
		{
			m_eCurState = HORNET_STATE::THROW_ANTICIPATE;
		}

		else if (m_iPatternCount % 6 == 2)
		{
			m_eCurState = HORNET_STATE::JUMP_ANTICIPATE;
		}

		else if (m_iPatternCount % 6 == 3)
		{
			m_eCurState = HORNET_STATE::EVADE_ANTICIPATE;
		}

		else if (m_iPatternCount % 6 == 4)
		{
			m_eCurState = HORNET_STATE::COUNTER_ANTICIPATE;
		}
		else if (m_iPatternCount % 6 == 5)
		{
			m_eCurState = HORNET_STATE::SPHERE_ANTICIPATE;
		}
		*/
		dwtime = GetTickCount64();
	}

	m_ePreState = m_eCurState;

}

void CHornet::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}


void CHornet::update_move()
{
	Vec2 vPos = GetPos();
	


	if (vPos.x - 1000 < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x > CPlayerMgr::GenInst()->GetCurPlayerPos().x)
	{
		if (m_eCurState != HORNET_STATE::DEAD)
		{

			if (m_eCurState != HORNET_STATE::RUSH
				&& m_eCurState != HORNET_STATE::RUSH_RECOVER
				&& m_eCurState != HORNET_STATE::JUMP
				&& m_eCurState != HORNET_STATE::JUMP_RUSH
				&& m_eCurState != HORNET_STATE::JUMP_LAND
				&& m_eCurState != HORNET_STATE::EVADE
				&& m_eCurState != HORNET_STATE::SPHERE
				&& m_eCurState != HORNET_STATE::SPHERE_RECOVER
				&& m_eCurState != HORNET_STATE::STUN_ANTICIPATE
				&& m_eCurState != HORNET_STATE::STUN)
			{
				m_iDir = -1;
			}



		}
	}

	else if (vPos.x + 1000 > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x < CPlayerMgr::GenInst()->GetCurPlayerPos().x)
	{
		if (m_eCurState != HORNET_STATE::DEAD)
		{
			if (m_eCurState == HORNET_STATE::IDLE)
			{
				//vPos.x += 100 * fDT;
			}

			if (m_eCurState != HORNET_STATE::RUSH
				&& m_eCurState != HORNET_STATE::RUSH_RECOVER
				&& m_eCurState != HORNET_STATE::JUMP
				&& m_eCurState != HORNET_STATE::JUMP_RUSH
				&& m_eCurState != HORNET_STATE::JUMP_LAND
				&& m_eCurState != HORNET_STATE::EVADE
				&& m_eCurState != HORNET_STATE::SPHERE
				&& m_eCurState != HORNET_STATE::SPHERE_RECOVER
				&& m_eCurState != HORNET_STATE::STUN_ANTICIPATE
				&& m_eCurState != HORNET_STATE::STUN)
				
			{
				m_iDir = 1;
			}

		}
	}



	//돌진 상태일때의 돌진 속도 
	if (m_eCurState == HORNET_STATE::RUSH && m_iDir == -1)
	{
		vPos.x -= 2000 * fDT;
	}

	if (m_eCurState == HORNET_STATE::RUSH && m_iDir == 1)
	{
		vPos.x += 2000 * fDT;
	}

	//GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));

	if (m_eCurState == HORNET_STATE::JUMP && m_iDir == -1)
	{
		vPos.x -= 300 * fDT;
		GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
		
		vDir = (CPlayerMgr::GenInst()->GetCurPlayerPos() - vPos).Normalize();

	}

	if (m_eCurState == HORNET_STATE::JUMP && m_iDir == 1)
	{
		vPos.x += 300 * fDT;
		GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
		vDir = (CPlayerMgr::GenInst()->GetCurPlayerPos() - vPos).Normalize();
	}

	if (m_eCurState == HORNET_STATE::JUMP_RUSH && m_iDir == -1)
	{

		// 땅과 충돌하면 이 거 진행 x
		if(GroundOn == false)
		{
		
			vPos.x += 1500 * vDir.x * fDT;
			vPos.y += 1500 * vDir.y * fDT;
			
		}
	
	}

	if (m_eCurState == HORNET_STATE::JUMP_RUSH && m_iDir == 1)
	{
		
		// 땅과 충돌하면 이거 진행 x 
		if (GroundOn == false)
		{
			
			vPos.x += 2000 * vDir.x * fDT;
			vPos.y += 2000 * vDir.y * fDT;
			
		}

	}

	if (m_eCurState == HORNET_STATE::EVADE && m_iDir == -1)
	{
		vPos.x += 2000 * fDT;
	}

	if (m_eCurState == HORNET_STATE::EVADE && m_iDir == 1)
	{
		vPos.x -= 2000 * fDT;
	}

	//GetRigidBody()->SetVelocity(Vec2(vV.x, 0.f));

	if (m_eCurState == HORNET_STATE::SPHERE_ANTICIPATE && m_iDir == -1)
	{
		vPos.x -= 500 * fDT;
		
		
		GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
		
		
	}

	if (m_eCurState == HORNET_STATE::SPHERE_ANTICIPATE && m_iDir == 1)
	{
	
		vPos.x += 500 * fDT;
		
		GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
		
	}

	if (m_eCurState == HORNET_STATE::SPHERE && m_iDir == -1)
	{
		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	}

	if (m_eCurState == HORNET_STATE::SPHERE && m_iDir == 1)
	{

		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	}

	if (m_eCurState == HORNET_STATE::SPHERE_RECOVER && m_iDir == -1)
	{
		if (GroundOn == false)
		{
			vPos.x -= 500 * fDT;
			vPos.y += 1000  * fDT;

		}
	}

	if (m_eCurState == HORNET_STATE::SPHERE_RECOVER && m_iDir == 1)
	{

		if (GroundOn == false)
		{
			vPos.x += 500 * fDT;
			vPos.y += 1000 * fDT;

		}
	}

	if (m_eCurState == HORNET_STATE::STUN_ANTICIPATE && m_iDir == -1)
	{
		vPos.x += 250 * fDT;
	}

	if (m_eCurState == HORNET_STATE::STUN_ANTICIPATE && m_iDir == 1)
	{

		vPos.x -= 250 * fDT;
	}


	SetPos(vPos);
}

void CHornet::update_state()
{

}

void CHornet::update_sound()
{
	
	CSound* pRushSound = CResMgr::GenInst()->FindSound(L"RUSH_HORNET");
	CSound* pRushEffectSound = CResMgr::GenInst()->FindSound(L"RUSH_HORNET_EFFECT_SOUND");

	CSound* pThrowSound = CResMgr::GenInst()->FindSound(L"THROW_HORNET");
	CSound* pThrowEffectSound = CResMgr::GenInst()->FindSound(L"THORW_HORNET_EFFECT_SOUND");
	CSound* pJumpRushSound = CResMgr::GenInst()->FindSound(L"Jump_Rush_SOUND");
	CSound* pJumpSound = CResMgr::GenInst()->FindSound(L"Jump_SOUND");
	CSound* pParryAnticipateSound = CResMgr::GenInst()->FindSound(L"Hornet_Parry_Anticipate_Sound");
	CSound* pParryPrePareSound = CResMgr::GenInst()->FindSound(L"Hornet_Parry_PrePare_Sound");
	CSound* pParrySound = CResMgr::GenInst()->FindSound(L"Hornet_Parry_Sound");

	CSound* pSphereSound = CResMgr::GenInst()->FindSound(L"Hornet_Sphere_Sound");
	CSound* pSphereEffectSound = CResMgr::GenInst()->FindSound(L"Hornet_Sphere_Effect_Sound");
	CSound* pCountStandSound = CResMgr::GenInst()->FindSound(L"Hornet_Count_Stance_Sound");
	CSound* pStunSound = CResMgr::GenInst()->FindSound(L"Hornet_Stun_Sound");


	pStunSound->SetVolume(65.f);
	pSphereEffectSound->SetVolume(80.f);

	switch (m_eCurState)
	{
	case HORNET_STATE::IDLE:
		break;
	case HORNET_STATE::JUMP_ANTICIPATE:
		break;
	case HORNET_STATE::COUNTER_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pParryAnticipateSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case HORNET_STATE::COUNTER_STANCE:
		if (!m_bSoundPlayed)
		{
			pCountStandSound->Play(false);
			pParryPrePareSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case HORNET_STATE::COUNTER_ATTACK_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pParrySound->SetVolume(100.f);
			pParrySound->Play(false);
			m_bSoundPlayed = true;
		}
		break;

	case HORNET_STATE::JUMP:
		if (!m_bSoundPlayed)
		{
			pJumpSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case HORNET_STATE::JUMP_RUSH:
		if (!m_bSoundPlayed)
		{
			CreateDashEffect();
			pRushEffectSound->Play(false);
			pJumpRushSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case HORNET_STATE::JUMP_LAND:
		break;
	case HORNET_STATE::RUSH_ANTICIPATE:
		break;
	case HORNET_STATE::RUSH:
		if (!m_bSoundPlayed)
		{
			CreateDashEffect();
			pRushEffectSound->Play(false);
			pRushSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case HORNET_STATE::RUSH_RECOVER:
		break;
	case HORNET_STATE::ATTACK_ANTICIPATE:
		break;
	case HORNET_STATE::ATTACK:
		break;
	case HORNET_STATE::ATTACK_RECOVER:
		break;
	case HORNET_STATE::THROW_ANTICIPATE:
		break;
	case HORNET_STATE::THROW:
		if (!m_bSoundPlayed)
		{
			CreateThrowEffect();
			CreateNeedle();
			CreateThread();
			pThrowSound->Play(false);
			pThrowEffectSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case HORNET_STATE::THROW_RECOVER:
		break;
	case HORNET_STATE::STUN_ANTICIPATE:
		if(!m_bSoundPlayed)
		{
			CreateStunEffect();
			pStunSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case HORNET_STATE::EVADE_ANTICIPATE:
		break;
	case HORNET_STATE::EVADE:
		break;

	case HORNET_STATE::SPHERE_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pJumpSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case HORNET_STATE::SPHERE:
		if(!m_bSoundPlayed)
		{
			CreateSphereBallEffect();
			pSphereSound ->Play(false);
			pSphereEffectSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case HORNET_STATE::DEAD:
		break;
	default:
		break;
	}
}

void CHornet::update_animation()
{


	// 평상시 가만히 있는 상태

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::IDLE)
	{
		GetAnimator()->Play(L"Idle_LEFT_HORNET", true);
		m_bSoundPlayed = false;
		//{
		//	if (GetAnimator()->GetAnimation()->IsFinish())
		//	{
		//		GetAnimator()->SetAnimationFrame(L"Idle_LEFT_HORNET", 0);
		//		m_eCurState = HORNET_STATE::IDLE;
		//		//7월 8일 수정
		//		m_bSoundPlayed = false;
		//	}
		//}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::IDLE)
	{
		GetAnimator()->Play(L"Idle_RIGHT_HORNET", true);
		m_bSoundPlayed = false;
		//if (GetAnimator()->GetAnimation()->IsFinish())
		//{
		//	GetAnimator()->SetAnimationFrame(L"Idle_RIGHT_HORNET", 0);
		//	m_eCurState = HORNET_STATE::IDLE;
		//	//7월 8일 수정
		//	m_bSoundPlayed = false;
		//}

	}

	// 돌진 관련 부분
	// ===========================================================
	if (m_iDir == -1 && m_eCurState == HORNET_STATE::RUSH_ANTICIPATE)
	{
		GetAnimator()->Play(L"RUSH_ANTICIPATE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"RUSH_ANTICIPATE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::RUSH;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::RUSH_ANTICIPATE)
	{
		GetAnimator()->Play(L"RUSH_ANTICIPATE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"RUSH_ANTICIPATE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::RUSH;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::RUSH)
	{
		
		GetAnimator()->Play(L"RUSH_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"RUSH_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::RUSH_RECOVER;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::RUSH)
	{
		
		GetAnimator()->Play(L"RUSH_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"RUSH_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::RUSH_RECOVER;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::RUSH_RECOVER)
	{
		GetAnimator()->Play(L"RUSH_RECOVER_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"RUSH_RECOVER_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::RUSH_RECOVER)
	{
		GetAnimator()->Play(L"RUSH_RECOVER_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"RUSH_RECOVER_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}


	//투창 부분
	//================================================================
	if (m_iDir == -1 && m_eCurState == HORNET_STATE::THROW_ANTICIPATE)
	{
		GetAnimator()->Play(L"THROW_ANTICIPATE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"THROW_ANTICIPATE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::THROW;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::THROW_ANTICIPATE)
	{
		GetAnimator()->Play(L"THROW_ANTICIPATE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"THROW_ANTICIPATE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::THROW;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::THROW)
	{

		GetAnimator()->Play(L"THROW_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"THROW_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::THROW_RECOVER;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::THROW)
	{

		GetAnimator()->Play(L"THROW_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"THROW_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::THROW_RECOVER;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::THROW_RECOVER)
	{
		GetAnimator()->Play(L"THROW_RECOVER_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"THROW_RECOVER_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::THROW_RECOVER)
	{
		GetAnimator()->Play(L"THROW_RECOVER_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"THROW_RECOVER_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}


	//점프 부분 
	//=============================================================================

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::JUMP_ANTICIPATE)
	{
		GetAnimator()->Play(L"JUMP_ANTICIPATE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"JUMP_ANTICIPATE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::JUMP;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::JUMP_ANTICIPATE)
	{
		GetAnimator()->Play(L"JUMP_ANTICIPATE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"JUMP_ANTICIPATE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::JUMP;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::JUMP)
	{

		GetAnimator()->Play(L"JUMP_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"JUMP_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::JUMP_RUSH;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::JUMP)
	{

		GetAnimator()->Play(L"JUMP_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"JUMP_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::JUMP_RUSH;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}
	if (m_iDir == -1 && m_eCurState == HORNET_STATE::JUMP_RUSH)
	{
		GetAnimator()->Play(L"JUMP_RUSH_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"JUMP_RUSH_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::JUMP_LAND;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::JUMP_RUSH)
	{
		GetAnimator()->Play(L"JUMP_RUSH_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"JUMP_RUSH_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::JUMP_LAND;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::JUMP_LAND)
	{
		GetAnimator()->Play(L"JUMP_LAND_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"JUMP_LAND_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::JUMP_LAND)
	{
		GetAnimator()->Play(L"JUMP_LAND_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"JUMP_LAND_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}


	// 백스탭 부분 패턴 
	// ============================================================

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::EVADE_ANTICIPATE)
	{
		GetAnimator()->Play(L"ANTICIPATE_EVADE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"ANTICIPATE_EVADE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::EVADE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::EVADE_ANTICIPATE)
	{
		GetAnimator()->Play(L"ANTICIPATE_EVADE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"ANTICIPATE_EVADE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::EVADE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::EVADE)
	{

		GetAnimator()->Play(L"EVADE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"EVADE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::EVADE)
	{

		GetAnimator()->Play(L"EVADE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"EVADE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	//패링
	//==================================================
	if (m_iDir == -1 && m_eCurState == HORNET_STATE::COUNTER_ANTICIPATE)
	{
		GetAnimator()->Play(L"COUNTER_ANTICIPATE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"COUNTER_ANTICIPATE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::COUNTER_STANCE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::COUNTER_ANTICIPATE)
	{
		GetAnimator()->Play(L"COUNTER_ANTICIPATE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"COUNTER_ANTICIPATE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::COUNTER_STANCE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::COUNTER_STANCE)
	{

		GetAnimator()->Play(L"COUNTER_STANCE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"COUNTER_STANCE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::COUNTER_END;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::COUNTER_STANCE)
	{

		GetAnimator()->Play(L"COUNTER_STANCE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"COUNTER_STANCE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::COUNTER_END;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::COUNTER_END)
	{
		GetAnimator()->Play(L"COUNTER_END_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"COUNTER_END_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::COUNTER_END)
	{
		GetAnimator()->Play(L"COUNTER_END_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"COUNTER_END_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	//카운터 부분 
	// =============================================================

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::COUNTER_ATTACK_ANTICIPATE)
	{
		GetAnimator()->Play(L"COUNTER_ATTACK_ANTICIPATE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"COUNTER_ATTACK_ANTICIPATE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::COUNTER_ATTACK;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::COUNTER_ATTACK_ANTICIPATE)
	{
		GetAnimator()->Play(L"COUNTER_ATTACK_ANTICIPATE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"COUNTER_ATTACK_ANTICIPATE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::COUNTER_ATTACK;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::COUNTER_ATTACK)
	{

		GetAnimator()->Play(L"COUNTER_ATTACK_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"COUNTER_ATTACK_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::COUNTER_ATTACK_RECOVER;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::COUNTER_ATTACK)
	{

		GetAnimator()->Play(L"COUNTER_ATTACK_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"COUNTER_ATTACK_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::COUNTER_ATTACK_RECOVER;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::COUNTER_ATTACK_RECOVER)
	{
		GetAnimator()->Play(L"COUNTER_ATTACK_RECOVER_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"COUNTER_ATTACK_RECOVER_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::COUNTER_ATTACK_RECOVER)
	{
		GetAnimator()->Play(L"COUNTER_ATTACK_RECOVER_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"COUNTER_ATTACK_RECOVER_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	// 원범위 공격 패턴 
	// ====================================================================================

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::SPHERE_ANTICIPATE)
	{
		GetAnimator()->Play(L"SPHERE_ANTICIPATE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SPHERE_ANTICIPATE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::SPHERE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::SPHERE_ANTICIPATE)
	{
		GetAnimator()->Play(L"SPHERE_ANTICIPATE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"SPHERE_ANTICIPATE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::SPHERE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::SPHERE)
	{

		GetAnimator()->Play(L"SPHERE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SPHERE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::SPHERE_RECOVER;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::SPHERE)
	{

		GetAnimator()->Play(L"SPHERE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"SPHERE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::SPHERE_RECOVER;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::SPHERE_RECOVER)
	{
		GetAnimator()->Play(L"SPHERE_RECOVER_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SPHERE_RECOVER_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::SPHERE_RECOVER)
	{
		GetAnimator()->Play(L"SPHERE_RECOVER_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"SPHERE_RECOVER_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}


	// 스턴 상태 
	// ========================================================================
	if (m_iDir == -1 && m_eCurState == HORNET_STATE::STUN_ANTICIPATE) // 여기서 부터 수정 
	{
		GetAnimator()->Play(L"STUN_ANTICIPATE_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"STUN_ANTICIPATE_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::STUN;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::STUN_ANTICIPATE)
	{
		GetAnimator()->Play(L"STUN_ANTICIPATE_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"STUN_ANTICIPATE_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::STUN;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == HORNET_STATE::STUN)
	{

		GetAnimator()->Play(L"STUN_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"STUN_LEFT_HORNET", 0);
				m_eCurState = HORNET_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::STUN)
	{

		GetAnimator()->Play(L"STUN_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"STUN_RIGHT_HORNET", 0);
			m_eCurState = HORNET_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	// Dead
	if (m_iDir == -1 && m_eCurState == HORNET_STATE::DEAD)
	{

		GetAnimator()->Play(L"STUN_LEFT_HORNET", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				DeleteObject(this);
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == HORNET_STATE::DEAD)
	{

		GetAnimator()->Play(L"STUN_RIGHT_HORNET", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			
			DeleteObject(this);
			m_bSoundPlayed = false;
		}

	}

	


	//GetAnimator()->Play(L"Idle_LEFT_HORNET", true);
	//GetAnimator()->Play(L"RUSH_ANTICIPATE_LEFT_HORNET", true);
	//GetAnimator()->Play(L"RUSH_LEFT_HORNET", true);
	//GetAnimator()->Play(L"RUSH_RECOVER_LEFT_HORNET", true);
}




void CHornet::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Ground")
	{
		GroundOn = true;
	}
}

void CHornet::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pHornetDamagedSound = CResMgr::GenInst()->FindSound(L"Hornet_Damaged");


	CObject* pOtherObj = _pOther->GetObj();

	
	if (L"SLASH" == _pOther->GetObj()->GetName()
		|| pOtherObj->GetName() == L"DOWN_SLASH_Effect")
	{

		//패링시 공격이 들어왔을 때 
		if(m_eCurState == HORNET_STATE::COUNTER_ANTICIPATE || m_eCurState == HORNET_STATE::COUNTER_STANCE)
		{
			m_bSoundPlayed = false;
			m_eCurState = HORNET_STATE::COUNTER_ATTACK_ANTICIPATE;
		}

		if (m_iPatternCount % 5 == 1)
		{
			m_bSoundPlayed = false;
			m_eCurState = HORNET_STATE::STUN_ANTICIPATE;
		}

		m_iHP--; 

		
		pHornetDamagedSound->Play(false);

		if (CPlayerMgr::GenInst()->GetPlayerMp() < 6)
		{
			CPlayerMgr::GenInst()->IncreaseMp(1);
		}


		if (m_iHP < 0)
		{

			CSound* pHorentDeadSound = CResMgr::GenInst()->FindSound(L"Horent_Death_Sound");
			pHorentDeadSound->Play(false);

			m_eCurState = HORNET_STATE::DEAD;

			// 여기다가 작성하기. 일단 Dead 상태로 만들고 해서 패턴 못쓰게 하기.
			//DeleteObject(this);
		}

	}

	if (L"FireBall" == _pOther->GetObj()->GetName())
	{

		m_iHP--;
		pHornetDamagedSound->Play(false);
		DeleteObject(pOtherObj);

		if (CPlayerMgr::GenInst()->GetPlayerMp() < 6)
		{
			CPlayerMgr::GenInst()->IncreaseMp(1);
		}


		if (m_iHP < 0)
		{

			CSound* pHorentDeadSound = CResMgr::GenInst()->FindSound(L"Horent_Death_Sound");
			pHorentDeadSound->Play(false);

			m_eCurState = HORNET_STATE::DEAD;

			// 여기다가 작성하기. 일단 Dead 상태로 만들고 해서 패턴 못쓰게 하기.
			//DeleteObject(this);
		}

	}
}

void CHornet::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Ground")
	{
		GroundOn = false;
	}
}


void CHornet::CreateDashEffect()
{
	CHornetDashEffect* pHornetDashEffect = new CHornetDashEffect;

	pHornetDashEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pHornetDashEffect->SetPos(GetPos() + Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pHornetDashEffect->SetPos(GetPos() - Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pHornetDashEffect->SetName(L"HORNET_DASH_EFFECT");

	CreateObject(pHornetDashEffect, GROUP_TYPE::SKILLEFFECT);
}

void CHornet::CreateNeedle()
{
	CNeedle* pHornetNeedleEffect = new CNeedle;

	pHornetNeedleEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pHornetNeedleEffect->SetPos(GetPos() - Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pHornetNeedleEffect->SetPos(GetPos() + Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pHornetNeedleEffect->SetName(L"HORNET_TRHOW_NEEDLE");

	CreateObject(pHornetNeedleEffect, GROUP_TYPE::MONSTER);
}

void CHornet::CreateThread()
{
	CNeedleThread* pHornetThreadEffect = new CNeedleThread;

	pHornetThreadEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pHornetThreadEffect->SetPos(GetPos() - Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pHornetThreadEffect->SetPos(GetPos() + Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pHornetThreadEffect->SetName(L"HORNET_TRHOW_THREAD");

	CreateObject(pHornetThreadEffect, GROUP_TYPE::SKILLEFFECT);
}

void CHornet::CreateThrowEffect()
{
	CThrowEffect* pThrowEffect = new CThrowEffect;

	pThrowEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pThrowEffect->SetPos(GetPos() + Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pThrowEffect->SetPos(GetPos() - Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pThrowEffect->SetName(L"HORNET_THROW_EFFECT");

	CreateObject(pThrowEffect, GROUP_TYPE::SKILLEFFECT);
}

void CHornet::CreateSphereBallEffect()
{
	CSphereBall* pSphereBallEffect = new CSphereBall;

	pSphereBallEffect->SetPos(GetPos()); // 플레이어의 좌표 받아옴

	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pSphereBallEffect->SetName(L"SPHERE_BALL_EFFECT");

	CreateObject(pSphereBallEffect, GROUP_TYPE::MONSTER);
}

void CHornet::CreateStunEffect()
{
	CStunEffect* pStuneffect = new CStunEffect;

	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 
	pStuneffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pStuneffect->SetPos(GetPos() - Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pStuneffect->SetPos(GetPos() + Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pStuneffect->SetName(L"Stun_Effect");

	CreateObject(pStuneffect, GROUP_TYPE::SKILLEFFECT);
}


