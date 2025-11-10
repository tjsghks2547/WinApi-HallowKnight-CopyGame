#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "C_Core.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "C_Core.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayerMgr.h"
#include "CSound.h"

CCamera::CCamera()
	:m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
	, m_pVeilTex(nullptr)
	, m_iCount(0)
	, m_fMapYOffset(0.f)
	, m_iTest(1892.f)
	, m_iSoundCount(0)
	, m_vOffset(Vec2(0.f,0.f))

{
	
}

CCamera::~CCamera()
{

}


void CCamera::SetLookAt(Vec2 _vLook)
{
	m_vLookAt = _vLook;
	float fMoveDist = (m_vLookAt - m_vPreLookAt).Length();
	m_fSpeed = (fMoveDist / m_fTime);
	//m_fAccTime = 0.f;
	m_fAccTime = 1.f;
}



void CCamera::init()
{
	Vec2 vResolution = CCore::GenInst()->GetResolution();
	m_pVeilTex = CResMgr::GenInst()->CreateTexture(L"CameraVeil",(UINT)vResolution.x, (UINT)vResolution.y);

}

void CCamera::update()
{
	if (m_pTargetObj)
	{

		if(m_pTargetObj ->IsDead())
		{
			m_pTargetObj = nullptr; 
		}
	
		

		else
		{
			// 7월 9일 
			m_vLookAt = m_pTargetObj->GetPos() + m_vOffset;
		}

	}

	
	/*if (KEY_HOLD(KEY::UP))
	{
		m_iTest -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_iTest += 500.f * fDT;
	}*/
   /*if(KEY_HOLD(KEY::UP))
   {
	   m_vLookAt.y -= 500.f * fDT; 
   }
   if (KEY_HOLD(KEY::DOWN))
   {
	   m_vLookAt.y += 500.f * fDT;
   }
   if (KEY_HOLD(KEY::LEFT))
   {
	   m_vLookAt.x -= 500.f * fDT;
   }
   if (KEY_HOLD(KEY::RIGHT))
   {
	   m_vLookAt.x += 500.f * fDT;
   }*/

	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산 

	if ((8056.f < CPlayerMgr::GenInst()->GetCurPlayerPos().x
		&& 11110.f > CPlayerMgr::GenInst()->GetCurPlayerPos().x)
		&& 2210 > CPlayerMgr::GenInst()->GetCurPlayerPos().y //2210 이였음
		&& CSceneMgr::GenInst()->GetCurScene()->GetName() == L"Start Scene")
	{
		
		
		if(m_pTargetObj !=nullptr)
		{
			Vec2 TargetPos = Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x, m_iTest);
			m_vLookAt = TargetPos;
			CalDiff();
		}

		m_iSoundCount++;
		if(m_iSoundCount ==1)
		{
			CResMgr::GenInst()->LoadSound(L"BossRoom_BGM",L"sound\\Boss Battle 1.wav");
			CSound* pBossRoomSound = CResMgr::GenInst()->FindSound(L"BossRoom_BGM");
			//CSound* pStage1BGM = CResMgr::GenInst()->FindSound()
			//pNewSound -> Play();
			//pNewSound -> SetPosition(50.f); // 백분률로 소리위치설정
			
			
			pBossRoomSound -> PlayToBGM(true);
			pBossRoomSound-> SetVolume(95.f);
		}
		//CalDiff();
		//else
		//{
		//	//Vec2 TargetPos = Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x, GetLookAt().y);
		//	//m_vLookAt = TargetPos
		//	m_vLookAt = Vec2(CPlayerMgr::GenInst()->GetCurPlayerPos().x, GetLookAt2().y);
		//	CalDiff();
		//}
	}

	else
	{
		
		CalDiff();
	}
	
   
}


void CCamera::CalDiff()
{
	// 이전 LookAt 과 현재 Look 의 차이값을 보정해서 현재의 LookAt을 구한다.

	m_fAccTime += fDT; // 시간 누적 
	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}

	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPreLookAt; // 방향벡터 구하는거와 같음.

		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPreLookAt + vLookDir.Normalize() * m_fSpeed * fDT; // 단위벡터화 하고 속도곱함	
		}
	}

	Vec2 vResolution = CCore::GenInst()->GetResolution();
	Vec2 vCenter = vResolution/2;



	// 현재 보고있는것과의 차이 계산 
	m_vDiff = m_vCurLookAt - vCenter;

	
	m_vPreLookAt = m_vCurLookAt;

	// 현재 카메라 위치 제한
	
	//if (m_vCurLookAt.x > m_fbound_maxX) m_vCurLookAt.x = maxX;
	//if (m_vCurLookAt.y < minY) m_vCurLookAt.y = minY;
	//if (m_vCurLookAt.y > maxY) m_vCurLookAt.y = maxY;




}




void CCamera::render(HDC _dc)
{
	if(m_listCamEffect.empty())
	{
		return;
	}

	// 시간 누적값을 체크 
	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDT;

	
	float fRatio = 0.f; // 이펙트 진행 비율 
	fRatio = effect.fCurTime / effect.fDuration;

	if(fRatio < 0.f)
	{
		fRatio = 0.f;
	}

	if(fRatio > 1.f)
	{
		fRatio = 1.f;
	}

	int iAlpha = 0;

	if(CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		iAlpha = (int)(255.f * fRatio);
	}

	else if(CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		iAlpha = (int)(255.f *(1.F - fRatio));
	}

	else if(CAM_EFFECT::VIBRATION ==effect.eEffect)
	{
		
	}


	//// 알파블랜딩 예시 

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha; // 전역적으로 적용되는 알파값  (투명도)

	AlphaBlend(_dc
		, 0
		, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDc()
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, bf);

	// 진행 시간이 이펙트 최대 지정 시간을 넘어선 경우 
	if (effect.fDuration < effect.fCurTime)
	{
		// 효과 종료 
		m_listCamEffect.pop_front();
	}

}

