#include "oepCatScript.h"
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"
//#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepAnimator.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepTime.h"
#include "..\OwnEnginePractice_SOURCE\CommonInclude.h"

namespace oep {
	CatScript::CatScript() : mState(eState::SitDown), mAnimator(nullptr), mTime(0.0f), mDirection(eDirection::End)
	{
	}

	void CatScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
	}

	void CatScript::Update()
	{
		switch (mState)
		{
		case eState::SitDown:
			sitDown();
			break;
		case eState::Move:
			move();
			break;
		case eState::LayDown:
			break;
		case eState::WakeUp:
			break;
		case eState::Grooming:
			break;
		default:
			break;
		}
	}

	void CatScript::LateUpdate()
	{

	}

	void CatScript::Render(HDC hdc)
	{
	}

	void CatScript::sitDown()
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.5f) {
			mState = eState::Move;
			int direction = rand() % 4;  //앉아있다가 이동할 때의 방향을 랜덤하게 하기 위한 랜덤 변수(이 값은 완전한 랜덤 값은 아니니 실제 게임에선 완전한 랜덤 값 사용)
			mDirection = (eDirection)direction;

			playWalkAnimationByDirection(mDirection);

			mTime = 0.0f;
		}
	}

	void CatScript::move()
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.5f) {
			int isSleep = rand() % 2;  //랜덤하게 자는지 안 자는지 결정(0 - 안 잔다, 1 - 잔다)
			
			if (isSleep == 1) {
				mState = eState::LayDown;
				mAnimator->PlayAnimation(L"LayDown", false);
			}
			else {
				mState = eState::SitDown;
				mAnimator->PlayAnimation(L"SitDown", false);
			}

			mTime = 0.0f;

			return;
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();

		translate(tr);
	}

	void CatScript::playWalkAnimationByDirection(eDirection direction)
	{
		switch (direction)
		{
		case eDirection::Left:
			mAnimator->PlayAnimation(L"LeftMove");
			break;
		case eDirection::Right:
			mAnimator->PlayAnimation(L"RightMove");
			break;
		case eDirection::Up:
			mAnimator->PlayAnimation(L"UpMove");
			break;
		case eDirection::Down:
			mAnimator->PlayAnimation(L"DownMove");
			break;
		default:
			assert(false);
			break;
		}
	}

	void CatScript::translate(Transform* transform)
	{
		Vector2 position = transform->GetPosition();

		switch (mDirection)
		{
		case eDirection::Left:
			position.x -= 100.0f * Time::DeltaTime();
			break;
		case eDirection::Right:
			position.x += 100.0f * Time::DeltaTime();
			break;
		case eDirection::Up:
			position.y -= 100.0f * Time::DeltaTime();
			break;
		case eDirection::Down:
			position.y += 100.0f * Time::DeltaTime();
			break;
		default:
			assert(false);
			break;
		}
		
		transform->SetPosition(position);
	}

	CatScript::~CatScript()
	{
	}
}