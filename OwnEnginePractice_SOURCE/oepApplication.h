#pragma once
#include "CommonInclude.h"  
//#include "oepGameObject.h"
#include "oepScene.h"

namespace oep {
	class Application
	{
	public:
		Application();  

		void Initialize(HWND hwnd, UINT width, UINT height);  //인자로 해상도를 추가로 받도록 설정
		void Run();  
		void Update();  
		void LateUpdate();  
		void Render();  

		~Application(); 

	private:
		void clearRenderTarget();
		void copyRenderTarger(HDC source, HDC dest);  //source - 복사 대상, dest - 복사될 위치
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
		
		//기존에는 게임 오브젝트를 하나하나씩 추가해주는 방식을 취했지만 실제 게임에서는 수많은 오브젝트를 가지고 있는데 이를 하나하나 추가해줄 수는 없으니 이들을 묶어서 관리해주어야 한다. 
		//GameObject mPlayer;  
		//std::vector<GameObject*> mGameObjects;  //그 방법으로 vector를 사용

		//이제 Application은 Scene을 가지고 있고 GameObject는 Scene이 가지고 있으면 된다.
		//왜냐하면, 오브젝트는 씬을 구성하는 부품이고 씬은 게임을 구성하는 부품이기 때문에 이렇게 따로 관리한다.
		//std::vector<Scene*> mScenes;

		//그러나 Application에서 모든 씬들을 관리한다면 코드도 길어지고 게임 실행과 윈도우 설정을 담당한다는 목적성에서도 벗어나기 때문에 Application에서는 씬을 관리하는 것이 아닌 씬을 관리하는
		//객체를 관리하는 방식으로 수정하는 것이 각 역할에 맞게 프로그램이 만들어지면서 유지 보수도 용이하고 가독성도 높일 수 있다.
	};
}
