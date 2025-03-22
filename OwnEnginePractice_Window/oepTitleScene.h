#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScene.h"

namespace oep {
	//TitleScene 클래스 - 게임의 타이틀 씬
	class TitleScene : public Scene
	{
	public:
		//PlayScene과 기본 골격은 거의 차이가 없다.(그 안에서 동작하는 결과의 차이만 있는 것이다.)
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
