#include "oepCat.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepTime.h"

namespace oep {
	void Cat::Initialize()
	{
		GameObject::Initialize();
	}

	void Cat::Update()
	{
		GameObject::Update();
	}

	void Cat::LateUpdate()
	{
		GameObject::LateUpdate();

		//���� �̷� ������Ʈ�� �ൿ ������ ���õ� ���� ��� ������Ʈ�� �´� ��ũ��Ʈ ������Ʈ���� ������ ���̴�.
		//if (Input::GetKey(eKeyCode::Right)) {
		//	Transform* tr = GetComponent<Transform>();
		//	Vector2 position = tr->GetPosition();
		//	position.x += 100.0f * Time::DeltaTime();
		//	tr->SetPosition(position);
		//}
	}

	void Cat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}