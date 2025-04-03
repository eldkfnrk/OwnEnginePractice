#pragma once
#include "CommonInclude.h" 
#include "oepScene.h"

namespace oep {
	class Application
	{
	public:
		Application();  

		void Initialize(HWND hwnd, UINT width, UINT height);  
		void Run();  
		void Update();  
		void LateUpdate();  
		void Render();  

		void Release();

		HWND GetHwnd() {
			return mHwnd;
		}

		HDC GetHdc() {
			return mHdc;
		}

		UINT GetWidth() {
			return mWidth;
		}

		UINT GetHeight() {
			return mHeight;
		}

		~Application(); 

	private:
		void clearRenderTarget();
		void copyRenderTarger(HDC source, HDC dest); 
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
	};
}
