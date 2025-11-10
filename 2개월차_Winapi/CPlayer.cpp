#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CMissile2.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPathMgr.h"
#include "CTexture.h"

#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CGravity.h"

#include "CPlayerMgr.h"
#include "CSLASH.h"
#include "CFocus.h"
#include "CFireBall.h"
#include "CProFireBall.h"
#include "CDashEffect.h"
#include "CUPSLASH.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CPlayerDamaged.h"
#include "CDownSlash.h"


#include "CWing.h"
#include "CNewDashEffect.h"
#include "CPlayerStunEffect.h"

CPlayer::CPlayer()
	: m_iHP(5)
	, m_ePreState(PLAYER_STATE::IDLE)
	, m_eCurState(PLAYER_STATE::WALK)
	, m_iDir(1)
	, m_iPrevDir(1)
	, i_Count(0)
	, m_eHpState(PLAYER_HP_STATE::END)
	, m_i_JumpCount(0)
	, m_iUpSlashEffectCount(0)
	, m_iDownSlashEffectCount(0)
	, m_i_SlashCount(0)
	, m_bGround(false)
	, m_bFallLeftAnimationSet(false)
	, m_bFallRightAnimationSet(false)
{
	dwtime = GetTickCount64();
	//Texture 로딩하기
	/*m_pTex = new CTexture;
	wstring strFilepath = CPathMgr::GenInst()->GetContentPath();
	strFilepath += L"texture\\player.bmp";
	m_pTex->Load(strFilepath);*/

	//m_pTex = CResMgr::GenInst()->LoadTexture(L"PlayerTex", L"texture\\F_18.bmp");
	CreateCollider();

	//충돌체 크기조정
	GetCollider()->SetOffsetPos(Vec2(0.f, 15.f));
	GetCollider()->SetScale(Vec2(25.f, 50.f));
	
	//애니메이션 원래 코드 
	CTexture* m_pIdileTex		 = CResMgr::GenInst()->LoadTexture(L"PlayerIdle", L"texture\\Player\\idle.bmp");
	CTexture* m_pWalkTex		 = CResMgr::GenInst()->LoadTexture(L"PlayerWalk", L"texture\\Player\\walk.bmp");
	CTexture* m_pJumpTex		 = CResMgr::GenInst()->LoadTexture(L"PlayerJump", L"texture\\Player\\jump.bmp");
	CTexture* m_pDoubleJumpTex   = CResMgr::GenInst()->LoadTexture(L"PlayerDoubleJump", L"texture\\Player\\Double_Jump.bmp");

	CTexture* m_pSlashTex		 = CResMgr::GenInst()->LoadTexture(L"PlayerSlash", L"texture\\Player\\knight_slash2.bmp");
	CTexture* m_pFocusTex        = CResMgr::GenInst()->LoadTexture(L"PlayerFocus", L"texture\\Player\\knight_Focus2.bmp");
	CTexture* m_pFireballCastTex = CResMgr::GenInst()->LoadTexture(L"PlayerFireball", L"texture\\Player\\fireballcast_knight.bmp");
	CTexture* m_pDashTex         = CResMgr::GenInst()->LoadTexture(L"PlayerDash", L"texture\\Player\\Knight_Dash.bmp");
	CTexture* m_pUpSlash		 = CResMgr::GenInst()->LoadTexture(L"PlayerUpSlash", L"texture\\Player\\Up_Slash_Real2.bmp");

	CTexture* m_pPlayerStunTex   = CResMgr::GenInst()->LoadTexture(L"PlayeStun", L"texture\\Player\\knight_Stun.bmp");
	CTexture* m_pPlyerDownSlashTex = CResMgr::GenInst()->LoadTexture(L"PlayeDownSlash", L"texture\\Player\\Down_Slash.bmp");

	CTexture* m_pPlyerFallTex = CResMgr::GenInst()->LoadTexture(L"PlayeFall", L"texture\\Player\\Knight_Fall.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Idle_LEFT", m_pIdileTex, Vec2(0.f, 0.f), Vec2(45.f, 96.f), Vec2(45.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"Idle_RIGHT", m_pIdileTex, Vec2(0.f, 96.f), Vec2(45.f, 96.f), Vec2(45.f, 0.f), 0.1f, 7);

	GetAnimator()->CreateAnimation(L"WALK_LEFT",  m_pWalkTex, Vec2(0.f, 0.f), Vec2(45.f, 96.f), Vec2(45.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT",   m_pWalkTex, Vec2(0.f, 96.f), Vec2(45.f, 96.f), Vec2(45.f, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(L"JUMP_LEFT", m_pJumpTex, Vec2(0.f, 0.f), Vec2(76.f, 108.f), Vec2(76.f, 0.f), 0.2f, 12);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", m_pJumpTex, Vec2(0.f, 108.f), Vec2(76.f, 108.f), Vec2(76.f, 0.f), 0.2f, 12);

	GetAnimator()->CreateAnimation(L"DOUBLE_JUMP_LEFT", m_pDoubleJumpTex, Vec2(344.f, 0.f), Vec2(86.f, 110.f), Vec2(86.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"DOUBLE_JUMP_RIGHT", m_pDoubleJumpTex, Vec2(344.f, 110.f), Vec2(86.f, 110.f), Vec2(86.f, 0.f), 0.2f, 4);

	GetAnimator()->CreateAnimation(L"SLASH_LEFT", m_pSlashTex, Vec2(0.f, 0.f), Vec2(100.f, 98.f), Vec2(100.f, 0.f), 0.02f, 9);
	GetAnimator()->CreateAnimation(L"SLASH_RIGHT", m_pSlashTex, Vec2(0.f, 98.f), Vec2(100.f, 98.f), Vec2(100.f, 0.f), 0.02f, 9);

	GetAnimator()->CreateAnimation(L"FOCUS_LEFT", m_pFocusTex, Vec2(0.f, 0.f), Vec2(54.f, 95.f), Vec2(54.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"FOCUS_RIGHT", m_pFocusTex, Vec2(0.f, 95.f), Vec2(54.f, 95.f), Vec2(54.f, 0.f), 0.1f, 7);
	
	GetAnimator()->CreateAnimation(L"FIREBALL_LEFT", m_pFireballCastTex, Vec2(0.f, 0.f), Vec2(81.f, 97.f), Vec2(81.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"FIREBALL_RIGHT", m_pFireballCastTex, Vec2(0.f, 97.f), Vec2(81.f, 97.f), Vec2(81.f, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(L"DASH_LEFT", m_pDashTex, Vec2(0.f, 0.f), Vec2(121.f, 86.f), Vec2(121.f, 0.f), 0.02f, 12);
	GetAnimator()->CreateAnimation(L"DASH_RIGHT", m_pDashTex, Vec2(0.f, 86.f), Vec2(121.f, 86.f), Vec2(121.f, 0.f), 0.02f, 12);

	GetAnimator()->CreateAnimation(L"UP_SLASH", m_pUpSlash, Vec2(0.f, 0.f), Vec2(73.f, 96.f), Vec2(73.f, 0.f), 0.05f, 9);

	GetAnimator()->CreateAnimation(L"DOWN_SLASH", m_pPlyerDownSlashTex, Vec2(0.f, 0.f), Vec2(89.f, 95.f), Vec2(89.f, 0.f), 0.05f, 10);

	GetAnimator()->CreateAnimation(L"STUN_LEFT", m_pPlayerStunTex, Vec2(0.f, 0.f), Vec2(71.f, 93.f), Vec2(0.f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"STUN_RIGHT",m_pPlayerStunTex, Vec2(0.f, 93.f), Vec2(71.f, 93.f), Vec2(0.f, 0.f), 0.3f, 1);

	GetAnimator()->CreateAnimation(L"FALL_LEFT", m_pPlyerFallTex, Vec2(0.f, 0.f), Vec2(57.f, 99.f), Vec2(57.f, 0.f), 1.f, 6);
	GetAnimator()->CreateAnimation(L"FALL_RIGHT", m_pPlyerFallTex, Vec2(0.f, 99.f), Vec2(57.f, 99.f), Vec2(57.f, 0.f), 1.f, 6);
	
	//사운드 관련 부분 
	CResMgr::GenInst()->LoadSound(L"Player_Walk", L"sound\\Player\\Knight_Walk.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Jump", L"sound\\Player\\Knight_jump.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Double_Jump", L"sound\\Player\\Knight_doubleJump.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Dash", L"sound\\Player\\Knight_dash.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Slash1", L"sound\\Player\\sword_1.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Slash2", L"sound\\Player\\sword_2.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Slash3", L"sound\\Player\\sword_3.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Slash4", L"sound\\Player\\sword_4.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Slash5", L"sound\\Player\\sword_5.wav");
	CResMgr::GenInst()->LoadSound(L"Player_focus_Success", L"sound\\Player\\Knight_focus_Success.wav");

	CResMgr::GenInst()->LoadSound(L"Player_Jump_Land", L"sound\\Player\\Knight_land_soft.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Fireballcast", L"sound\\Player\\Knight_fireball.wav");
	CResMgr::GenInst()->LoadSound(L"Player_Knight_damaged", L"sound\\Player\\Knight_damage.wav");
	///

	GetAnimator()->Play(L"Idle_RIGHT", true); //true면 반복재생 false면 1회재생 (모든프레임)

	CreateGravity();


	//강체 추가
	CreateRigidBody();

	//애니메이션 오프셋 관련 코드 
	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	/*for (UINT i = 0; i < pAnim->GetMaxFrame(); i++)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}*/

	//플레이어 hp 설정 
	CPlayerMgr::GenInst()->SetPlayerHp(m_iHP);
	CPlayerMgr::GenInst()->SetPlayerMp(6);

}

CPlayer::~CPlayer()
{
	/*if (nullptr != m_pTex)
	{
		delete m_pTex;
		m_pTex = nullptr;
	}*/
}

void CPlayer::update()
{
	//Vec2 vPos = GetPos(); // 지역변수이기 때문에 생명주기 확인
	


	update_move();

	update_state();

	update_sound();

	update_animation();

	/*if (KEY_TAP(KEY::Q))
	{
		SetPos(Vec2(200.f, 100.f));
	}*/

	GetAnimator()->update();

	m_ePreState = m_eCurState;
	m_iPrevDir = m_iDir;

	

	
	//6월 21일 이후 애니메이션 프레임워크 코드
	//GetAnimator()->update();
	
	
	//SetPos(vPos); // 값을 넘겨줘서 메모리값을 넘겨줌 
	
	//=====================
	//퀘스트 관련 코드 
	//=====================

	if (KEY_TAP(KEY::R))
	{
		CPlayerMgr::GenInst()->QuestPageIncrease(1);
	}

	if (KEY_TAP(KEY::T))
	{
		CPlayerMgr::GenInst()->QuestPageDecrease(1);
	}

	if (KEY_TAP(KEY::I))
	{
		CPlayerMgr::GenInst()->SetInventoryOnOff();
	}

	if(KEY_TAP(KEY::N))
	{
		CPlayerMgr::GenInst()->QuestPage2Increase(1);
	}
}

void CPlayer::render(HDC _dc)
{
	
	GetAnimator()->render(_dc);
	// 컴포넌트 (충돌체, etc ..)가 있는 경우 출력.
	//component_render(_dc);


	//플레이어 실시간 좌표값 받아오는것  
	/*wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"Pos : %f,%f", GetPos().x, GetPos().y);
	SetTextColor(_dc, RGB(255, 255, 255));
	SetBkMode(_dc, TRANSPARENT);
	TextOut(_dc, 100, 500, szBuffer,29);*/
	HFONT hFont = CreateFont(
		40,                // 글자 높이
		0,                 // 글자 너비 (0은 자동 조정)
		0,                 // 문자 기울기 (각도)
		0,                 // 기준선과의 각도
		FW_NORMAL,         // 글자 굵기
		FALSE,             // 이탤릭체
		FALSE,             // 밑줄
		FALSE,             // 취소선
		DEFAULT_CHARSET,   // 문자 집합
		OUT_DEFAULT_PRECIS,// 출력 정밀도
		CLIP_DEFAULT_PRECIS,// 클리핑 정밀도
		DEFAULT_QUALITY,   // 출력 품질
		DEFAULT_PITCH | FF_SWISS,// 글꼴 가족 및 글꼴 속성
		L"이사만루체 Medium");         // 글꼴 이름

	HFONT hOldFont = (HFONT)SelectObject(_dc, hFont);

	wchar_t szBuffer[255] = {};
	int len = swprintf_s(szBuffer, L"%d", CPlayerMgr::GenInst()->GetGeoCount());
	swprintf_s(szBuffer, L"%d", CPlayerMgr::GenInst()->GetGeoCount());
	SetTextColor(_dc, RGB(255, 255, 255));
	SetBkMode(_dc, TRANSPARENT);
	TextOut(_dc, 160, 180, szBuffer, len);

	SelectObject(_dc, hOldFont);
	DeleteObject(hFont);
}


void CPlayer::update_state()
{
	
	if (KEY_HOLD(KEY::LEFT))
	{
		m_iDir = -1;
		if (m_eCurState != PLAYER_STATE::JUMP 
			&& m_eCurState !=PLAYER_STATE::DOUBLE_JUMP
			&& m_eCurState != PLAYER_STATE::STUN
			&& m_eCurState != PLAYER_STATE::DASH)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
		
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		m_iDir = 1;
		if (m_eCurState != PLAYER_STATE::JUMP
			&& m_eCurState !=PLAYER_STATE::DOUBLE_JUMP 
			&& m_eCurState != PLAYER_STATE::STUN
			&& m_eCurState != PLAYER_STATE::DASH)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (KEY_TAP(KEY::SPACE) && m_eCurState != PLAYER_STATE::STUN)
	{
		if(m_i_JumpCount == 1)
		{
			m_eCurState = PLAYER_STATE::DOUBLE_JUMP;
			m_i_JumpCount = 0;
		}

		else if(m_i_JumpCount == 0)
		{
			m_eCurState = PLAYER_STATE::JUMP;
			m_i_JumpCount++;
		}

		if(GetRigidBody())
		{
			// 점프 크기 조절
			//GetRigidBody()->AddVelocity(Vec2(0.f, -200.f)); // 중력 가속도 계속 받는 점프 (이중점프시 영향받음)
			// 스테틱 변수 통해 땅에 닿았을때 OnCollisionEnter에서 스테틱변수 다시 0으로 만드는 방식으로 하면 될듯 
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
		}
	}


	if(KEY_NONE(KEY::LEFT)&& KEY_NONE(KEY::RIGHT)
		&& m_eCurState != PLAYER_STATE::JUMP 
		&& m_eCurState != PLAYER_STATE::DOUBLE_JUMP
		&& m_eCurState != PLAYER_STATE::DASH
		&& m_eCurState != PLAYER_STATE::SLASH 
		&& m_eCurState != PLAYER_STATE::FOCUS 
		&& m_eCurState != PLAYER_STATE::FIREBALL
		&& m_eCurState != PLAYER_STATE::UPSLASH
		&& m_eCurState != PLAYER_STATE::STUN
		&& m_eCurState != PLAYER_STATE::DOWN_SLASH
		&& m_eCurState != PLAYER_STATE::FALL)
	{
		
		m_eCurState = PLAYER_STATE::IDLE;
	}


	if(KEY_TAP(KEY::C) 
		&& !(KEY_HOLD(KEY::UP))
		&& !(KEY_HOLD(KEY::DOWN))
		&& m_eCurState != PLAYER_STATE::STUN
		&& m_eCurState != PLAYER_STATE::UPSLASH
		&& m_eCurState != PLAYER_STATE::DOWN_SLASH
		)
	{
		
		// 이부분 테스트중 
		m_eCurState = PLAYER_STATE::SLASH;
		//GetAnimator()->GetAnimation()->SetFrame(0);

	}

	if(KEY_TAP(KEY::A)
		&& m_eCurState != PLAYER_STATE::STUN)
	{
		CreateFocusEffect();
		if(CPlayerMgr::GenInst()->GetPlayerMp() >= 1)
		{
			CPlayerMgr::GenInst()->DecreaseMp(1);
		}
		
		GetAnimator()->GetAnimation()->SetFrame(0);
		
		m_eCurState = PLAYER_STATE::FOCUS;

		CPlayerMgr::GenInst()->IncreaseHp(1);
		//플레리어 피가 5이상 올라가면 예외처리로 5 이상 못넘어가 처리 
		if(CPlayerMgr::GenInst()->GetPlayerHp()>5)
		{
			CPlayerMgr::GenInst()->SetPlayerHp(5);
		}

		
		m_eHpState = PLAYER_HP_STATE::HP_STATE_UP;
	}
	
	if(KEY_TAP(KEY::E) && m_eCurState != PLAYER_STATE::STUN)
	{
		CreateFireBallEffect();
		CreateFireBall();
		if (CPlayerMgr::GenInst()->GetPlayerMp() >= 1)
		{
			CPlayerMgr::GenInst()->DecreaseMp(1);
		}
		m_eCurState = PLAYER_STATE::FIREBALL;
	}

	if(KEY_TAP(KEY::Z))
	{
		m_eCurState = PLAYER_STATE::DASH;
	}

	if (KEY_HOLD(KEY::UP)&& KEY_TAP(KEY::C))
	{
		m_eCurState = PLAYER_STATE::UPSLASH;
	}

	if (KEY_HOLD(KEY::DOWN) && KEY_HOLD(KEY::C))
	{
		m_eCurState = PLAYER_STATE::DOWN_SLASH;
	}

	if(m_eCurState != PLAYER_STATE::JUMP
		&& m_eCurState != PLAYER_STATE::DOUBLE_JUMP
		&& m_eCurState != PLAYER_STATE::DOWN_SLASH
		&& m_eCurState != PLAYER_STATE::SLASH
		&& m_eCurState != PLAYER_STATE::UPSLASH
		&& m_eCurState != PLAYER_STATE::FIREBALL
		&& m_eCurState != PLAYER_STATE::DASH
		&& m_eCurState != PLAYER_STATE::STUN
		&& m_eCurState != PLAYER_STATE::FOCUS
		&& m_bGround == false)
	{
		m_eCurState = PLAYER_STATE::FALL;
	}




	// 플레이어 hp 바 관련 코드 
	const vector<CObject*>& groupObjects = CSceneMgr::GenInst()->GetCurScene()->GetGroupObject(GROUP_TYPE::UI);
	vector<CObject*>::const_iterator iter = groupObjects.begin();
	for (; iter != groupObjects.end(); iter++)
	{
		if ((*iter)->GetName() == L"HpBarUI5")
		{
			if (CPlayerMgr::GenInst()->GetPlayerHp() == 5)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_UP)
				{
					(*iter)->GetAnimator()->Play(L"Hp_Refill", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}

				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Idle", true);
				}

			}

			if (CPlayerMgr::GenInst()->GetPlayerHp()<5)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_DOWN && CPlayerMgr::GenInst()->GetPlayerHp()==4)
				{
					(*iter)->GetAnimator()->Play(L"Hp_break", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}
				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Empty", true);
				}
			}
		}
		//================================================================

		if ((*iter)->GetName() == L"HpBarUI4")
		{
			if (CPlayerMgr::GenInst()->GetPlayerHp() >= 4)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_UP && CPlayerMgr::GenInst()->GetPlayerHp()==4)
				{
					(*iter)->GetAnimator()->Play(L"Hp_Refill", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}

				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Idle", true);
				}

			}

			if (CPlayerMgr::GenInst()->GetPlayerHp() < 4)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_DOWN && CPlayerMgr::GenInst()->GetPlayerHp() == 3)
				{
					(*iter)->GetAnimator()->Play(L"Hp_break", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}
				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Empty", true);
				}
			}
		}

		//=====================================================================================
		if ((*iter)->GetName() == L"HpBarUI3")
		{
			if (CPlayerMgr::GenInst()->GetPlayerHp() >= 3)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_UP && CPlayerMgr::GenInst()->GetPlayerHp() == 3)
				{
					(*iter)->GetAnimator()->Play(L"Hp_Refill", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}

				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Idle", true);
				}

			}

			if (CPlayerMgr::GenInst()->GetPlayerHp() < 3)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_DOWN && CPlayerMgr::GenInst()->GetPlayerHp() == 2)
				{
					(*iter)->GetAnimator()->Play(L"Hp_break", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}
				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Empty", true);
				}
			}
		}
		//=====================================================================================
		if ((*iter)->GetName() == L"HpBarUI2")
		{
			if (CPlayerMgr::GenInst()->GetPlayerHp() >=2)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_UP && CPlayerMgr::GenInst()->GetPlayerHp() == 2)
				{
					(*iter)->GetAnimator()->Play(L"Hp_Refill", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}

				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Idle", true);
				}

			}

			if (CPlayerMgr::GenInst()->GetPlayerHp() < 2)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_DOWN && CPlayerMgr::GenInst()->GetPlayerHp() == 1)
				{
					(*iter)->GetAnimator()->Play(L"Hp_break", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}
				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Empty", true);
				}
			}
		}
		//=====================================================================================
		if ((*iter)->GetName() == L"HpBarUI1")
		{
			if (CPlayerMgr::GenInst()->GetPlayerHp() >=1)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_UP && CPlayerMgr::GenInst()->GetPlayerHp() == 1)
				{
					(*iter)->GetAnimator()->Play(L"Hp_Refill", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}

				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Idle", true);
				}

			}

			if (CPlayerMgr::GenInst()->GetPlayerHp() < 1)
			{
				if (m_eHpState == PLAYER_HP_STATE::HP_STATE_DOWN && CPlayerMgr::GenInst()->GetPlayerHp() == 0)
				{
					(*iter)->GetAnimator()->Play(L"Hp_break", false);
					if ((*iter)->GetAnimator()->GetAnimation()->IsFinish())
					{
						m_eHpState = PLAYER_HP_STATE::END;
						(*iter)->GetAnimator()->SetRepeat(true);
					}
				}
				else
				{
					(*iter)->GetAnimator()->Play(L"Hp_Empty", true);
				}
			}
		}
	}
}

