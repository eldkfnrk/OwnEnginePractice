#pragma once
#include "oepComponent.h"

namespace oep {
	//Collider Ŭ���� - ������Ʈ�� ���� �浹 ó���� ���� Ŭ����
	//���� ������ ���÷� ���� ���� ������ �ϰ� ������ ������ �������� �޾� ü���� �پ��� ���� �� �� �ִµ� �̶� �� Ÿ�� ������ ���� �ʿ��� ���� �ٷ� 
	//���� �浹�� ó���ϴ� Collider Ŭ������ ���̴�.
	//�� Collider�� ���̵��� �ϸ� ������ �����ϱ� �������� �׷��� �Ǹ� ȭ���� Collider�� ���� ���������� ��Ȯ�� �ð� ���� ������ ������ ���� �ֱ� ������
	//�����δ� �츮 ���� �� ���̵��� ����� �ǰ� Collider�� �ݵ�� ������Ʈ�� ������ ����� �� �ʿ���� �뷫���� �ٻ�ġ ���·� ������ִ°� ȿ�����̴�.
	//�ֳ��ϸ�, �浹ü�� ���� ������ ������Ʈ�� ������ ����� ������ �׸� �� ������ ����ϰ� �����ǵ��� �� ���� ������ �� �����ؼ� ������ ���� �� �ֱ� �����̴�.
	class Collider : public Component
	{
	public:
		Collider();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetOffset(Vector2 offset) {
			mOffset = offset;
		}

		Vector2 GetOffset() {
			return mOffset;
		}

		~Collider();

	private:
		Vector2 mOffset;  //��� �浹ü�� offset�� ������.(offset = ������Ʈ�� ������)
	};
}
