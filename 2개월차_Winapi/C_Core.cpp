#include "pch.h"
#include "C_Core.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"

#include "resource.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CPlayerMgr.h"
#include "CScene.h"


//최초 정적 변수 초기화 
//C_Core* C_Core::g_pInst = nullptr;  // C_Core의 포인터인데 어떤 포인터냐면을
// C_Core :: 연산자를 통해 알려줌 그래서 왜냐하면 g_pinst는 객체에 속하고 있지 않기 때문에

//C_Core::g_pInst = nullptr;  // g_plnst가 퍼블릭일때 가능 


CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0) // 초기화 수행 
	, m_arrBrsuh{}
	, m_arrPen{}
	, m_bRender(false)

{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // 윈도우 핸들 비트맵에 그린 DC는 Release로 지워야한다


	for(int i =0 ; i<(UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
	
	DestroyMenu(m_hMenu);
}


int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hWnd = _hwnd;
	m_ptResolution = _ptResolution;

	//RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };

	//해상도에 맞게 윈도우 크기 조정
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y),false);
	//AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	//SetWindowPos(m_hWnd, nullptr, 300, 30, rt.right - rt.left, rt.bottom - rt.top, 0);

	//rt.right - rt.left;  // 가로길이
	//rt.bottom - rt.;  // 세로 길이 

	// 메뉴바 생성 
	m_hMenu = LoadMenu(nullptr,MAKEINTRESOURCEW(IDC_MY2WINAPI));

	//_ptResolution.x = 1;
	//_ptResolution.y = 2;

	m_hDC = GetDC(m_hWnd); // 윈도우가 보유하고 있는 비트맵을 할당한다는 의미

	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다
	m_pMemTex = CResMgr::GenInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
	// 자주 사용 할 펜 및 브러쉬 생성
	CreatBrsuhPen();

	//Manger 초기화 
	CPathMgr::GenInst()->init(); // 이거를 CScene보다 먼저 해줘야하는거 기억하기! ( 객체 생성 순서가 달라지므로 )
	CTimeMgr::GenInst()->init();
	CKeyMgr::GenInst()->init();
	CCamera::GenInst()->init();
	CSoundMgr::GenInst()->init();
	CSceneMgr::GenInst()->init();
	//CCollisionMgr::GenInst()->init();
	CPlayerMgr::GenInst()->init();
	
	//CResMgr::GenInst()->LoadSound(L"BGM_01",L"sound\\Boss Battle 1.wav");
	//CSound* pNewSound = CResMgr::GenInst()->FindSound(L"BGM_01");
	//
	////pNewSound -> Play();
	////pNewSound -> SetPosition(50.f); // 백분률로 소리위치설정
	//
	//pNewSound -> PlayToBGM(true);
	//pNewSound -> SetVolume(95.f);

	


	return S_OK;

}




void CCore::progress()
{	// =================
	//Manager Update
	// =================
	
	CTimeMgr::GenInst()->Update(); //여기서 프레임 작업 진행
	CKeyMgr::GenInst()->update();
	CCamera::GenInst()->update();


	// =================
	// Scene Upadate
	// =================
	CSceneMgr::GenInst()->update();

	// =================
	// 충돌체크
	// =================
	CCollisionMgr::GenInst()->update();


	//UI 이벤트 체크 
	CUIMgr::GenInst()->update();

	//========================================
	// 랜더링
	//========================================

	//Clear();
	//SelectGDI gdi(m_pMemTex->GetDc(), BRUSH_TYPE::BLACK);

	if (CSceneMgr::GenInst()->GetCurScene()->GetName() == L"FINAL_BOSS_CUT_SCENE")
	{
		if(m_bRender ==false)
		{
			Rectangle(m_pMemTex->GetDc(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1); //하얀 화면을 넣은것

			CSceneMgr::GenInst()->render(m_pMemTex->GetDc()); // 비트맵에 그리고 
			CCamera::GenInst()->render(m_pMemTex->GetDc());

			BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
				m_pMemTex->GetDc(), 0, 0, SRCCOPY); //SRCCOPY 는 복사의 의미

			m_bRender = true;
		}
	}

	else
	{
		Rectangle(m_pMemTex->GetDc(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1); //하얀 화면을 넣은것

		CSceneMgr::GenInst()->render(m_pMemTex->GetDc()); // 비트맵에 그리고 
		CCamera::GenInst()->render(m_pMemTex->GetDc());

		BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
			m_pMemTex->GetDc(), 0, 0, SRCCOPY); //SRCCOPY 는 복사의 의미
	}
	

	// =================
	// 이벤트 지연처리 
	// =================

	CEventMgr::GenInst()->update();

	
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDc(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDc(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreatBrsuhPen()
{
	// hollow brush
	m_arrBrsuh[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrsuh[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// red pen ,blue pen , green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
}

void CCore::DockMenu()
{
	SetMenu(m_hWnd,m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0,0,(long)_vResolution.x,(long)_vResolution.y };

	//해상도에 맞게 윈도우 크기 조정
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}

