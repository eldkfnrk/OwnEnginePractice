#pragma once
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"

namespace oep {
	//�÷��̾ ���� �����ؼ� �ൿ�ϴ� ���� �ƴ� �������� �ൿ ����� �������� ����
	//RPG ������ �ϴٺ��� ���� �����ϴ� �÷��̾ �ְ� �÷��̾ �����ϴ� ���͵��� �ִµ� ���͵��� �÷��̾��� �Է��� �ƴ� ���ڰ� ������ �ִ� �ൿ ����� �־�
	//�÷��̾ ������ ���� �����ϰ� �÷��̾��� ������ ������ �������� �޴� ���� ������ �ϴµ� �̸� ��� �ϴ��� �����ϴ� ���� ����� ����
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