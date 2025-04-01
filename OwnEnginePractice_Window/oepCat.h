#pragma once
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"

namespace oep {
	//플레이어가 직접 조작해서 행동하는 것이 아닌 독자적인 행동 방식을 가지도록 설계
	//RPG 게임을 하다보면 직접 조작하는 플레이어가 있고 플레이어를 공격하는 몬스터들이 있는데 몬스터들은 플레이어의 입력이 아닌 각자가 가지고 있는 행동 방식이 있어
	//플레이어가 가까이 오면 공격하고 플레이어의 공격을 맞으면 데미지를 받는 등의 동작을 하는데 이를 어떻게 하는지 설계하는 것을 배워볼 예정
	class Cat : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:

	};
}