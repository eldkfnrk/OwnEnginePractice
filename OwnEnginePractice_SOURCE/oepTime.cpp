#include "oepTime.h"

namespace oep {
	//정적 멤버 변수이기 때문에 반드시 cpp파일에서 초기화(정적 멤버 변수는 구조체 외에서 초기화를 시켜주어야 하는데 헤더 파일에서 해도 괜찮지만 선언과 정의의 분리를 확실히 하기 위해 cpp파일에 한다.)
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;

	void Time::Initialize()
	{
		//CPU의 고유 진동수를 구하는 함수
		//인자로는 LARGE_INTEGER 구조체의 포인터(주소 값)를 받는다. 
		//call-by-reference로 인해 내부에서 매개 변수의 값이 변하면 해당 인자로 넘어간 변수의 값도 변하기 때문에 인자로 들어간 변수에 고유 진동수 값이 저장
		QueryPerformanceFrequency(&CpuFrequency);

		//컴퓨터가 시작하고 현재까지의 진동수를 구하는 함수
		//인자로는 위의 함수와 똑같이 LARGE_INTEGER 구조체의 포인터(주소 값)를 받는다.
		//초기화 과정에서는 PrevFrequency 변수에 저장하는 이유는 우리가 구해야 할 것은 Application의 Update 한 루프를 돌 때의 시간을 구하는 것이지만 초기화 과정에서는 Update함수를 돌기 전이기도 하고 
		//초기화는 프로그램이 시작하자마자 이루어지기 때문에 당시의 진동수를 구하기 때문에 프로그램이 시작한 시기의 진동수이기 때문에 최초의 진동수인 것이다. 그래서 이와 같이 PrevFrequency 변수에 저장한다.
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		//현재 진동수를 저장
		QueryPerformanceCounter(&CurrentFrequency);

		//1프레임 동안의 진동수(현재 진동수에서 이전까지의 진동수를 빼면 구할 수 있다.)
		//QuadPart는 저장된 값을 8바이트 전부 사용하겠다는 의미로 LowPart는 앞의 4바이트 HighPart는 뒤의 4바이트를 사용하겠다는 의미
		//static_cast는 C++ 방식의 형 변환으로 float는 4바이트인데 LARGE_INTEGER는 8바이트이기 때문에 크기가 안 맞기 때문에 문제가 생길 수 있어서 알맞게 형 변환을 시켜주어야 한다.
		float differenceFrequency = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);

		//DeltaTime은 한 프레임 동안의 진동수에 CPU 고유 진동수를 나누어서 구한다.(이번에는 float와 LARGE_INTEGER 구조체 간의 연산이었기 때문에 또 알맞게 형 변환을 해주어야 한다.)
		DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);

		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;  //현재 진동수는 이 함수를 벗어나면 이전까지의 진동수가 되기에 CurrentFrequency의 값을 PrevFrequency에 전달(8바이트 그대로 전달)
	}

	void Time::Render(HDC hdc)
	{
		static float time = 0.0f;  //한 번만 초기화하면 되기 때문에 정적 변수로 선언

		time += DeltaTimeValue;  //프레임마다 계속 DeltaTime을 더해주면 프로그램을 실행한 시간을 알 수 있다.

		//wchar_t -> 확장형 문자라는 뜻으로 ASCII코드가 아닌 UNICODE를 사용한다. 그래서 2바이트 크기를 갖는다.
		wchar_t time_str[50] = L"";  //""앞에 L은 이 문자열이 UNICODE(2바이트)임을 알려주는 장치(무조건 L만 가능)
		swprintf_s(time_str, 50, L"Time : %f", time);  //%f는 C언어의 출력 형식으로 이를 빌려와서 문자열을 만들고 이를 첫 번째 인자로 들어온 문자형 배열에 저장
		int time_len = wcsnlen_s(time_str, 50);

		float fps = 1.0f / DeltaTimeValue;

		wchar_t fps_str[50] = L"";  //""앞에 L은 이 문자열이 UNICODE(2바이트)임을 알려주는 장치(무조건 L만 가능)
		swprintf_s(fps_str, 50, L"Time : %.2f", fps);  //%f는 C언어의 출력 형식으로 이를 빌려와서 문자열을 만들고 이를 첫 번째 인자로 들어온 문자형 배열에 저장
		int fps_len = wcsnlen_s(fps_str, 50);

		//std::wcstoul  //C++은 wcout을 사용하는데 이 경우 2바이트짜리 변수를 사용하려면 해당 변수의 문자가 어느 나라의 2바이트 문자인지를 미리 정해주어야 한다.

		TextOut(hdc, 0, 0, time_str, time_len);  //(0,0) 위치에 4번째 인자로 들어온 문자열을 5번쨰 인자로 들어온 정수만큼의 길이로 화면에 출력해주는 함수
		TextOut(hdc, 0, 15, fps_str, fps_len);
	}
}