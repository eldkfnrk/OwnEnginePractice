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
		//FSM(Finite-State Machine) 패턴
		//상태(State)를 기반으로 동작을 제어하는 방식을 구현하기 위한 디자인 패턴
		//이 패턴은 단 하나의 상태만을 가질 수 있어 상태를 기준으로 어떤 동작을 수행할지 결정하기 때문에 현재 상태만 알 수 있으면 어떤 동작을 수행하려 하는지 
		//명확히 파악할 수 있고 구현이 쉽다는 장점이 있다. 그래서 이 패턴을 플레이어는 물론 몬스터 AI 등에도 적용시켜 구현해볼 예정이다.

		//모든 프로그램을 만들 때 주의해야 할 것은 무작정 if문을 추가해 나가서 코드를 이해하기 힘들게 하지 않는 것이다.
		//그러니 중요한 것은 if문을 최대한 안 쓰도록 필요한 경우에만 쓰도록 주의하여야 한다.
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
		
		//FSM 패턴은 보통 state마다 행동이 다르기 때문에 switch문을 자주 사용한다.
		//소소한 꿀팁으로 switch를 입력하고 tab키를 누르면 switch문의 기본형이 자동 완성된다.
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