void CPlayer::update_move()
{
	//CRigidBody* pRigid = GetRigidBody();

	Vec2 vPos = GetPos();


	if (KEY_HOLD(KEY::LEFT) && m_eCurState != PLAYER_STATE::STUN)
	{
		vPos.x -= 500.f * fDT;
	
	}

	if (KEY_HOLD(KEY::RIGHT) && m_eCurState != PLAYER_STATE::STUN)
	{
		
		vPos.x += 500.f * fDT;

	}

	if (KEY_TAP(KEY::C) 
		&& !(KEY_AWAY(KEY::UP))
		&& !(KEY_AWAY(KEY::DOWN))
		&& !(KEY_TAP(KEY::UP))
		&& !(KEY_TAP(KEY::DOWN))
		&& !(KEY_HOLD(KEY::UP))
		&& !(KEY_HOLD(KEY::DOWN))
		/*&& m_bGround==true*/)
	{
		/// 7월 1일 이게 지금 두번 발동함
		i_Count++;
		if (i_Count < 2)
		{
			CreateSlash();
			i_Count = 0;
			
		}
	}

	if (KEY_TAP(KEY::C) && (KEY_HOLD(KEY::UP)))
	{
		/// 7월 1일 이게 지금 두번 발동함
		m_iUpSlashEffectCount++;
		if (m_iUpSlashEffectCount < 2)
		{
			CreateUpSlashEffect();
			m_iUpSlashEffectCount = 0;

		}
	}

	if (KEY_TAP(KEY::C) && (KEY_HOLD(KEY::DOWN)))
	{
		/// 7월 1일 이게 지금 두번 발동함
		m_iDownSlashEffectCount++;
		if (m_iDownSlashEffectCount < 2)
		{
			CreateDownSlashEffect();
			m_iDownSlashEffectCount = 0;

		}
	}

	if(m_eCurState == PLAYER_STATE::DASH)
	{
		if(m_iDir ==1)
		{
			vPos.x += 1500.f * fDT; 
		}

		else if(m_iDir == -1)
		{
			vPos.x -= 1500.f * fDT; 
		}
	}


	if (CPlayerMgr::GenInst()->GetGroundHit() == true)
	{
		GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
		CPlayerMgr::GenInst()->SetGroundHit(false);
	}



	SetPos(vPos);

	//플레이어의 위치 실시간 저장 
	//저장해서 스킬 이펙트의 효과를 플레이어 주위에서 발생시킴
	CPlayerMgr::GenInst()->SetCurPlayerPos(vPos);
	

}

