#include "pch.h"
#include "CStoreCusor.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"
#include "CSound.h"


CStoreCusor::CStoreCusor()
	:CUI(false)
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"Store_Window_Cursor", L"texture\\UI\\store_select3.bmp");

	m_pSoulball = CResMgr::GenInst()->LoadTexture(L"Store_Window_SoulBall", L"texture\\UI\\soulball_information_3.bmp");
	m_pFocus    = CResMgr::GenInst()->LoadTexture(L"Store_Window_Focus", L"texture\\UI\\focus_information.bmp");

	CResMgr::GenInst()->LoadSound(L"ui_option_click3", L"sound\\ui_option_click.wav");
	CResMgr::GenInst()->LoadSound(L"item_buy", L"sound\\geo_deplete_count_down.wav");
}

CStoreCusor::~CStoreCusor()
{
}

void CStoreCusor::update()
{
	CSound* pItemBuySound = CResMgr::GenInst()->FindSound(L"item_buy");
	CSound* pUiMoveSound = CResMgr::GenInst()->FindSound(L"ui_option_click3");

	pItemBuySound->SetVolume(90.f);
	pUiMoveSound->SetVolume(80.f);

	if (CPlayerMgr::GenInst()->GetStoreOnOff())
	{

		if (KEY_TAP(KEY::UP))
		{
			pUiMoveSound->Play(false);
			CPlayerMgr::GenInst()->SetStoreCusor(1);
			SetPos(Vec2(525.f, 250.f));
		}

		if (KEY_TAP(KEY::DOWN))
		{
			pUiMoveSound->Play(false);
			CPlayerMgr::GenInst()->SetStoreCusor(2);
			SetPos(Vec2(525.f, 350.f));
		}


		if (KEY_TAP(KEY::ENTER))
		{
			if (CPlayerMgr::GenInst()->GetGeoCount() >= 300)
			{
				pItemBuySound->Play(false);
				CPlayerMgr::GenInst()->DecreaseGeo(300);
			}

		}
	}
}

void CStoreCusor::render(HDC _dc)
{
	HFONT hFont = CreateFont(
		25,                // 글자 높이
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

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255; // 전역적으로 적용되는 알파값  (투명도) 

	

	if (CPlayerMgr::GenInst()->GetStoreOnOff())
	{

		float width = (float)m_pTex->Width();
		float height = (float)m_pTex->Height();
		Vec2 vPos = GetPos();



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



		if (CPlayerMgr::GenInst()->GetStoreCusor() == 1)
		{
			float width = (float)m_pSoulball->Width();
			float height = (float)m_pSoulball->Height();
			Vec2 vPos = Vec2(760.f, 225.f);

			AlphaBlend(_dc
				, (int)(vPos.x - width / 2.f)
				, (int)(vPos.y - height / 2.f)
				, (int)(width)
				, (int)(height)
				, m_pSoulball->GetDc()
				, 0
				, 0
				, (int)width
				, (int)height
				, bf);

			//여기다가 SetText해서 해당 아이템 설명 쓰고
			//아이템 설명위에는 큰 이미지 넣으면 될거같음.
			wchar_t szBuffer1[255] = {};
			swprintf_s(szBuffer1, L"영령을 풀어줍니다.");
			int len1 = swprintf_s(szBuffer1, L"영령을 풀어줍니다.");
			SetTextColor(_dc, RGB(255, 255, 255));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, 670, 325, szBuffer1, len1);

			wchar_t szBuffer2[255] = {};
			swprintf_s(szBuffer2, L"주문은 영혼을 고갈");
			int len2 = swprintf_s(szBuffer2, L"주문은 영혼을 고갈");
			SetTextColor(_dc, RGB(255, 255, 255));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, 670, 375, szBuffer2, len2);

			wchar_t szBuffer3[255] = {};
			swprintf_s(szBuffer3, L"시킵니다");
			int len3 = swprintf_s(szBuffer3, L"시킵니다");
			SetTextColor(_dc, RGB(255, 255, 255));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, 670, 425, szBuffer3, len3);
		}

		else if (CPlayerMgr::GenInst()->GetStoreCusor() == 2)
		{
			float width = (float)m_pFocus->Width();
			float height = (float)m_pFocus->Height();
			Vec2 vPos = Vec2(760.f, 225.f);

			AlphaBlend(_dc
				, (int)(vPos.x - width / 2.f)
				, (int)(vPos.y - height / 2.f)
				, (int)(width)
				, (int)(height)
				, m_pFocus->GetDc()
				, 0
				, 0
				, (int)width
				, (int)height
				, bf);

			wchar_t szBuffer1[255] = {};
			swprintf_s(szBuffer1, L"적을 공격하여 영혼을");
			int len1 = swprintf_s(szBuffer1, L"적을 공격하여 영혼을");
			SetTextColor(_dc, RGB(255, 255, 255));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, 670, 325, szBuffer1, len1);

			wchar_t szBuffer2[255] = {};
			swprintf_s(szBuffer2, L"모으십시오");
			int len2 = swprintf_s(szBuffer2, L"모으십시오");
			SetTextColor(_dc, RGB(255, 255, 255));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, 670, 375, szBuffer2, len2);

			wchar_t szBuffer3[255] = {};
			swprintf_s(szBuffer3, L"영혼을 집중해 치유");
			int len3 = swprintf_s(szBuffer3, L"영혼을 집중해 치유");
			SetTextColor(_dc, RGB(255, 255, 255));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, 670, 425, szBuffer3, len3);

			wchar_t szBuffer4[255] = {};
			swprintf_s(szBuffer4, L"할 수 있습니다.");
			int len4 = swprintf_s(szBuffer4, L"할 수 있습니다.");
			SetTextColor(_dc, RGB(255, 255, 255));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, 670, 475, szBuffer4, len4);
		}
	}

	
	SelectObject(_dc, hOldFont);
	DeleteObject(hFont);
	
	
}


