#include "oepPlayerScript.h"
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepTime.h"

namespace oep {
	PlayerScript::PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
	}

	void PlayerScript::Update()
	{
		if (Input::GetKey(eKeyCode::Right)) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 position = tr->GetPosition();
			position.x += 100.0f * Time::DeltaTime();
			tr->SetPosition(position);
		}

		if (Input::GetKey(eKeyCode::Left)) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 position = tr->GetPosition();
			position.x -= 100.0f * Time::DeltaTime();
			tr->SetPosition(position);
		}

		if (Input::GetKey(eKeyCode::Up)) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 position = tr->GetPosition();
			position.y -= 100.0f * Time::DeltaTime();
			tr->SetPosition(position);
		}

		if (Input::GetKey(eKeyCode::Down)) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 position = tr->GetPosition();
			position.y += 100.0f * Time::DeltaTime();
			tr->SetPosition(position);
		}
	}

	void PlayerScript::LateUpdate()
	{
		
	}

	void PlayerScript::Render(HDC hdc)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}
}