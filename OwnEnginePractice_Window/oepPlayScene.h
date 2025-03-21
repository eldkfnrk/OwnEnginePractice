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

		~PlayScene();

	private:

	};
}