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

			//제대로 마우스 커서 위치 정보를 받아오는지 확인하기 위한 테스트 코드
			//Vector2 mousePos = Input::GetMousePosition();
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
		//이 동작은 애니메이션이 끝나면 종료되도록 하기 위해 애니메이션의 종료 여부를 가지고 온다.
		if (mAnimator->IsComplete()) {
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle");
		}

		//실제 프로그램의 메모리 영역은 4가지로 나뉘게 된다. 맨 위 영역은 코드 영역으로 작성한 코드들이 올라가는 영역이다. 즉, 함수같은 것들이 저장되는 공간이다.
		//그 아래의 영역을 데이터 영역이라고 하여 데이터가 저장되는데 전역 변수나 정적 변수가 이곳에 위치한다. 위에서 2번째 영역에 데이터를 올리는 이유는 위에 있어야 
		//밑에 영역에서 접근할 수 있기 때문이다. 그 아래 영역은 힙이라고 하여 new나 malloc으로 메모리 할당을 한 변수들이 위치한다. 즉, 동적 할당한 것들이 저장되는 공간이다.
		//맨 아래 영역은 스택 영역으로 지역 변수들이 위치한다. 즉, 선언된 위치에서만 사용할 수 있는 변수들이 저장되는 공간이다.
		//이것을 통해 기본적인 메모리의 구조를 알게 되었고 그로 인해 알게된 것이 또 하나 있는데 바로 함수도 주소 값이 있다는 것이다.
		//그리고 이 함수의 주소 값을 저장할 수 있는 타입의 변수를 함수 포인터라고 한다. 사용하는 방법은 아래와 같다.
		//void Add() 함수가 있다 -> void (*Func1)(); -> Func1=Add;
		//기본 형태는 "반환형 함수명(매개변수...)" 형태의 함수를 저장할 함수 포인터는 "반환형 (*포인터명)(매개변수 타입...)"으로 값을 할당할 땐 "포인터명=함수명"으로 한다.

		//함수 포인터를 설명한 이유는 애니메이션은 애니메이션만 있는 게 아니라 이에 대응하는 이벤트가 있기 마련이다.
		//예를 들어 게임에서 땅을 파면 땅을 판 지면이 파져야 하고 흙에 물을 주면 흙은 촉촉히 젖는 등의 동작과 관련된 이벤트가 있다. 그리고 이 이벤트들을 담당하는 함수들이 있을 것이다.
		//그리고 우리는 그것을 함수 포인터를 이용하여 이 이벤트들을 처리하려고 한다.
	}

	PlayerScript::~PlayerScript()
	{
	}
}