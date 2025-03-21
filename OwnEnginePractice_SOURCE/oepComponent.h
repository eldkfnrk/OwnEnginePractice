#pragma once
#include "oepEntity.h"

namespace oep {
	class GameObject;  

	class Component : public Entity
	{
	public:
		Component();

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

		~Component();

	private:
		GameObject* mOwner;
	};
}
