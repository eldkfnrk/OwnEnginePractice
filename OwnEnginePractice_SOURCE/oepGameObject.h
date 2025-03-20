#pragma once
#include "CommonInclude.h"
#include "oepComponent.h"

namespace oep {
	//게임 오브젝트란 씬에 배치할 수 있는 오브젝트를 말한다. 게임 오브젝트는 이동, 회전, 스케일과 같은 트랜스 폼을 지원하는 범용 클래스인 것이다.
	//즉, 화면 상에 존재하는 UI, 몬스터, 플레이어 등등이 모두 씬을 구성하는 단위라고 생각하면 된다.

	class GameObject
	{
	public:
		GameObject();

		//void Update();
		//void LateUpdate();
		//void Render(HDC hdc);

		//게임 오브젝트도 많은 종류가 있기 때문에 이 클래스를 기반으로 파생되는 여러 종류의 오브젝트들에 대응하기 위해 가상 함수로 만들고 알아서 재정의하도록 설정
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		//void SetPosition(float x, float y) {
		//	mX = x;
		//	mY = y;
		//}

		//게임 오브젝트에 컴포넌트를 추가하는 함수(컴포넌트의 자료형이 각 클래스일 것이기 때문에 모두 대응하기 위해 템플릿 함수로 작성)
		template <typename T>
		T* AddComponent() {
			T* comp = new T();
			comp->SetOwner(this);
			mComponents.push_back(comp);

			return comp;
		}

		//게임 오브젝트가 가지고 있는 컴포넌트들을 가져오는 함수(컴포넌트의 자료형이 각 클래스일 것이기 때문에 모두 대응하기 위해 템플릿 함수로 작성)
		template <typename T>
		T* GetComponent() {
			T* comp = nullptr;
			for (Component* component : mComponents) {
				comp = dynamic_cast<T*>(component);  //dynamic_cast는 형 변환의 방법 중 하나로 기본 클래스에 대한 포인터나 참조가 있고 이를 파생 클래스로 변환하려는 경우 주로 사용되는 방법이다.
				//해당 타입에 맞다면 해당 타입으로 형 변환한 객체 주소 값을 반환하고 아니라면 nullptr을 반환해준다.
				//만약에 T에 대응하는 컴포넌트 클래스 자료형이 아닌 다른 컴포넌트 클래스 자료형의 객체가 형 dynamic_cast로 형 변환을 시도하면 dynamic_cast는 nullptr을 반환한다.
				if (comp) {  //comp가 nullptr인 경우 if문에 걸리게 된다.(즉, 원하는 자료형의 컴포넌트가 아니면 for문을 탈출하도록 설정) 
					break;
				}
			}

			return comp;
		}

		~GameObject();

	private:
		//게임 오브젝트의 좌표
		//float mX;
		//float mY;

		//위의 게임 오브젝트의 좌표는 이제 게임 오브젝트가 관리하는 것이 아닌 Transform 컴포넌트가 관리하게 될 것이다.
		std::vector<Component*> mComponents;
	};
}
