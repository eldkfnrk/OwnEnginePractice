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

		//추가 도화지가 그려질 DC
		HDC mBackHdc;

		//더블 버퍼링에 필요해서 추가한 도화지
		HBITMAP mBackBuffer;  

		//해상도
		UINT mWidth;  
		UINT mHeight;
	};
}
