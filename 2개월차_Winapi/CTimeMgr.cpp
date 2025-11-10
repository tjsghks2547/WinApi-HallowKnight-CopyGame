#include "pch.h"
#include "CTimeMgr.h"
#include "C_Core.h"

CTimeMgr::CTimeMgr()
	:m_llCurCount{}
	,m_llPrevCount{}
	,m_llFrequency{}
	,m_dDT(0.)
	,m_dAcc(0.)
	,m_iCallCount(0)
	,m_iFPS(0)
{

}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llPrevCount); // <- 현재 카운트
	//QueryPerformanceCounter(); // 초당 새는 단위가 천만단위 

	QueryPerformanceFrequency(&m_llFrequency); // <- 초당 카운트 횟수(m_llFrequency.QuadPart에 저장됨)
	//빈번도,얼마나 자주 즉 1초당 얼마나 카운트가 발생하는지에 대한 수를 얻음
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/(double) m_llFrequency.QuadPart; // 정수끼리 나누면 0이 나올수있으니 x -> float형을 쓰는데 더 정확하게 값을 나타내기 위해 double형 사용 
	
	//1초에 100을 셀수 있는데 50을 셌으면 0.5초가 지나간걸 알수있듯이
	// 그 원리를 사용

//디버깅 할때 순식간에 좌표 이동하는 현상 발생 (m_DT가 디버깅 할 때도 계속 증가하므로 그럼)
#ifdef _DEBUG
	if (m_dDT > (1. / 60))
		m_dDT = (1./  60);
#endif
	

	//이전 카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	m_llPrevCount = m_llCurCount;


	++m_iCallCount;
	m_dAcc += m_dDT; //DT(델타타임) 누적 

	if(m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT: %f",m_iFPS,m_dDT);
		SetWindowText(CCore::GenInst()->GetMainHwnd(), szBuffer);


	}

	// 한 프레임에 걸린 시간값 
}
