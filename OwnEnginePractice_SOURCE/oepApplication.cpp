#include "oepApplication.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr) /*mSpeed(0.0f), mX(0.0f), mY(0.0f)*/ {
		
	}

	void Application::Initialize(HWND hwnd) {
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);  
		//mPlayer.SetPosition(0.0f, 0.0f);
	}

	void Application::Run() {
		Update();
		LateUpdate();
		Render();
	}

	//아래의 Update, LateUpdate, Render함수처럼 GameObject함수 관련 동작을 해당 클래스에서 구현하고 해당 함수를 불러오는 식으로 하면 
	//Application 클래스에서는 굳이 해당 클래스 객체의 동작에 관여할 필요없이 게임 동작만을 수행할 수 있게 된다.
	void Application::Update() {
		////현재 오브젝트의 좌표
		//float x = mPlayer.GetPositionX();
		//float y = mPlayer.GetPositionY();

		//if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		//	//mX -= 0.01f;
		//	x -= 0.01f;
		//}

		//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		//	//mX += 0.01f;
		//	x += 0.01f;
		//}

		//if (GetAsyncKeyState(VK_UP) & 0x8000) {
		//	//mY -= 0.01f;
		//	y -= 0.01f;
		//}

		//if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		//	//mY += 0.01f;
		//	y += 0.01f;
		//}

		////위의 키 입력을 통해 좌표가 바뀌게 되는 것을 적용시켜주기 위한 함수 호출
		//mPlayer.SetPosition(x, y);

		mPlayer.Update();
	}

	void Application::LateUpdate() {
		mPlayer.LateUpdate();
	}

	void Application::Render() {
		////Rectangle(mHdc, 200 + mX, 200 + mY, 300 + mX, 300 + mY);

		////오브젝트의 좌표
		//float x = mPlayer.GetPositionX();
		//float y = mPlayer.GetPositionY();

		//Rectangle(mHdc, 100 + x, 100 + y, 200 + x, 200 + y);

		////기존에는 직접 Application에서 오브젝트의 이동을 구현했다면 지금은 게임 오브젝트를 만들고 이를 한 번 거쳐서 구현
		////이렇게 또 다시 클래스로 묶어서 객체로 만들어 관리하는 이유는 이것이 조금 더 코드를 짧고 편하게 하며 쉽게 관리하는 방법이기 때문이다.
		////지금은 오브젝트가 하나 밖에 없으니 기존보다 코드가 늘어나 보이겠지만 오브젝트가 3~4개만 되어도 좌표가 늘어나고 그러면서 좌표 수정에
		////있어 실수가 생길 가능성이 커지는데 이를 클래스로 묶고 해당 클래스의 객체로 만들어 이용하면 어떤 객체의 좌표인지 실수할 일이 줄고
		////객체들을 묶어서 관리할 수도 있고 코드도 간결해질 수 있으니 한 클래스에서 모든 작업을 하는 것이 아닌 역할에 맞는 클래스를 여러 개 
		////만들고 이들을 사용하는 것이 더 효율적이고 유용하게 코드를 만들 수 있게 한다.

		mPlayer.Render(mHdc);
	}

	Application::~Application() {

	}
}