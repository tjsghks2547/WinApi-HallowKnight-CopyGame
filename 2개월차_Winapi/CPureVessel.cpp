#include "pch.h"
#include "CPureVessel.h"
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
#include "CSpikeEffect.h"
#include "COrb.h"
#include "CSpear.h"
#include "CSpear20minusAngle.h"
#include "CSpear5angle.h"
#include "CSpear8_5MinusAngle.h"
#include "CSpear15Angle.h"
#include "CSpear30angle.h"

//CResMgr::GenInst()->LoadSound(L"orb_boom", L"sound\\Vessel_Sound\\gg_pure_vessel_small_orb_appear_and_burst.wav");
//CSound* pOrbBoom = CResMgr::GenInst()->FindSound(L"orb_boom");
//pOrbBoom->SetVolume(80.f);
//pOrbBoom->Play(false);

CPureVessel::CPureVessel()
	: m_iHP(50)
	, m_iDir(1)
	, m_iCount(0)
	, m_iPatternCount(0)
	, m_bSoundPlayed(false)
	, m_eCurState(PURE_VESSEL_STATE::IDLE)
	, m_ePreState(PURE_VESSEL_STATE::IDLE)
	, GroundOn(false)
	, m_iSlashCount(0)
	, m_bSpearMinus20(false)
	, m_bSpear5Angle(false)
	, m_bSpear8_5Angle(false)
	, m_bSpear15Angle(false)
	, m_bSpear30Angle(false)
	, m_bCircleEffect1(false)
	, m_bCircleEffect2(false)
	, m_bCircleEffect3(false)
	, m_bCircleEffect4(false)
	, m_bCircleEffect5(false)
	, m_bCircleEffect6(false)
	, m_bCircleEffect7(false)

