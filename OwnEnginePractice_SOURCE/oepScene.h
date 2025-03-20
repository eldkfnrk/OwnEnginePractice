#pragma once
#include "oepEntity.h"
#include "oepGameObject.h"

namespace oep {
	//Scene 클래스 - 게임의 씬을 구성을 잡아주는 클래스(이 클래스를 상속받아서 각 씬을 만들어 나간다.)
	//씬이라는 것은 영화에서 하나의 장면을 의미하는데 영화는 이런 씬을 여러 개 찍어서 이어붙여서 만들어진다. 게임도 이와 마찬가지로 여러 씬들이 있고 이를 유기적으로 연결해서 플레이할 수 있게
	//만들어진다. 예를 들어 처음 게임에 접속하면 보이는 로비 화면도 하나의 씬이고 플레이를 위해 게임에 들어가는 동안 보이는 로딩 화면도 하나의 씬이고 실제로 플레이가 가능한 화면도 하나의 씬이다.
	//이렇게 여러 개의 씬을 만들고 이를 유기적으로 연결해 이동시킬 수 있도록 만들어야 하나의 게임이 만들어지는 것이다.(예시 - 롤의 실제 플레이 화면과 로비 화면, 로딩 화면, 캐릭터 선택 화면)
	//Scene 클래스는 이런 여러 씬들을 만들 때 사용되는 기본적인 형태를 가지고 있으며 각 씬들은 이 형태를 따라서 게임에 알맞게 만들어져 사용되는 것이다.(유니티는 씬 언리얼은 레벨이라 부른다.)
	class Scene : public Entity
	{
	public:
		Scene();

		//이 클래스는 상속을 해주는 클래스이기 때문에 이를 사용하여 생성되는 씬들은 이 함수들을 재정의하여 알맞게 수정을 할 수 있도록 해주어야 한다.
		//그렇게 하기 위해서는 함수들이 가상 함수로 선언되어야 하기 때문에 앞에 virtual을 붙여 가상 함수로 선언해준다.(재정의가 필요하지 않은 함수는 virtual을 사용하지 않아도 된다.)
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		//자식 클래스가 private 멤버인 게임 오브젝트 트리에 직접 게임 오브젝트를 추가할 수 없으니 간접적으로 추가할 수 있도록 함수 생성
		void AddGameObject(GameObject* gameObj);

		~Scene();
		
	private:
		std::vector<GameObject*> mGameObjects;
	};
}
