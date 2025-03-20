#include "oepApplication.h"
#include "oepInput.h"
#include "oepTime.h"
#include "oepSceneManager.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr), mWidth(0), mHeight(0), mBackHdc(NULL), mBackBuffer(NULL)/*, mGameObjects{}*/ {  //�迭�� �̿� ���� ������� �ʱ�ȭ���ش�.

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

		//�� ���� ������Ʈ�� �迭�� ����
		//GameObject* gameObj = new GameObject();
		//mGameObjects.push_back(gameObj);

		//������ ��ġ�� ���� 10���� ������Ʈ�� �����ϱ� ���� for��
		//for (size_t i = 0; i < 10; i++) {
		//	GameObject* gameObj = new GameObject();

		//	//rand()�Լ��� C����� �Լ��� ������ ���� ���� ��ȯ�ϴ� �Լ�(ȭ���� �Ѿ�� �����Ǵ� ���� �� �Ǳ� ������ ������ �����ڷ� �ػ󵵺��� ū ���� ������ ���� ���Ҵ�.)
		//	gameObj->SetPosition(rand() % 1600, rand() % 900); 
		//	mGameObjects.push_back(gameObj);
		//}

		//���� ������ ���� Scene�� ����ϰ� �̷� ���� �ʱ�ȭ�ϴ� ���� SceneManager�� ����Ͽ� �����Ѵ�. �׷��� ������ Application������ SceneManager�� �ʱ�ȭ �Լ��� ������ �ȴ�.
		//Update, LateUpdate, Render ���� ���������� SceneManager�� �Լ� ȣ�⸸ �ϸ� �ǵ��� �����ϸ� �ȴ�.
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

		//�迭�� ����� ��� ���� ������Ʈ�� ������Ʈ�ؾ� �ϱ� ������ for���� ����Ͽ� ��� ��ȸ���־�� �Ѵ�.
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
		//Rectangle(mBackHdc, -1, -1, 1601, 901);  //���(�ػ󵵿� ���� 1600, 900���� �����ϸ� ȭ���� �� ä���� ���ؼ� ���� �κ��� ���̱� ������ ȭ�麸�� ���� �� ũ�� ����� �־���.)  
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
		//ȭ���� ����ϰ� ���ִ� �۾��� �Լ��� ������Ҵ�.
		Rectangle(mBackHdc, -1, -1, 1601, 901);   
	}

	void Application::copyRenderTarger(HDC source, HDC dest) {  //source - ���� ���, dest - ����� ��ġ
		//mBackHdc�� mHdc�� ����(BitBlt �Լ� - �ڿ� DC�� �տ� DC�� �����ϴ� �Լ�)
		BitBlt(dest, 0, 0, mWidth, mHeight, source, 0, 0, SRCCOPY);
	}

	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height) {
		//������ ������ �Լ��� ������Ҵ�.

		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0,0,width,height };

		//���� ������ �ػ�
		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(hwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(hwnd, true);
	}

	void Application::createBuffer(UINT width, UINT height) {
		//���� ���۸��� ���� �� ���۸� �����ϴ� ������ �Լ��� ������Ҵ�.
		
		//������ �ػ󵵿� �´� �����(��ȭ��) ����
		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);

		//����۸� ����ų DC ����
		mBackHdc = CreateCompatibleDC(mHdc);

		//DC�� ����۸� ����Ű���� ����
		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);  //������ ���� ������ �� �ִ� ����Ʈ ��Ʈ���� ����
	}

	void Application::initializeEtc() {
		//�ٸ� ���� �Լ��� ����ϴ� Ŭ������ Initialize�� �Լ��� ������Ҵ�.
		Input::Initialize();
		Time::Initialize();
	}
}