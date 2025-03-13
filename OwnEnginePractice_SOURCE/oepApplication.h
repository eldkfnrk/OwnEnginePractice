#pragma once
//CommonInclude 헤더 파일처럼 두루 사용되는 파일들은 자주 #include되다 보니 중복이 되는 경우가 많은데 #pragma once 명령어 덕분에 신경을 쓰지 않아도 된다.
//그러나 빌드 시간에는 영향을 줄 수도 있어서 빌드 시간 줄일 때는 중복을 찾아 지우는 편이다.
#include "CommonInclude.h"  
#include "oepGameObject.h"

namespace oep {
	class Application
	{
	public:
		Application();  

		void Initialize(HWND hwnd);  
		void Run();  
		void Update();  
		void LateUpdate();  
		void Render();  

		~Application();  

	private:
		HWND mHwnd;  
		HDC mHdc;  

		GameObject mPlayer;  
	};
}
