#include "oepApplication.h"
#include "oepInput.h"
#include "oepTime.h"
#include "oepSceneManager.h"
#include "oepResources.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr), mWidth(0), mHeight(0), mBackHdc(NULL), mBackBuffer(NULL) {

	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height) {
		adjustWindowRect(hwnd, width, height);

		createBuffer(width, height);

		initializeEtc();

		SceneManager::Initialize();
	}

	void Application::Run() {
		Update();
		LateUpdate();
		Render();

		//모든 동작이 다 끝난 후 삭제할 대상들을 일괄 삭제(이러면 한 프레임 진행 완료 후 다음 프레임이 진행되기 전에 모두 삭제할 수 있다.)
		Destroy();
	}

	void Application::Update() {
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate() {
		SceneManager::LateUpdate();
	}

	void Application::Render() { 
		clearRenderTarget();

		SceneManager::Render(mBackHdc);

		Time::Render(mBackHdc);

		copyRenderTarger(mBackHdc, mHdc);
	}

	void Application::Destroy() {
		SceneManager::Destroy();
	}

	void Application::Release() {
		SceneManager::Release();
		Resources::Release();
	}

	Application::~Application() {

	}

	void Application::clearRenderTarget() {
		Rectangle(mBackHdc, -1, -1, 1601, 901);   
	}

	void Application::copyRenderTarger(HDC source, HDC dest) {  
		BitBlt(dest, 0, 0, mWidth, mHeight, source, 0, 0, SRCCOPY);
	}

	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height) {
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0,0,width,height };

		//실제 윈도우 해상도
		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(hwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(hwnd, true);
	}

	void Application::createBuffer(UINT width, UINT height) {
		//윈도우 해상도에 맞는 백버퍼(도화지) 생성
		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);

		//백버퍼를 가르킬 DC 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		//DC가 백버퍼를 가르키도록 연결
		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);  //기존에 새로 생성할 떄 있던 디폴트 비트맵을 삭제
	}

	void Application::initializeEtc() {
		Input::Initialize();
		Time::Initialize();
	}
}