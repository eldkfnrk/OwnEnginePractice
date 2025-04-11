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

		//��� ������ �� ���� �� ������ ������ �ϰ� ����(�̷��� �� ������ ���� �Ϸ� �� ���� �������� ����Ǳ� ���� ��� ������ �� �ִ�.)
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

		//���� ������ �ػ�
		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(hwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(hwnd, true);
	}

	void Application::createBuffer(UINT width, UINT height) {
		//������ �ػ󵵿� �´� �����(��ȭ��) ����
		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);

		//����۸� ����ų DC ����
		mBackHdc = CreateCompatibleDC(mHdc);

		//DC�� ����۸� ����Ű���� ����
		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);  //������ ���� ������ �� �ִ� ����Ʈ ��Ʈ���� ����
	}

	void Application::initializeEtc() {
		Input::Initialize();
		Time::Initialize();
	}
}