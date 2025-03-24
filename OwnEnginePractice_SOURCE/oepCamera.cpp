#include "oepCamera.h"
#include "oepGameObject.h"
#include "oepTransform.h"

namespace oep {
	Camera::Camera() : Component(enums::eComponentType::Camera), mDistance(Vector2::One), mResolution(Vector2(1600.0f, 900.0f)), mLookPosition(Vector2::Zero), mTarget(nullptr)
	{
	}

	void Camera::Initialize()
	{
	}

	void Camera::Update()
	{
		if (mTarget) {  //Ÿ���� �ִ� ���
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();  //ī�޶� ���ߴ� Ÿ���� �ִ� ��� ī�޶� �ٶ󺸴� ��ġ�� Ÿ���� ��ġ�� ����
		}
		else {  //Ÿ���� ���� ���
			Transform* cameraTr = GetOwner()->GetComponent<Transform>();
			mLookPosition = cameraTr->GetPosition();
		}

		//ī�޶�� ȭ���� �߾��� ���� �ִ�. �̶� ȭ���� �߾��� ��ǥ�� �ػ��� ���� ���� ������ �ִ�. 
		//�׷��� ������ �ٶ󺸰� �ִ� �߾��� ��ġ���� �ػ��� ���� ���� ���ָ� ī�޶� ���ߴ� ���� ī�޶��� �Ÿ��� ���� �� �ִ�.
		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::LateUpdate()
	{
	}

	void Camera::Render(HDC hdc)
	{
	}

	Camera::~Camera()
	{
	}
}