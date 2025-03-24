#pragma once
#include "oepEntity.h"
#include "CommonInclude.h"

namespace oep {
	//Resource 클래스 - 게임의 리소스들의 기본 골격을 하는 클래스
	//리소스란 게임에서 사용되는 데이터를 의미하는데 이때 리소스의 종류에는 이미지, 사운드 등이 있다.
	//게임의 플레이 데이터를 저장해놓은 HDD나 클라우드 등도 리소스 중 하나이다.
	class Resource : public Entity  //추상 클래스(순수 가상 함수가 하나라도 포함되면 추상 클래스가 된다.)
	{
	public:
		Resource(enums::eResourceType type);  //반드시 리소스의 타입을 알아야 하기 때문에 생성자 호출 시 리소스 타입을 전달하라고 매개 변수를 추가

		//이 문법은 순수 가상 함수라는 것으로 가상 함수를 선언할 때 =0을 붙여주면 순수 가상 함수라는 의미이다.
		//순수 가상 함수를 사용하는 이유는 해당 함수가 포함된 클래스를 추상 클래스로 만들기 위해 사용한다.
		//추상 클래스란 우리가 이 클래스를 이 자체로 메모리 영역에 할당이 일이 없는 경우 이 클래스로 객체 할당 자체가 안 되도록 막은 클래스를 의미한다.
		//이를 사용하는 이유는 이 클래스의 객체는 실제 메모리에 할당이 불가능하도록 만듦으로써 이 클래스 안에 있는 것들은 무조건 상속받아서 사용하도록 만들기 위해서이다.
		//그리고 순수 가상 함수는 상속받은 자식 클래스가 반드시 재정의를 해주어야 한다. 그 의미는 이 함수의 정의는 따로 없어야 한다는 의미이다.
		//HRESULT 자료형은 기본 자료형 bool과 비슷한 자료형으로 윈도우 API에 정의된 자료형이다.
		//이를 사용하는 이유는 윈도우 자체에서 편리하게 사용하기 위해서 따로 정의한 것이기 때문에 윈도우 프로그래밍을 하는 경우 이를 사용하는 것이 더 편하다.
		virtual HRESULT Load(const std::wstring& path) = 0;  //순수 가상 함수

		void SetPath(const std::wstring& path) {
			mPath = path;
		}

		const std::wstring& GetPath() {
			return mPath;
		}

		virtual ~Resource();

	private:
		//리소스가 무슨 종류의 리소스인지를 알기 위한 열거형 타입 변수
		const enums::eResourceType mType;
		std::wstring mPath;  //리소스의 경로를 저장할 변수
	};
}
