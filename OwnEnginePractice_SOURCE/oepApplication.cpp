#include "oepApplication.h"
#include "oepInput.h"

namespace oep {
	Application::Application() : mHwnd(nullptr), mHdc(nullptr) {
		
	}

	void Application::Initialize(HWND hwnd) {
		mHwnd = hwnd;
		mHdc = GetDC(hwnd); 

		//�� �Լ��� �� ���� ȣ����� ������ ���� ��� �迭�� �� �� ���̱� ������ ������ �߻��Ѵ�.
		//�� �Լ��� ���α׷� ���� �� �� �� ���� ����Ǹ� �Ǳ⿡ �̰����� ȣ���ϸ� �ȴ�.
		Input::Initialize();
	}

	void Application::Run() {
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update() {
		//Ű�� ������ ���� ���� �÷��� �߿� �Ͼ�� �����̱� ������ ������ �Ѱ��ϴ� �̰����� ȣ���Ѵ�.
		//input�� update�� ���� ����Ǿ�� Ű �Է¿� ���� ������ �ϴ� ������Ʈ�� ������ ���� �ʰ� �ȴ�.
		//������ ũ�� �߿����� ������ ��� ������ �ǰ� ������ �˾ƾ� �Ѵ�.
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