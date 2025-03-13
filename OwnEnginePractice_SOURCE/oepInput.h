#pragma once
#include "CommonInclude.h"

namespace oep {
	//엔진을 직접 제작한 제작자는 그냥 int형 변수의 숫자 값을 넣었을 때 어떤 상태인지를 알 수 있지만 만약 다른 사람이 코드를 보면 이게 무엇을 의미하는 것인지 모를 수 밖에 없는데
	//그럴 때 열거형을 사용하여 정수에 이름을 붙이면 제작자 이외의 사람이 봐도 쉽게 이해할 수 있게 될 것이다. 이렇게 조금이라도 알아보기 쉽게 코드를 작성하는 것이 좋다.
	enum class eKeyState {  //enum class는 열거형을 만들 때 동일한 이름을 사용할 경우가 있을 수 있는데 이를 구분하기 위한 것으로 열거형의 네임스페이스라고 보면 된다.
		Down,  //누를 때
		Pressed,  //누르고 있을 때
		Up,  //뗄 때
		None,  //아무것도 안 할 때
	};

	enum class eKeyCode {  //우선 영어 키에 대응하도록만 설정
		Q,W,E,R,T,Y,U,I,O,P,
		A,S,D,F,G,H,J,K,L,
		Z,X,C,V,B,N,M,
		End,
	};

	//Input 클래스 - 키 입력에 관한 것을 모아놓기 위한 클래스
	class Input
	{
	public:
		struct Key  //키에 대한 구조체(어떤 키에 대하여 어떤 상태로 눌려있는지에 대한 정보를 저장)
		{
			//char keyCode;  //키보드의 어떤 키인지 저장하는 변수
			//위처럼 char형 변수를 사용하면 대소문자를 구분해주어야 하기 때문에 그냥 열거형을 사용하여 숫자를 이용해 어떤 키인지 저장
			eKeyCode keycode;  //키보드의 어떤 키인지만 알면 되기에 각 키에 대응하는 숫자인지만 확인하면 돼서 열거형을 사용	
			eKeyState state;  //키의 상태
			bool bPressed;  //키가 눌려있는지를 확인하기 위한 변수
		};

		static void Initialize();  //초기화
		static void Update();  //매 프레임마다 키의 상태를 확인해주기 위한 업데이트

		//키의 상태를 확인하기 위한 정적 멤버 함수(정적 멤버 변수가 private멤버이기 때문에 외부에서 접근이 불가능하여 외부에서 상태를 보기 위한 간접 접근을 하게 해주는 함수들)
		static bool GetKeyDown(eKeyCode code) { //down
			return mKeys[(UINT)code].state == eKeyState::Down;
		}

		static bool GetKeyUp(eKeyCode code) {  //up
			return mKeys[(UINT)code].state == eKeyState::Up;
		}

		static bool GetKey(eKeyCode code) {  //pressed
			return mKeys[(UINT)code].state == eKeyState::Pressed;
		}

	private:
		//키의 상태는 크게 3가지로 분류할 수 있다.
		//누를 때(Down), 누르고 있을 때(Pressed), 뗄 때(Up) 
		//int mState;
		//eKeyState mState;  //키의 상태를 나타내는 변수

		//그러나 키는 하나가 아닌 여러 개이기 때문에 모든 키의 상태를 저장하기 위해서 배열을 사용하여 키의 상태를 저장하여야 한다.
		//어떤 키가 어떤 상태인지를 알기 위해 저장하는 것이니 해당 정보를 가지고 있는 구조체 Key의 배열을 만들어 저장하면 된다.
		//정적 멤버로 선언한 이유는 여러 클래스에서 전역 변수처럼 사용하고 싶은데 그냥 전역 변수로 만들면 문제가 될 수 있으니 클래스 내에서 전역 변수처럼 사용하기 위해서 정적 멤버로 선언하여 사용하는 것이다.
		static std::vector<Key> mKeys;  //벡터 사용
	};
}
