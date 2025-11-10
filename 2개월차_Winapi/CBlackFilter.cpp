#include "pch.h"
#include "CBlackFilter.h"



CBlackFilter::CBlackFilter()
	:CUI(false)
{
}

CBlackFilter::~CBlackFilter()
{
}


void CBlackFilter::update()
{
}

void CBlackFilter::render(HDC _dc)
{
	HRGN hRgn = CreateEllipticRgn(44, 46, 156, 156);

	// 검정색으로 채우기
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	FillRgn(_dc, hRgn, hBrush);

	SelectClipRgn(_dc, hRgn);


	// 리소스 정리
	DeleteObject(hRgn);
	DeleteObject(hBrush);
}

