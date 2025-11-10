#include "pch.h"
#include "CFalseKnight.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"
#include "CStone.h"
#include "CSound.h"
#include "CRigidBody.h"
#include "CAttackWave.h"
#include "CStunEffect.h"

CFalseKnight::CFalseKnight()
	:m_iHP(20)
	, m_iCount(0)
	, m_iPatternCount(0)
	, m_iStoneCount(0)
	, m_eCurState(KNIGHT_STATE::IDLE)
	, m_bSoundPlayed(false)
	, m_bAngryCount(0)
	, m_iGetVelocityCount(0)
	, m_iStunCount(1)
{
	CreateCollider();
	CreateAnimator();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(-15.f, 20.f));
	GetCollider()->SetScale(Vec2(200.f, 200.f));

	//애니메이션 원래 코드 
	CTexture* m_pIdileTex = CResMgr::GenInst()->LoadTexture(L"FalseKnightIdle", L"texture\\FalseKnight\\FalseKnight_Idle2.bmp");
	CTexture* m_pAttackAnticipateTex = CResMgr::GenInst()->LoadTexture(L"FalseKnightAttackAnticipate", L"texture\\FalseKnight\\FalseKnight_Attack_Anticipate.bmp");
	CTexture* m_pAttackTex = CResMgr::GenInst()->LoadTexture(L"FalseKnightAttack", L"texture\\FalseKnight\\FalseKnight_Attack.bmp");
	CTexture* m_pAttackRecoverTex = CResMgr::GenInst()->LoadTexture(L"FalseKnightAttackRecover", L"texture\\FalseKnight\\FalseKnight_Attack_Recover.bmp");
	CTexture* m_pRushAnticipateTex = CResMgr::GenInst()->LoadTexture(L"FalseKnightRushAnticipate", L"texture\\FalseKnight\\FalseKnight_Rush_Anticipate.bmp");
	CTexture* m_pRushTex = CResMgr::GenInst()->LoadTexture(L"FalseKnightRush", L"texture\\FalseKnight\\FalseKnight_Rush.bmp");
	CTexture* m_pJumpAnticipateTex = CResMgr::GenInst()->LoadTexture(L"FalseJumpAnticipate", L"texture\\FalseKnight\\Jump_Anticipate.bmp");
	CTexture* m_pJumpTex = CResMgr::GenInst()->LoadTexture(L"FalseJump", L"texture\\FalseKnight\\FalseKnight_Jump.bmp");
	CTexture* m_pJumplandTex = CResMgr::GenInst()->LoadTexture(L"FalseJumpLand", L"texture\\FalseKnight\\Jump_land.bmp");

	CTexture* m_pRollTex = CResMgr::GenInst()->LoadTexture(L"FalseRoll", L"texture\\FalseKnight\\falseKnight_roll.bmp");
	CTexture* m_pRollEndTex = CResMgr::GenInst()->LoadTexture(L"FalseRollEnd", L"texture\\FalseKnight\\falseKnight_rollEnd.bmp");
	CTexture* m_pRollStunTex = CResMgr::GenInst()->LoadTexture(L"FalseRollStun", L"texture\\FalseKnight\\falseKnight_open.bmp");

	CTexture* m_pDeadTex = CResMgr::GenInst()->LoadTexture(L"FalseDead", L"texture\\FalseKnight\\false_Knight_Die.bmp");

	GetAnimator()->CreateAnimation(L"Idle_LEFT_FALSEKNIGHT", m_pIdileTex, Vec2(0.f, 0.f), Vec2(474.f, 292.f), Vec2(474.f, 0.f), 0.15f, 5);
	GetAnimator()->CreateAnimation(L"Idle_RIGHT_FALSEKNIGHT", m_pIdileTex, Vec2(0.f, 292.f), Vec2(474.f, 292.f), Vec2(474.f, 0.f), 0.15f, 5);

	GetAnimator()->CreateAnimation(L"ATTACK_ANTICIPATE_LEFT_FALSEKNIGHT", m_pAttackAnticipateTex, Vec2(0.f, 0.f), Vec2(565.f, 296.f), Vec2(565.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"ATTACK_ANTICIPATE_RIGHT_FALSEKNIGHT", m_pAttackAnticipateTex, Vec2(0.f, 296.f), Vec2(565.f, 296.f), Vec2(565.f, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(L"ATTACK_LEFT_FALSEKNIGHT", m_pAttackTex, Vec2(0.f, 0.f), Vec2(559.f, 439.f), Vec2(559.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"ATTACK_RIGHT_FALSEKNIGHT", m_pAttackTex, Vec2(0.f, 439.f), Vec2(559.f, 439.f), Vec2(559.f, 0.f), 0.1f, 3);

	GetAnimator()->CreateAnimation(L"ATTACK_RECOVER_LEFT_FALSEKNIGHT", m_pAttackRecoverTex, Vec2(0.f, 0.f), Vec2(446.f, 427.f), Vec2(446.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"ATTACK_RECOVER_RIGHT_FALSEKNIGHT", m_pAttackRecoverTex, Vec2(0.f, 427.f), Vec2(446.f, 427.f), Vec2(446.f, 0.f), 0.1f, 5);

	GetAnimator()->CreateAnimation(L"RUSH_ANTICIPATE_LEFT_FALSEKNIGHT", m_pRushAnticipateTex, Vec2(0.f, 0.f), Vec2(362.f, 279.f), Vec2(362.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"RUSH_ANTICIPATE_RIGHT_FALSEKNIGHT", m_pRushAnticipateTex, Vec2(0.f, 279.f), Vec2(362.f, 279.f), Vec2(362.f, 0.f), 0.5f, 2);

	GetAnimator()->CreateAnimation(L"RUSH_LEFT_FALSEKNIGHT", m_pRushTex, Vec2(0.f, 0.f), Vec2(393.f, 361.f), Vec2(393.f, 0.f), 0.3f, 5);
	GetAnimator()->CreateAnimation(L"RUSH_RIGHT_FALSEKNIGHT", m_pRushTex, Vec2(0.f, 361.f), Vec2(393.f, 361.f), Vec2(393.f, 0.f), 0.3f, 5);

	
	//광폭화 
	GetAnimator()->CreateAnimation(L"ANGRY_ATTACK_ANTICIPATE_LEFT_FALSEKNIGHT", m_pAttackAnticipateTex, Vec2(0.f, 0.f), Vec2(565.f, 296.f), Vec2(565.f, 0.f), 0.05f, 6);
	GetAnimator()->CreateAnimation(L"ANGRY_ATTACK_ANTICIPATE_RIGHT_FALSEKNIGHT", m_pAttackAnticipateTex, Vec2(0.f, 296.f), Vec2(565.f, 296.f), Vec2(565.f, 0.f), 0.05f, 6);

	GetAnimator()->CreateAnimation(L"ANGRY_ATTACK_LEFT_FALSEKNIGHT", m_pAttackTex, Vec2(0.f, 0.f), Vec2(559.f, 439.f), Vec2(559.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"ANGRY_ATTACK_RIGHT_FALSEKNIGHT", m_pAttackTex, Vec2(0.f, 439.f), Vec2(559.f, 439.f), Vec2(559.f, 0.f), 0.1f, 3);

	GetAnimator()->CreateAnimation(L"ANGRY_ATTACK_RECOVER_LEFT_FALSEKNIGHT", m_pAttackRecoverTex, Vec2(0.f, 0.f), Vec2(446.f, 427.f), Vec2(446.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"ANGRY_ATTACK_RECOVER_RIGHT_FALSEKNIGHT", m_pAttackRecoverTex, Vec2(0.f, 427.f), Vec2(446.f, 427.f), Vec2(446.f, 0.f), 0.1f, 5);


	//점프 애니메이션 
	GetAnimator()->CreateAnimation(L"JUMP_LEFT_LAND", m_pJumplandTex, Vec2(0.f, 0.f), Vec2(454.f, 280.f), Vec2(454.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT_LAND", m_pJumplandTex, Vec2(0.f, 280.f), Vec2(454.f, 280.f), Vec2(454.f, 0.f), 0.2f, 3);

	GetAnimator()->CreateAnimation(L"JUMP_LEFT_ANTICIPATE", m_pJumpAnticipateTex, Vec2(0.f, 0.f), Vec2(454.f, 280.f), Vec2(454.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT_ANTICIPATE", m_pJumpAnticipateTex, Vec2(0.f, 280.f), Vec2(454.f, 280.f), Vec2(454.f, 0.f), 0.2f, 3);

	GetAnimator()->CreateAnimation(L"JUMP_LEFT", m_pJumpTex, Vec2(0.f, 0.f), Vec2(530.f, 250.f), Vec2(530.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", m_pJumpTex, Vec2(0.f, 250.f), Vec2(530.f, 250.f), Vec2(530.f, 0.f), 0.2f, 4);

	//구르기 애니메이션 

	GetAnimator()->CreateAnimation(L"ROLL_LEFT",  m_pRollTex, Vec2(0.f, 0.f), Vec2(482.f, 379.f), Vec2(482.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"ROLL_RIGHT", m_pRollTex, Vec2(0.f, 379.f), Vec2(482.f, 379.f), Vec2(482.f, 0.f), 0.1f, 5);

	GetAnimator()->CreateAnimation(L"ROLL_LEFT_END", m_pRollEndTex, Vec2(0.f, 0.f), Vec2(280.f, 343.f), Vec2(280.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"ROLL_RIGHT_END", m_pRollEndTex, Vec2(0.f, 343.f), Vec2(280.f, 343.f), Vec2(280.f, 0.f), 0.1f, 4);

	GetAnimator()->CreateAnimation(L"ROLL_STUN_LEFT", m_pRollStunTex, Vec2(0.f, 0.f), Vec2(280.f, 335.f), Vec2(280.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"ROLL_STUN_RIGHT", m_pRollStunTex, Vec2(0.f, 335.f), Vec2(280.f, 335.f), Vec2(280.f, 0.f), 0.1f, 4);

	GetAnimator()->CreateAnimation(L"ROLL_STUN_END_LEFT", m_pRollStunTex, Vec2(840.f, 0.f), Vec2(280.f, 335.f), Vec2(280.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"ROLL_STUN_END_RIGHT", m_pRollStunTex, Vec2(840.f, 335.f), Vec2(280.f, 335.f), Vec2(280.f, 0.f), 0.1f, 1);

	
	// 죽음 애니메이션 
	GetAnimator()->CreateAnimation(L"DEAD_LEFT",  m_pDeadTex, Vec2(0.f, 0.f), Vec2(219.f, 190.f), Vec2(0.f, 0.f), 5.f, 1);
	GetAnimator()->CreateAnimation(L"DEAD_RIGHT", m_pDeadTex, Vec2(0.f, 190.f), Vec2(219.f, 190.f), Vec2(0.f, 0.f), 5.f, 1);

	GetAnimator()->Play(L"Idle_LEFT_FALSEKNIGHT", true);

	//사운드 관련 코드 
	CResMgr::GenInst()->LoadSound(L"Damaged_armor", L"sound\\False_Knight\\false_knight_damage_armour.wav");
	CResMgr::GenInst()->LoadSound(L"hit_Ground", L"sound\\False_Knight\\false_knight_strike_ground.wav");
	CResMgr::GenInst()->LoadSound(L"Rush", L"sound\\False_Knight\\False_Knight_Attack_New_01.wav");
	CResMgr::GenInst()->LoadSound(L"Rage", L"sound\\False_Knight\\FKnight_Rage.wav");
	CResMgr::GenInst()->LoadSound(L"BrokeBarrel", L"sound\\barrel_death_1.wav");
	CResMgr::GenInst()->LoadSound(L"Attack_voice", L"sound\\False_Knight\\False_Knight_Attack_New_05.wav");
	CResMgr::GenInst()->LoadSound(L"Jump_Anticipate", L"sound\\False_Knight\\False_Knight_Attack_New_03.wav");
	CResMgr::GenInst()->LoadSound(L"Jump_Sound", L"sound\\False_Knight\\false_knight_jump.wav");
	CResMgr::GenInst()->LoadSound(L"Jump_Land_Sound", L"sound\\False_Knight\\false_knight_land.wav");
	CResMgr::GenInst()->LoadSound(L"Roll_Sound", L"sound\\False_Knight\\false_knight_roll.wav");
	CResMgr::GenInst()->LoadSound(L"Stun_Hit_Sound", L"sound\\False_Knight\\Fknight_hit_01.wav");
	CResMgr::GenInst()->LoadSound(L"Death_Sound", L"sound\\False_Knight\\FKnight_death.wav");
	
	//중력 설정 
	CreateGravity();
	CreateRigidBody();


	//애니메이션 오프셋 관련 코드 
	CAnimation* pAttack_Left = GetAnimator()->FindAnimation(L"ATTACK_LEFT_FALSEKNIGHT");
	for (UINT i = 0; i < pAttack_Left->GetMaxFrame(); i++)
	{
		pAttack_Left->GetFrame(i).vOffset = Vec2(0.f, -50.f);
	}

	CAnimation* pAttack_Right = GetAnimator()->FindAnimation(L"ATTACK_RIGHT_FALSEKNIGHT");
	for (UINT i = 0; i < pAttack_Right->GetMaxFrame(); i++)
	{
		pAttack_Right->GetFrame(i).vOffset = Vec2(0.f, -50.f);
	}

	CAnimation* pANGRY_Attack_Left = GetAnimator()->FindAnimation(L"ANGRY_ATTACK_LEFT_FALSEKNIGHT");
	for (UINT i = 0; i < pANGRY_Attack_Left->GetMaxFrame(); i++)
	{
		pANGRY_Attack_Left->GetFrame(i).vOffset = Vec2(0.f, -50.f);
	}

	CAnimation* pANGRY_Attack_Right = GetAnimator()->FindAnimation(L"ANGRY_ATTACK_RIGHT_FALSEKNIGHT");
	for (UINT i = 0; i < pANGRY_Attack_Right->GetMaxFrame(); i++)
	{
		pANGRY_Attack_Right ->GetFrame(i).vOffset = Vec2(0.f, -50.f);
	}

	//================================================================
	// 어택 애니메이션 오프셋 조정
	CAnimation* pAttack_Recover_Left = GetAnimator()->FindAnimation(L"ATTACK_RECOVER_LEFT_FALSEKNIGHT");
	for (UINT i = 0; i < pAttack_Recover_Left->GetMaxFrame(); i++)
	{
		pAttack_Recover_Left->GetFrame(i).vOffset = Vec2(0.f, -55.f);
	}

	CAnimation* pAttack_Recover_Right = GetAnimator()->FindAnimation(L"ATTACK_RECOVER_RIGHT_FALSEKNIGHT");
	for (UINT i = 0; i < pAttack_Recover_Right->GetMaxFrame(); i++)
	{
		pAttack_Recover_Right->GetFrame(i).vOffset = Vec2(0.f, -55.f);
	}

	// ================================================================
	// 돌진 애니메이션 오프셋 조정 
	CAnimation* pRush_LEFT = GetAnimator()->FindAnimation(L"RUSH_LEFT_FALSEKNIGHT");
	for (UINT i = 0; i < pRush_LEFT->GetMaxFrame(); i++)
	{
		pRush_LEFT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pRush_RIGHT = GetAnimator()->FindAnimation(L"RUSH_RIGHT_FALSEKNIGHT");
	for (UINT i = 0; i < pRush_RIGHT->GetMaxFrame(); i++)
	{
		pRush_RIGHT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	// 구르기 애니메이션 오프셋 조정 
	CAnimation* pRoll_LEFT = GetAnimator()->FindAnimation(L"ROLL_LEFT");
	for (UINT i = 0; i < pRoll_LEFT->GetMaxFrame(); i++)
	{
		pRoll_LEFT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pROll_RIGHT = GetAnimator()->FindAnimation(L"ROLL_RIGHT");
	for (UINT i = 0; i < pROll_RIGHT->GetMaxFrame(); i++)
	{
		pROll_RIGHT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pRollEND_LEFT = GetAnimator()->FindAnimation(L"ROLL_LEFT_END");
	for (UINT i = 0; i < pRollEND_LEFT->GetMaxFrame(); i++)
	{
		pRollEND_LEFT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pROllEND_RIGHT = GetAnimator()->FindAnimation(L"ROLL_RIGHT_END");
	for (UINT i = 0; i < pROllEND_RIGHT->GetMaxFrame(); i++)
	{
		pROllEND_RIGHT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pRollStun_LEFT = GetAnimator()->FindAnimation(L"ROLL_STUN_LEFT");
	for (UINT i = 0; i < pRollStun_LEFT->GetMaxFrame(); i++)
	{
		pRollStun_LEFT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pROllStun_RIGHT = GetAnimator()->FindAnimation(L"ROLL_STUN_RIGHT");
	for (UINT i = 0; i < pROllStun_RIGHT->GetMaxFrame(); i++)
	{
		pROllStun_RIGHT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}


	CAnimation* pRollStunEND_LEFT = GetAnimator()->FindAnimation(L"ROLL_STUN_END_LEFT");
	for (UINT i = 0; i < pRollStunEND_LEFT->GetMaxFrame(); i++)
	{
		pRollStunEND_LEFT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pROllStunEND_RIGHT = GetAnimator()->FindAnimation(L"ROLL_STUN_END_RIGHT");
	for (UINT i = 0; i < pROllStunEND_RIGHT->GetMaxFrame(); i++)
	{
		pROllStunEND_RIGHT->GetFrame(i).vOffset = Vec2(0.f, -35.f);
	}

	CAnimation* pDEAD_LEFT = GetAnimator()->FindAnimation(L"DEAD_LEFT");
	for (UINT i = 0; i < pDEAD_LEFT->GetMaxFrame(); i++)
	{
		pDEAD_LEFT->GetFrame(i).vOffset = Vec2(0.f, 50.f);
	}

	CAnimation* pDEAD_RIGHT = GetAnimator()->FindAnimation(L"DEAD_RIGHT");
	for (UINT i = 0; i < pDEAD_RIGHT->GetMaxFrame(); i++)
	{
		pDEAD_RIGHT->GetFrame(i).vOffset = Vec2(0.f, 50.f);
	}

	dwtime = GetTickCount64();
}

CFalseKnight::~CFalseKnight()
{

}

void CFalseKnight::update()
{

	
	update_move();
	update_state();
	update_sound();
	update_animation();

	Vec2 vPos = GetPos();

	if (vPos.x - 1500 < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x + 1500 > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& CPlayerMgr::GenInst()->GetCurPlayerPos().y < 2200.f)
	{
		//여기서 조건좀 수정해서 몇초에 한번씩 패턴주기.
		if (m_iHP == 15 && m_eCurState != KNIGHT_STATE::DEAD)
		{

			if (m_iStunCount == 1)
			{
				CreateStunEffect();
				m_eCurState = KNIGHT_STATE::ROLL;
				m_iStunCount = 2;
			}

		}

		else if (m_iHP == 10 && m_eCurState != KNIGHT_STATE::DEAD)
		{

			if (m_iStunCount == 2)
			{
				CreateStunEffect();
				m_eCurState = KNIGHT_STATE::ROLL;
				m_iStunCount = 3;
			}

		}

		else if (m_iHP == 5 && m_eCurState != KNIGHT_STATE::DEAD)
		{

			
			if (m_iStunCount == 3)
			{
				CreateStunEffect();
				m_eCurState = KNIGHT_STATE::ROLL;
				m_iStunCount = 4;
			}

		}

		else if (dwtime + 3000 < GetTickCount64() && m_eCurState != KNIGHT_STATE::DEAD)
		{
			m_iPatternCount++;

			if (m_iHP < 15 && m_iPatternCount % 4 == 3)
			{
				m_eCurState = KNIGHT_STATE::ANGRY_ATTACK_ANTICIPATE;
			}
			if (m_iPatternCount % 4 == 2)
			{
				m_eCurState = KNIGHT_STATE::JUMP_ANTICIPATE;
			}

			else if (m_iPatternCount % 4 == 1)
			{
				m_eCurState = KNIGHT_STATE::ATTACK_ANTICIPATE;
			}

			else if (m_iPatternCount % 4 == 0)
			{
				m_eCurState = KNIGHT_STATE::RUSH_ANTICIPATE;

			}

			dwtime = GetTickCount64();
		}

		m_ePreState = m_eCurState;
	}
}

void CFalseKnight::render(HDC _dc)
{
	GetAnimator()->render(_dc);
	//component_render(_dc);
}



void CFalseKnight::update_move()
{
	Vec2 vPos = GetPos();

	if (vPos.x - 1000 < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& CPlayerMgr::GenInst()->GetCurPlayerPos().y < 2200.f
		)
	{
		if (m_eCurState != KNIGHT_STATE::DEAD)
		{

			if (m_eCurState == KNIGHT_STATE::IDLE )
			{
				vPos.x -= 100 * fDT;
			}

			/*if (m_eCurState == KNIGHT_STATE::RUSH)
			{
				vPos.x -= 400 * fDT;
			}*/
			
			if (m_eCurState != KNIGHT_STATE::RUSH
				&& m_eCurState != KNIGHT_STATE::JUMP
				&& m_eCurState != KNIGHT_STATE::JUMP_LAND)
			{
				m_iDir = -1;
			}

			

		}
	}

	if (m_eCurState == KNIGHT_STATE::RUSH && m_iDir == -1)
	{
		vPos.x -= 500 * fDT;
	}
	


	else if (vPos.x + 1000 > CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& vPos.x < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& CPlayerMgr::GenInst()->GetCurPlayerPos().y < 2200.f)
		{
			if (m_eCurState != KNIGHT_STATE::DEAD)
			{
				if (m_eCurState == KNIGHT_STATE::IDLE)
				{
					vPos.x += 100 * fDT;
				}

				/*if (m_eCurState == KNIGHT_STATE::RUSH)
				{
					vPos.x += 500 * fDT;
				}*/
				if (m_eCurState != KNIGHT_STATE::RUSH
					&& m_eCurState != KNIGHT_STATE::JUMP
					&& m_eCurState != KNIGHT_STATE::JUMP_LAND)
				{
					m_iDir = 1;
				}

				
				//m_eCurState = KNIGHT_STATE::ATTACK_ANTICIPATE;
				
			}
		}

	if (m_eCurState == KNIGHT_STATE::RUSH && m_iDir == 1)
	{

		vPos.x += 500 * fDT;
	}
	

	// 보스몬스터 ROLL 과정 
	if (m_eCurState == KNIGHT_STATE::ROLL && m_iDir == -1)
	{
		vPos.x += 500 * fDT;
	}

	if (m_eCurState == KNIGHT_STATE::ROLL && m_iDir == 1)
	{
		vPos.x -= 500 * fDT;
	}

	/*if (m_eCurState == KNIGHT_STATE::ROLLEND && m_iDir == -1)
	{
		vPos.x += 200 * fDT;
	}

	if (m_eCurState == KNIGHT_STATE::ROLLEND && m_iDir == 1)
	{
		vPos.x -= 200 * fDT;
	}*/

	

	if (m_eCurState == KNIGHT_STATE::JUMP && m_iDir == -1)
	{
		vPos.x -= 500 * fDT;
		m_iGetVelocityCount++;
		if (GetRigidBody() && m_iGetVelocityCount <3)
		{
			// 점프 크기 조절
			//GetRigidBody()->AddVelocity(Vec2(0.f, -200.f)); // 중력 가속도 계속 받는 점프 (이중점프시 영향받음)
			// 스테틱 변수 통해 땅에 닿았을때 OnCollisionEnter에서 스테틱변수 다시 0으로 만드는 방식으로 하면 될듯 
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
		}
	}

	if (m_eCurState == KNIGHT_STATE::JUMP && m_iDir == 1)
	{
		vPos.x += 500 * fDT;
		m_iGetVelocityCount++;
		if (GetRigidBody() && m_iGetVelocityCount < 3)
		{
			// 점프 크기 조절
			//GetRigidBody()->AddVelocity(Vec2(0.f, -200.f)); // 중력 가속도 계속 받는 점프 (이중점프시 영향받음)
			// 스테틱 변수 통해 땅에 닿았을때 OnCollisionEnter에서 스테틱변수 다시 0으로 만드는 방식으로 하면 될듯 
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
		}
		
	}

	if (m_eCurState == KNIGHT_STATE::JUMP_LAND)
	{
		vPos.y += 500 * fDT;
		m_iGetVelocityCount = 0;
	
	}

	SetPos(vPos);
}

void CFalseKnight::update_state()
{
	

}

void CFalseKnight::update_sound()
{
	CSound* pAttakGroundSound = CResMgr::GenInst()->FindSound(L"hit_Ground");
	CSound* pRushSound = CResMgr::GenInst()->FindSound(L"Rush");
	CSound* pRageSound = CResMgr::GenInst()->FindSound(L"Rage");
	CSound* pAttackSound = CResMgr::GenInst()->FindSound(L"Attack_voice");

	CSound* pJumpAnticipateSound = CResMgr::GenInst()->FindSound(L"Jump_Anticipate");
	CSound* pJumpSound = CResMgr::GenInst()->FindSound(L"Jump_Sound");
	CSound* pJumpLandSound = CResMgr::GenInst()->FindSound(L"Jump_Land_Sound");
	CSound* pRollSound = CResMgr::GenInst()->FindSound(L"Roll_Sound");

	
	switch (m_eCurState)
	{
	case KNIGHT_STATE::IDLE:
		break;
	case KNIGHT_STATE::RUSH_ANTICIPATE:
		break;
	case KNIGHT_STATE::RUSH:
		if (!m_bSoundPlayed)
		{
			pRushSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case KNIGHT_STATE::ATTACK_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pAttackSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
		break;
	case KNIGHT_STATE::ATTACK:
		if (!m_bSoundPlayed)
		{
			pAttakGroundSound->Play(false);
			m_bSoundPlayed = true; 
		}
		break;
	case KNIGHT_STATE::ATTACK_RECOVER:
		break;
	case KNIGHT_STATE::ANGRY_ATTACK_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pRageSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case KNIGHT_STATE::ANGRY_ATTACK:
		break;
	case KNIGHT_STATE::ANGRY_ATTACK_RECOVER:
		break;
	case KNIGHT_STATE::DEAD:
		break;

	case KNIGHT_STATE::JUMP_ANTICIPATE:
		if (!m_bSoundPlayed)
		{
			pJumpAnticipateSound ->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case KNIGHT_STATE::JUMP:
		if (!m_bSoundPlayed)
		{
			pJumpSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	case KNIGHT_STATE::JUMP_LAND:
		if (!m_bSoundPlayed)
		{
			pJumpLandSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;

	case KNIGHT_STATE::ROLL:
		if (!m_bSoundPlayed)
		{
			pRollSound->Play(false);
			m_bSoundPlayed = true;
		}
		break;
	}
	
}

void CFalseKnight::update_animation()
{
	

	// 여기가 공격 시작 부분 
	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::ATTACK_ANTICIPATE)
	{
		GetAnimator()->Play(L"ATTACK_ANTICIPATE_LEFT_FALSEKNIGHT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::ATTACK;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::ATTACK_ANTICIPATE)
	{
		GetAnimator()->Play(L"ATTACK_ANTICIPATE_RIGHT_FALSEKNIGHT", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::ATTACK;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}
		
	}


	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::ATTACK)
	{
		GetCollider()->SetOffsetPos(Vec2(-200.f, 20.f));
		GetAnimator()->Play(L"ATTACK_LEFT_FALSEKNIGHT", false);
		CCamera::GenInst()->BossRoomControlCamera(-200.f);

		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				CreateAttackWave();
				m_eCurState = KNIGHT_STATE::ATTACK_RECOVER;
				GetCollider()->SetOffsetPos(Vec2(-15.f, 20.f));
				
			}
		}
	}


	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::ATTACK)
	{
		
		GetCollider()->SetOffsetPos(Vec2(-200.f, 20.f));
		GetAnimator()->Play(L"ATTACK_RIGHT_FALSEKNIGHT", false);
		CCamera::GenInst()->BossRoomControlCamera(-200.f);

		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			CreateAttackWave();
			m_eCurState = KNIGHT_STATE::ATTACK_RECOVER;
			GetCollider()->SetOffsetPos(Vec2(-15.f, 20.f));
			
		}

	}


	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::ATTACK_RECOVER)
	{
		GetAnimator()->Play(L"ATTACK_RECOVER_LEFT_FALSEKNIGHT", false);
		CCamera::GenInst()->BossRoomControlCamera(120.f);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::IDLE;
				//// 7월 8일 수정 
				//m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::ATTACK_RECOVER)
	{
		GetAnimator()->Play(L"ATTACK_RECOVER_RIGHT_FALSEKNIGHT", false);
		CCamera::GenInst()->BossRoomControlCamera(120.f);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::IDLE;
			////7월 8일 수정
			//m_bSoundPlayed = false;
		}

	}



	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::IDLE)
	{
		GetAnimator()->Play(L"Idle_LEFT_FALSEKNIGHT", true);
		//// 7월 8일 수정 
		m_bSoundPlayed = false;
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::IDLE;
			
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::IDLE)
	{
		GetAnimator()->Play(L"Idle_RIGHT_FALSEKNIGHT", true);
		//// 7월 8일 수정 
		m_bSoundPlayed = false;
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::IDLE;
		}

	}

	

	//======================================================================
	//======================================================================
	//돌진 


	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::RUSH_ANTICIPATE)
	{
		GetAnimator()->Play(L"RUSH_ANTICIPATE_LEFT_FALSEKNIGHT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::RUSH;
				m_bSoundPlayed = false; 
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::RUSH_ANTICIPATE)
	{
		GetAnimator()->Play(L"RUSH_ANTICIPATE_RIGHT_FALSEKNIGHT", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::RUSH;
			m_bSoundPlayed = false; 
		}

	}


	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::RUSH)
	{
		
		GetAnimator()->Play(L"RUSH_LEFT_FALSEKNIGHT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::IDLE;
				
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::RUSH)
	{
		
		GetAnimator()->Play(L"RUSH_RIGHT_FALSEKNIGHT", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::IDLE;
		}

	}

	//======================================================================
	//======================================================================
	//광폭화


	if (m_eCurState == KNIGHT_STATE::ANGRY_ATTACK_ANTICIPATE)
	{
		m_bAngryCount++;
		if(m_bAngryCount==1)
		{
			m_bSoundPlayed = false;
		}
		

		GetAnimator()->Play(L"ATTACK_ANTICIPATE_LEFT_FALSEKNIGHT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{	
				CCamera::GenInst()->BossRoomControlCamera(-200.f);
				if(m_iStoneCount<1)	
				{
					CreateFallStone();
				}
				m_iStoneCount++;
			/*	CCamera::GenInst()->SetTarget(nullptr);
				CCamera::GenInst()->SetLookAty(200.f);*/
				//CCamera::GenInst()->SetLookAt(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x, CCamera::GenInst()->GetLookAt().y - 100));
				//CCamera::GenInst()->virbration(2.f);
				//CCamera::GenInst()->ControlLeftTargetPos();
				GetAnimator()->Play(L"ANGRY_ATTACK_LEFT_FALSEKNIGHT", false);
				
				
				if(GetAnimator()->GetAnimation()->IsFinish())
				{
					CCamera::GenInst()->BossRoomControlCamera(400.f);
					m_iStoneCount = 0;
					//CreateFallStone();
					//CCamera::GenInst()->SetLookAty(-100.f);
					//CCamera::GenInst()->SetLookAt(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x, CCamera::GenInst()->GetLookAt().y +100));
					//CCamera::GenInst()->ControlRightTargetPos();
					GetAnimator()->Play(L"ANGRY_ATTACK_RIGHT_FALSEKNIGHT", false);
					//CCamera::GenInst()->SetLookAt(Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x+1000, CPlayerMgr::GenInst()->GetCurPlayerPos().y));
					if (GetAnimator()->GetAnimation()->IsFinish())
					{
						GetAnimator()->SetAnimationFrame(L"ANGRY_ATTACK_LEFT_FALSEKNIGHT", 0);
						GetAnimator()->SetAnimationFrame(L"ANGRY_ATTACK_RIGHT_FALSEKNIGHT", 0);
						m_iCount++;

						if(m_iCount ==7)
						{
							m_eCurState = KNIGHT_STATE::RUSH_ANTICIPATE;
							m_iCount = 0;
							m_bAngryCount = 0; 
						}
					}
				}
			}
		}
	}

	//점프 공격 부분 애니메이션 

	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::JUMP_ANTICIPATE)
	{
		GetAnimator()->Play(L"JUMP_LEFT_ANTICIPATE", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::JUMP;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::JUMP_ANTICIPATE)
	{
		GetAnimator()->Play(L"JUMP_LEFT_ANTICIPATE", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::JUMP;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::JUMP)
	{
		GetAnimator()->Play(L"JUMP_LEFT", false);
		CCamera::GenInst()->BossRoomControlCamera(-150.f);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::JUMP_LAND;
				m_bSoundPlayed = false; 
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::JUMP)
	{
		GetAnimator()->Play(L"JUMP_RIGHT", false);
		CCamera::GenInst()->BossRoomControlCamera(-150.f);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::JUMP_LAND;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::JUMP_LAND)
	{
		GetAnimator()->Play(L"JUMP_LEFT_LAND", false);
		CCamera::GenInst()->BossRoomControlCamera(200.f);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				CreateJumpWave();
				
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::IDLE;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::JUMP_LAND)
	{
		
		GetAnimator()->Play(L"JUMP_RIGHT_LAND", false);
		CCamera::GenInst()->BossRoomControlCamera(200.f);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			CreateJumpWave();
			
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	//구르기 과정 
	//ROLL_LEFT, ROLL_LEFT_END

	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::ROLL)
	{
		GetAnimator()->Play(L"ROLL_LEFT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::ROLLEND;
				//7월 8일 수정
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::ROLL)
	{
		GetAnimator()->Play(L"ROLL_RIGHT", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::ROLLEND;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::ROLLEND)
	{
		GetAnimator()->Play(L"ROLL_LEFT_END", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->GetAnimation()->SetFrame(0);
				m_eCurState = KNIGHT_STATE::STUN_OPEN;
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::ROLLEND)
	{
		GetAnimator()->Play(L"ROLL_RIGHT_END", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->GetAnimation()->SetFrame(0);
			m_eCurState = KNIGHT_STATE::STUN_OPEN;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::STUN_OPEN)
	{
		GetAnimator()->Play(L"ROLL_STUN_LEFT", false);
		{
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->Play(L"ROLL_STUN_END_LEFT", true);
				//GetAnimator()->GetAnimation()->SetFrame(3);
				//m_eCurState = KNIGHT_STATE::IDLE;
				m_bSoundPlayed = false;
			}
		}
	}

	else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::STUN_OPEN)
	{
		GetAnimator()->Play(L"ROLL_STUN_RIGHT", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->Play(L"ROLL_STUN_END_RIGHT", true);
			//GetAnimator()->GetAnimation()->SetFrame(3);
			//m_eCurState = KNIGHT_STATE::IDLE;
			//7월 8일 수정
			m_bSoundPlayed = false;
		}

	}

	//죽음
	
	if (m_iHP < 0) 
	{
		m_eCurState = KNIGHT_STATE::DEAD;
		

		if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::DEAD)
		{
			GetAnimator()->Play(L"ROLL_LEFT", false);
			
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->Play(L"DEAD_LEFT", false);
				if (GetAnimator()->GetAnimation()->IsFinish())
				{
					
					DeleteObject(this);
				}
			}
		}

		else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::DEAD)
		{
			
			GetAnimator()->Play(L"ROLL_RIGHT", false);
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->Play(L"DEAD_RIGHT", false);
				if (GetAnimator()->GetAnimation()->IsFinish())
				{
					DeleteObject(this);
				}
			}
		}
	}
	
}

void CFalseKnight::CreateFallStone()
{
	CStone* pStone = new CStone;

	pStone->SetPos(GetPos() - Vec2((float)(rand()%2001)-1000.f, 500.f)); // 플레이어의 좌표 받아옴

	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pStone->SetName(L"Stone");

	CreateObject(pStone, GROUP_TYPE::MONSTER);
}

void CFalseKnight::CreateAttackWave()
{

	CAttackWave* pAttackWaveEffect = new CAttackWave;

	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 
	pAttackWaveEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pAttackWaveEffect->SetPos(GetPos() - Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pAttackWaveEffect->SetPos(GetPos() + Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pAttackWaveEffect->SetName(L"Attack_Wave");

	CreateObject(pAttackWaveEffect, GROUP_TYPE::MONSTER);
}

void CFalseKnight::CreateJumpWave()
{
	CAttackWave* pAttackWaveEffect1 = new CAttackWave;
	CAttackWave* pAttackWaveEffect2 = new CAttackWave;
	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 
	
	pAttackWaveEffect1->SetDir(-1);
	pAttackWaveEffect1->SetPos(GetPos() - Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	
	pAttackWaveEffect2->SetDir(1);
	pAttackWaveEffect2->SetPos(GetPos() + Vec2(80.f, 0.f));
	
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pAttackWaveEffect1->SetName(L"Jump_Attack_Wave_Left");
	pAttackWaveEffect2->SetName(L"Jump_Attack_Wave_Right");

	CreateObject(pAttackWaveEffect1, GROUP_TYPE::MONSTER);
	CreateObject(pAttackWaveEffect2, GROUP_TYPE::MONSTER);
}



void CFalseKnight::OnCollision(CCollider* _pOther)
{

}

void CFalseKnight::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pDamagedArmor = CResMgr::GenInst()->FindSound(L"Damaged_armor");
	CSound* pDamagedBody = CResMgr::GenInst()->FindSound(L"Stun_Hit_Sound");
	//CSound* pDeathSound = CResMgr::GenInst()->FindSound(L"Enemy_Death");

	CObject* pOtherObj = _pOther->GetObj();
	if(pOtherObj->GetName() == L"DOWN_SLASH_Effect")
	{
		CPlayerMgr::GenInst()->SetGroundHit(true);
	}

	if (L"SLASH" == _pOther->GetObj()->GetName()
		|| pOtherObj->GetName() == L"DOWN_SLASH_Effect")
	{

		if (m_iDir == -1 && m_eCurState == KNIGHT_STATE::STUN_OPEN)
		{
			GetAnimator()->SetAnimationFrame(L"ROLL_STUN_LEFT", 2);
			pDamagedBody->Play(false);
		}

		else if (m_iDir == 1 && m_eCurState == KNIGHT_STATE::STUN_OPEN)
		{
			GetAnimator()->SetAnimationFrame(L"ROLL_STUN_RIGHT", 2);
			pDamagedBody->Play(false);
		}
		m_iHP--;
		if(CPlayerMgr::GenInst()->GetPlayerMp()<6)
		{
			CPlayerMgr::GenInst()->IncreaseMp(1);
		}
		
		pDamagedArmor->Play(false);


		if(m_iHP<0)
		{
			CSound* pDeadSound = CResMgr::GenInst()->FindSound(L"Death_Sound");

			pDeadSound->Play(false);

			CResMgr::GenInst()->LoadSound(L"BGM_01", L"sound\\S19_Crossroads_Bass.wav");
			CSound* pNewSound = CResMgr::GenInst()->FindSound(L"BGM_01");
			pNewSound->PlayToBGM(true);
			
			// 여기다가 작성하기. 일단 Dead 상태로 만들고 해서 패턴 못쓰게 하기.
			
		}

		

	}

	if (L"FireBall" == _pOther->GetObj()->GetName())
	{
		m_iHP--;
		DeleteObject(pOtherObj);


		pDamagedArmor->Play(false);

		if (m_iHP < 0)
		{
			DeleteObject(this);
		}
	}

}

void CFalseKnight::OnCollisionExit(CCollider* _pOther)
{

}

void CFalseKnight::CreateStunEffect()
{
	CStunEffect* pStuneffect1 = new CStunEffect;

	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 
	pStuneffect1->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pStuneffect1->SetPos(GetPos() - Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pStuneffect1->SetPos(GetPos() + Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pStuneffect1->SetName(L"Stun_Effect");

	CreateObject(pStuneffect1, GROUP_TYPE::SKILLEFFECT);
}
