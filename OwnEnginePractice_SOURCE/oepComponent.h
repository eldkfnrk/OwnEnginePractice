#pragma once
#include "oepEntity.h"

namespace oep {
	class GameObject;  

	class Component : public Entity
	{
	public:
		Component(enums::eComponentType type);

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetOwner(GameObject* owner) {
			mOwner = owner;
		}

		GameObject* GetOwner() {
			return mOwner;
		}

		enums::eComponentType GetType() {
			return mType;
		}	

		~Component();

	private:
		GameObject* mOwner;
		enums::eComponentType mType;  //컴포넌트 타입을 저장(컴포넌트를 벡터에 저장할 때 컴포넌트 순서를 맞추기 위해서 이를 저장)
	};
}
