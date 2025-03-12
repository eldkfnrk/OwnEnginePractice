// Window_Editor.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Window_Editor.h"
#include "..\OwnEnginePractice_SOURCE\oepApplication.h"  //정적 라이브러리 연결
//이때 주의해야 할 것은 라이브러리를 참조하지 않으면 cpp파일로 함수를 정의한 것을 사용하지 못 할 수 있기에 꼭 참조를 해주어야 한다.

Application app;

//폴더 이름에 최대한 한글이 들어가지 않게 해야 한다.(파일 경로에 한글이 들어가게 되면 문제가 발생할 확률이 높기 때문에)

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

    // 기본 메시지 루프입니다:
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}

    //위처럼 WinAPI의 기본적인 행동은 메시지 기반 즉, 입력이 없으면 동작도 없는 방식이다. 윈도우 기반 응용 프로그램에 적합한 방식을 취하고 있다.
    //그러나, 게임은 입력이 없어도 계속해서 게임 내부적으로 동작이 있기 때문에 메시지 기반 시스템인 WinAPI와는 안 맞는다. 
    //그래서 메시지 기반 WinAPI를 게임에 맞게 변경해주어야 한다.

    //GetMessage(&msg, nullptr, 0, 0)
    //위 함수는 프로세스에서 발생한 메시지를 메시지 큐에서 가져오는 함수
    //즉, 메시지 큐에 아무 메시지도 없다면 아무 메시지도 가져오지 않게 된다.
    //그래서 메시지가 없다면 프로그램이 동작하지 않게 되는 것이다.

    //PeekMessage
    //이 함수는 메시지 큐에 메시지 유무에 관계없이 항상 함수가 리턴된다.
    //메시지가 있으면 true를 없으면 false를 반환하기 때문에 항상 동작하도록 설정 후 메시지 유무에 따른 동작 변화를 가지게 하여
    //게임에 필요한 시스템을 구현할 수 있다.

    while (true) {
        //메시지가 있는 경우  
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {  
            //이 함수의 마지막 인수는 메시지를 어떻게 처리할 것인지를 묻는 것으로 아무것도 안 하면 
            //메시지 큐에 메시지가 계속 남게 되기에 없애주도록 인자를 전달한다.
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
            //메시지가 없을 경우 여기서 처리
            //게임 로직이 들어가면 된다.
        }
    }

    //이렇게 해서 API와 관련된 모든 기능은 끝났고 이제 만들려는 게임에 알맞는 게임 로직을 구현해서 실행하면 된다.

    //그런데 게임을 만들 때 하나의 프로젝트에만 계속 파일을 추가하게 되면 빌드 시간이 증가하게 된다. 그 시간을 줄이기 위해
    //각 역할에 맞게 프로젝트들을 나누어 파일을 관리하려 한다. 그러면 수정이 발생한 파일이 있는 프로젝트만 빌드를 하면 되기에
    //시간을 단축할 수 있을 것이다. 이때 파일들을 모아놓는 프로젝트는 정적 라이브러리 구성할 예정인데 이는 다음과 같은 과정을 거친다.
    //우선 빈 프로젝트를 추가해주고 이 프로젝트의 속성으로 들어가 '모든 구성', '모든 플랫폼'으로 설정 후 '구성 속성'의 '일반' 탭으로
    //가서 구성 형식을 '애플리케이션'에서 '정적 라이브러리'로 수정하고 적용시켜서 정적 라이브러리를 만들어 사용한다.

    //정적 라이브러리를 사용하는 이유는 추가한 프로젝트는 실행할 프로젝트가 아닌 파일을 모아놓는 프로젝트이기 때문으로 엔진에 상황에 
    //알맞게 프로젝트를 구성하고 사용하면 된다.

    //정적 라이브러리가 있다는 것은 동적 라이브러리도 있다는 의미로 이 둘의 차이를 조금 알아보자.
    //정적 라이브러리는 나의 프로그램의 메모리 내에 존재하여 동작한다. 그때 게임이 두 개가 돌아가고 있다 가정해보면 동시에 사용하는 
    //라이브러리가 존재할 것인데 정적 라이브러리를 사용하면 라이브러리가 두 개가 올라가게 되면서 낭비가 발생하게 된다. 이를 보완하기 위한
    //것이 동적 라이브러리로 이는 라이브러리가 필요한 프로그램을 키든 안 키든 메모리 공간에 라이브러리를 올려놓고 파일들은 이에 접근하여 
    //사용하는 것으로 이렇게 하면 라이브러리는 하나만 있어 메모리 낭비를 해결할 수 있다.

    //이렇게 둘의 차이를 알아봤으니 각각의 장단점을 알아보자.
    //정적 라이브러리의 장점
    //1.시스템 환경이 변해도 어플리케이션에 아무런 영향이 없다.(프로그램 자체에 라이브러리가 들어가 있는 것이기 때문이다.)
    //2.컴파일 시 필요한 라이브러리를 적재하기 때문에 이식성이 좋다.
    //3.런타임 시 외부 참조할 필요가 없기 때문에 속도가 빠르다.
    //정적 라이브러리의 단점
    //1.같은 코드를 가진 프로그램이 실행할 경우가 있다면 코드가 중복될 수 있으니 그만큼 메모리를 낭비한다.
    //2.라이브러리가 변경되면 변경된 라이브러리만 재배포하면 되는 게 아니라 다시 컴파일해서 새로 빌드된 버전 전체를 재배포하여야 한다.
    //동적 라이브러리의 장점
    //1.메모리 절약이 가능하다.
    //2.보다 쉽게 업그레이드 후 배포 가능
    //3.서로 다른 프로그램에서 동일한 함수를 호출 가능
    //4.프로그램 변경 시 라이브러리만 재배포하면 되니까 유지보수가 쉽다.
    //동적 라이브러리의 단점
    //1.컴파일 과정에서 문제가 되는 것을 알지 못하기 때문에 재배포 후 문제가 발생할 가능성이 있고 해결도 쉽지 않다.
    //2.외부 의존도가 높기 때문에 이식성이 낮다.
    //3.공유 라이브러리를 메모리에 올려놓고 사용하기 때문에 해당 라이브러리를 찾아서 접근해야 되기 때문에 속도가 느리다.

    //정적 라이브러리는 보통 개인 환경에서 플레이가 가능하게 배포하는 게임들에서 사용하고 동적 라이브러리는 웹 기반 게임 중 게임하면서 배포되는
    //게임들이 있는데 이 게임들은 동적 라이브러리를 사용한다. 이렇게 되는 이유는 정적 라이브러리는 장점에서 알 수 있듯이 시스템 환경의 영향이 없고
    //이식성이 좋기 때문에 배포만 성공적이라면 문제가 없고 또 라이브러리를 포함하기 때문에 오류가 발생하면 개발 과정에서 바로 보여져 수정이 용이하고
    //테스트도 쉽기 때문이다. 그러나 동적 라이브러리는 오류 발견이 어렵고 테스트를 할 수 없어 재배포한 라이브러리가 문제가 될 수 있긴 하지만 언제든지
    //라이브러리만 수정해서 재배포하면 따로 패치 파일을 받을 필요가 없이 플레이 중에도 수정이 되기 때문에 사용하게 되는 것이다.
    //그렇기 때문에 게임의 상황에 알맞게 설정해서 사용하면 된다.(이 엔진은 정적 라이브러리 사용)

    //그리고 또 따로 엔진 코드들을 모아놓는 공유 항목 프로젝트를 생성해서 엔진 관련 동작을 모아놓을 예정인데 이 코드들을 정적 라이브러리가 사용해야
    //하기 때문에 정적 라이브러리의 참조 항목을 통해 공유 항목 프로젝트를 참조하도록 만들어야 한다.

    //각 프로젝트의 역할
    //Editor_Window - 윈도우 출력, 프로그램 툴 추가
    //OwnEnginePractice_Window - 게임 컨텐츠
    //OwnEnginePractice_SOURCE - 엔진 구성

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
