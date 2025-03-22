#pragma once
#include "CommonInclude.h"
#include "oepComponent.h"

namespace oep {
	class GameObject
	{
	public:
		GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent() {
			T* comp = new T();
			comp->SetOwner(this);
			mComponents.push_back(comp);

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

		~GameObject();

	private:
		void initializeTransform();

	private:
		std::vector<Component*> mComponents;
	};
}
