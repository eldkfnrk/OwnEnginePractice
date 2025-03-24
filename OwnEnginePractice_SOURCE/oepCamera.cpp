#include "oepCamera.h"
#include "oepGameObject.h"
#include "oepTransform.h"
#include "oepApplication.h"

extern oep::Application application;

namespace oep {
	Camera::Camera() : Component(enums::eComponentType::Camera), mDistance(Vector2::One)
		, mResolution(Vector2::Zero), mLookPosition(Vector2::Zero), mTarget(nullptr)
	{
	}

	void Camera::Initialize()
	{
		//ī�޶� �ػ󵵸� ������ ũ�⿡ �׻� �µ��� ������ �ػ󵵸� �����ͼ� ī�޶� �ػ󵵿� ����
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
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