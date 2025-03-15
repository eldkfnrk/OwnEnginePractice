#pragma once
#include "CommonInclude.h"  
#include "oepGameObject.h"

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
		//여기서 하나 알고 갈 점은 HDC, HWND, HBITMAP처럼 윈도우 API의 자료형 중 H가 붙은 자료형은 해당 자료형의 핸들 즉, 주소 값을 받아서 사용하는 자료형이다.
		HWND mHwnd;  
		HDC mHdc;  

		//원래 더블 버퍼링 알고리즘의 동작은 한 버퍼가 화면 출력을 하면 뒷 버퍼는 업데이트된 화면을 그려놓고 다음 프레임에서 뒷 버퍼였던 버퍼가 화면 출력을 하고 앞 버퍼였던 버퍼가
		//뒤로 이동해 업데이트된 화면을 그려놓고를 반복 즉, 계속 반복해서 앞뒤가 바뀌며 출력하는 동작인데 여기선 약간의 꼼수를 활용하여 더블 버퍼링을 구현한다.
		//그 꼼수란 바로 DC를 하나 더 추가하고 한 DC에서 계속 화면 출력을 하고 뒷 버퍼는 그리고 앞 버퍼에 덮어씌우고 또 지우고 그리고 덮어씌우고를 반복하도록 구현하는 것이다.
		//왜 이런 꼼수를 쓰냐면 계속 버퍼를 교체해주는 작업을 생략하기 위해서로 이렇게 하면 추가 DC로 인해 메모리 사용량이 많아지지만 교환 작업이 없어지니 연산을 줄일 수 있다.
		//그러기 위해서는 원래는 비트맵을 교환하는 방식이었지만 DC를 추가하고 계속 그렸다 지윘다를 반복하도록 만든다.
		HDC mBackHdc;

		//더블 버퍼링에 필요해서 추가한 도화지
		HBITMAP mBackBuffer;  //비트맵이란 압축이 되어 있지 않은 그림 파일 즉, 원본 그대로의 그림 파일이다.

		//해상도(윈도우의 실제 작업 영역 크기)
		UINT mWidth;  //너비(x축 길이)
		UINT mHeight;  //높이(y축 길이)

		GameObject mPlayer;  
	};
}
