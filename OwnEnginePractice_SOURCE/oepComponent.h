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
		enums::eComponentType mType;  //������Ʈ Ÿ���� ����(������Ʈ�� ���Ϳ� ������ �� ������Ʈ ������ ���߱� ���ؼ� �̸� ����)
	};
}
