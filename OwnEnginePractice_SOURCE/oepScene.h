#pragma once
#include "oepEntity.h"
#include "oepGameObject.h"  
#include "oepLayer.h"

namespace oep {
	class Scene : public Entity
	{
	public:
		Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		virtual void OnEnter();  
		virtual void OnExit();  


		void AddGameObject(GameObject* gameObj, const enums::eLayerType type);  

		Layer* GetLayer(const enums::eLayerType type) {
			return mLayers[(UINT)type];
		}

		~Scene();

	private:
		void createLayers();
		
	private:
		std::vector<Layer*> mLayers;  
	};
}