{
	CreateCollider();
	CreateAnimator();

	CreateGravity();
	CreateRigidBody();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 75.f));
	GetCollider()->SetScale(Vec2(200.f, 200.f));


	//Idle
	CTexture* m_pIdleTex = CResMgr::GenInst()->LoadTexture(L"Pure_Idle", L"texture\\PureVessel\\Idle.bmp");

	//Slash Anticipate
	CTexture* m_pPureSlashAnticipateTex = CResMgr::GenInst()->LoadTexture(L"Pure_Slash_LEFT_Anticipate", L"texture\\PureVessel\\Slash_Anticipate_test.bmp");
	
	//Slash
	CTexture* m_pPureSlashTex = CResMgr::GenInst()->LoadTexture(L"Pure_Slash", L"texture\\PureVessel\\SLASH2.bmp");


	//Dash
	CTexture* m_pDashAnticipateTex = CResMgr::GenInst()->LoadTexture(L"Pure_Dash_Anticipate", L"texture\\PureVessel\\DASH_Anticipate.bmp");
	CTexture* m_pDashTex = CResMgr::GenInst()->LoadTexture(L"Pure_Dash", L"texture\\PureVessel\\DASH.bmp");
	CTexture* m_pDashEndTex = CResMgr::GenInst()->LoadTexture(L"Pure_Dash_End", L"texture\\PureVessel\\DASH_END.bmp");

	//Roar
	CTexture* m_pRoarAnticipateTex = CResMgr::GenInst()->LoadTexture(L"Pure_Roar_Anticipate", L"texture\\PureVessel\\Roar_Anticipate.bmp");
	CTexture* m_pRoarTex = CResMgr::GenInst()->LoadTexture(L"Pure_Roar", L"texture\\PureVessel\\Roar.bmp");
	CTexture* m_pRoarEndTex = CResMgr::GenInst()->LoadTexture(L"Pure_Roar_End", L"texture\\PureVessel\\Roar_End.bmp");

	//Spike Attack
	CTexture* m_pSpikeAttackAnticipateTex = CResMgr::GenInst()->LoadTexture(L"Pure_Spike_Anticipate", L"texture\\PureVessel\\SpikeAttack_Anticipate.bmp");
	CTexture* m_pSpikeAttackTex = CResMgr::GenInst()->LoadTexture(L"Pure_Spike", L"texture\\PureVessel\\SpikeAttack.bmp");
	CTexture* m_pSpikeAttackEndTex = CResMgr::GenInst()->LoadTexture(L"Pure_Spike_End", L"texture\\PureVessel\\SpikeAttack_End.bmp");

	//TelePort
	CTexture* m_pTelePortAnticipateTex = CResMgr::GenInst()->LoadTexture(L"Pure_TelePort_Anticipate", L"texture\\PureVessel\\Teleport_Anticipate.bmp");
	CTexture* m_pTelePortTex = CResMgr::GenInst()->LoadTexture(L"Pure_TelePort", L"texture\\PureVessel\\Teleport.bmp");

	//DartShot
	CTexture* m_pDartShotAnticipateTex = CResMgr::GenInst()->LoadTexture(L"Pure_Dart_Shoot_Anticipate", L"texture\\PureVessel\\DartShot_Anticipate.bmp");
	CTexture* m_pDartShotTex = CResMgr::GenInst()->LoadTexture(L"Pure_Dart_Shoot", L"texture\\PureVessel\\DartShot_Real2.bmp");
	CTexture* m_pDartShotEndTex = CResMgr::GenInst()->LoadTexture(L"Pure_Dart_Shoot_End", L"texture\\PureVessel\\DartShot_End.bmp");

	//Dead
	CTexture* m_pDeadTex = CResMgr::GenInst()->LoadTexture(L"Pure_Dead", L"texture\\PureVessel\\Purvessel_Dead.bmp");


	//Idle
	GetAnimator()->CreateAnimation(L"IDLE_LEFT_PURE",  m_pIdleTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.15f, 5);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT_PURE", m_pIdleTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.15f, 5);


	//Slash Anticipate
	GetAnimator()->CreateAnimation(L"SLASH_ANTICIPATE_LEFT_PURE",  m_pPureSlashAnticipateTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.05f, 8);
	GetAnimator()->CreateAnimation(L"SLASH_ANTICIPATE_RIGHT_PURE", m_pPureSlashAnticipateTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.05f, 8);

	//Slash
	GetAnimator()->CreateAnimation(L"SLASH_LEFT_PURE",  m_pPureSlashTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.15f, 11);
	GetAnimator()->CreateAnimation(L"SLASH_RIGHT_PURE", m_pPureSlashTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.15f, 11);

	//Dash Anticipate
	GetAnimator()->CreateAnimation(L"DASH_ANTICIPATE_LEFT_PURE",  m_pDashAnticipateTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"DASH_ANTICIPATE_RIGHT_PURE", m_pDashAnticipateTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 6);

	//Dash
	GetAnimator()->CreateAnimation(L"DASH_LEFT_PURE",  m_pDashTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"DASH_RIGHT_PURE", m_pDashTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.2f, 3);

	//Dash End
	GetAnimator()->CreateAnimation(L"DASH_END_LEFT_PURE",  m_pDashEndTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"DASH_END_RIGHT_PURE", m_pDashEndTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 4);


	//Roar Anticipate
	GetAnimator()->CreateAnimation(L"ROAR_ANTICIPATE_LEFT_PURE",  m_pRoarAnticipateTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"ROAR_ANTICIPATE_RIGHT_PURE", m_pRoarAnticipateTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 6);


	//Roar
	GetAnimator()->CreateAnimation(L"ROAR_LEFT_PURE",  m_pRoarTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.15f, 7);
	GetAnimator()->CreateAnimation(L"ROAR_RIGHT_PURE", m_pRoarTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.15f, 7);

	//Roar End
	GetAnimator()->CreateAnimation(L"ROAR_END_LEFT_PURE",  m_pRoarEndTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"ROAR_END_RIGHT_PURE", m_pRoarEndTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 4);


	//SpikeAttack Anticipate
	GetAnimator()->CreateAnimation(L"SPIKE_ANTICIPATE_LEFT_PURE",  m_pSpikeAttackAnticipateTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"SPIKE_ANTICIPATE_RIGHT_PURE", m_pSpikeAttackAnticipateTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 4);

	//Spike Attack
	GetAnimator()->CreateAnimation(L"SPIKE_LEFT_PURE",  m_pSpikeAttackTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.15f, 4);
	GetAnimator()->CreateAnimation(L"SPIKE_RIGHT_PURE", m_pSpikeAttackTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.15f, 4);

	//Spike End
	GetAnimator()->CreateAnimation(L"SPIKE_END_LEFT_PURE",  m_pSpikeAttackEndTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"SPIKE_END_RIGHT_PURE", m_pSpikeAttackEndTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.1f, 4);


	//TelePort Anticipate
	GetAnimator()->CreateAnimation(L"TELEPORT_ANTICIPATE_LEFT_PURE",  m_pTelePortAnticipateTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.05f, 5);
	GetAnimator()->CreateAnimation(L"TELEPORT_ANTICIPATE_RIGHT_PURE", m_pTelePortAnticipateTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.05f, 5);

	//TelePort
	GetAnimator()->CreateAnimation(L"TELEPORT_LEFT_PURE",  m_pTelePortTex, Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.05f, 5);
	GetAnimator()->CreateAnimation(L"TELEPORT_RIGHT_PURE", m_pTelePortTex, Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.05f, 5);

	//DartShot Anticipate
	GetAnimator()->CreateAnimation(L"DART_SHOT_ANTICIPATE_LEFT_PURE",  m_pDartShotAnticipateTex, Vec2(0.f, 0.f), Vec2(626.f, 466.f), Vec2(626.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"DART_SHOT_ANTICIPATE_RIGHT_PURE", m_pDartShotAnticipateTex, Vec2(0.f, 466.f), Vec2(626.f, 466.f), Vec2(626.f, 0.f), 0.1f, 5);
	
	//DartShot
	GetAnimator()->CreateAnimation(L"DART_SHOT_LEFT_PURE",  m_pDartShotTex, Vec2(0.f, 0.f), Vec2(626.f, 466.f), Vec2(626.f, 0.f), 0.15f, 7);
	GetAnimator()->CreateAnimation(L"DART_SHOT_RIGHT_PURE", m_pDartShotTex, Vec2(0.f, 466.f), Vec2(626.f, 466.f), Vec2(626.f, 0.f), 0.15f, 7);

	//DartShot End 
	GetAnimator()->CreateAnimation(L"DART_SHOT_END_LEFT_PURE",  m_pDartShotEndTex, Vec2(0.f, 0.f), Vec2(626.f, 466.f), Vec2(626.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"DART_SHOT_END_RIGHT_PURE", m_pDartShotEndTex, Vec2(0.f, 466.f), Vec2(626.f, 466.f), Vec2(626.f, 0.f), 0.1f, 4);


	//Dead
	GetAnimator()->CreateAnimation(L"DEAD_LEFT_PURE",  m_pDeadTex , Vec2(0.f, 0.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.5f, 6);
	GetAnimator()->CreateAnimation(L"DEAD_RIGHT_PURE", m_pDeadTex , Vec2(0.f, 606.f), Vec2(864.f, 606.f), Vec2(864.f, 0.f), 0.5f, 6);



	//Sound

	CResMgr::GenInst()->LoadSound(L"DASH_PURE_VESSEL", L"sound\\Vessel_Sound\\Dash_On.wav");
	CResMgr::GenInst()->LoadSound(L"SPIKE_ATTACK_ANTICIAPTE_PURE_VESSEL", L"sound\\Vessel_Sound\\Spike_On_Sound.wav");
	CResMgr::GenInst()->LoadSound(L"SPIKE_ATTACK_PURE_VESSEL", L"sound\\Vessel_Sound\\SpikeAttack_On.wav");
	CResMgr::GenInst()->LoadSound(L"SPIKE_ATTACK_END_PURE_VESSEL", L"sound\\Vessel_Sound\\Spike_End_Sound.wav");
	CResMgr::GenInst()->LoadSound(L"TELEPORT_PURE_VESSEL", L"sound\\Vessel_Sound\\Tele_In.wav");

	CResMgr::GenInst()->LoadSound(L"SLASH_PURE_VESSEL1", L"sound\\Vessel_Sound\\Slash_01.wav");
	CResMgr::GenInst()->LoadSound(L"SLASH_PURE_VESSEL2", L"sound\\Vessel_Sound\\Slash_02.wav");
	CResMgr::GenInst()->LoadSound(L"SLASH_PURE_VESSEL3", L"sound\\Vessel_Sound\\Slash_03.wav");

	CResMgr::GenInst()->LoadSound(L"RORE_ANTICIPATE_PURE_VESSEL", L"sound\\Vessel_Sound\\Roar_Focus.wav");
	CResMgr::GenInst()->LoadSound(L"RORE_PURE_VESSEL", L"sound\\Vessel_Sound\\Roar_On.wav");

	CResMgr::GenInst()->LoadSound(L"DART_SHOT_VESSEL", L"sound\\Vessel_Sound\\gg_pure_vessel_sword_shoot.wav");
	
	CResMgr::GenInst()->LoadSound(L"Enemy_Damage5", L"sound\\enemy_damage.wav");
	CResMgr::GenInst()->LoadSound(L"orb_boom1", L"sound\\Vessel_Sound\\gg_pure_vessel_small_orb_appear_and_burst.wav");
	CResMgr::GenInst()->LoadSound(L"orb_boom2", L"sound\\Vessel_Sound\\gg_pure_vessel_small_orb_appear_and_burst.wav");
	CResMgr::GenInst()->LoadSound(L"orb_boom3", L"sound\\Vessel_Sound\\gg_pure_vessel_small_orb_appear_and_burst.wav");
	CResMgr::GenInst()->LoadSound(L"orb_boom4", L"sound\\Vessel_Sound\\gg_pure_vessel_small_orb_appear_and_burst.wav");
	CResMgr::GenInst()->LoadSound(L"orb_boom5", L"sound\\Vessel_Sound\\gg_pure_vessel_small_orb_appear_and_burst.wav");
	CResMgr::GenInst()->LoadSound(L"orb_boom6", L"sound\\Vessel_Sound\\gg_pure_vessel_small_orb_appear_and_burst.wav");

	dwtime = GetTickCount64();
}

CPureVessel::~CPureVessel()
{

}

void CPureVessel::update()
{
	
	update_move();
	update_state();
	update_sound();
	update_animation();

	PURE_VESSEL_STATE patterns[] = {
	PURE_VESSEL_STATE::SLASH_ANTICIPATE,
	PURE_VESSEL_STATE::SPIKE_ATTACK_ANTICIPATE,
	PURE_VESSEL_STATE::DASH_ANTICIPATE,
	PURE_VESSEL_STATE::ROAR_ANTICIPATE,
	PURE_VESSEL_STATE::TELEPORT_DART_ANTICIPATE,
	PURE_VESSEL_STATE::TELEPORT_ANTICIPATE,
	PURE_VESSEL_STATE::TELEPORT_DART_ANTICIPATE
	};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 6);

	if (dwtime + 2500 < GetTickCount64() && m_eCurState != PURE_VESSEL_STATE::DEAD)
	{
		m_iPatternCount++;
		int randomIndex = dis(gen);
		m_eCurState = patterns[randomIndex];

		/*if (m_iPatternCount % 7 == 0)
		{
			m_eCurState = PURE_VESSEL_STATE::SLASH_ANTICIPATE;
		}

		else if (m_iPatternCount % 7 == 1)
		{
			m_eCurState = PURE_VESSEL_STATE::SPIKE_ATTACK_ANTICIPATE;
		}

		else if (m_iPatternCount % 7 == 2)
		{
			m_eCurState = PURE_VESSEL_STATE::DASH_ANTICIPATE;
		}

		else if (m_iPatternCount % 7 == 3)
		{
			m_eCurState = PURE_VESSEL_STATE::ROAR_ANTICIPATE;
		}

		else if (m_iPatternCount % 7 == 4)
		{
			m_eCurState = PURE_VESSEL_STATE::TELEPORT_DART_ANTICIPATE;
		}

		else if (m_iPatternCount % 7 == 5)
		{
			m_eCurState = PURE_VESSEL_STATE::TELEPORT_ANTICIPATE;
		}

		else if (m_iPatternCount % 7 == 6)
		{
			m_eCurState = PURE_VESSEL_STATE::TELEPORT_DART_ANTICIPATE;
		}*/

		


		dwtime = GetTickCount64();
	}

	m_ePreState = m_eCurState;

}

void CPureVessel::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}

