#pragma once
#include "oepCollider.h"

namespace oep {
	class CircleCollider2D : public Collider
	{
	public:
		CircleCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~CircleCollider2D();

	private:
		float mRadius;  //���� �浹ü�� ������(�浹ü ������Ʈ�� ��ǥ�� �߽����� ������ ũ���� ���� �����Ǿ ���� �浹 ó���� �� ����)
	};
}
