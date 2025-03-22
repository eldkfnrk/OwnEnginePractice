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

		//게임은 플레이 중 씬 간의 이동이 있게 되는데 그 경우 원래 씬에서 다른 씬으로 변경될 때 원래 씬에서 필요한 동작이 있을 것이고 씬이 바뀌면서 바뀐 씬에서 선행으로 이루어져야 할 동작이 있을 것이기에
		//이것들은 각 씬마다 반드시 있어야 하기 때문에 Scene 클래스에서 가상 함수로 가지고 있어야 한다.
		virtual void OnEnter();  //씬에 입장할 때 해당 씬에서 필요한 동작을 모아놓은 함수(이 함수는 바뀌기 전 씬에서 호출되어서 선행된 후 바뀐 씬으로 이동하여야 한다.)
		virtual void OnExit();  //씬을 탈출할 때 해당 씬에서 필요한 동작을 모아놓은 함수

		//void AddGameObject(GameObject* gameObj);  //레이어에서도 이 동작을 하고 이 클래스에서도 이 동작을 하지만 약간의 차이가 있다. 그것은 아래의 함수로 정의

		void AddGameObject(GameObject* gameObj, const eLayerType type);  //씬에서 게임 오브젝트를 추가할 때는 이 게임 오브젝트의 레이어가 어딘지까지 알아야 한다.

		~Scene();
		
	private:
		//std::vector<GameObject*> mGameObjects;  //이 구문은 레이어 클래스로 이동
		//지금까지는 씬에서 씬을 구성하는 게임 오브젝트들을 관리했지만 이제는 레이어를 추가해서 게임 오브젝트는 알맞는 레이어에 배치가 되게 될테니 씬에서는 레이어를 관리하고 각 레이어는 배치된 오브젝트들을
		//관리하면 되니 씬은 레이어들을 각 레이어는 알맞는 오브젝트들을 관리하면 된다. 그러니 지금까지 씬에서 하던 것들을 레이어에서 하면 된다.

		std::vector<Layer*> mLayers;  //이렇게 되면 레이어 배열 안에 원소로 게임 오브젝트 배열을 가지고 있는 모양이 되어 2차원 배열의 형태를 띄게 된다.
	};
}