void CPureVessel::update_move()
{

	Vec2 vPos = GetPos();



	if (vPos.x - 1000 < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x > CPlayerMgr::GenInst()->GetCurPlayerPos().x)
	{
		if (m_eCurState != PURE_VESSEL_STATE::DEAD)
		{

			if (m_eCurState != PURE_VESSEL_STATE::DASH
				&& m_eCurState != PURE_VESSEL_STATE::DASH_END
				&& m_eCurState != PURE_VESSEL_STATE::SPIKE_ATTACK
				&& m_eCurState != PURE_VESSEL_STATE::SPIKE_ATTACK_END
				&& m_eCurState != PURE_VESSEL_STATE::SLASH
				&& m_eCurState != PURE_VESSEL_STATE::TELEPORT_ANTICIPATE
				&& m_eCurState != PURE_VESSEL_STATE::TELEPORT
				&& m_eCurState != PURE_VESSEL_STATE::DART_SHOT
				
				)
				
			{
				m_iDir = -1;
			}



		}
	}

	else if (vPos.x + 1000 > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x < CPlayerMgr::GenInst()->GetCurPlayerPos().x)
	{
		if (m_eCurState != PURE_VESSEL_STATE::DEAD)
		{
			if (m_eCurState != PURE_VESSEL_STATE::DASH
				&& m_eCurState != PURE_VESSEL_STATE::DASH_END
				&& m_eCurState != PURE_VESSEL_STATE::SPIKE_ATTACK
				&& m_eCurState != PURE_VESSEL_STATE::SPIKE_ATTACK_END
				&& m_eCurState != PURE_VESSEL_STATE::SLASH
				&& m_eCurState != PURE_VESSEL_STATE::TELEPORT_ANTICIPATE
				&& m_eCurState != PURE_VESSEL_STATE::TELEPORT

				&& m_eCurState != PURE_VESSEL_STATE::DART_SHOT)

			{
				m_iDir = 1;
			}

		}
	}


	//돌진 상태일때의 돌진 속도 
	if (m_eCurState == PURE_VESSEL_STATE::DASH && m_iDir == -1)
	{
		vPos.x -= 2000 * fDT;
	}

	else if (m_eCurState == PURE_VESSEL_STATE::DASH && m_iDir == 1)
	{
		vPos.x += 2000 * fDT;
	}

	//SLASH 상태 속도 
	if (m_eCurState == PURE_VESSEL_STATE::SLASH && m_iDir == -1)
	{
		vPos.x -= 500 * fDT;
	}

	else if (m_eCurState == PURE_VESSEL_STATE::SLASH && m_iDir == 1)
	{
		vPos.x += 500 * fDT;
	}



	if (m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK_ANTICIPATE && m_iDir == -1)
	{
		vPos.x -= 300 * fDT;
		GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -700.f));

		vDir = (CPlayerMgr::GenInst()->GetCurPlayerPos() - vPos).Normalize();

	}

	if (m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK_ANTICIPATE && m_iDir == 1)
	{
		vPos.x += 300 * fDT;
		GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -700.f));
		vDir = (CPlayerMgr::GenInst()->GetCurPlayerPos() - vPos).Normalize();
	}

	if (m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK && m_iDir == -1)
	{

		// 땅과 충돌하면 이 거 진행 x
		if (GroundOn == false)
		{

			vPos.x += 2000 * vDir.x * fDT;
			vPos.y += 2000 * 1* fDT;

		}

	}

	if (m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK && m_iDir == 1)
	{

		// 땅과 충돌하면 이거 진행 x 
		if (GroundOn == false)
		{

			vPos.x += 2000 * vDir.x * fDT;
			vPos.y += 2000 * 1 * fDT;

		}

	}


	if (m_eCurState == PURE_VESSEL_STATE::TELEPORT && m_iDir == -1)
	{
		if(GetAnimator()->GetAnimation()->GetCurrentFrm()==1)
		{
			vPos.x = CPlayerMgr::GenInst()->GetCurPlayerPos().x;
			vPos.y = CPlayerMgr::GenInst()->GetCurPlayerPos().y - 500.f;
		}
	}

	if (m_eCurState == PURE_VESSEL_STATE::TELEPORT && m_iDir == 1)
	{
		if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 1)
		{
			vPos.x = CPlayerMgr::GenInst()->GetCurPlayerPos().x;
			vPos.y = CPlayerMgr::GenInst()->GetCurPlayerPos().y - 500.f;
		}
	}


	if (m_eCurState == PURE_VESSEL_STATE::TELEPORT_DART && m_iDir == -1)
	{
		if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 1)
		{
			vPos.x = CPlayerMgr::GenInst()->GetCurPlayerPos().x + 500.f;
			vPos.y = CPlayerMgr::GenInst()->GetCurPlayerPos().y;
		}
	}

	if (m_eCurState == PURE_VESSEL_STATE::TELEPORT_DART && m_iDir == 1)
	{
		if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 1)
		{
			vPos.x = CPlayerMgr::GenInst()->GetCurPlayerPos().x - 500.f;
			vPos.y = CPlayerMgr::GenInst()->GetCurPlayerPos().y;
		}
	}



	SetPos(vPos);
}

