#include "oepPlayer.h"

namespace oep {
	//���� ������Ʈ�� ���۵��� �״�� ����(��� ������ �θ� Ŭ������ �ߴ���� �ϴµ� override�� ���� �� ������ ���� �� ������Ʈ������ �ϴ� �ٸ� ������ ���� �� �ֱ� ������)
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
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}