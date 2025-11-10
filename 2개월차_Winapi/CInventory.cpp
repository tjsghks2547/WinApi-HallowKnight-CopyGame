#include "pch.h"
#include "CInventory.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"
#include "CSound.h"


CInventory::CInventory()
	:CUI(false)
	,m_iCount(0)
	,m_iItemNumber(0)
{
	m_pTex = CResMgr::GenInst()->LoadTexture(L"inventory", L"texture\\UI\\inventory_made2.bmp");
	CResMgr::GenInst()->LoadSound(L"ui_option_click2", L"sound\\ui_option_click.wav");
	CResMgr::GenInst()->LoadSound(L"ui_option_enter", L"sound\\ui_button_confirm.wav");
}

CInventory::~CInventory()
{

}


void CInventory::update()
{

	CSound* pUiClickSound2 = CResMgr::GenInst()->FindSound(L"ui_option_click2");
	CSound* pUiEnterSound = CResMgr::GenInst()->FindSound(L"ui_option_enter");
	pUiClickSound2->SetVolume(100.f);
	pUiEnterSound->SetVolume(100.f);
	if (CPlayerMgr::GenInst()->GetInventoryStatus())
	{
		if (KEY_TAP(KEY::F))
		{
			//m_iItemNumber++;
			pUiClickSound2->Play(false);
			CPlayerMgr::GenInst()->IncreaseItemCusor();
			
		}

		else if(KEY_TAP(KEY::G))
		{
			//m_iItemNumber--;
			pUiClickSound2->Play(false);
			CPlayerMgr::GenInst()->DecreaseItemCusor();
			
		}


		else if(KEY_TAP(KEY::ENTER))
		{
			switch (CPlayerMgr::GenInst()->GetItemCusor())
			{

			case -1:
				pUiEnterSound->Play(false);
				CPlayerMgr::GenInst()->GetItemList().push_back(CPlayerMgr::GenInst()->GetEquipList().at(1));
				CPlayerMgr::GenInst()->GetEquipList().erase(CPlayerMgr::GenInst()->GetEquipList().begin()+1);
				break;

			case 0:
				pUiEnterSound->Play(false);
				CPlayerMgr::GenInst()->GetItemList().push_back(CPlayerMgr::GenInst()->GetEquipList().at(0));
				CPlayerMgr::GenInst()->GetEquipList().erase(CPlayerMgr::GenInst()->GetEquipList().begin());

				break;

			case 1:
				pUiEnterSound->Play(false);
				CPlayerMgr::GenInst()->GetEquipList().push_back(CPlayerMgr::GenInst()->GetItemList().at(0));
				CPlayerMgr::GenInst()->GetItemList().erase(CPlayerMgr::GenInst()->GetItemList().begin());

				break;
			case 2:
				pUiEnterSound->Play(false);
				CPlayerMgr::GenInst()->GetEquipList().push_back(CPlayerMgr::GenInst()->GetItemList().at(1));
				CPlayerMgr::GenInst()->GetItemList().erase(CPlayerMgr::GenInst()->GetItemList().begin()+1);

				break;
			case 3:
				CPlayerMgr::GenInst()->GetEquipList().push_back(CPlayerMgr::GenInst()->GetItemList().at(0));
				CPlayerMgr::GenInst()->GetItemList().erase(CPlayerMgr::GenInst()->GetItemList().begin());

				break;
			case 4:
				CPlayerMgr::GenInst()->GetEquipList().push_back(CPlayerMgr::GenInst()->GetItemList().at(0));
				CPlayerMgr::GenInst()->GetItemList().erase(CPlayerMgr::GenInst()->GetItemList().begin());
				break;

			}
		}
	}
}

