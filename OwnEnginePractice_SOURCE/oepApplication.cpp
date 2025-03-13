#include "oepApplication.h"
#include "oepInput.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr) {
		
	}

	void Application::Initialize(HWND hwnd) {
		mHwnd = hwnd;
		mHdc = GetDC(hwnd); 

		//이 함수가 한 번도 호출되지 않으면 정적 멤버 배열이 텅 빈 것이기 때문에 문제가 발생한다.
		//이 함수는 프로그램 실행 중 단 한 번만 실행되면 되기에 이곳에서 호출하면 된다.
		Input::Initialize();
	}

	void Application::Run() {
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update() {
		//키가 눌리는 것은 게임 플레이 중에 일어나는 동작이기 때문에 동작을 총괄하는 이곳에서 호출한다.
		//input의 update가 먼저 선행되어야 키 입력에 따른 동작을 하는 오브젝트에 영향을 주지 않게 된다.
		//순서가 크게 중요하진 않지만 어떻게 동작이 되게 될지는 알아야 한다.
		Input::Update();
		mPlayer.Update();
	}

	void Application::LateUpdate() {
		mPlayer.LateUpdate();
	}

	void Application::Render() {
		mPlayer.Render(mHdc);
	}

	Application::~Application() {

	}
}