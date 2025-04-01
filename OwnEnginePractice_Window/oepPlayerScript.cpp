#include "oepPlayerScript.h"
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepAnimator.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepTime.h"

namespace oep {
	PlayerScript::PlayerScript() : mState(eState::SitDown), mAnimator(nullptr)
	{
	}

	void PlayerScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
	}

	void PlayerScript::Update()
	{
		//FSM(Finite-State Machine) ����
		//����(State)�� ������� ������ �����ϴ� ����� �����ϱ� ���� ������ ����
		//�� ������ �� �ϳ��� ���¸��� ���� �� �־� ���¸� �������� � ������ �������� �����ϱ� ������ ���� ���¸� �� �� ������ � ������ �����Ϸ� �ϴ��� 
		//��Ȯ�� �ľ��� �� �ְ� ������ ���ٴ� ������ �ִ�. �׷��� �� ������ �÷��̾�� ���� ���� AI ��� ������� �����غ� �����̴�.

		//��� ���α׷��� ���� �� �����ؾ� �� ���� ������ if���� �߰��� ������ �ڵ带 �����ϱ� ����� ���� �ʴ� ���̴�.
		//�׷��� �߿��� ���� if���� �ִ��� �� ������ �ʿ��� ��쿡�� ������ �����Ͽ��� �Ѵ�.
		//if (Input::GetKey(eKeyCode::Right)) {
		//	Transform* tr = GetOwner()->GetComponent<Transform>();
		//	Vector2 position = tr->GetPosition();
		//	position.x += 100.0f * Time::DeltaTime();
		//	tr->SetPosition(position);
		//}

		//if (Input::GetKey(eKeyCode::Left)) {
		//	Transform* tr = GetOwner()->GetComponent<Transform>();
		//	Vector2 position = tr->GetPosition();
		//	position.x -= 100.0f * Time::DeltaTime();
		//	tr->SetPosition(position);
		//}

		//if (Input::GetKey(eKeyCode::Up)) {
		//	Transform* tr = GetOwner()->GetComponent<Transform>();
		//	Vector2 position = tr->GetPosition();
		//	position.y -= 100.0f * Time::DeltaTime();
		//	tr->SetPosition(position);
		//}

		//if (Input::GetKey(eKeyCode::Down)) {
		//	Transform* tr = GetOwner()->GetComponent<Transform>();
		//	Vector2 position = tr->GetPosition();
		//	position.y += 100.0f * Time::DeltaTime();
		//	tr->SetPosition(position);
		//}
		
		//FSM ������ ���� state���� �ൿ�� �ٸ��� ������ switch���� ���� ����Ѵ�.
		//�Ҽ��� �������� switch�� �Է��ϰ� tabŰ�� ������ switch���� �⺻���� �ڵ� �ϼ��ȴ�.
		switch (mState)
		{
		case PlayerScript::eState::SitDown:
			sitDown();
			break;
		case PlayerScript::eState::Walk:
			move();
			break;
		case PlayerScript::eState::Sleep:
			break;
		case PlayerScript::eState::WakeUp:
			break;
		case PlayerScript::eState::Grooming:
			break;
		default:
			break;
		}
	}

	void PlayerScript::LateUpdate()
	{
		
	}

	void PlayerScript::Render(HDC hdc)
	{
	}

	void PlayerScript::sitDown()
	{
		if (Input::GetKey(eKeyCode::Right)) {
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"RightWalk");
		}
		
		if (Input::GetKey(eKeyCode::Left)) {
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"LeftWalk");
		}
		
		if (Input::GetKey(eKeyCode::Up)) {
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"BackWalk");
		}
		
		if (Input::GetKey(eKeyCode::Down)) {
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"FrontWalk");
		}
	}

	void PlayerScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 position = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Right)) {
			position.x += 100.0f * Time::DeltaTime();
		}

		else if (Input::GetKey(eKeyCode::Left)) {
			position.x -= 100.0f * Time::DeltaTime();
		}

		else if (Input::GetKey(eKeyCode::Up)) {
			position.y -= 100.0f * Time::DeltaTime();
		}

		else if (Input::GetKey(eKeyCode::Down)) {
			position.y += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::Right) || Input::GetKeyUp(eKeyCode::Left) || Input::GetKeyUp(eKeyCode::Up) || Input::GetKeyUp(eKeyCode::Down)) {
			mState = eState::SitDown;
			mAnimator->PlayAnimation(L"SitDown", false);
		}

		tr->SetPosition(position);
	}

	PlayerScript::~PlayerScript()
	{
	}
}