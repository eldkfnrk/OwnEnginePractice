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

		void Destroy();  //프로그램 중간에 메모리를 해제시켜주기 위한 함수
		void Release();  //프로그램을 종료시킬 때 할당된 모든 메모리를 해제시켜주기 위한 함수

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

		//추가 도화지가 그려질 DC
		HDC mBackHdc;

		//더블 버퍼링에 필요해서 추가한 도화지
		HBITMAP mBackBuffer;  

		//해상도
		UINT mWidth;  
		UINT mHeight;
	};
}
