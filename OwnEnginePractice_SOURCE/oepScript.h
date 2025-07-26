#pragma once
#include "oepComponent.h"

namespace oep {
	class Script : public Component
	{
	public:
		Script();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//�� �Լ����� ��ũ��Ʈ�� �ۼ��� �� ����� �޾Ƽ� ����ϸ� �ȴ�.
		virtual void OnCollisionEnter(class Collider* other);  //�� �浹ü�� �� �浹�ؼ� �پ��� �� ȣ���� �Լ�
		virtual void OnCollisionStay(class Collider* other);  //�� �浹ü�� �浹 �� �������� ���� �� ��, ������ ���°� ���ӵǰ� ���� �� ȣ���� �Լ�
		virtual void OnCollisionExit(class Collider* other);  //�� �浹ü�� �浹�ϴٰ� ������ ���������� �� ȣ���� �Լ�(�� �̻� �浹x)

		~Script();

	private:

	};
}