void CPlayer::update_animation()
{

	/*if(m_ePreState == m_eCurState && m_iPrevDir == m_iDir)
	{
		return;
	}*/

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir ==- 1)
		{
			GetAnimator()->Play(L"Idle_LEFT", true);
			
		}
		else
		{
			GetAnimator()->Play(L"Idle_RIGHT", true);
			
		}
	}
		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)
		{
			GetAnimator()->Play(L"WALK_LEFT", true);

		}
		else
		{
			GetAnimator()->Play(L"WALK_RIGHT", true);
		}
	}

		break;

	
	case PLAYER_STATE::JUMP:
	{
		if (m_iDir == -1)
		{
			GetAnimator()->Play(L"JUMP_LEFT", false);
			if(GetAnimator()->GetAnimation()->IsFinish())
			{
				m_eCurState = PLAYER_STATE::FALL;
			}
			//GetAnimator()->SetAnimationFrame(L"JUMP_LEFT", 9);
			// 이 밑에 fall 애니메이션 넣으면 될듯 
		}
		else
		{
			GetAnimator()->Play(L"JUMP_RIGHT", false);
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				m_eCurState = PLAYER_STATE::FALL;
			}
				//GetAnimator()->SetAnimationFrame(L"JUMP_RIGHT", 9);
			
		}
	}
		break;


	case PLAYER_STATE::DOUBLE_JUMP:
	{
		if (m_iDir == -1)
		{
			//여기서 방향전환될때 좀 문제임
			GetAnimator()->Play(L"DOUBLE_JUMP_LEFT", false);
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				m_eCurState = PLAYER_STATE::FALL;
			}
				//GetAnimator()->SetAnimationFrame(L"DOUBLE_JUMP_LEFT", 3);
			// 이 밑에 fall 애니메이션 넣으면 될듯 
		}
		else
		{
			GetAnimator()->Play(L"DOUBLE_JUMP_RIGHT", false);
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				m_eCurState = PLAYER_STATE::FALL;
			}
				//GetAnimator()->SetAnimationFrame(L"DOUBLE_JUMP_RIGHT", 3);

		}
	}
	break;

	case PLAYER_STATE::DASH:
	{
		if (m_iDir == -1)
		{
			//여기서 방향전환될때 좀 문제임
			GetAnimator()->Play(L"DASH_LEFT", false);
			//CreateDashEffect();
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				m_eCurState = PLAYER_STATE::IDLE;
				GetAnimator()->SetAnimationFrame(L"DASH_LEFT", 0);
			}
			// 이 밑에 fall 애니메이션 넣으면 될듯 
		}
		else
		{
			GetAnimator()->Play(L"DASH_RIGHT", false);
			//CreateDashEffect();
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				m_eCurState = PLAYER_STATE::IDLE;
				GetAnimator()->SetAnimationFrame(L"DASH_RIGHT", 0);
			}

		}
	}
	break;

	case PLAYER_STATE::SLASH:
	{
		if (m_iDir == -1)
		{
			
			GetAnimator()->Play(L"SLASH_LEFT", false);
			if(GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SLASH_LEFT", 0);
				m_eCurState = PLAYER_STATE::IDLE;

			}
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			//if (GetAnimator()->GetAnimation()->GetCurrentFrm() != 8)
			//{
			//	GetAnimator()->Play(L"SLASH_LEFT", true);

			//	//GetAnimator()->Play(L"SLASH_LEFT_EFFECT", true);
			//	
			//}

			/*else
			{
				m_eCurState = PLAYER_STATE::IDLE;
			}*/
		}
		else
		{

			GetAnimator()->Play(L"SLASH_RIGHT", false);
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				GetAnimator()->SetAnimationFrame(L"SLASH_RIGHT", 0);
				m_eCurState = PLAYER_STATE::IDLE;

			}
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			/*if (GetAnimator()->GetAnimation()->GetCurrentFrm() != 8)
			{
				GetAnimator()->Play(L"SLASH_RIGHT", true);

			}*/

			/*else
			{
				m_eCurState = PLAYER_STATE::IDLE;
			}*/
			
		}
	
	}
		break;


	case PLAYER_STATE::UPSLASH:
	{
		/*if (m_iDir == -1)
		{*/
		GetAnimator()->Play(L"UP_SLASH", false);
		if (GetAnimator()->GetAnimation()->IsFinish())
		{
			GetAnimator()->SetAnimationFrame(L"UP_SLASH", 0);
			m_eCurState = PLAYER_STATE::IDLE;

		}
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			//if (GetAnimator()->GetAnimation()->GetCurrentFrm() != 4)
			//{
			//	GetAnimator()->Play(L"UP_SLASH", true);

			//	//GetAnimator()->Play(L"SLASH_LEFT_EFFECT", true);

			//}

			//else
			//{
			//	m_eCurState = PLAYER_STATE::IDLE;
			//}
		//}
		//else
		//{
		//	// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
		//	if (GetAnimator()->GetAnimation()->GetCurrentFrm() != 4)
		//	{
		//		GetAnimator()->Play(L"UP_SLASH", true);

		//	}

		//	else
		//	{
		//		m_eCurState = PLAYER_STATE::IDLE;
		//	}

		//}

	}
	break;

	case PLAYER_STATE::DOWN_SLASH:
	{
		if (GetAnimator()->GetAnimation()->GetCurrentFrm() != 9)
		{
			GetAnimator()->Play(L"DOWN_SLASH", true);

			//GetAnimator()->Play(L"SLASH_LEFT_EFFECT", true);
		}

		else
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}

	}
	break;
	case PLAYER_STATE::FOCUS:
	{
		if (m_iDir == -1)
		{
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			GetAnimator()->Play(L"FOCUS_LEFT", false);

			if(GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
			{
				
				m_eCurState = PLAYER_STATE::IDLE;
				GetAnimator()->GetAnimation()->SetFrame(0);
				GetAnimator()->SetRepeat(true);
			}
				
		}
		else
		{
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			GetAnimator()->Play(L"FOCUS_RIGHT", false);

			if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
			{
				m_eCurState = PLAYER_STATE::IDLE;
				GetAnimator()->GetAnimation()->SetFrame(0);
				GetAnimator()->SetRepeat(true);
			}

		}

	}
			break;

	case PLAYER_STATE::STUN:
	{
		if (m_iDir == -1)
		{
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			GetAnimator()->Play(L"STUN_RIGHT", false);

			if (GetAnimator()->GetAnimation()->IsFinish())
			{

				m_eCurState = PLAYER_STATE::IDLE;
				GetAnimator()->GetAnimation()->SetFrame(0);
				GetAnimator()->SetRepeat(true);
			}

		}
		else
		{
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			GetAnimator()->Play(L"STUN_LEFT", false);

			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				m_eCurState = PLAYER_STATE::IDLE;
				GetAnimator()->GetAnimation()->SetFrame(0);
				GetAnimator()->SetRepeat(true);
			}

		}

	}
	break;

	case PLAYER_STATE::FALL:
	{
		if (m_iDir == -1)
		{
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			GetAnimator()->Play(L"FALL_LEFT", false);
			if(GetAnimator()->GetAnimation()->IsFinish())
			{
				if (!m_bFallLeftAnimationSet)
				{
					GetAnimator()->SetAnimationFrame(L"FALL_LEFT", 3);
					m_bFallLeftAnimationSet = true;
				}

				else
				{
					m_bFallLeftAnimationSet = false;
				}
			}

			
			

		}
		else
		{
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			GetAnimator()->Play(L"FALL_RIGHT", false);
			if (GetAnimator()->GetAnimation()->IsFinish())
			{
				if (!m_bFallRightAnimationSet)
				{
					GetAnimator()->SetAnimationFrame(L"FALL_RIGHT", 3);
					m_bFallRightAnimationSet = true;
				}

				else
				{
					m_bFallRightAnimationSet = false;
				}
			}

			

		}

	}
	break;

	case PLAYER_STATE::FIREBALL:
	{
		if (m_iDir == -1)
		{
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			GetAnimator()->Play(L"FIREBALL_LEFT", false);

			if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
			{

				m_eCurState = PLAYER_STATE::IDLE;
				GetAnimator()->GetAnimation()->SetFrame(0);
				GetAnimator()->SetRepeat(true);
			}

		}
		else
		{
			// 캐릭터의 모션이 특정 프레임에 갔을 때의 조건 
			GetAnimator()->Play(L"FIREBALL_RIGHT", false);

			if (GetAnimator()->GetAnimation()->GetCurrentFrm() == 5)
			{
				m_eCurState = PLAYER_STATE::IDLE;
				GetAnimator()->GetAnimation()->SetFrame(0);
				GetAnimator()->SetRepeat(true);
			}

		}

	}
	break;
	
	
	}
}

