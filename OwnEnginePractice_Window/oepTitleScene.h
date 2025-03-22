#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScene.h"

namespace oep {
	class TitleScene : public Scene
	{
	public:
		TitleScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

		~TitleScene();

	private:

	};
}
