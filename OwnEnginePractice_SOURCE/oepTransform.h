#pragma once
#include "oepComponent.h"

namespace oep {
	using namespace math;  

	class Transform : public Component
	{
	public:
		Transform();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetPosition(Vector2 pos) {
			mPosition.x = pos.x;
			mPosition.y = pos.y;
		}

		Vector2 GetPosition() {
			return mPosition;
		}

		void SetRotation(float rotation) {
			mRotation = rotation;
		}

		float GetRotation() {
			return mRotation;
		}
		
		void SetScale(Vector2 scale) {
			mScale.x = scale.x;
			mScale.y = scale.y;
		}

		Vector2 GetScale() {
			return mScale;
		}

		~Transform();

	private:
		//Transform ������Ʈ�� �������� ������Ʈ�� ��ġ ���� �Ӹ� �ƴ϶� ������Ʈ�� ũ��� �������� ��� ���ӹ޾� �����ϵ��� ����
		Vector2 mPosition;  
		Vector2 mScale;  //�� ������Ʈ�� ������ �ִ� ������Ʈ�� ũ��
		float mRotation;  //������Ʈ�� ����(ȸ��)
	};
}
