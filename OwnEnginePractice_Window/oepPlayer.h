#pragma once
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"

namespace oep {
	//Player 클래스 - 플레이어에 해당하는 게임 오브젝트
	class Player : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:

	};
}
