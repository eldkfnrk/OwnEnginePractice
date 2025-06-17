#include "oepApplication.h"
#include "oepInput.h"
#include "oepTime.h"
#include "oepSceneManager.h"
#include "oepResources.h"
#include "oepCollisionManager.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr), mWidth(0), mHeight(0), mBackHdc(NULL), mBackBuffer(NULL) {

	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height) {
		adjustWindowRect(hwnd, width, height);

		createBuffer(width, height);

		initializeEtc();

		CollisionManager::Initialize();
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
		CollisionManager::Update();  //충돌 관련 업데이트, 렌더 등의 동작들은 적절한 위치에 넣어주지 않으면 원치 않는 동작이 진행되기 때문에 고려를 잘하고 진행해야 한다.
		SceneManager::Update();
	}

	void Application::LateUpdate() {
		CollisionManager::LateUpdate();
		SceneManager::LateUpdate();
	}

	void Application::Render() { 
		clearRenderTarget();

		Time::Render(mBackHdc);
		CollisionManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);

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
		//도형들이 모두 흰색이라 구분이 안 되어 임시로 배경이 되는 도형의 색을 변경(회색으로 설정)
		//그래픽스를 배울 때 보통 화면에 잘 보이게 하기 위해서 배경색은 회색이나 하늘색으로 많이 한다.
		HBRUSH backGroundBrush = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, backGroundBrush);

		Rectangle(mBackHdc, -1, -1, 1601, 901);   

		SelectObject(mBackHdc, oldBrush);
		DeleteObject(backGroundBrush);
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