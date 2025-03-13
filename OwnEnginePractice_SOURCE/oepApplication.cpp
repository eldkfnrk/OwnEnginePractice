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

	//�Ʒ��� Update, LateUpdate, Render�Լ�ó�� GameObject�Լ� ���� ������ �ش� Ŭ�������� �����ϰ� �ش� �Լ��� �ҷ����� ������ �ϸ� 
	//Application Ŭ���������� ���� �ش� Ŭ���� ��ü�� ���ۿ� ������ �ʿ���� ���� ���۸��� ������ �� �ְ� �ȴ�.
	void Application::Update() {
		////���� ������Ʈ�� ��ǥ
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

		////���� Ű �Է��� ���� ��ǥ�� �ٲ�� �Ǵ� ���� ��������ֱ� ���� �Լ� ȣ��
		//mPlayer.SetPosition(x, y);

		mPlayer.Update();
	}

	void Application::LateUpdate() {
		mPlayer.LateUpdate();
	}

	void Application::Render() {
		////Rectangle(mHdc, 200 + mX, 200 + mY, 300 + mX, 300 + mY);

		////������Ʈ�� ��ǥ
		//float x = mPlayer.GetPositionX();
		//float y = mPlayer.GetPositionY();

		//Rectangle(mHdc, 100 + x, 100 + y, 200 + x, 200 + y);

		////�������� ���� Application���� ������Ʈ�� �̵��� �����ߴٸ� ������ ���� ������Ʈ�� ����� �̸� �� �� ���ļ� ����
		////�̷��� �� �ٽ� Ŭ������ ��� ��ü�� ����� �����ϴ� ������ �̰��� ���� �� �ڵ带 ª�� ���ϰ� �ϸ� ���� �����ϴ� ����̱� �����̴�.
		////������ ������Ʈ�� �ϳ� �ۿ� ������ �������� �ڵ尡 �þ ���̰����� ������Ʈ�� 3~4���� �Ǿ ��ǥ�� �þ�� �׷��鼭 ��ǥ ������
		////�־� �Ǽ��� ���� ���ɼ��� Ŀ���µ� �̸� Ŭ������ ���� �ش� Ŭ������ ��ü�� ����� �̿��ϸ� � ��ü�� ��ǥ���� �Ǽ��� ���� �ٰ�
		////��ü���� ��� ������ ���� �ְ� �ڵ嵵 �������� �� ������ �� Ŭ�������� ��� �۾��� �ϴ� ���� �ƴ� ���ҿ� �´� Ŭ������ ���� �� 
		////����� �̵��� ����ϴ� ���� �� ȿ�����̰� �����ϰ� �ڵ带 ���� �� �ְ� �Ѵ�.

		mPlayer.Render(mHdc);
	}

	Application::~Application() {

	}
}