#include "pch.h"
#include "CLiquidUI.h"

// Hp바 이미지넣기 위해 넣은 헤더 
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CPlayerMgr.h"


CLiquidUI::CLiquidUI()
	:CUI(false)
{
	CreateAnimator(false);
   

	CTexture* m_pSoulLiquidTex = CResMgr::GenInst()->LoadTexture(L"Soul_Liquid", L"texture\\Soul_Fill.bmp");

	GetAnimator()->CreateAnimation(L"Soul_Glow", m_pSoulLiquidTex, Vec2(0.f, 0.f), Vec2(130.f, 125.f), Vec2(130.f, 0.f), 0.1f, 8);
	GetAnimator()->Play(L"Soul_Glow", true);
   
    m_iLiquid_amount = CPlayerMgr::GenInst()->GetPlayerMp();
}

CLiquidUI::~CLiquidUI()
{
}

void CLiquidUI::update()
{
    switch (CPlayerMgr::GenInst()->GetPlayerMp())
    {
    case 0:
        m_iLiquid_amount = -120;
        break;
    case 1:
        m_iLiquid_amount = -100;
        break;
    case 2:
        m_iLiquid_amount = -80;
        break;
    case 3:
        m_iLiquid_amount = -60;
        break;
    case 4:
        m_iLiquid_amount = -40;
        break;
    case 5:
        m_iLiquid_amount = -20;
        break;
    case 6:
        m_iLiquid_amount = 0;
        break;
    }

 
}

void CLiquidUI::render(HDC _dc)
{
   
    

        HDC memDC = CreateCompatibleDC(_dc);
        HBITMAP memBitmap = CreateCompatibleBitmap(_dc, 130, 125);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

        // 메모리 DC를 흰색으로 채우기
        RECT rect = { 0, 0, 130, 125 };
        //RECT rect = { 0, 0, 130, 225 };
        HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
        FillRect(memDC, &rect, hBrush);

        // 애니메이션을 메모리 DC에 렌더링
        GetAnimator()->render(memDC);

        //// 원형 클리핑 영역 설정
        //HRGN hRgn = CreateEllipticRgn(40, 40, 161, 161);
        HRGN hRgn = CreateEllipticRgn(44, 46, 156, 156);
        SelectClipRgn(_dc, hRgn);

        // 메모리 DC의 내용을 실제 DC에 복사
        //BitBlt(_dc, 30, 30, 160, 155, memDC, 0.f, 0.f, SRCCOPY);
        BitBlt(_dc, 30, 30, 160, 165, memDC, 0, m_iLiquid_amount, SRCCOPY);

        //여기서  memDc 뒤에 있는 0 값만 수정해주면 된다. 



        // 리소스 정리
        SelectClipRgn(_dc, NULL);
        DeleteObject(hRgn);
        SelectObject(memDC, oldBitmap);
        DeleteObject(memBitmap);
        DeleteDC(memDC);
    

}


