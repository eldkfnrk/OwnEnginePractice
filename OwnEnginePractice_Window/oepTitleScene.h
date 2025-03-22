#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScene.h"

namespace oep {
	//TitleScene Ŭ���� - ������ Ÿ��Ʋ ��
	class TitleScene : public Scene
	{
	public:
		//PlayScene�� �⺻ ����� ���� ���̰� ����.(�� �ȿ��� �����ϴ� ����� ���̸� �ִ� ���̴�.)
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
