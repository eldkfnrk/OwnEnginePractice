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
		if (mTarget) {  //타겟이 있는 경우
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();  //카메라가 비추는 타겟이 있는 경우 카메라가 바라보는 위치는 타겟의 위치로 설정
		}
		else {  //타겟이 없는 경우
			Transform* cameraTr = GetOwner()->GetComponent<Transform>();
			mLookPosition = cameraTr->GetPosition();
		}

		//카메라는 화면의 중앙을 보고 있다. 이때 화면의 중앙의 좌표는 해상도의 절반 값을 가지고 있다. 
		//그렇기 때문에 바라보고 있는 중앙의 위치에서 해상도의 절반 값을 빼주면 카메라가 비추는 대상과 카메라의 거리를 구할 수 있다.
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