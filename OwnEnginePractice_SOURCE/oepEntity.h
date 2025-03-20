#pragma once
#include "CommonInclude.h"

namespace oep {
	//Entity 클래스 - 디버깅 시 각 객체의 구분을 쉽게 하기 위한 기본 정보 클래스
	//지금까지는 디버깅 시 객체의 주소나 객체가 가지고 있는 값을 보고 구분하였는데 주소 값은 거의 유사하고 구분할 수 없는 값을 가지지 않은 객체의 구분이 굉장히 어려웠는데 이를
	//조금이라도 쉽게 구분하기 위해 각 객체에 이름을 부여하는 등의 작업을 해주기 위하여 해당 클래스를 구성해주었다. 그리고 디버깅 시 객체를 구분해야 하는 경우 이 클래스를 상속받아 사용
	class Entity
	{
	public:
		Entity();


		//두 함수 모두 참조형를 쓰는 이유는 참조가 아니면 값이 복사가 되서 넘어가는데 문자열은 배열이기 때문에 길면 시간이 오래 걸려서 그렇다.
		void SetName(const std::wstring& name) {
			mName = name;
		}

		std::wstring& GetName() {
			return mName;
		}

		virtual ~Entity();  //상속 시에는 소멸자도 virtual이 붙어야 한다.

	private:
		//string은 1바이트짜리 문자형 배열, wstring은 2바이트짜리 문자형 배열(2바이트이기 때문에 한글도 저장이 가능)
		std::wstring mName;  //이름
	};
}
