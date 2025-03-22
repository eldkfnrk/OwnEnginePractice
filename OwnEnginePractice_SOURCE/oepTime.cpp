#include "oepTime.h"

namespace oep {
	//���� ��� �����̱� ������ �ݵ�� cpp���Ͽ��� �ʱ�ȭ(���� ��� ������ ����ü �ܿ��� �ʱ�ȭ�� �����־�� �ϴµ� ��� ���Ͽ��� �ص� �������� ����� ������ �и��� Ȯ���� �ϱ� ���� cpp���Ͽ� �Ѵ�.)
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;

	void Time::Initialize()
	{
		QueryPerformanceFrequency(&CpuFrequency);  //CPU�� ���� ������

		QueryPerformanceCounter(&PrevFrequency);  //���� �ĺ��� ���� ���� �ñ����� CPU ������
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency);  //��������� CPU �������� ����

		float differenceFrequency = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);  //1������ ������ ������

		//DeltaTime�� �� ������ ������ �������� CPU ���� �������� ����� ���Ѵ�.
		DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);

		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;  //���� �������� �� �Լ��� ����� ���������� �������� �Ǳ⿡ CurrentFrequency�� ���� PrevFrequency�� ����
	}

	void Time::Render(HDC hdc)
	{
		//������ ���� ȭ�鿡 ������� �ʾƵ� �Ǳ⿡ ����(�ʿ��ϸ� ���� UI�� ����� �װ��� ǥ�⸦ ��ų ����)
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