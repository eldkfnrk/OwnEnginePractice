#pragma once
#include "CommonInclude.h"  

namespace oep {
	class Time
	{ 
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static float DeltaTime() {  //DeltaTime�� ��ȯ�ϴ� �Լ�(DeltaTime�� ���� ������ �Ұ��ϴ� ���� ������ �����ϵ��� ����)
			return DeltaTimeValue;
		}

	private:
		static LARGE_INTEGER CpuFrequency;  //�ش� ��ǻ�� CPU�� ���� �������� ����
		static LARGE_INTEGER PrevFrequency;  //���� ������(�ٷ� ���� ���������� ������)
		static LARGE_INTEGER CurrentFrequency;  //���� ������(���� ������ ������)
		static float DeltaTimeValue;  //�ش� ��ǻ���� DeltaTime(1������ �� �����ϴ� �ð�)
	};
}
