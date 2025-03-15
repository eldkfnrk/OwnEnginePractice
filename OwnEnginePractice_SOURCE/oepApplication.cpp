#include "oepApplication.h"
#include "oepInput.h"
#include "oepTime.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr), mWidth(0), mHeight(0), mBackHdc(NULL), mBackBuffer(NULL) {
		
	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height) {
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		mWidth = width;
		mHeight = height;
		
		RECT rect = { 0,0,width,height };  //윈도우 안에 있는 RECT라는 자료구조(네모 자료구조)

		//윈도우의 실제 작업 영역 크기를 인자로 받는 값으로 지정하는 함수
		//첫 번째 인자는 영역 크기에 관한 자료 구조의 주소 값을 두 번째 인자는 윈도우 스타일(main에서 윈도우 만들 때 스타일 그대로 사용해도 다른 스타일을 사용해도 괜찮다)을 세 번째 인자는 메뉴바 여부를 받는다.
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		//윈도우가 출력되는 위치를 정하는 함수로 3,4번째 인자는 시작 위치고 5,6번째 인자는 각각 가로 세로 길이를 의미(마지막 인자는 크게 의미는 없고 그냥 0을 넣으면 된다.)
		SetWindowPos(mHwnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0);
		ShowWindow(mHwnd, true);  //윈도우를 재설정했으니 재설정된 값이 적용된 출력되기 위하여 main파일에서 이동

		//윈도우 해상도에 맞는 백버퍼(도화지) 생성
		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);	

		//백버퍼를 가르킬 DC 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		//DC가 백버퍼를 가르키도록 연결
		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);  //기존에 새로 생성할 떄 있던 디폴트 비트맵을 삭제

		Input::Initialize();
		Time::Initialize();
	}

	void Application::Run() {
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update() {
		Time::Update();
		Input::Update();
		mPlayer.Update();
	}

	void Application::LateUpdate() {
		mPlayer.LateUpdate();
	}

	void Application::Render() {
		//지금까지 게임 엔진을 구성하면서 2가지의 문제점이 있었는데 하나는 컴퓨터 성능에 따른 결과 값의 차이가 있다는 것이고 또 다른 하나는 게임 오브젝트인 도형을 이동시킬 때 이동한 화면에 검은색 잔상이 남게 된다는
		//것이 있었다. 첫 번째 문제는 DeltaTime(1프레임 당 실행 시간)을 차등 값으로 결과 값에 곱하면 모든 컴퓨터에서 동일한 결과 값을 낼 수 있는 것을 활용하기 위해 Time 클래스를 구성하고 이를 이용하여 해결했다.
		//이제 하나 남은 이동 시 남는 잔상 문제를 해결해야 하는데 이때 사용하는 것이 더블 버퍼링이라는 것이다.

		//더블 버퍼링이란 한 화면에 두 버퍼(도화지)를 만들어 앞에 있는 버퍼에 출력하는 동안 업데이트된 내용을 뒤에 있는 버퍼에 그리고 뒤에 있는 버퍼와 앞에 있는 버퍼를 교환한 뒤 뒤로 이동한 버퍼는 또 업데이트된
		//내용을 다시 그리는 방식으로 이렇게 하면 한 개의 버퍼만을 사용하던 기존의 방식에서 생기는 이동 시 잔상이 남는 문제를 해결할 수 있게 된다.

		//도형 추가(도화지를 추가하는 것을 따라해보는 과정)
		//이 도형은 한 가지 문제점이 있는데 바로 크기의 문제가 있다. 이게 무슨 말이냐 하면 우리는 윈도우 창의 크기를 (1600, 900)으로 설정하고 생성했는데 그럼 이때 화면에 출력되는 윈도우 창에서 DC가 출력되는
		//부분의 크기는 실질적으로 1600, 900 보다 작다. 왜냐하면, 윈도우 창은 상단에 제목과 여러 동작을 하는 도구들이 있기 때문으로 이를 브라우저 상단 영역이라 하고 실제 화면이 출력되는 실제 작업 영역은	
		//1600, 900 보다 작게 되는 것이다. 그래서 화면의 크기가 안 맞게 되고 그러면서 화면 출력 시 깜빡임이 발생하게 되는 문제가 발생한다. 그렇기 때문에 우리는 실제 작업 영역의 크기를 알고 이를 활용해야 한다.
		//Rectangle(mHdc, 0, 0, 1600, 900);
		
		//실제로 도화지 역할을 하는 것은 DC이다. 지금까지 화면에 출력된 것은 DC라는 도화지 안에 도형을 그려서 윈도우 창에 띄워준 것이라고 볼 수 있다. 그렇기 때문에 더블 버퍼링을 위해선 DC가 하나 더 필요하다.
		//DC가 도화지 역할을 한다고 했지만 사실은 DC 안에 텅 빈 도화지인 이미지 파일을 가지고 있는 것이다. 이 도화지 역할을 하는 이미지 파일은 비트맵 파일로 DC에는 텅 빈 비트맵 파일이 기본으로 들어있다.

		//mPlayer.Render(mHdc);
		//Time::Render(mHdc);	

		//이제 그림은 백버퍼에서만 그리면 되기에 그림을 그리는 DC를 백버퍼를 가리키는 DC로 설정
		Rectangle(mBackHdc, 0, 0, 1600, 900);  //배경 화면(없으면 배경이 검은색으로 출력된다.)
		mPlayer.Render(mBackHdc);
		Time::Render(mBackHdc);

		//그러나 이렇게 되면 앞 버퍼에서 화면 출력을 하도록 만들지 않아서 백버퍼에만 그림이 있어 우리가 보는 화면에 보이지 않게 되기에 백버퍼에 그려진 그림을 앞버퍼에 복사하여 화면 출력이 되도록 해야 한다.
		//그러기 위해 사용하는 것이 BitBlt 함수로 백버퍼에 있는 것을 원본 버퍼에 복사하는 함수이다.
		//그러니 1번째 인자는 복사되는 DC 6번째 인자는 복사 대상이 되는 DC인 것이다. 2~5번째 인자는 복사의 크기로 축소되어 복사될 수도 있다. 그리고 7~8번째 인자는 복사 시작 위치로 100,100이면 100,100부터
		//복사를 한다. 그러니 더블 버퍼링에선 그런 일이 발생하지 않게 0,0부터 복사한다. 그리고 마지막 인자는 어떻게 복사할 것인지에 대한 옵션으로 여기선 기본적인 복사인 SRCCOPY를 사용한다.
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
	}

	Application::~Application() {

	}
}