#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScene.h"

namespace oep {
	class PlayScene : public Scene
	{
	public:
		PlayScene();

		//상속받은 클래스의 가상 함수를 override
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~PlayScene();

	private:

	};
}