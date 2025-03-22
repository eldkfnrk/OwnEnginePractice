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

		//OnEnter�� OnExit�� ����� �����ϳ� Ȯ���ϱ� ���� �׽�Ʈ �ڵ�(������ ������Ʈ �̵��� ������ �̵��߾ ���� ������ �ٽ� ���ƿ��� �� ��ġ�� ���ƿ;� �ϴ� �̸� �ٽ� ���� �ִ� ������ �ǵ����� �۾�)
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