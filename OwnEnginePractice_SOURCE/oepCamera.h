#pragma once
#include "oepComponent.h"

namespace oep {
	using namespace oep::math;

	class Camera : public Component
	{
	public:
		Camera();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//������Ʈ�� ��ġ ������ ���ڷ� �޾� ī�޶��� �̵� �Ÿ��� ���� ������Ʈ�� ��ġ�� ���ϴ� �Լ�
		Vector2 CalculatePosition(Vector2 pos) {
			return pos - mDistance;
		}

		void SetTarget(GameObject* target) {
			mTarget = target;
		}

		~Camera();

	private:
		class GameObject* mTarget;  

		Vector2 mDistance;  //ī�޶�� ī�޶� ���ߴ� ����� �Ÿ�
		Vector2 mResolution;  //ȭ�� �ػ�
		Vector2 mLookPosition;  //ī�޶� �ٶ󺸴� ��ġ ����
	};
}
