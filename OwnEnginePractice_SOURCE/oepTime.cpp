#include "oepTime.h"

namespace oep {
	//정적 멤버 변수이기 때문에 반드시 cpp파일에서 초기화(정적 멤버 변수는 구조체 외에서 초기화를 시켜주어야 하는데 헤더 파일에서 해도 괜찮지만 선언과 정의의 분리를 확실히 하기 위해 cpp파일에 한다.)
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;

	void Time::Initialize()
	{
		QueryPerformanceFrequency(&CpuFrequency);  //CPU의 고유 진동수

		QueryPerformanceCounter(&PrevFrequency);  //부팅 후부터 게임 시작 시까지의 CPU 진동수
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency);  //현재까지의 CPU 진동수를 저장

		float differenceFrequency = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);  //1프레임 동안의 진동수

		//DeltaTime은 한 프레임 동안의 진동수에 CPU 고유 진동수를 나누어서 구한다.
		DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);

		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;  //현재 진동수는 이 함수를 벗어나면 이전까지의 진동수가 되기에 CurrentFrequency의 값을 PrevFrequency에 전달
	}

	void Time::Render(HDC hdc)
	{
		//이제는 굳이 화면에 출력하지 않아도 되기에 삭제(필요하면 따로 UI를 만들어 그곳에 표기를 시킬 예정)
		//static float time = 0.0f;  

		//time += DeltaTimeValue;  

		//wchar_t time_str[50] = L"";  
		//swprintf_s(time_str, 50, L"Time : %f", time);  
		//int time_len = wcsnlen_s(time_str, 50);

		//float fps = 1.0f / DeltaTimeValue;

		//wchar_t fps_str[50] = L""; 
		//swprintf_s(fps_str, 50, L"Time : %.2f", fps);  
		//int fps_len = wcsnlen_s(fps_str, 50);

		//TextOut(hdc, 0, 0, time_str, time_len);  
		//TextOut(hdc, 0, 15, fps_str, fps_len);
	}
}