void CPlayer::update_sound()
{
	// 사운드 부분 

	
	CSound* pPlayerWalkSound = CResMgr::GenInst()->FindSound(L"Player_Walk");
	CSound* pPlayerJumpSound = CResMgr::GenInst()->FindSound(L"Player_Jump");
	CSound* pPlayerDoubleJumpSound = CResMgr::GenInst()->FindSound(L"Player_Double_Jump");
	CSound* pPlayerDashSound = CResMgr::GenInst()->FindSound(L"Player_Dash");
	CSound* pPlayerSlashSound1 = CResMgr::GenInst()->FindSound(L"Player_Slash1");
	CSound* pPlayerSlashSound2 = CResMgr::GenInst()->FindSound(L"Player_Slash2");
	CSound* pPlayerSlashSound3 = CResMgr::GenInst()->FindSound(L"Player_Slash3");
	CSound* pPlayerSlashSound4 = CResMgr::GenInst()->FindSound(L"Player_Slash4");
	CSound* pPlayerSlashSound5 = CResMgr::GenInst()->FindSound(L"Player_Slash5");

	CSound* pPlayerFocusSound = CResMgr::GenInst()->FindSound(L"Player_focus_Success");
	CSound* pPlayerFireBallCastSound = CResMgr::GenInst()->FindSound(L"Player_Fireballcast");
	CSound* pPlayerDamagedSound = CResMgr::GenInst()->FindSound(L"Player_Knight_damaged");
	


	//pPlayerWalkSound->Play(false);
	//pNewSound -> SetPosition(50.f); // 백분률로 소리위치설정

	//pNewSound->PlayToBGM(true);
	pPlayerWalkSound->SetVolume(55.f);
	pPlayerJumpSound->SetVolume(55.f);
	pPlayerSlashSound1->SetVolume(55.f);


	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
		//pPlayerWalkSound->Stop();
		if (m_eCurState != m_ePreState)
		{
			pPlayerWalkSound->Stop(true);
			pPlayerJumpSound->Stop(true);
			pPlayerDoubleJumpSound->Stop(true);
			pPlayerDashSound->Stop(true);
		}
		break;
	case PLAYER_STATE::WALK:
		if (m_eCurState != m_ePreState)
		{
			pPlayerWalkSound->Play(true);
		}
		break;

	case PLAYER_STATE::FALL:
		if (m_eCurState != m_ePreState)
		{
			pPlayerWalkSound->Stop(true);
		}
		break;
		break;
	case PLAYER_STATE::SLASH:
		if (m_eCurState != m_ePreState)
		{
			switch (m_i_SlashCount)
			{
			case 0:
				pPlayerSlashSound1->Play(false);
				pPlayerWalkSound->Stop();
				pPlayerJumpSound->Stop();
				m_i_SlashCount++;
				break;
			case 1:
				pPlayerSlashSound2->Play(false);
				pPlayerWalkSound->Stop();
				pPlayerJumpSound->Stop();
				m_i_SlashCount++;
				break;
			case 2:
				pPlayerSlashSound3->Play(false);
				pPlayerWalkSound->Stop();
				pPlayerJumpSound->Stop();
				m_i_SlashCount++;
				break;
			case 3:
				pPlayerSlashSound4->Play(false);
				pPlayerWalkSound->Stop();
				pPlayerJumpSound->Stop();
				m_i_SlashCount = 0;
				break;
			/*case 4:
				pPlayerSlashSound5->Play(false);
				pPlayerWalkSound->Stop();
				pPlayerJumpSound->Stop();
				m_i_SlashCount = 0;
				break;*/
			}
		}
		break;
	case PLAYER_STATE::UPSLASH:
		if (m_eCurState != m_ePreState)
		{
			pPlayerSlashSound2->Play(false);
			pPlayerWalkSound->Stop();
			pPlayerJumpSound->Stop();
		}

		break;
	case PLAYER_STATE::ATTACK:
		break;
	case PLAYER_STATE::JUMP:
		if (m_eCurState != m_ePreState)
		{
			pPlayerJumpSound->Play(false);
			pPlayerWalkSound->Stop();
		}
		break;
	case PLAYER_STATE::DOUBLE_JUMP:
		if (m_eCurState != m_ePreState)
		{
			pPlayerDoubleJumpSound->Play(false);
			CreateWingEffect();
			pPlayerWalkSound->Stop();
		}
		break;
	case PLAYER_STATE::DASH:
		if (m_eCurState != m_ePreState)
		{
			CreateNewDashEffect();
			pPlayerDashSound->Play(false);
			pPlayerWalkSound->Stop();
		}
		break;
	case PLAYER_STATE::FOCUS:
		if (m_eCurState != m_ePreState)
		{
			pPlayerFocusSound->Play(false);
			pPlayerWalkSound->Stop();
		}
		break;
	case PLAYER_STATE::FIREBALL:
		if (m_eCurState != m_ePreState)
		{
			pPlayerFireBallCastSound->Play(false);
			pPlayerWalkSound->Stop();
		}
		
		break;
	case PLAYER_STATE::STUN:
		if (m_eCurState != m_ePreState)
		{
			CreateStunEffect();
			pPlayerDamagedSound->Play(false);
			pPlayerWalkSound->Stop();
		}

		break;

	case PLAYER_STATE::DOWN_SLASH:
		if (m_eCurState != m_ePreState)
		{
			pPlayerSlashSound4->Play(false);
		}

		break;
	case PLAYER_STATE::DEAD:
		break;
	default:
		break;
	}
}



