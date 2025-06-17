#pragma once
#include "CommonInclude.h"
#include "oepComponent.h"
//#include "oepObject.h"

//위와 같이 oepObject.h 파일을 참조하지 않고 따로 네임 스페이스에다가 선언만 하는 이유는 이미 해당 파일이 이 클래스가 들어있는 파일을 참조하고 있기 때문에 순환 참조가 
//발생하는 것을 막고 아래와 같이 클래스 내에 friend 선언을 할 수 있도록 하기 위해서이다.
namespace oep::object {
	//static 아니면 오류가 발생한다.(이유는 모르겠다.)
	static void Destroy(GameObject* gameObj);
}

namespace oep {
	class GameObject
	{
	public:
		//friend선언은 해당 클래스 외부의 함수나 객체 등이 해당 클래스 내부의 private 멤버까지도 직접 접근이 가능하다고 선언하는 것이다.
		//그러면 아래의 함수는 이제 이 클래스의 private 멤버까지 직접 접근이 가능한데 이 경우 객체지향의 캡슐화가 무너지기 때문에 정말 필요한 경우 제외 남용하지 않아야 한다.
		friend void object::Destroy(GameObject* gameObj);

		enum class eState {
			Active,  //오브젝트 활성화 상태
			Paused,  //오브젝트 비활성화 상태(또 사용할 수 있도록 지우지는 않는 상태)
			Dead,  //오브젝트 비활성화 상태(삭제 대상)
			End,
		};

		GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent() {
			T* comp = new T();
			comp->SetOwner(this);

			mComponents[(UINT)comp->GetType()] = comp;  //이제 puch_back 대신 지정된 위치의 원소에 삽입
			//mComponents.push_back(comp);

			return comp;
		}

		template <typename T>
		T* GetComponent() {
			T* comp = nullptr;
			for (Component* component : mComponents) {
				comp = dynamic_cast<T*>(component); 
				if (comp) {  
					break;
				}
			}

			return comp;
		}

		eState GetState() {
			return mState;
		}

		void SetActive(bool power) {
			//오브젝트의 활성화할 것인지를 인자로 받아 true이면 Active상태로 false라면 Paused상태로 변경 
			if (power == true) {
				mState = eState::Active;
			}
			if (power == false) {
				mState = eState::Paused;
			}
		}

		bool IsActive() {
			return mState == eState::Active;
		}
		//void Death() {  //오브젝트의 상태를 Dead로 바꾸는 함수
		//	mState = eState::Dead;
		//}

		~GameObject();

	private:
		void initializeTransform();
		void death() {  //오브젝트의 상태를 Dead로 바꾸는 함수
			mState = eState::Dead;
		}

	private:
		std::vector<Component*> mComponents;
		eState mState;  //오브젝트의 상태
	};
}
