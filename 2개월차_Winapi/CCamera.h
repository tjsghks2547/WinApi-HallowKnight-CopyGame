#pragma once
#include "CTimeMgr.h"

class CObject; 
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	VIBRATION,
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT		 eEffect; // 카메라 효과
	float			 fDuration; // 효과 최대 진행 시간
	float			 fCurTime; // 카메라 효과 현재 진행된 시간 
};


class CCamera
{
	SINGLE(CCamera);

private:
	int					m_iSoundCount;
	int					m_iCount;
	float				m_iTest;
	

	Vec2				m_vLookAt; // 카메라 보는 위치 
	Vec2				m_vCurLookAt; // 이전 위치와 현재위치 보정 위치 
	Vec2				m_vPreLookAt; //카메라가 보는 이전 프레임 위치
	CObject*			m_pTargetObj; // 카메라 타겟 오브젝트
	Vec2				m_vDiff;   // 해상도 중심위치와 , 카메라 LookAt 간의 차이 값

	float				m_fTime;  // 타겟을 따라가는데 걸리는 시간 
	float				m_fSpeed; // 타겟을 따라가는 속도 
	float				m_fAccTime; // 누적 시간
	float				m_fMapYOffset;


	Vec2				m_vOffset;


	//카메라 바운딩 (경계 설정) 
	float				m_fbound_maxX;
	float				m_fbound_minX;


	list<tCamEffect>	m_listCamEffect;
	CTexture*			m_pVeilTex; // 카메라 가림막 텍스쳐 (검은색으로)

public: 

	void MoveMap(float _yOffset) { m_fMapYOffset += _yOffset; }

	void SetLookAt(Vec2 _vLook);
	void SetLookAtX(float _vLook) { m_vLookAt.x -= _vLook; }
	void SetLookAty(float _vLook) { m_vLookAt.y -= _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	void BossRoomControlCamera(float _f) { m_iTest -= _f * fDT; }
	void SetBossRoomControlCamera(float _f) { m_iTest = 1892.f; }

	void SetMaxBoundX(float _f) { m_fbound_maxX = _f; }
	void SetMinBoundX(float _f) { m_fbound_minX = _f; }
	

	void SetOffSet(Vec2 _vLookat) { m_vOffset = _vLookat; }

	CObject* GetTarget() { return m_pTargetObj; }

	
	Vec2 GetLookAt2() { return m_vLookAt; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2  _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void Set_mvLookAt(Vec2 _v) { m_vLookAt = _v; }

	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f; 

		m_listCamEffect.push_back(ef);

		if(0.f == _fDuration)
		{
			assert(nullptr);
		}
	}; // 호출되면 점점 밝아지는 

	void FadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
		{
			assert(nullptr);
		}
	} // 호출되면 점점 어두워지는 

	void virbration(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::VIBRATION;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
		{
			assert(nullptr);
		}
	} // 카메라 위로 

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff();
};

