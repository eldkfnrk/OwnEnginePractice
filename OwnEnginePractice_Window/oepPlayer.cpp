#include "oepPlayer.h"

namespace oep {
	//게임 오브젝트의 동작들을 그대로 수행(모든 동작을 부모 클래스가 했던대로 하는데 override를 굳이 한 이유는 이후 이 오브젝트에서만 하는 다른 동작이 있을 수 있기 때문에)
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