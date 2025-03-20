#include "oepApplication.h"
#include "oepInput.h"
#include "oepTime.h"
#include "oepSceneManager.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr), mWidth(0), mHeight(0), mBackHdc(NULL), mBackBuffer(NULL)/*, mGameObjects{}*/ {  //배열은 이와 같은 방식으로 초기화해준다.

	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height) {
		//mHwnd = hwnd;
		//mHdc = GetDC(hwnd);

		//mWidth = width;
		//mHeight = height;

		//RECT rect = { 0,0,width,height };

		//AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		//SetWindowPos(mHwnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0);
		//ShowWindow(mHwnd, true);
		adjustWindowRect(hwnd, width, height);

		//mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);

		//mBackHdc = CreateCompatibleDC(mHdc);

		//HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		//DeleteObject(oldBitmap);
		createBuffer(width, height);

		//Input::Initialize();
		//Time::Initialize();
		initializeEtc();

		//새 게임 오브젝트를 배열에 삽입
		//GameObject* gameObj = new GameObject();
		//mGameObjects.push_back(gameObj);

		//랜덤한 위치를 가진 10개의 오브젝트를 생성하기 위한 for문
		//for (size_t i = 0; i < 10; i++) {
		//	GameObject* gameObj = new GameObject();

		//	//rand()함수는 C언어의 함수로 랜덤한 숫자 값을 반환하는 함수(화면을 넘어가서 생성되는 것은 안 되기 때문에 나머지 연산자로 해상도보다 큰 값이 나오는 것을 막았다.)
		//	gameObj->SetPosition(rand() % 1600, rand() % 900); 
		//	mGameObjects.push_back(gameObj);
		//}

		//위의 동작은 이제 Scene이 담당하고 이런 씬을 초기화하는 것은 SceneManager가 담당하여 실행한다. 그렇기 때문에 Application에서는 SceneManager의 초기화 함수만 있으면 된다.
		//Update, LateUpdate, Render 또한 마찬가지로 SceneManager의 함수 호출만 하면 되도록 수정하면 된다.
		SceneManager::Initialize();
	}

	void Application::Run() {
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update() {
		Time::Update();
		Input::Update();
		//mPlayer.Update();

		//배열에 저장된 모든 게임 오브젝트를 업데이트해야 하기 떄문에 for문을 사용하여 모두 순회해주어야 한다.
		//for (size_t i = 0; i < mGameObjects.size(); i++) {
		//	mGameObjects[i]->Update();
		//}

		SceneManager::Update();
	}

	void Application::LateUpdate() {
		//mPlayer.LateUpdate();
		//for (size_t i = 0; i < mGameObjects.size(); i++) {
		//	mGameObjects[i]->LateUpdate();
		//}

		SceneManager::LateUpdate();
	}

	void Application::Render() {
		//Rectangle(mBackHdc, -1, -1, 1601, 901);  //배경(해상도에 맞춰 1600, 900으로 설정하면 화면을 꽉 채우지 못해서 검은 부분이 보이기 때문에 화면보다 조금 더 크게 만들어 주었다.)  
		clearRenderTarget();

		//mPlayer.Render(mBackHdc);
		//for (size_t i = 0; i < mGameObjects.size(); i++) {
		//	mGameObjects[i]->Render(mBackHdc);
		//}

		SceneManager::Render(mBackHdc);

		Time::Render(mBackHdc);

		//BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
		copyRenderTarger(mBackHdc, mHdc);
	}

	Application::~Application() {

	}

	void Application::clearRenderTarget() {
		//화면을 깔끔하게 헤주는 작업을 함수로 묶어놓았다.
		Rectangle(mBackHdc, -1, -1, 1601, 901);   
	}

	void Application::copyRenderTarger(HDC source, HDC dest) {  //source - 복사 대상, dest - 복사될 위치
		//mBackHdc를 mHdc에 복사(BitBlt 함수 - 뒤에 DC를 앞에 DC가 복사하는 함수)
		BitBlt(dest, 0, 0, mWidth, mHeight, source, 0, 0, SRCCOPY);
	}

	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height) {
		//윈도우 세팅을 함수로 묶어놓았다.

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
		//더블 버퍼링을 위한 새 버퍼를 생성하는 과정을 함수로 묶어놓았다.
		
		//윈도우 해상도에 맞는 백버퍼(도화지) 생성
		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);

		//백버퍼를 가르킬 DC 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		//DC가 백버퍼를 가르키도록 연결
		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);  //기존에 새로 생성할 떄 있던 디폴트 비트맵을 삭제
	}

	void Application::initializeEtc() {
		//다른 정적 함수를 사용하는 클래스의 Initialize를 함수로 묶어놓았다.
		Input::Initialize();
		Time::Initialize();
	}
}