#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScript.h"

namespace oep {
	//�� Ŭ������ ��ũ��Ʈ ������Ʈ�ε� �÷��̾ ������ ������ ������Ʈ�� �� ������Ʈ���� ������ �ٸ��� ������ ��ũ��Ʈ ������Ʈ�� ���� ���� �����Ѵ�.
	class PlayerScript : public Script
	{
	public:
		PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~PlayerScript();

	private:

	};
}