void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CSound* pPlayerJumpLand = CResMgr::GenInst()->FindSound(L"Player_Jump_Land");

	const vector<CObject*>& groupObjects = CSceneMgr::GenInst()->GetCurScene()->GetGroupObject(GROUP_TYPE::UI);
	vector<CObject*>::const_iterator iter = groupObjects.begin();


	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == _pOther->GetObj()->GetName())
	{
		//점프 사운드 
		pPlayerJumpLand->Play(false);

		m_bGround = true;

		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
			m_i_JumpCount = 0;
			GetAnimator()->SetAnimationFrame(L"JUMP_RIGHT", 0);
			GetAnimator()->SetAnimationFrame(L"JUMP_LEFT", 0);
			GetAnimator()->SetAnimationFrame(L"DOUBLE_JUMP_RIGHT", 0);
			GetAnimator()->SetAnimationFrame(L"DOUBLE_JUMP_LEFT", 0);
		}
	}
	
	if ((L"Beetle" == _pOther->GetObj()->GetName()
		|| L"FalseKnight" == _pOther->GetObj()->GetName()
		|| L"Stone" == _pOther->GetObj()->GetName()
		|| L"Attack_Wave" == _pOther->GetObj()->GetName()
		|| L"Jump_Attack_Wave_Left" == _pOther->GetObj()->GetName()
		|| L"Jump_Attack_Wave_Right" == _pOther->GetObj()->GetName()
		|| L"Hornet" == _pOther->GetObj()->GetName()
		|| L"HORNET_TRHOW_NEEDLE" == _pOther->GetObj()->GetName()
		|| L"SPHERE_BALL_EFFECT" == _pOther->GetObj()->GetName()
		|| L"Fly_Bug" == _pOther->GetObj()->GetName()
		|| L"Crawl" == _pOther->GetObj()->GetName()
		|| L"Dash_Bug" == _pOther->GetObj()->GetName()
		|| L"Pure_Vessel" == _pOther->GetObj()->GetName()
		|| L"SPEAR" == _pOther->GetObj()->GetName()
		|| L"Spike_Effect" == _pOther->GetObj()->GetName()
		|| L"MushRoom" == _pOther->GetObj()->GetName())
		&& m_eCurState != PLAYER_STATE::DASH)

	{

		if (dwtime + 1000 < GetTickCount64())
		{
			if (CPlayerMgr::GenInst()->GetPlayerHp() > 0)
			{
				for (; iter != groupObjects.end(); iter++)
				{

					if ((*iter)->GetName() == L"HpBarUI" + to_wstring(CPlayerMgr::GenInst()->GetPlayerHp()))
					{
						//여기다가 해골 부셔지는 애니메이션 넣으면 될듯
						(*iter)->GetAnimator()->Play(L"Hp_break", false);
						CPlayerMgr::GenInst()->DecreaseHp(1);
						
						m_eHpState = PLAYER_HP_STATE::HP_STATE_DOWN;
					}


				}
				//CPlayerMgr::GenInst()->DecreaseHp(1);
			}

			m_eCurState = PLAYER_STATE::STUN;
			CreateDamagedEffect();
			dwtime = GetTickCount64();

		}
		

		//const vector<CObject*>& groupObjects = CSceneMgr::GenInst()->GetCurScene()->GetGroupObject(GROUP_TYPE::UI);

		//vector<CObject*>::const_iterator iter = groupObjects.begin();
		
		//for(; iter!=groupObjects.end(); iter++)
		//{
		//	
		//	if((*iter)->GetName() == L"HpBarUI" + to_wstring(CPlayerMgr::GenInst()->GetPlayerHp()))
		//	{
		//		//여기다가 해골 부셔지는 애니메이션 넣으면 될듯
		//		(*iter)->GetAnimator()->Play(L"Hp_break", false);
		//		//CPlayerMgr::GenInst()->DecreaseHp(1);
		//		m_eHpState = PLAYER_HP_STATE::HP_STATE_DOWN;
		//	}

		//	
		//}

		
	}

	//if (L"FalseKnight" == _pOther->GetObj()->GetName())
	//{

	//	if (dwtime + 4000 < GetTickCount64())
	//	{
	//		if (CPlayerMgr::GenInst()->GetPlayerHp() > 0)
	//		{
	//			CPlayerMgr::GenInst()->DecreaseHp(1);
	//		}

	//		m_eCurState = PLAYER_STATE::STUN;
	//		CreateDamagedEffect();
	//		dwtime = GetTickCount64();

	//	}


	//	const vector<CObject*>& groupObjects = CSceneMgr::GenInst()->GetCurScene()->GetGroupObject(GROUP_TYPE::UI);

	//	vector<CObject*>::const_iterator iter = groupObjects.begin();

	//	for (; iter != groupObjects.end(); iter++)
	//	{

	//		if ((*iter)->GetName() == L"HpBarUI" + to_wstring(CPlayerMgr::GenInst()->GetPlayerHp()))
	//		{
	//			//여기다가 해골 부셔지는 애니메이션 넣으면 될듯
	//			(*iter)->GetAnimator()->Play(L"Hp_break", false);
	//			CPlayerMgr::GenInst()->DecreaseHp(1);
	//			m_eHpState = PLAYER_HP_STATE::HP_STATE_DOWN;
	//		}


	//	}


}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == _pOther->GetObj()->GetName())
	{
		m_bGround = false; 
	}
}



