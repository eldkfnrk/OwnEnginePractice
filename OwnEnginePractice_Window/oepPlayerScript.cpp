#include "oepPlayerScript.h"
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepAnimator.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepTime.h"
#include "..\OwnEnginePractice_SOURCE\oepObject.h"
#include "..\OwnEnginePractice_SOURCE\oepResources.h"
#include "oepCat.h"
#include "oepCatScript.h"

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
			mAnimator->PlayAnimation(L"FrontGiveWater", false);

			//고양이 npc 추가
			Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
			graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
			CatScript* catSc = cat->AddComponent<CatScript>();
			Animator* catAnimator = cat->AddComponent<Animator>();

			//모든 에니메이션을 가지고 만들어놓고 있어야 한다.
			catAnimator->CreateAnimation(L"DownMove", catTex, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
			catAnimator->CreateAnimation(L"RightMove", catTex, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
			catAnimator->CreateAnimation(L"UpMove", catTex, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
			catAnimator->CreateAnimation(L"LeftMove", catTex, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
			catAnimator->CreateAnimation(L"SitDown", catTex, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"Grooming", catTex, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"LayDown", catTex, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);  //lay down - 눕다
			catAnimator->CreateAnimation(L"WakeUp", catTex, Vector2(0.0f, 226.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->PlayAnimation(L"SitDown", false);

			cat->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 200.0f));
			cat->GetComponent<Transform>()->SetRotation(0.0f);
			cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
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