#include "oepApplication.h"
#include "oepInput.h"
#include "oepTime.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr) {
		
	}

	void Application::Initialize(HWND hwnd) {
		mHwnd = hwnd;
		mHdc = GetDC(hwnd); 

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
		mPlayer.Render(mHdc);
		Time::Render(mHdc);	
	}

	Application::~Application() {

	}
}