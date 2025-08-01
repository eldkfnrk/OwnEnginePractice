#pragma once
#include "oepEntity.h"
#include "CommonInclude.h"
#include "oepGameObject.h"

namespace oep {
	class Layer
	{
	public:
		Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		
		virtual void Destroy();

		void AddGameObject(GameObject* gameObj);

		const std::vector<GameObject*> GetGameObjects() {  //값이 변하지 않고 그대로 반환해야 하기 때문에 const 사용
			return mGameObjects;
		}

		~Layer();

	private:
		void findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs);
		void deleteGameObjects(std::vector<GameObject*> deleteObjs);

	private:
		std::vector<GameObject*> mGameObjects;  //각 레이어에 배치된 게임 오브젝트들 저장하는 벡터
	};

	//typedef를 복습해보자면 이 키워드는 자료형에 별명을 붙여주는 것으로 자료형 이름이 길 때 이를 줄여서 사용하는 용도로 많이 사용
	typedef std::vector<GameObject*>::iterator GameObjectIter;
}
