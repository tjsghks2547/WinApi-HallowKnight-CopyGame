// 2개월차_Winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "2개월차_Winapi.h"
#include "C_Core.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 메모리 누수 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(); //동적 배열 할당안된거 호출 스택 확인 용도. 

    //new int;


    // TODO: 여기에 코드를 입력합니다.
   // C_Core* pCore =C_Core::GetInstance(); // 힙메모리 주소를 받은것 pCore는 
    
   // C_Core::GetInstance();

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    


    //Core 초기화 및 객체 생성 
    if (FAILED(CCore::GenInst()->init(g_hWnd, POINT{1280,760})))//여기서 핸들값 얻어옴
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"Error", MB_OK);
        return FALSE;
    }




    // 단축키 테이블 정보 로딩 
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2WINAPI));

    MSG msg;
    //DWORD dwTime = GetTickCount64();

    // PeekMessage는 항상 반환되는 함수. 조건이 있든 없든 
    // 즉 메세지의 유무와 관계없이 true , false 반환 
    // 메세지 큐에  메세지가 있으면 true 없으면 false 반환 
    // 즉 메세지가 없어도 계속 작동할 수 있도록 만드는 것이 궁극적인 목표로 peekmessage를 사용 
    
    while (true) 
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // 마지막 확인한 메세지를 제거할지 안할지를 결정하는 매개변수  PM_REMOVE는 마지막 확인한 메세지를 삭제하는것
        {
            if (WM_QUIT == msg.message)
            {
                break; 
            }
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }      

        // 메세지가 없는동안 호출
        else
        {
            //if (dwTime + 10 < GetTickCount64())
            {
                // Game 코드 수행  
                // 디자인 패턴 (설계 유형)
                // 싱글톤 패턴 
                CCore::GenInst()->progress();
                //dwTime = GetTickCount64();
            }
        }
     
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;//MAKEINTRESOURCEW(IDC_MY2WINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    g_hWnd = CreateWindowW(szWindowClass, L"HollowKnight", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

// 이런 함수 있다고 선언해줌
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            // 타일 메뉴 
            case ID_MENU_TILE:
            {
                INT_PTR iRet = DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);

                if(iRet == IDOK)
                {

                }
            }
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT: // 무효화 영역이 발생하면 이 코드가 실행됨 
        {
            PAINTSTRUCT ps;
            //Device Context 만들어서 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps);

            // DC의 목적지는 hWnd
            // DC의 펜은 기본펜 (Black)
            // DC의 브러쉬는 기본 브러쉬(White)
            // 
            // 직접 펜을 만들어서 DC에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0,0,255));

            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
          
            //// 변경된 펜으로 사각형 그림
            //Rectangle(hdc,
            //        1080, 608,
            //        1280, 768);
            

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            /*EndPaint(hWnd, &ps);*/
        }
        break;

    case WM_KEYDOWN:
        break;


    case WM_LBUTTONDOWN:
    
        break; 
 
    case WM_MOUSEMOVE:
   
        break;

    case WM_LBUTTONUP:
    
    break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



// 1. 플레이어 미사일 종류 추가. 
// 2. 몬스터도 미사일 패턴 추가 해보기 

// 3. 1,2번 된다면 충돌기능도 구현해보기 