#include "oepPlayerScript.h"
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepAnimator.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepTime.h"

namespace oep {
	PlayerScript::PlayerScript() : mState(eState::Idle), mAnimator(nullptr)
	{
	}

	void PlayerScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
	}

	void PlayerScript::Update()
	{
		switch (mState)
		{
		case PlayerScript::eState::Idle:
			idle();
			break;
		case PlayerScript::eState::Walk:
			move();
			break;
		case PlayerScript::eState::Sleep:
			break;
		case PlayerScript::eState::WakeUp:
			break;
		case PlayerScript::eState::GiveWater:
			giveWater();
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

	void PlayerScript::idle()
	{
		if (Input::GetKey(eKeyCode::MLButton)) {
			mState = eState::GiveWater;
			mAnimator->PlayAnimation(L"FrontGiveWater");
		}

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

		//if (Input::GetKey(eKeyCode::Right)) {
		//	position.x += 100.0f * Time::DeltaTime();
		//}

		//else if (Input::GetKey(eKeyCode::Left)) {
		//	position.x -= 100.0f * Time::DeltaTime();
		//}

		//else if (Input::GetKey(eKeyCode::Up)) {
		//	position.y -= 100.0f * Time::DeltaTime();
		//}

		//else if (Input::GetKey(eKeyCode::Down)) {
		//	position.y += 100.0f * Time::DeltaTime();
		//}

		//if (Input::GetKeyUp(eKeyCode::Right) || Input::GetKeyUp(eKeyCode::Left) || Input::GetKeyUp(eKeyCode::Up) || Input::GetKeyUp(eKeyCode::Down)) {
		//	mState = eState::Idle;
		//	mAnimator->PlayAnimation(L"Idle", false);
		//}

		tr->SetPosition(position);
	}

	void PlayerScript::giveWater()
	{
		if (mAnimator->IsComplete()) {
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle");
		}
	}

	void PlayerScript::AttackEffect()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}
}