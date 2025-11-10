#include "pch.h"
#include "CStore.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"
#include "CSound.h"


CStore::CStore()
	:CUI(false)
	,m_iCount(0)
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"Store_Window", L"texture\\UI\\Store_window.bmp");

	CResMgr::GenInst()->LoadSound(L"Brumm_talk", L"sound\\Brumm_talk_01.wav");
	CResMgr::GenInst()->LoadSound(L"Brumm_talk2", L"sound\\Brumm_talk_02.wav");
}

CStore::~CStore()
{

}


void CStore::update()
{
	CSound* Brumm_talk = CResMgr::GenInst()->FindSound(L"Brumm_talk");
	CSound* Brumm_talk2 = CResMgr::GenInst()->FindSound(L"Brumm_talk2");
	Brumm_talk->SetVolume(70.f);
	Brumm_talk2->SetVolume(70.f);

	if(KEY_TAP(KEY::U))
	{
		m_iCount++;
		CPlayerMgr::GenInst()->SetStoreOnOff();

		switch (m_iCount)
		{
		case 1:
			Brumm_talk->Play(false);
			break;

		case 2:
			Brumm_talk2->Play(false);
			m_iCount = 0;
			break;
		}
		
	}


}

void CStore::render(HDC _dc)
{

	if (CPlayerMgr::GenInst()->GetStoreOnOff())
	{

		float width = (float)m_pTex->Width();
		float height = (float)m_pTex->Height();
		Vec2 vPos = GetPos();

		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = 240; // 전역적으로 적용되는 알파값  (투명도) 

		AlphaBlend(_dc
			, (int)(vPos.x - width / 2.f)
			, (int)(vPos.y - height / 2.f)
			, (int)(width)
			, (int)(height)
			, m_pTex->GetDc()
			, 0
			, 0
			, (int)width
			, (int)height
			, bf);
	}
}


