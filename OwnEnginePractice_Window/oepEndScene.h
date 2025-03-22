#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScene.h"

namespace oep {
	//EndScene 클래스 - 게임의 마지막 엔딩 씬
	class EndScene : public Scene
	{
	public:
		EndScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

		~EndScene();

	private:

	};
}
