#pragma once
#include "CommonInclude.h"  

namespace oep {
	class Time
	{ 
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static float DeltaTime() {  //DeltaTime을 반환하는 함수(DeltaTime에 직접 접근은 불가하니 간접 접근이 가능하도록 구현)
			return DeltaTimeValue;
		}

	private:
		static LARGE_INTEGER CpuFrequency;  //해당 컴퓨터 CPU의 고유 진동수를 저장
		static LARGE_INTEGER PrevFrequency;  //이전 진동수(바로 이전 루프까지의 진동수)
		static LARGE_INTEGER CurrentFrequency;  //현재 진동수(현재 루프의 진동수)
		static float DeltaTimeValue;  //해당 컴퓨터의 DeltaTime(1프레임 당 실행하는 시간)
	};
}
