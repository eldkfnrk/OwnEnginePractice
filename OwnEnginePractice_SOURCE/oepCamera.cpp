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
		//카메라 해상도를 윈도우 크기에 항상 맞도록 윈도우 해상도를 가져와서 카메라 해상도에 대입
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
	}

	void Camera::Update()
	{
		if (mTarget) {  //타겟이 있는 경우
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();  //카메라가 비추는 타겟이 있는 경우 카메라가 바라보는 위치는 타겟의 위치로 설정
		}
		else {  //타겟이 없는 경우
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