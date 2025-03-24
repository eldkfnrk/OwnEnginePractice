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

		//이제 이런 오브젝트의 행동 로직과 관련된 것은 모두 오브젝트에 맞는 스크립트 컴포넌트에서 수행할 것이다.
		//if (Input::GetKey(eKeyCode::Right)) {
		//	Transform* tr = GetComponent<Transform>();
		//	Vector2 position = tr->GetPosition();
		//	position.x += 100.0f * Time::DeltaTime();
		//	tr->SetPosition(position);
		//}
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}