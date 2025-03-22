#include "oepPlayer.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepTime.h"

namespace oep {
	void Player::Initialize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		//OnEnter와 OnExit가 제대로 동작하나 확인하기 위한 테스트 코드(씬에서 오브젝트 이동이 가능해 이동했어도 씬을 나가고 다시 돌아오면 원 위치로 돌아와야 하니 이를 다시 원래 있던 곳으로 되돌리는 작업)
		if (Input::GetKey(eKeyCode::Right)) {
			Transform* tr = GetComponent<Transform>();
			Vector2 position = tr->GetPosition();
			position.x += 100.0f * Time::DeltaTime();
			tr->SetPos(position);
		}
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}