#include "pch.h"
#include "CElderBugQuest.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPlayerMgr.h"
#include "CSound.h"


CElderBugQuest::CElderBugQuest()
	:CUI(false)
{
	
	m_pTex = CResMgr::GenInst()->LoadTexture(L"Quest_Window", L"texture\\Npc\\QuestWindow.bmp");

	CResMgr::GenInst()->LoadSound(L"ElderBug_talk1", L"sound\\ElderBug\\Elderbug_01.wav");
	CResMgr::GenInst()->LoadSound(L"ElderBug_talk2", L"sound\\ElderBug\\Elderbug_02.wav");
	CResMgr::GenInst()->LoadSound(L"ElderBug_talk3", L"sound\\ElderBug\\Elderbug_03.wav");
	CResMgr::GenInst()->LoadSound(L"ElderBug_talk4", L"sound\\ElderBug\\Elderbug_04.wav");
	CResMgr::GenInst()->LoadSound(L"ElderBug_talk5", L"sound\\ElderBug\\Elderbug_05.wav");
}

CElderBugQuest::~CElderBugQuest()
{
}

void CElderBugQuest::update()
{
}

void CElderBugQuest::render(HDC _dc)
{
	CSound* pElderBugtalk1 = CResMgr::GenInst()->FindSound(L"ElderBug_talk1");
	CSound* pElderBugtalk2 = CResMgr::GenInst()->FindSound(L"ElderBug_talk2");
	CSound* pElderBugtalk3 = CResMgr::GenInst()->FindSound(L"ElderBug_talk3");
	CSound* pElderBugtalk4 = CResMgr::GenInst()->FindSound(L"ElderBug_talk4");
	CSound* pElderBugtalk5 = CResMgr::GenInst()->FindSound(L"ElderBug_talk5");



	HFONT hFont = CreateFont(
		30,                // 글자 높이
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

	if (CPlayerMgr::GenInst()->GetCurPlayerPos().x >= 5456
		&& CPlayerMgr::GenInst()->GetCurPlayerPos().x <= 5546)
	{
		float width = (float)m_pTex->Width();
		float height = (float)m_pTex->Height();
		Vec2 vPos = GetPos();


		if (CPlayerMgr::GenInst()->GetQuestPage() > 0 && CPlayerMgr::GenInst()->GetQuestPage() <5)
		{


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
		
		if ((CPlayerMgr::GenInst()->GetQuestPage() == 0))
		{
			pElderBugtalk1->Play(false);
		}
		
		if ((CPlayerMgr::GenInst()->GetQuestPage() == 1))
		{
			pElderBugtalk2->Play(false);
			wchar_t szBuffer[19] = {};
			swprintf_s(szBuffer, L"자네같은 벌레만을 기다려 왔네..");
			SetTextColor(_dc, RGB(255, 255, 255));
			//SetBkColor(_dc, RGB(0, 0, 0));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 155), (int)((vPos.y - (float)(height / 2)) + 110), szBuffer, 19);
		}

		else if((CPlayerMgr::GenInst()->GetQuestPage() == 2))
		{
			pElderBugtalk3->Play(false);
			wchar_t szBuffer[20] = {};
			wchar_t szBuffer2[16] = {};
			swprintf_s(szBuffer, L"현재 숲속 너머의 호넷이라는 괴물이");
			swprintf_s(szBuffer2, L"우리 벌레들을 억압하고 있네");

			SetTextColor(_dc, RGB(255, 255, 255));
			//SetBkColor(_dc, RGB(0, 0, 0));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 135), (int)((vPos.y - (float)(height / 2)) + 110), szBuffer, 20);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 170), (int)((vPos.y - (float)(height / 2)) + 160), szBuffer2, 16);
		}

		else if ((CPlayerMgr::GenInst()->GetQuestPage() == 3))
		{
			pElderBugtalk4->Play(false);
			wchar_t szBuffer[13] = {};
			swprintf_s(szBuffer, L"호넷의 처리를 부탁하네");
			SetTextColor(_dc, RGB(255, 255, 255));
			//SetBkColor(_dc, RGB(0, 0, 0));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 200), (int)((vPos.y - (float)(height / 2)) + 110), szBuffer, 13);
		}

		else if ((CPlayerMgr::GenInst()->GetQuestPage() == 4))
		{
			//pElderBugtalk5->Play(false);
			wchar_t szBuffer[16] = {};
			wchar_t szBuffer2[20] = {};
			wchar_t szBuffer3[10] = {};
			swprintf_s(szBuffer, L"이 노인의 부탁을 들어주다니");
			swprintf_s(szBuffer2, L"감동이네.. 앞으로의 여정에 필요한");
			swprintf_s(szBuffer3, L"아이템들을 주겠네");
			SetTextColor(_dc, RGB(255, 255, 255));
			//SetBkColor(_dc, RGB(0, 0, 0));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 180), (int)((vPos.y - (float)(height / 2)) + 90), szBuffer, 16);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 145), (int)((vPos.y - (float)(height / 2)) + 130), szBuffer2, 20);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 220), (int)((vPos.y - (float)(height / 2)) + 170), szBuffer3, 10);
		}

		// 2번째 퀘스트 
		if (CPlayerMgr::GenInst()->GetQuestPage2() > 0 && CPlayerMgr::GenInst()->GetQuestPage2() < 5)
		{
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

		if ((CPlayerMgr::GenInst()->GetQuestPage2() == 0))
		{
			pElderBugtalk1->Play(false);
		}
		else if ((CPlayerMgr::GenInst()->GetQuestPage2() == 1))
		{
			pElderBugtalk2->Play(false);
			wchar_t szBuffer[19] = {};
			swprintf_s(szBuffer, L"호넷을 물리치다니 정말 고맙다네.");
			SetTextColor(_dc, RGB(255, 255, 255));
			//SetBkColor(_dc, RGB(0, 0, 0));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 155), (int)((vPos.y - (float)(height / 2)) + 110), szBuffer, 19);
		}

		else if ((CPlayerMgr::GenInst()->GetQuestPage2() == 2))
		{
			pElderBugtalk3->Play(false);
			wchar_t szBuffer[24] = {};
			swprintf_s(szBuffer, L"염치없지만 한번만 더 도와줄 수 있겠나..");
			SetTextColor(_dc, RGB(255, 255, 255));
			//SetBkColor(_dc, RGB(0, 0, 0));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 115), (int)((vPos.y - (float)(height / 2)) + 110), szBuffer, 24);
		}

		else if ((CPlayerMgr::GenInst()->GetQuestPage2() == 3))
		{
			pElderBugtalk4->Play(false);
			wchar_t szBuffer[24] = {};
			wchar_t szBuffer2[16] = {};
			swprintf_s(szBuffer, L"아직 숲속 너머의 순수한 그릇이라는 괴물이");
			swprintf_s(szBuffer2, L"우리 벌레들을 억압하고 있네");

			SetTextColor(_dc, RGB(255, 255, 255));
			//SetBkColor(_dc, RGB(0, 0, 0));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 135), (int)((vPos.y - (float)(height / 2)) + 110), szBuffer, 20);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 170), (int)((vPos.y - (float)(height / 2)) + 160), szBuffer2, 16);
		}

		else if ((CPlayerMgr::GenInst()->GetQuestPage2() == 4))
		{
			pElderBugtalk4->Play(false);
			wchar_t szBuffer[16] = {};
			wchar_t szBuffer2[24] = {};
			swprintf_s(szBuffer, L"부탁을 들어줘서 정말 고맙네");
			swprintf_s(szBuffer2, L"순수한 그릇이 있는 장소로 이동시켜주겠네.");

			SetTextColor(_dc, RGB(255, 255, 255));
			//SetBkColor(_dc, RGB(0, 0, 0));
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 170), (int)((vPos.y - (float)(height / 2)) + 110), szBuffer, 16);
			TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 95), (int)((vPos.y - (float)(height / 2)) + 160), szBuffer2, 24);
		}
	}

	else
	{
		SelectObject(_dc, hOldFont);
		DeleteObject(hFont);
	}

}


