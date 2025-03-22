#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScene.h"

namespace oep {
	class PlayScene : public Scene
	{
	public:
		PlayScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

		~PlayScene();

	private:
		class Player* bg;  //Player 클래스를 모르기 때문에 전방 선언(전방 선언은 순환 참조를 방지하기 위해서만 사용하는 것이 아닌 이렇게 클래스를 모르는 경우에 사용해도 된다.)
	};
}