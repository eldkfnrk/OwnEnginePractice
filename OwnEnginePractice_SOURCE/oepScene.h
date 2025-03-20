#pragma once
#include "oepEntity.h"
#include "oepGameObject.h"

namespace oep {
	class Scene : public Entity
	{
	public:
		Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameObj);

		~Scene();
		
	private:
		std::vector<GameObject*> mGameObjects;
	};
}