void CInventory::render(HDC _dc)
{


	if (CPlayerMgr::GenInst()->GetInventoryStatus())
	{
		Vec2 vPos = GetPos();

		float width = (float)m_pTex->Width();
		float height = (float)m_pTex->Height();

		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = 200; // 전역적으로 적용되는 알파값  (투명도) 

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

		// 아이템 정렬 
		if(CPlayerMgr::GenInst()->GetItemList().size()>0)
		{
			m_iCount = 0;
			for (auto iter = CPlayerMgr::GenInst()->GetItemList().begin(); iter != CPlayerMgr::GenInst()->GetItemList().end(); ++iter) 
			{
				(*iter)->SetPos(Vec2(220.f + 120.f * m_iCount, 410.f));
				m_iCount++;
			}
		}

		//장비창 정렬 

		if (CPlayerMgr::GenInst()->GetEquipList().size() > 0)
		{
			m_iCount = 0;
			for (auto iter = CPlayerMgr::GenInst()->GetEquipList().begin(); iter != CPlayerMgr::GenInst()->GetEquipList().end(); ++iter)
			{
				(*iter)->SetPos(Vec2(150.f + 150*m_iCount, 250.f));
				m_iCount++;
			}
		}

		
		if(CPlayerMgr::GenInst()->GetItemCusor()==1 && CPlayerMgr::GenInst()->GetItemList().size()>0)
		{
			auto iter = CPlayerMgr::GenInst()->GetItemList().begin();
			
				if((*iter)->GetName() == L"Clock_item1")
				{
					
					wchar_t szBuffer1[255] = {};
					swprintf_s(szBuffer1, L"심연의 물질로 만들어진 망토");
					int len1 = swprintf_s(szBuffer1, L"심연의 물질로 만들어진 망토");
					SetTextColor(_dc, RGB(255, 255, 255));
					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) +400), szBuffer1, len1);

					wchar_t szBuffer2[255] = {};
					swprintf_s(szBuffer2, L"착용자가 피해를 입지 않고 적과 적의");
					int len2 = swprintf_s(szBuffer2, L"착용자가 피해를 입지 않고 적과");
					SetTextColor(_dc, RGB(255, 255, 255));
					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 450), szBuffer2, len2);

					wchar_t szBuffer3[255] = {};
					swprintf_s(szBuffer3, L"적의 공격을 관통해 대시할 수 있게");
					int len3 = swprintf_s(szBuffer2, L"적의 공격을 관통해 대시할 수 있게");
					SetTextColor(_dc, RGB(255, 255, 255));
					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 500), szBuffer3, len3);

					wchar_t szBuffer4[255] = {};
					swprintf_s(szBuffer4, L"합니다");
					int len4 = swprintf_s(szBuffer2, L"합니다");
					SetTextColor(_dc, RGB(255, 255, 255));
					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 550), szBuffer4, len4);


					//이미지 출력
					CTexture* m_pClockTex = CResMgr::GenInst()->LoadTexture(L"clock_item", L"texture\\UI\\cloak2.bmp");
					Vec2 vTextPos = Vec2(1000.f, 250.f);
					int iWidth = (int)m_pClockTex->Width();
					int iHeight = (int)m_pClockTex->Height();
					TransparentBlt(_dc
						, (int)((vTextPos.x - (float)(iWidth / 2)))
						, (int)((vTextPos.y - (float)(iHeight / 2)))
						, iWidth
						, iHeight
						, m_pClockTex->GetDc()
						, 0, 0, iWidth, iHeight, RGB(0, 0, 0));

				
				}

				else if((*iter)->GetName() == L"Wing_item1")
				{
					wchar_t szBuffer1[255] = {};
					swprintf_s(szBuffer1, L"어둠 속에서 반짝이는 천상의");
					int len1 = swprintf_s(szBuffer1, L"어둠 속에서 반짝이는 천상의");
					SetTextColor(_dc, RGB(255, 255, 255));
					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 400), szBuffer1, len1);

					wchar_t szBuffer2[255] = {};
					swprintf_s(szBuffer2, L"물질로 만든 날개.");
					int len2 = swprintf_s(szBuffer2, L"물질로 만든 날개.");
					SetTextColor(_dc, RGB(255, 255, 255));
					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 450), szBuffer2, len2);

					wchar_t szBuffer3[255] = {};
					swprintf_s(szBuffer3, L"공중에서 다시 점프할 수 있게.");
					int len3 = swprintf_s(szBuffer2, L"공중에서 다시 점프할 수 있게.");
					SetTextColor(_dc, RGB(255, 255, 255));
					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 500), szBuffer3, len3);

					wchar_t szBuffer4[255] = {};
					swprintf_s(szBuffer4, L"합니다");
					int len4 = swprintf_s(szBuffer2, L"합니다");
					SetTextColor(_dc, RGB(255, 255, 255));
					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 550), szBuffer4, len4);

					//이미지 출력
					CTexture* m_pWingTex = CResMgr::GenInst()->LoadTexture(L"Wing_item", L"texture\\UI\\wing.bmp");
					Vec2 vTextPos = Vec2(1000.f, 250.f);
					int iWidth  = (int)m_pWingTex->Width();
					int iHeight = (int)m_pWingTex->Height();
					TransparentBlt(_dc
						, (int)((vTextPos.x - (float)(iWidth / 2)))
						, (int)((vTextPos.y - (float)(iHeight / 2)))
						, iWidth
						, iHeight
						, m_pWingTex->GetDc()
						, 0, 0, iWidth, iHeight, RGB(32, 34, 64));
				}
			
		}

		else if (CPlayerMgr::GenInst()->GetItemCusor() == 2 && CPlayerMgr::GenInst()->GetItemList().size() > 1)
		{
			auto iter = CPlayerMgr::GenInst()->GetItemList().begin()+1;

			if ((*iter)->GetName() == L"Clock_item1")
			{

				wchar_t szBuffer1[255] = {};
				swprintf_s(szBuffer1, L"심연의 물질로 만들어진 망토");
				int len1 = swprintf_s(szBuffer1, L"심연의 물질로 만들어진 망토");
				SetTextColor(_dc, RGB(255, 255, 255));
				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 400), szBuffer1, len1);

				wchar_t szBuffer2[255] = {};
				swprintf_s(szBuffer2, L"착용자가 피해를 입지 않고 적과 적의");
				int len2 = swprintf_s(szBuffer2, L"착용자가 피해를 입지 않고 적과");
				SetTextColor(_dc, RGB(255, 255, 255));
				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 450), szBuffer2, len2);

				wchar_t szBuffer3[255] = {};
				swprintf_s(szBuffer3, L"적의 공격을 관통해 대시할 수 있게");
				int len3 = swprintf_s(szBuffer2, L"적의 공격을 관통해 대시할 수 있게");
				SetTextColor(_dc, RGB(255, 255, 255));
				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 500), szBuffer3, len3);

				wchar_t szBuffer4[255] = {};
				swprintf_s(szBuffer4, L"합니다");
				int len4 = swprintf_s(szBuffer2, L"합니다");
				SetTextColor(_dc, RGB(255, 255, 255));
				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 550), szBuffer4, len4);


				//이미지 출력
				CTexture* m_pClockTex = CResMgr::GenInst()->LoadTexture(L"clock_item", L"texture\\UI\\cloak2.bmp");
				Vec2 vTextPos = Vec2(1000.f, 250.f);
				int iWidth = (int)m_pClockTex->Width();
				int iHeight = (int)m_pClockTex->Height();
				TransparentBlt(_dc
					, (int)((vTextPos.x - (float)(iWidth / 2)))
					, (int)((vTextPos.y - (float)(iHeight / 2)))
					, iWidth
					, iHeight
					, m_pClockTex->GetDc()
					, 0, 0, iWidth, iHeight, RGB(0, 0, 0));


			}

			else if ((*iter)->GetName() == L"Wing_item1")
			{
				wchar_t szBuffer1[255] = {};
				swprintf_s(szBuffer1, L"어둠 속에서 반짝이는 천상의");
				int len1 = swprintf_s(szBuffer1, L"어둠 속에서 반짝이는 천상의");
				SetTextColor(_dc, RGB(255, 255, 255));
				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 400), szBuffer1, len1);

				wchar_t szBuffer2[255] = {};
				swprintf_s(szBuffer2, L"물질로 만든 날개.");
				int len2 = swprintf_s(szBuffer2, L"물질로 만든 날개.");
				SetTextColor(_dc, RGB(255, 255, 255));
				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 450), szBuffer2, len2);

				wchar_t szBuffer3[255] = {};
				swprintf_s(szBuffer3, L"공중에서 다시 점프할 수 있게.");
				int len3 = swprintf_s(szBuffer2, L"공중에서 다시 점프할 수 있게.");
				SetTextColor(_dc, RGB(255, 255, 255));
				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 500), szBuffer3, len3);

				wchar_t szBuffer4[255] = {};
				swprintf_s(szBuffer4, L"합니다");
				int len4 = swprintf_s(szBuffer2, L"합니다");
				SetTextColor(_dc, RGB(255, 255, 255));
				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, (int)((vPos.x - (float)(width / 2)) + 820), (int)((vPos.y - (float)(height / 2)) + 550), szBuffer4, len4);

				//이미지 출력
				CTexture* m_pWingTex = CResMgr::GenInst()->LoadTexture(L"Wing_item", L"texture\\UI\\wing.bmp");
				Vec2 vTextPos = Vec2(1000.f, 250.f);
				int iWidth = (int)m_pWingTex->Width();
				int iHeight = (int)m_pWingTex->Height();
				TransparentBlt(_dc
					, (int)((vTextPos.x - (float)(iWidth / 2)))
					, (int)((vTextPos.y - (float)(iHeight / 2)))
					, iWidth
					, iHeight
					, m_pWingTex->GetDc()
					, 0, 0, iWidth, iHeight, RGB(32, 34, 64));
			}

		}

		
	}

}

void CInventory::MouseOn()
{
}

void CInventory::MouseLbtnDown()
{
}

void CInventory::MouseLbtnUp()
{
}



