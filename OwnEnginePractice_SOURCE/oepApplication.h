#pragma once
#include "CommonInclude.h"  
//#include "oepGameObject.h"
#include "oepScene.h"

namespace oep {
	class Application
	{
	public:
		Application();  

		void Initialize(HWND hwnd, UINT width, UINT height);  //���ڷ� �ػ󵵸� �߰��� �޵��� ����
		void Run();  
		void Update();  
		void LateUpdate();  
		void Render();  

		~Application(); 

	private:
		void clearRenderTarget();
		void copyRenderTarger(HDC source, HDC dest);  //source - ���� ���, dest - ����� ��ġ
		void adjustWindowRect(HWND hwnd, UINT width, UINT height);
		void createBuffer(UINT width, UINT height);
		void initializeEtc();

	private:
		HWND mHwnd;  
		HDC mHdc;  

		//�߰� ��ȭ���� �׷��� DC
		HDC mBackHdc;

		//���� ���۸��� �ʿ��ؼ� �߰��� ��ȭ��
		HBITMAP mBackBuffer;  

		//�ػ�
		UINT mWidth;  
		UINT mHeight;  
		
		//�������� ���� ������Ʈ�� �ϳ��ϳ��� �߰����ִ� ����� �������� ���� ���ӿ����� ������ ������Ʈ�� ������ �ִµ� �̸� �ϳ��ϳ� �߰����� ���� ������ �̵��� ��� �������־�� �Ѵ�. 
		//GameObject mPlayer;  
		//std::vector<GameObject*> mGameObjects;  //�� ������� vector�� ���

		//���� Application�� Scene�� ������ �ְ� GameObject�� Scene�� ������ ������ �ȴ�.
		//�ֳ��ϸ�, ������Ʈ�� ���� �����ϴ� ��ǰ�̰� ���� ������ �����ϴ� ��ǰ�̱� ������ �̷��� ���� �����Ѵ�.
		//std::vector<Scene*> mScenes;

		//�׷��� Application���� ��� ������ �����Ѵٸ� �ڵ嵵 ������� ���� ����� ������ ������ ����Ѵٴ� ������������ ����� ������ Application������ ���� �����ϴ� ���� �ƴ� ���� �����ϴ�
		//��ü�� �����ϴ� ������� �����ϴ� ���� �� ���ҿ� �°� ���α׷��� ��������鼭 ���� ������ �����ϰ� �������� ���� �� �ִ�.
	};
}