void CPureVessel::update_state()
{


}

void CPureVessel::update_sound()
{
	CSound* pDashSound = CResMgr::GenInst()->FindSound(L"DASH_PURE_VESSEL");
	CSound* pSpikeAttackAnticipateSound = CResMgr::GenInst()->FindSound(L"SPIKE_ATTACK_ANTICIAPTE_PURE_VESSEL");
	CSound* pSpikeAttackSound = CResMgr::GenInst()->FindSound(L"SPIKE_ATTACK_PURE_VESSEL");
	CSound* pSpikeAttackEndSound = CResMgr::GenInst()->FindSound(L"SPIKE_ATTACK_END_PURE_VESSEL");
	CSound* pTelePortSound = CResMgr::GenInst()->FindSound(L"TELEPORT_PURE_VESSEL");
	
	CSound* pSlashSound1 = CResMgr::GenInst()->FindSound(L"SLASH_PURE_VESSEL1");
	
	CSound* pRoarAnticipateSound = CResMgr::GenInst()->FindSound(L"RORE_ANTICIPATE_PURE_VESSEL");
	CSound* pRoarSound = CResMgr::GenInst()->FindSound(L"RORE_PURE_VESSEL");

	CSound* pDartShotSound = CResMgr::GenInst()->FindSound(L"DART_SHOT_VESSEL");


	switch (m_eCurState)
	{
	case PURE_VESSEL_STATE::IDLE:
		break;

	case PURE_VESSEL_STATE::ROAR_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pRoarAnticipateSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;

	case PURE_VESSEL_STATE::ROAR:
		if (!m_bSoundPlayed)
		{
			//CreateCirCleEffect1();
			pRoarSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;

	case PURE_VESSEL_STATE::ROAR_END:
		break;
	case PURE_VESSEL_STATE::COUNTER:
		break;
	case PURE_VESSEL_STATE::DARK_TENTACLE:
		break;
	case PURE_VESSEL_STATE::DART_SHOT:
		if (!m_bSoundPlayed)
		{
			CreateMinus45SpearEffect();
			pDartShotSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case PURE_VESSEL_STATE::DASH_ANTICIPATE:
		break;
	case PURE_VESSEL_STATE::DASH:
		if (!m_bSoundPlayed)
		{
			pDashSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case PURE_VESSEL_STATE::DASH_END:
		break;
	
	case PURE_VESSEL_STATE::SLASH_ANTICIPATE:
		break;
	case PURE_VESSEL_STATE::SLASH:
		if (!m_bSoundPlayed)
		{
			pSlashSound1->Play(false);
			m_bSoundPlayed = true;
			break;
		}
		break;
	case PURE_VESSEL_STATE::SPIKE_ATTACK_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pSpikeAttackAnticipateSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case PURE_VESSEL_STATE::SPIKE_ATTACK:
		if (!m_bSoundPlayed)
		{
			CreateSpikeAnticipateEffect();
			pSpikeAttackSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case PURE_VESSEL_STATE::SPIKE_ATTACK_END:
		if (!m_bSoundPlayed)
		{
			pSpikeAttackEndSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case PURE_VESSEL_STATE::DEAD:
		break;

	case PURE_VESSEL_STATE::TELEPORT_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pTelePortSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;

	case PURE_VESSEL_STATE::TELEPORT:
		if (!m_bSoundPlayed)
		{
			pTelePortSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;

	case PURE_VESSEL_STATE::TELEPORT_DART_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pTelePortSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;

	case PURE_VESSEL_STATE::TELEPORT_DART:
		if (!m_bSoundPlayed)
		{
			pTelePortSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	
	default:
		break;
	}
}

void CPureVessel::update_animation()
{

	// IDLE 코드 

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::IDLE)
	{
		GetAnimator()->Play(L"IDLE_LEFT_PURE", true);
		
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::IDLE)
	{
		GetAnimator()->Play(L"IDLE_RIGHT_PURE", true);
		
	}


	// Slash 코드 
	// ====================================================================
	CSound* pSlashSound2 = CResMgr::GenInst()->FindSound(L"SLASH_PURE_VESSEL3");
	CSound* pSlashSound3 = CResMgr::GenInst()->FindSound(L"SLASH_PURE_VESSEL3");

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::SLASH_ANTICIPATE)
	{
		GetAnimator()->Play(L"SLASH_ANTICIPATE_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SLASH_ANTICIPATE_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::SLASH;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::SLASH_ANTICIPATE)
	{
		GetAnimator()->Play(L"SLASH_ANTICIPATE_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"SLASH_ANTICIPATE_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::SLASH;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::SLASH)
	{

		if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 3)
		{
			pSlashSound2->Play(false);
			m_bSoundPlayed = false;
		}
		
		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 6)
		{
			pSlashSound3->Play(false);
			m_bSoundPlayed = false;
		}
		
		GetAnimator()->Play(L"SLASH_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SLASH_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::SLASH)
	{
		if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 3)
		{
			pSlashSound2->Play(false);
			m_bSoundPlayed = false;
		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 6)
		{
			pSlashSound3->Play(false);
			m_bSoundPlayed = false;
		}
		GetAnimator()->Play(L"SLASH_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"SLASH_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}


	//  Dash 코드
	// ===========================================================
	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::DASH_ANTICIPATE)
	{
		GetAnimator()->Play(L"DASH_ANTICIPATE_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"DASH_ANTICIPATE_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::DASH;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::DASH_ANTICIPATE)
	{
		GetAnimator()->Play(L"DASH_ANTICIPATE_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"DASH_ANTICIPATE_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::DASH;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::DASH)
	{

		GetAnimator()->Play(L"DASH_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"DASH_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::DASH_END;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::DASH)
	{

		GetAnimator()->Play(L"DASH_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"DASH_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::DASH_END;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::DASH_END)
	{
		GetAnimator()->Play(L"DASH_END_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"DASH_END_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::DASH_END)
	{
		GetAnimator()->Play(L"DASH_END_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"DASH_END_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}


	//  ROAR 코드
	// ===========================================================

	CSound* pOrbBoom1 = CResMgr::GenInst()->FindSound(L"orb_boom1");
	CSound* pOrbBoom2 = CResMgr::GenInst()->FindSound(L"orb_boom2");
	CSound* pOrbBoom3 = CResMgr::GenInst()->FindSound(L"orb_boom3");
	CSound* pOrbBoom4 = CResMgr::GenInst()->FindSound(L"orb_boom4");
	CSound* pOrbBoom5 = CResMgr::GenInst()->FindSound(L"orb_boom5");
	CSound* pOrbBoom6 = CResMgr::GenInst()->FindSound(L"orb_boom6");
	//pOrbBoom->SetVolume(85.F);


	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::ROAR_ANTICIPATE)
	{
		GetAnimator()->Play(L"ROAR_ANTICIPATE_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"ROAR_ANTICIPATE_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::ROAR;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::ROAR_ANTICIPATE)
	{
		GetAnimator()->Play(L"ROAR_ANTICIPATE_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"ROAR_ANTICIPATE_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::ROAR;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::ROAR)
	{
		GetAnimator()->Play(L"ROAR_LEFT_PURE", false);

		if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 0)
		{
			if (m_bCircleEffect1 == false)
			{
				CreateCirCleEffect1();
				pOrbBoom1->Play(false);
				m_bCircleEffect1 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 1)
		{
			if (m_bCircleEffect2 == false)
			{
				
				CreateCirCleEffect2();
				pOrbBoom2->Play(false);
				m_bCircleEffect2 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 2)
		{
			if (m_bCircleEffect3 == false)
			{
				CreateCirCleEffect3();
				pOrbBoom3->Play(false);
				m_bCircleEffect3 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 4)
		{
			if (m_bCircleEffect4 == false)
			{
				CreateCirCleEffect4();
				pOrbBoom4->Play(false);
				m_bCircleEffect4 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
		{
			if (m_bCircleEffect5 == false)
			{
				CreateCirCleEffect5();
				pOrbBoom5->Play(false);
				m_bCircleEffect5 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 6)
		{
			if (m_bCircleEffect6 == false)
			{
				CreateCirCleEffect6();
				pOrbBoom6->Play(false);
				m_bCircleEffect6 = true;
			}

		}


	
		if (GetAnimator()->GetAnimation()->IsFinish())
		{

			GetAnimator()->SetAnimationFrame(L"ROAR_LEFT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::ROAR_END;
			//7월 8일 수정
			m_bCircleEffect1 = false;
			m_bCircleEffect2 = false;
			m_bCircleEffect3 = false;
			m_bCircleEffect4 = false;
			m_bCircleEffect5 = false;
			m_bCircleEffect6 = false;
			m_bCircleEffect7 = false;

			m_bSoundPlayed = false;

		}
	
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::ROAR)
	{
		

		GetAnimator()->Play(L"ROAR_RIGHT_PURE", false);

		if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 0)
		{
			if (m_bCircleEffect1 == false)
			{

				CreateCirCleEffect1();
				pOrbBoom1->Play(false);
				m_bCircleEffect1 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 1)
		{
			if (m_bCircleEffect2 == false)
			{

				CreateCirCleEffect2();
				pOrbBoom2->Play(false);
				m_bCircleEffect2 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 2)
		{
			if (m_bCircleEffect3 == false)
			{
				CreateCirCleEffect3();
				pOrbBoom3->Play(false);
				m_bCircleEffect3 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 4)
		{
			if (m_bCircleEffect4 == false)
			{
				CreateCirCleEffect4();
				pOrbBoom4->Play(false);
				m_bCircleEffect4 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
		{
			if (m_bCircleEffect5 == false)
			{
				CreateCirCleEffect5();
				pOrbBoom5->Play(false);
				m_bCircleEffect5 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 6)
		{
			if (m_bCircleEffect6 == false)
			{
				CreateCirCleEffect6();
				pOrbBoom6->Play(false);
				m_bCircleEffect6 = true;
			}

		}



		if (GetAnimator()->GetAnimation()->IsFinish())
		{

			GetAnimator()->SetAnimationFrame(L"ROAR_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::ROAR_END;
			//7월 8일 수정
			m_bCircleEffect1 = false;
			m_bCircleEffect2 = false;
			m_bCircleEffect3 = false;
			m_bCircleEffect4 = false;
			m_bCircleEffect5 = false;
			m_bCircleEffect6 = false;
			m_bCircleEffect7 = false;

			m_bSoundPlayed = false;

		}

	}

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::ROAR_END)
	{
		GetAnimator()->Play(L"ROAR_END_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"ROAR_END_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::ROAR_END)
	{
		GetAnimator()->Play(L"ROAR_END_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"ROAR_END_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}


	//Spike Attack
	//=========================================================================================
	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK_ANTICIPATE)
	{
		GetAnimator()->Play(L"SPIKE_ANTICIPATE_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SPIKE_ANTICIPATE_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::SPIKE_ATTACK;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK_ANTICIPATE)
	{
		GetAnimator()->Play(L"SPIKE_ANTICIPATE_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"SPIKE_ANTICIPATE_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::SPIKE_ATTACK;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK)
	{

		GetAnimator()->Play(L"SPIKE_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SPIKE_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::SPIKE_ATTACK_END;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK)
	{

		GetAnimator()->Play(L"SPIKE_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"SPIKE_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::SPIKE_ATTACK_END;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK_END)
	{
		GetAnimator()->Play(L"SPIKE_END_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SPIKE_END_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::SPIKE_ATTACK_END)
	{
		GetAnimator()->Play(L"SPIKE_END_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"SPIKE_END_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}


	//TelePort
	//=====================================================================
	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::TELEPORT_ANTICIPATE)
	{
		GetAnimator()->Play(L"TELEPORT_ANTICIPATE_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"TELEPORT_ANTICIPATE_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::TELEPORT;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::TELEPORT_ANTICIPATE)
	{
		GetAnimator()->Play(L"TELEPORT_ANTICIPATE_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"TELEPORT_ANTICIPATE_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::TELEPORT;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::TELEPORT)
	{

		GetAnimator()->Play(L"TELEPORT_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"TELEPORT_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::SPIKE_ATTACK;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::TELEPORT)
	{

		GetAnimator()->Play(L"TELEPORT_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"TELEPORT_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::SPIKE_ATTACK;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	//Dart Shot Anticipate

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::DART_SHOT_ANTICIPATE)
	{
		GetAnimator()->Play(L"DART_SHOT_ANTICIPATE_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"DART_SHOT_ANTICIPATE_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::DART_SHOT;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::DART_SHOT_ANTICIPATE)
	{
		GetAnimator()->Play(L"DART_SHOT_ANTICIPATE_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"DART_SHOT_ANTICIPATE_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::DART_SHOT;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}


	//DartShot
	CSound* pDartShotSound2 = CResMgr::GenInst()->FindSound(L"DART_SHOT_VESSEL");

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::DART_SHOT)
	{
		GetAnimator()->Play(L"DART_SHOT_LEFT_PURE", false);
		if(GetAnimator()->GetAnimation()->GetCurrentFrm()==1)
		{
			if(m_bSpearMinus20 == false)
			{
				CreateMinus20SpearEffect();
				pDartShotSound2->Play(false);
				m_bSpearMinus20 = true; 
			}
			
		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 2)
		{
			if (m_bSpear8_5Angle == false)
			{
				Create8_5AngleSpearEffect();
				pDartShotSound2->Play(false);
				m_bSpear8_5Angle = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 3)
		{
			if (m_bSpear5Angle == false)
			{
				Create5AngleSpearEffect();
				pDartShotSound2->Play(false);
				m_bSpear5Angle = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 4)
		{
			if (m_bSpear15Angle == false)
			{
				Create15AngleSpearEffect();
				pDartShotSound2->Play(false);
				m_bSpear15Angle = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
		{
			if (m_bSpear30Angle == false)
			{
				Create30AngleSpearEffect();
				pDartShotSound2->Play(false);
				m_bSpear30Angle = true;
			}

		}
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"DART_SHOT_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::IDLE;
				m_bSpearMinus20 = false;
				m_bSpear8_5Angle = false;
				m_bSpear5Angle = false;
				m_bSpear15Angle = false;
				m_bSpear30Angle = false;

				
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::DART_SHOT)
	{
		GetAnimator()->Play(L"DART_SHOT_RIGHT_PURE", false);

		if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 1)
		{
			if (m_bSpearMinus20 == false)
			{
				CreateMinus20SpearEffect();
				pDartShotSound2->Play(false);
				m_bSpearMinus20 = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 2)
		{
			if (m_bSpear8_5Angle == false)
			{
				Create8_5AngleSpearEffect();
				pDartShotSound2->Play(false);
				m_bSpear8_5Angle = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 3)
		{
			if (m_bSpear5Angle == false)
			{
				Create5AngleSpearEffect();
				pDartShotSound2->Play(false);
				m_bSpear5Angle = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 4)
		{
			if (m_bSpear15Angle == false)
			{
				Create15AngleSpearEffect();
				pDartShotSound2->Play(false);
				m_bSpear15Angle = true;
			}

		}

		else if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
		{
			if (m_bSpear30Angle == false)
			{
				Create30AngleSpearEffect();
				pDartShotSound2->Play(false);
				m_bSpear30Angle = true;
			}

		}
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"DART_SHOT_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::IDLE;
			m_bSpearMinus20 = false;
			m_bSpear8_5Angle = false;
			m_bSpear5Angle = false;
			m_bSpear15Angle = false;
			m_bSpear30Angle = false;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	// TelePortDart
	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::TELEPORT_DART_ANTICIPATE)
	{
		GetAnimator()->Play(L"TELEPORT_ANTICIPATE_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"TELEPORT_ANTICIPATE_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::TELEPORT_DART;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::TELEPORT_DART_ANTICIPATE)
	{
		GetAnimator()->Play(L"TELEPORT_ANTICIPATE_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"TELEPORT_ANTICIPATE_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::TELEPORT_DART;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::TELEPORT_DART)
	{

		GetAnimator()->Play(L"TELEPORT_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"TELEPORT_LEFT_PURE", 0);
				m_eCurState = PURE_VESSEL_STATE::DART_SHOT_ANTICIPATE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::TELEPORT_DART)
	{

		GetAnimator()->Play(L"TELEPORT_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"TELEPORT_RIGHT_PURE", 0);
			m_eCurState = PURE_VESSEL_STATE::DART_SHOT_ANTICIPATE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	//DEAD 
	if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::DEAD)
	{
		GetAnimator()->Play(L"DEAD_LEFT_PURE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				CPlayerMgr::GenInst()->SetFinalEndingOnOff(true);
				
				DeleteObject(this);
				ChangeScene(SCENE_TYPE::END_SCEEN);
				//여기다가 신전환 넣기 
				
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::DEAD)
	{
		GetAnimator()->Play(L"DEAD_RIGHT_PURE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			CPlayerMgr::GenInst()->SetFinalEndingOnOff(true);
			DeleteObject(this);
			ChangeScene(SCENE_TYPE::END_SCEEN);
			//여기다가 신전환 넣기 
			
		}

	}





	//if (m_iDir == -1 && m_eCurState == PURE_VESSEL_STATE::DART_SHOT_END)
	//{

	//	GetAnimator()->Play(L"DART_SHOT_END_LEFT_PURE", false);
	//	{
	//		if (GetAnimator()->GetAnimation()->IsFinish())
	//		{
	//			GetAnimator()->SetAnimationFrame(L"DART_SHOT_END_LEFT_PURE", 0);
	//			m_eCurState = PURE_VESSEL_STATE::IDLE;
	//			//7월 8일 수정
	//			m_bSoundPlayed = false;
	//		}
	//	}
	//}

	//else if (m_iDir == 1 && m_eCurState == PURE_VESSEL_STATE::DART_SHOT_END)
	//{

	//	GetAnimator()->Play(L"DART_SHOT_END_RIGHT_PURE", false);
	//	if (GetAnimator()->GetAnimation()->IsFinish())
	//	{
	//		GetAnimator()->SetAnimationFrame(L"DART_SHOT_END_RIGHT_PURE", 0);
	//		m_eCurState = PURE_VESSEL_STATE::IDLE;
	//		//7월 8일 수정
	//		m_bSoundPlayed = false;
	//	}

	//}






}




void CPureVessel::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Ground")
	{
		GroundOn = true;
	}
}

void CPureVessel::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pDamagedSound2 = CResMgr::GenInst()->FindSound(L"Enemy_Damage5");

	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"DOWN_SLASH_Effect")
	{
		pDamagedSound2->Play(false);
		CPlayerMgr::GenInst()->SetGroundHit(true);

	}

	if (L"SLASH" == _pOther->GetObj()->GetName()
		|| pOtherObj->GetName() == L"DOWN_SLASH_Effect")
	{
		pDamagedSound2->Play(false);

		m_iHP--;
		if (CPlayerMgr::GenInst()->GetPlayerMp() < 6)
		{
			CPlayerMgr::GenInst()->IncreaseMp(1);
		}



		if (m_iHP < 0)
		{
			m_eCurState = PURE_VESSEL_STATE::DEAD;
			// 여기다가 작성하기. 일단 Dead 상태로 만들고 해서 패턴 못쓰게 하기.

		}



	}

	if (L"FireBall" == _pOther->GetObj()->GetName())
	{
		m_iHP--;
		DeleteObject(pOtherObj);

		if (m_iHP < 0)
		{
			m_eCurState = PURE_VESSEL_STATE::DEAD;
		}
	}

}

void CPureVessel::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Ground")
	{
		GroundOn = false;
	}
}


void CPureVessel::CreateSpikeAnticipateEffect()
{
	CSpikeEffect* pSpikeEffect1 = new CSpikeEffect;

	//pSpikeEffect->SetPos(GetPos() - Vec2(100.f, 0.f)); // 플레이어의 좌표 받아옴
	pSpikeEffect1->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x, 957.f));
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pSpikeEffect1->SetName(L"Spike_Effect");

	CreateObject(pSpikeEffect1, GROUP_TYPE::SKILLEFFECT);


	CSpikeEffect* pSpikeEffect2 = new CSpikeEffect;
	pSpikeEffect2->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x-300, 957.f));
	pSpikeEffect2->SetName(L"Spike_Effect");
	CreateObject(pSpikeEffect2, GROUP_TYPE::SKILLEFFECT);

	CSpikeEffect* pSpikeEffect3 = new CSpikeEffect;
	pSpikeEffect3->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x + 300, 957.f));
	pSpikeEffect3->SetName(L"Spike_Effect");
	CreateObject(pSpikeEffect3, GROUP_TYPE::SKILLEFFECT);

	CSpikeEffect* pSpikeEffect4 = new CSpikeEffect;
	pSpikeEffect4->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x + 600, 957.f));
	pSpikeEffect4->SetName(L"Spike_Effect");
	CreateObject(pSpikeEffect4, GROUP_TYPE::SKILLEFFECT);


	CSpikeEffect* pSpikeEffect5 = new CSpikeEffect;
	pSpikeEffect5->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x - 600, 957.f));
	pSpikeEffect5->SetName(L"Spike_Effect");
	CreateObject(pSpikeEffect5, GROUP_TYPE::SKILLEFFECT);


	CSpikeEffect* pSpikeEffect6 = new CSpikeEffect;
	pSpikeEffect6->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x - 900, 957.f));
	pSpikeEffect6->SetName(L"Spike_Effect");
	CreateObject(pSpikeEffect6, GROUP_TYPE::SKILLEFFECT);

	CSpikeEffect* pSpikeEffect7 = new CSpikeEffect;
	pSpikeEffect7->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x + 900, 957.f));
	pSpikeEffect7->SetName(L"Spike_Effect");
	CreateObject(pSpikeEffect7, GROUP_TYPE::SKILLEFFECT);
}



void CPureVessel::CreateMinus45SpearEffect()
{
	CSpear* pCSpearEffect = new CSpear;

	pCSpearEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pCSpearEffect->SetPos(GetPos() + Vec2(100.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pCSpearEffect->SetPos(GetPos() - Vec2(-100.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pCSpearEffect->SetName(L"SPEAR");

	CreateObject(pCSpearEffect, GROUP_TYPE::SKILLEFFECT);
}


void CPureVessel::CreateMinus20SpearEffect()
{
	CSpear20minusAngle* pCSpearEffect = new CSpear20minusAngle;

	pCSpearEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pCSpearEffect->SetPos(GetPos() + Vec2(100.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pCSpearEffect->SetPos(GetPos() - Vec2(-100.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pCSpearEffect->SetName(L"SPEAR");

	CreateObject(pCSpearEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPureVessel::Create5AngleSpearEffect()
{
	CSpear5angle* pCSpearEffect = new CSpear5angle;

	pCSpearEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pCSpearEffect->SetPos(GetPos() + Vec2(100.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pCSpearEffect->SetPos(GetPos() - Vec2(-100.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pCSpearEffect->SetName(L"SPEAR");

	CreateObject(pCSpearEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPureVessel::Create8_5AngleSpearEffect()
{
	CSpear8_5MinusAngle* pCSpearEffect = new CSpear8_5MinusAngle;

	pCSpearEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pCSpearEffect->SetPos(GetPos() + Vec2(100.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pCSpearEffect->SetPos(GetPos() - Vec2(-100.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pCSpearEffect->SetName(L"SPEAR");

	CreateObject(pCSpearEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPureVessel::Create15AngleSpearEffect()
{
	CSpear15Angle* pCSpearEffect = new CSpear15Angle;

	pCSpearEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pCSpearEffect->SetPos(GetPos() + Vec2(100.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pCSpearEffect->SetPos(GetPos() - Vec2(-100.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pCSpearEffect->SetName(L"SPEAR");

	CreateObject(pCSpearEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPureVessel::Create30AngleSpearEffect()
{
	CSpear30angle* pCSpearEffect = new CSpear30angle;

	pCSpearEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pCSpearEffect->SetPos(GetPos() + Vec2(100.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pCSpearEffect->SetPos(GetPos() - Vec2(100.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pCSpearEffect->SetName(L"SPEAR");

	CreateObject(pCSpearEffect, GROUP_TYPE::SKILLEFFECT);
}


void CPureVessel::CreateCirCleEffect1()
{
	COrb* pCirCleEffect1 = new COrb;

	//pSpikeEffect->SetPos(GetPos() - Vec2(100.f, 0.f)); // 플레이어의 좌표 받아옴
	pCirCleEffect1->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x, CPlayerMgr::GenInst()->GetCurPlayerPos().y - 300.f));
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pCirCleEffect1->SetName(L"CirCle_Effect");
	CreateObject(pCirCleEffect1, GROUP_TYPE::SKILLEFFECT);

}

void CPureVessel::CreateCirCleEffect2()
{
	COrb* pCirCleEffect2 = new COrb;
	pCirCleEffect2->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x - 500, CPlayerMgr::GenInst()->GetCurPlayerPos().y - 400.f));
	pCirCleEffect2->SetName(L"CirCle_Effect");
	CreateObject(pCirCleEffect2, GROUP_TYPE::SKILLEFFECT);
}

void CPureVessel::CreateCirCleEffect3()
{
	COrb* pCirCleEffect3 = new COrb;
	pCirCleEffect3->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x + 500, CPlayerMgr::GenInst()->GetCurPlayerPos().y - 400.f));
	pCirCleEffect3->SetName(L"CirCle_Effect");
	CreateObject(pCirCleEffect3, GROUP_TYPE::SKILLEFFECT);
}

void CPureVessel::CreateCirCleEffect4()
{
	COrb* pCirCleEffect4 = new COrb;
	pCirCleEffect4->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x - 300, CPlayerMgr::GenInst()->GetCurPlayerPos().y - 100.f));
	pCirCleEffect4->SetName(L"CirCle_Effect");
	CreateObject(pCirCleEffect4, GROUP_TYPE::SKILLEFFECT);
}

void CPureVessel::CreateCirCleEffect5()
{
	COrb* pCirCleEffect5 = new COrb;
	pCirCleEffect5->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x + 300, CPlayerMgr::GenInst()->GetCurPlayerPos().y - 100.f));
	pCirCleEffect5->SetName(L"CirCle_Effect");
	CreateObject(pCirCleEffect5, GROUP_TYPE::SKILLEFFECT);
}

void CPureVessel::CreateCirCleEffect6()
{
	COrb* pCirCleEffect6 = new COrb;
	pCirCleEffect6->SetPos(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x - 700, CPlayerMgr::GenInst()->GetCurPlayerPos().y - 250.f));
	pCirCleEffect6->SetName(L"CirCle_Effect");
	CreateObject(pCirCleEffect6, GROUP_TYPE::SKILLEFFECT);
}


