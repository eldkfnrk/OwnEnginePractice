﻿// Window_Editor.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Window_Editor.h"
#include "..\OwnEnginePractice_SOURCE\oepApplication.h"  //정적 라이브러리 연결
#include "..\OwnEnginePractice_Window\oepLoadScenes.h"
#include "..\OwnEnginePractice_Window\oepLoadResources.h"

oep::Application application;

//GDIPLUS를 사용하기 위한 초기 세팅
ULONG_PTR gpToken;  //ULONG_PTR -> long long 포인터
Gdiplus::GdiplusStartupInput gpsi;  //GdiplusStartupInput - Gdiplus를 사용하기 위한 구조체

//폴더 이름에 최대한 한글이 들어가지 않게 해야 한다.(파일 경로에 한글이 들어가게 되면 문제가 발생할 확률이 높기 때문에)

//이 강의에서는 팩맨을 완성시켜볼 예정

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

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
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //메모리 릭(누수) 검사 코드
    //프로그램을 실행시킨 다음 종료시키면 해제하지 않은 메모리와 그 크기들을 출력에 보여준다.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //메모리 릭이 발생한 메모리가 할당된 위치를 유추할 수 있도록 오류 코드로 이동(인자로는 메모리 생성 순서를 넣는데 이는 위의 코드에서 출력해준 내용에 나온다.)
    //_CrtSetBreakAlloc(662);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWEDITOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWEDITOR));

    MSG msg;

    while (true) {
        //메시지가 있는 경우  
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {  
            if (msg.message == WM_QUIT)  //메시지가 QUIT이면 프로그램 종료
                break;

            //프로그램 메시지가 있다면 번역하여 메시지에게 전달
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {  //메시지가 없는 경우
            application.Run();
        }
    }

    //씬에 사용된 Gdiplus들을 먼저 메모리 해제시킨 다음에 씬매니저에 저장된 모든 씬들의 메모리를 해제(메모리 해제 순서도 중요하기 때문에 이 순서를 지켜주어야 한다.)
    Gdiplus::GdiplusShutdown(gpToken);  //gpToken 메모리 해제
    application.Release();  //씬매니저의 씬들과 리소스들의 메모리 해제

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWEDITOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWEDITOR);
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
    //윈도우의 기본 동작
    //wndclass 생성 -> createWindow -> showWindow -> wndProc(메시지 처리)
    
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //윈도우 해상도
   //const UINT width = 1600;
   //const UINT height = 900;

   //팩맨을 원본 파일 그대로 플레이하면 화면이 굉장히 작기 때문에 윈도우를 적절한 크기(맵의 3배)로 설정
   const UINT width = 672;
   const UINT height = 846;

   //핸들은 윈도우 생성과 동시에 생성
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

   application.Initialize(hWnd, width, height);  //객체의 초기화 함수 호출(여기서 호출하는 이유는 핸들을 인자로 전달하기 위해서이다.)

   if (!hWnd)
   {
      return FALSE;
   }

   //ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   Gdiplus::GdiplusStartup(&gpToken, &gpsi, NULL);  //Gdiplus를 활성화

   //load Resources -> 프로그램이 실행됨과 동시에 게임에 모든 모든 리소스를 Resource에 추가
   //이 함수는 반드시 LoadScenes 함수보다 먼저 호출되어야 하는데 그 이유는 씬에서 리소스를 사용해야 하는데 리소스가 추가가 안 되어 있으면 당연히 찾는 리소스가 없으니
   //정상적으로 씬이 구성되지 않을 것이기 때문이다.
   oep::LoadResources();

   //load Scenes -> 프로그램이 실행됨과 동시에 게임에 모든 씬들을 SceneManager에 추가
   oep::LoadScenes();

   //rand() 함수는 실행을 한 번 하면 값이 고정이 되는데 그러면 랜덤한 동작을 실행해야 하는데 일정한 동작만 실행하게 되는 문제가 발생
   //srand(time(NULL));  //이를 해결하는 것이 시간에 따른 랜덤 값을 주는 이 함수를 실행시켜주는 것이다.(시간 값은 계속 다를 것이기 때문이다.)

   //시간 말고 또 하나 랜덤한 값을 배출하는 것이 메모리의 값이다. 이것은 윈도우가 프로그램이 실행됨과 동시에 메모리를 할당하는 것이고 할당하는 메모리는 할당할 때마다 변하기 때문이다.
   int a = 0;
   srand((UINT)(&a));  //인자(시드)로 메모리 주소 값을 전달(매개변수의 자료형은 unsigned int 이니 알맞게 형 변환을 시켜주어야 한다.

   //그러나 시간도 완벽한 해결법은 아니니 실제 랜덤한 동작을 원한다면 시간 라이브러리나 랜덤한 값을 배출해주는 라이브러리를 따로 가져와서 사용해야 한다.

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
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
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
