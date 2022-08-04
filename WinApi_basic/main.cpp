// WinApi_basic.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "WinApi_basic.h"
#include "CCore.h"
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND           g_hwnd;                            // 메인 윈도우
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다: // 함수 전방 선언
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


// SAL 주석 _In_,_In_opt_ etc... opt는 쓸모없는것을 뜻함
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // 메모리 릭 누수 체크

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   // _CrtSetBreakAlloc(217);
    
    //아무것도 아닌 것들(참조되지 않은것을 의미하기 위해 있음)
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.



    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIBASIC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화
    //Failed안에 들어간 값이 음수면 true -> E_FAIL은 음수값을 반환함
    //window에서 반환하는 값의 형태는 보통 hr;
    if (FAILED(CCore::GetInst()->init(g_hwnd, POINT{ 1280,768 }))) {
        MessageBox(nullptr,L"core 객체 초기화 실패",L"ERROR",MB_OK);
        return FALSE;
        }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIBASIC));

    MSG msg;

    // SetTimer(g_hwnd, 0, 0, nullptr);



    // PeekMessage
    // 메세지 유무와 관계없이 반환
    // 메세지큐에서 메세지를 확인할 경우 true, 메세지큐에 메세지가 없는 경우 false를 반환한다.

    // 기본 메시지 루프입니다:
    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == msg.message)
                break;
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {
            // 메세지가 없는동안 호출
            // Game 코드 수행
            // 디자인 패턴(설계 유형)
            // 싱글톤 패턴
            CCore::GetInst()->progress();
        }
    }
    // KillTimer(g_hwnd, 0);
    return (int)msg.wParam;
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIBASIC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIBASIC);
    wcex.lpszClassName  = szWindowClass; //등록 키값
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

   //해당 윈도우의 ID 값을 받아옴
   g_hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hwnd)
   {
      return FALSE;
   }

   ShowWindow(g_hwnd, nCmdShow);
   UpdateWindow(g_hwnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

INT_PTR __stdcall TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
            case IDM_TILE:
            {
                INT_PTR iRet = DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);

                if (iRet == IDOK)
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            // hdc라는 Device Context생성 후 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context(그리기)

            //Rectangle(hdc, 1180, 668, 1280, 768);

            EndPaint(hWnd, &ps);
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
