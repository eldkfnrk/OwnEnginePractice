#include "oepApplication.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr), mSpeed(0.0f), mX(0.0f), mY(0.0f) {
		//생성자가 호출되면 반드시 멤버 변수의 값을 초기화시켜 주어야 한다.(이 값은 프로그램의 영향은 안 가고 실제 값은 초기화 함수에서 결정)
	}

	void Application::Initialize(HWND hwnd) {
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);  //GetDC함수는 DC를 가져오는 함수 
	}

	void Application::Run() {
		//이 함수에서 순서가 굉장히 중요하다. 항상 이 순서로 정렬되도록 해야 한다.
		//왜냐하면, 일단 업데이트를 한 후 그 다음 업데이트를 진행하고 업데이트 된 내용을 바탕으로 화면을 출력해야 하기 때문이다.
		//그러지 않으면 화면이 먼저 출력되어서 유저의 입력이 적용이 안 되거나 업데이트 순서가 바뀌어 문제가 생길 수도 있기 때문이다.
		//C++에서는 사소해 보이더라도 코드의 순서가 프로그램의 영향을 주기 때문에 방지책이 없다면 신경써야 한다.
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update() {
		//mSpeed += 0.01f;

		//사용자의 입력에 따라 도형을 움직이도록 하는 테스트 코드
		//이때 코드는 아래의 조건들을 만족하여야 한다.
		//1.오른쪽 키를 입력하면 x가 플러스로 왼쪽 키를 입력하면 x가 마이너스로 이동
		//2.위쪽 키를 입력하면 y가 마이너스로 아래쪽 키를 입력하면 y가 플러스로 이동
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			//GetAsyncKeyState함수는 인자로 전달받은 키의 상태를 반환하는 함수로 0x8000은 키가 입력되었다는 것을 의미
			//그리고 인자로 전달되는 값은 각 키보드 키에 할당된 ASCII코드 값을 정의한 것을 가져와서 사용
			//예를 들어 A 키의 상태를 알고 싶다면 인자에 VK_A로 정의된 정수를 전달하는 것이다.
			mX -= 0.01f;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			mX += 0.01f;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			mY -= 0.01f;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			mY += 0.01f;
		}

		//위의 동작을 LateUpdate나 Render함수에서 돌려도 되지만 굳이 Update에서 하는 이유는 각자 할 일에 맞게 분리시켜 놓아야
		//코드가 길어지고 복잡해졌을 때 문제 발생 시 어느 곳에서 발생한 문제인지 찾기 편하기 위해서 그리고 역할 분담이 잘 되어있다면
		//어느 부분을 수정할 때 찾기 편해지기 때문에 함수의 역할을 잘 구분짓고 각 역할에 맞는 내용을 추가하는 것이 좋다.
	}
	void Application::LateUpdate() {

	}

	void Application::Render() {
		//Rectangle(mHdc, 200, 200, 300, 300);  //직사각형을 생성하여 화면(DC)에 출력하는 함수
		//Rectangle(mHdc, 200 + mSpeed, 200, 300 + mSpeed, 300);  //도형이 mSpeed만큼 오른쪽으로 이동하도록 변경
		Rectangle(mHdc, 200 + mX, 200 + mY, 300 + mX, 300 + mY);  //특정 키 입력에 따라 도형이 이동하도록 변경
	}

	Application::~Application() {

	}
}