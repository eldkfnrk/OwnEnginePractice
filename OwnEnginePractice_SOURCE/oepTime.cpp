#include "oepTime.h"

namespace oep {
	//���� ��� �����̱� ������ �ݵ�� cpp���Ͽ��� �ʱ�ȭ(���� ��� ������ ����ü �ܿ��� �ʱ�ȭ�� �����־�� �ϴµ� ��� ���Ͽ��� �ص� �������� ����� ������ �и��� Ȯ���� �ϱ� ���� cpp���Ͽ� �Ѵ�.)
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;

	void Time::Initialize()
	{
		//CPU�� ���� �������� ���ϴ� �Լ�
		//���ڷδ� LARGE_INTEGER ����ü�� ������(�ּ� ��)�� �޴´�. 
		//call-by-reference�� ���� ���ο��� �Ű� ������ ���� ���ϸ� �ش� ���ڷ� �Ѿ ������ ���� ���ϱ� ������ ���ڷ� �� ������ ���� ������ ���� ����
		QueryPerformanceFrequency(&CpuFrequency);

		//��ǻ�Ͱ� �����ϰ� ��������� �������� ���ϴ� �Լ�
		//���ڷδ� ���� �Լ��� �Ȱ��� LARGE_INTEGER ����ü�� ������(�ּ� ��)�� �޴´�.
		//�ʱ�ȭ ���������� PrevFrequency ������ �����ϴ� ������ �츮�� ���ؾ� �� ���� Application�� Update �� ������ �� ���� �ð��� ���ϴ� �������� �ʱ�ȭ ���������� Update�Լ��� ���� ���̱⵵ �ϰ� 
		//�ʱ�ȭ�� ���α׷��� �������ڸ��� �̷������ ������ ����� �������� ���ϱ� ������ ���α׷��� ������ �ñ��� �������̱� ������ ������ �������� ���̴�. �׷��� �̿� ���� PrevFrequency ������ �����Ѵ�.
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		//���� �������� ����
		QueryPerformanceCounter(&CurrentFrequency);

		//1������ ������ ������(���� ���������� ���������� �������� ���� ���� �� �ִ�.)
		//QuadPart�� ����� ���� 8����Ʈ ���� ����ϰڴٴ� �ǹ̷� LowPart�� ���� 4����Ʈ HighPart�� ���� 4����Ʈ�� ����ϰڴٴ� �ǹ�
		//static_cast�� C++ ����� �� ��ȯ���� float�� 4����Ʈ�ε� LARGE_INTEGER�� 8����Ʈ�̱� ������ ũ�Ⱑ �� �±� ������ ������ ���� �� �־ �˸°� �� ��ȯ�� �����־�� �Ѵ�.
		float differenceFrequency = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);

		//DeltaTime�� �� ������ ������ �������� CPU ���� �������� ����� ���Ѵ�.(�̹����� float�� LARGE_INTEGER ����ü ���� �����̾��� ������ �� �˸°� �� ��ȯ�� ���־�� �Ѵ�.)
		DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);

		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;  //���� �������� �� �Լ��� ����� ���������� �������� �Ǳ⿡ CurrentFrequency�� ���� PrevFrequency�� ����(8����Ʈ �״�� ����)
	}

	void Time::Render(HDC hdc)
	{
		static float time = 0.0f;  //�� ���� �ʱ�ȭ�ϸ� �Ǳ� ������ ���� ������ ����

		time += DeltaTimeValue;  //�����Ӹ��� ��� DeltaTime�� �����ָ� ���α׷��� ������ �ð��� �� �� �ִ�.

		//wchar_t -> Ȯ���� ���ڶ�� ������ ASCII�ڵ尡 �ƴ� UNICODE�� ����Ѵ�. �׷��� 2����Ʈ ũ�⸦ ���´�.
		wchar_t time_str[50] = L"";  //""�տ� L�� �� ���ڿ��� UNICODE(2����Ʈ)���� �˷��ִ� ��ġ(������ L�� ����)
		swprintf_s(time_str, 50, L"Time : %f", time);  //%f�� C����� ��� �������� �̸� �����ͼ� ���ڿ��� ����� �̸� ù ��° ���ڷ� ���� ������ �迭�� ����
		int time_len = wcsnlen_s(time_str, 50);

		float fps = 1.0f / DeltaTimeValue;

		wchar_t fps_str[50] = L"";  //""�տ� L�� �� ���ڿ��� UNICODE(2����Ʈ)���� �˷��ִ� ��ġ(������ L�� ����)
		swprintf_s(fps_str, 50, L"Time : %.2f", fps);  //%f�� C����� ��� �������� �̸� �����ͼ� ���ڿ��� ����� �̸� ù ��° ���ڷ� ���� ������ �迭�� ����
		int fps_len = wcsnlen_s(fps_str, 50);

		//std::wcstoul  //C++�� wcout�� ����ϴµ� �� ��� 2����Ʈ¥�� ������ ����Ϸ��� �ش� ������ ���ڰ� ��� ������ 2����Ʈ ���������� �̸� �����־�� �Ѵ�.

		TextOut(hdc, 0, 0, time_str, time_len);  //(0,0) ��ġ�� 4��° ���ڷ� ���� ���ڿ��� 5���� ���ڷ� ���� ������ŭ�� ���̷� ȭ�鿡 ������ִ� �Լ�
		TextOut(hdc, 0, 15, fps_str, fps_len);
	}
}