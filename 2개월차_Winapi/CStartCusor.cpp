#include "pch.h"
#include "CStartCusor.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "C_Core.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"
#include "CSound.h"


CStartCusor::CStartCusor()
	:m_pCusorTex(nullptr)
	,m_iCount(0)
	,m_bSoundPlay(false)
{
	m_pCusorTex = CResMgr::GenInst()->LoadTexture(L"Cusor", L"texture\\UI\\start_cursor.bmp");
	CResMgr::GenInst()->LoadSound(L"ui_option_click", L"sound\\ui_option_click.wav");
	
}

CStartCusor::~CStartCusor()
{
}


void CStartCusor::update()
{
	CSound* pUiClickSound = CResMgr::GenInst()->FindSound(L"ui_option_click");
	pUiClickSound->SetVolume(100.f);

	if(KEY_TAP(KEY::DOWN))
	{
		m_iCount++;
		m_bSoundPlay = false;

		switch (m_iCount)
		{
		case 1:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(715.f, 450.f));
			break;

		case 2:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(690.f, 497.5f));
			break;

		case 3:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(690.f, 540.f));
			break;

		case 4:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(705.f, 587.5f));
			break;
		case 5:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(715.f, 633.5f));
			break;
		default:
			break;
		}
		
	}


	if (KEY_TAP(KEY::UP))
	{
		m_iCount--;
		m_bSoundPlay = false;

		switch (m_iCount)
		{
		case 1:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(715.f, 450.f));
			break;

		case 2:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(690.f, 497.5f));
			break;

		case 3:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(690.f, 540.f));
			break;

		case 4:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(705.f, 587.5f));
			break;
		case 5:
			if (m_bSoundPlay == false)
			{

				pUiClickSound->Play(false);
				m_bSoundPlay = true;
			}
			SetPos(Vec2(715.f, 633.5f));
			break;
		default:
			break;
		}

	}

	if(m_iCount ==1)
	{
		if(KEY_TAP(KEY::ENTER))
		{
			ChangeScene(SCENE_TYPE::START);
		}
	}

}

void CStartCusor::render(HDC _dc)
{

	Vec2 vPos = GetPos();
	
	float width =  (float)m_pCusorTex->Width();
	float height = (float)m_pCusorTex->Height();
	
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255; // 전역적으로 적용되는 알파값  (투명도) 
	
	AlphaBlend(_dc
		, (int)(vPos.x - width / 2.f)
		, (int)(vPos.y - height / 2.f)
		, (int)(width)
		, (int)(height)
		, m_pCusorTex->GetDc()
		, 0
		, 0
		, (int)width
		, (int)height
		, bf);
}

