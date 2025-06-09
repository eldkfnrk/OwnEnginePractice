#pragma once
#include "CommonInclude.h"  

namespace oep {
	class Time
	{ 
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		//자주 사용하는 함수 중 헤더 파일에 정의된 함수들은 inline 명령어를 사용하여 인라인 함수로 만들어 준다.
		//인라인 함수란 컴파일러가 메모리에 별도의 명령어 세트를 작성하지 않고 함수 정의에서 호출 함수의 코드로 직접 코드를 복사하는 함수라는 뜻이다.
		//함수 호출 시 우선 스택에 함수로 전달할 매개변수와 함께 호출이 끝난 뒤 돌아갈 반환 주소값을 저장하고 프로그램의 제어가 함수의 위치로 넘어와 함수 
		//내에 선언된 지역 변수도 스택에 저장 그때부터 함수의 모든 코드를 실행하게 되고, 실행이 전부 끝나면 반환값을 넘겨준다.그 후 프로그램의 제어는 스택에 
		//저장된 돌아갈 반환 주소값으로 이동하여, 스택에 저장된 함수 호출 정보를 제거한다. 그리고 이 과정을 함수 호출마다 반복한다.
		//그렇기 때문에 함수 호출은 약간의 시간이 소요되는데 함수의 실행 시간이 긴 함수는 문제가 되지 않으나 함수의 실행 시간이 짧은 함수는 이 시간마저 부담이
		//될 수 있기 때문에 이 경우 함수를 호출한 위치에 함수의 모든 코드를 바로 삽입하는 인라인 함수를 사용한다.
		//인라인 함수는 호출하는 시간을 절약하지만 함수 호출 과정에서 얻는 이점을 포기하는 것이기에 코드가 적은 함수에만 사용하는 것이 권장된다.
		//그리고 헤더 파일에 정의한 함수들은 코드가 적기 때문에 바로 정의한 것이어서 인라인 함수로 만들어 사용하는 것이 최적화에 도움을 준다.
		//그러나 inline을 사용한다고 무조건 인라인 함수가 되는 것은 아니고 컴파일러가 판단할 때 인라인 함수가 아니라고 판단할 수도 있다.
		//그래서 사용할 수 있는 것이 __forceinline이라는 것으로 이것은 조금 더 컴파일러에게 어필하는 것이다. 그러나 이것도 무조건은 아니다.
		__forceinline static float DeltaTime() {  //DeltaTime을 반환하는 함수(DeltaTime에 직접 접근은 불가하니 간접 접근이 가능하도록 구현)
			return DeltaTimeValue;
		}

	private:
		static LARGE_INTEGER CpuFrequency;  //해당 컴퓨터 CPU의 고유 진동수를 저장
		static LARGE_INTEGER PrevFrequency;  //이전 진동수(바로 이전 루프까지의 진동수)
		static LARGE_INTEGER CurrentFrequency;  //현재 진동수(현재 루프의 진동수)
		static float DeltaTimeValue;  //해당 컴퓨터의 DeltaTime(1프레임 당 실행하는 시간)
	};
}