void CPlayer::CreateSlash()
{
	CSLASH* pSlashEffect = new CSLASH;
	
	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 
	pSlashEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pSlashEffect->SetPos(GetPos() - Vec2(50.f,15.f)); // 플레이어의 좌표 받아옴
	}

	else if(m_iDir ==1)
	{
		pSlashEffect->SetPos(GetPos() + Vec2(150.f, -15.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pSlashEffect->SetName(L"SLASH");

	CreateObject(pSlashEffect, GROUP_TYPE::SKILLEFFECT);

}

void CPlayer::CreateFocusEffect()
{
	CFocus* pFocusEffect = new CFocus;
	
	pFocusEffect->SetPos(GetPos()-Vec2(0.f,30.f)); // 플레이어의 좌표 받아옴

	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pFocusEffect->SetName(L"FOCUS");

	CreateObject(pFocusEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPlayer::CreateFireBallEffect()
{
	CFireBall* pFireballeffect = new CFireBall;

	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 
	pFireballeffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pFireballeffect->SetPos(GetPos() - Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pFireballeffect->SetPos(GetPos() + Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pFireballeffect->SetName(L"FireBall_Effect");

	CreateObject(pFireballeffect, GROUP_TYPE::SKILLEFFECT);

}

void CPlayer::CreateFireBall()
{
	CProFireBall* pFireball = new CProFireBall;

	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 
	pFireball->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pFireball->SetPos(GetPos() - Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pFireball->SetPos(GetPos() + Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pFireball->SetName(L"FireBall");

	CreateObject(pFireball, GROUP_TYPE::SKILLEFFECT);
}

void CPlayer::CreateDashEffect()
{

	CDashEffect* pDashEffect = new CDashEffect;

	pDashEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pDashEffect->SetPos(GetPos() + Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pDashEffect->SetPos(GetPos() - Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pDashEffect->SetName(L"DASH_EFFECT");

	CreateObject(pDashEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPlayer::CreateNewDashEffect()
{
	CNewDashEffect* pNewDashEffect = new CNewDashEffect;

	pNewDashEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pNewDashEffect->SetPos(GetPos() + Vec2(80.f, 0.f)); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pNewDashEffect->SetPos(GetPos() - Vec2(80.f, 0.f));
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pNewDashEffect->SetName(L"DASH_EFFECT");

	CreateObject(pNewDashEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPlayer::CreateUpSlashEffect()
{
	CUPSLASH* pUpSlashEffect = new CUPSLASH;

	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 
	
	pUpSlashEffect->SetPos(GetPos() - Vec2(0.f, 100.f)); // 플레이어의 좌표 받아옴
	

	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pUpSlashEffect->SetName(L"UP_SLASH_Effect");

	CreateObject(pUpSlashEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPlayer::CreateDownSlashEffect()
{
	CDownSlash* pDownSlashEffect = new CDownSlash;

	//여기서 오프셋 부분 건들면 될듯 방향에 따라서 
	//그리고 slash의 h 파일에 Dir 맴버 변수 추가해서 넣으면 
	//방향값 까지 받아올듯함 

	pDownSlashEffect->SetPos(GetPos() + Vec2(0.f, 100.f)); // 플레이어의 좌표 받아옴


	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pDownSlashEffect->SetName(L"DOWN_SLASH_Effect");

	CreateObject(pDownSlashEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPlayer::CreateDamagedEffect()
{

	CPlayerDamaged* pPlayerDamagedEffect = new CPlayerDamaged;

	pPlayerDamagedEffect->SetPos(GetPos()); // 플레이어의 좌표 받아옴

	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pPlayerDamagedEffect->SetName(L"Damaged_Effect");

	CreateObject(pPlayerDamagedEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPlayer::CreateWingEffect()
{
	CWing* pCWingEffect = new CWing;

	pCWingEffect->SetDir(m_iDir);
	if (m_iDir == -1)
	{
		pCWingEffect->SetPos(GetPos()); // 플레이어의 좌표 받아옴
	}

	else if (m_iDir == 1)
	{
		pCWingEffect->SetPos(GetPos());
	}
	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pCWingEffect->SetName(L"WING_EFFECT");

	CreateObject(pCWingEffect, GROUP_TYPE::SKILLEFFECT);
}

void CPlayer::CreateStunEffect()
{
	CPlayerStunEffect* pPlayerStunEffect = new CPlayerStunEffect;

	pPlayerStunEffect->SetPos(GetPos()); // 플레이어의 좌표 받아옴

	//pSlashEffect->SetScale(GetScale()); // 플레이어의 크기와 같음
	pPlayerStunEffect->SetName(L"PLAYER_STUN_EFFECT");

	CreateObject(pPlayerStunEffect, GROUP_TYPE::SKILLEFFECT);
}

