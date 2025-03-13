#pragma once
#include "CommonInclude.h"

namespace oep {
	//Application 클래스 - 게임 플레이에 필요한 로직을 총괄하여 관리하는 클래스
	//결국 게임에 필요한 모든 동작은 이 클래스의 멤버 함수들을 통해 이루어지게 된다.
	class Application
	{
	public:
		//C나 C++은 이렇게 헤더 파일에 함수의 선언을 cpp파일에 함수의 정의를 나누어 주는 것이 좋다.
		Application();  //생성자

		void Initialize(HWND hwnd);  //초기화
		void Run();  //게임에 필요한 모든 기능을 모아서 메인에서 동작하도록 통합해놓은 함수
		void Update();  //업데이트 - 매 프레임마다 진행되는 게임 동작과 이로 인한 변화를 업데이트 해주는 함수
		void LateUpdate();  //업데이트 함수의 내용을 분할해주는 함수(업데이트 후 업데이트할 내용이 이 함수에 추가)
		void Render();  //렌더 - 화면을 그려주는 함수

		~Application();  //소멸자

	private:
		//이 두 변수는 주소값(포인터)이다.
		HWND mHwnd;  //핸들을 저장 - 필요할 때마다 따로 불러올 필요없이 클래스 멤버로 선언하여 사용하면 간편
		HDC mHdc;  //매번 DC를 가져오지 말고 저장하고 사용

		float mSpeed;  //화면에 출력한 도형을 이동시켜 보는 테스트를 위한 변수

		//도형 이동을 테스트하기 위한 변수
		float mX;
		float mY;
	};
}
