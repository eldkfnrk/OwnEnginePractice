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

			//����� ���콺 Ŀ�� ��ġ ������ �޾ƿ����� Ȯ���ϱ� ���� �׽�Ʈ �ڵ�
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
		//�� ������ �ִϸ��̼��� ������ ����ǵ��� �ϱ� ���� �ִϸ��̼��� ���� ���θ� ������ �´�.
		if (mAnimator->IsComplete()) {
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle");
		}

		//���� ���α׷��� �޸� ������ 4������ ������ �ȴ�. �� �� ������ �ڵ� �������� �ۼ��� �ڵ���� �ö󰡴� �����̴�. ��, �Լ����� �͵��� ����Ǵ� �����̴�.
		//�� �Ʒ��� ������ ������ �����̶�� �Ͽ� �����Ͱ� ����Ǵµ� ���� ������ ���� ������ �̰��� ��ġ�Ѵ�. ������ 2��° ������ �����͸� �ø��� ������ ���� �־�� 
		//�ؿ� �������� ������ �� �ֱ� �����̴�. �� �Ʒ� ������ ���̶�� �Ͽ� new�� malloc���� �޸� �Ҵ��� �� �������� ��ġ�Ѵ�. ��, ���� �Ҵ��� �͵��� ����Ǵ� �����̴�.
		//�� �Ʒ� ������ ���� �������� ���� �������� ��ġ�Ѵ�. ��, ����� ��ġ������ ����� �� �ִ� �������� ����Ǵ� �����̴�.
		//�̰��� ���� �⺻���� �޸��� ������ �˰� �Ǿ��� �׷� ���� �˰Ե� ���� �� �ϳ� �ִµ� �ٷ� �Լ��� �ּ� ���� �ִٴ� ���̴�.
		//�׸��� �� �Լ��� �ּ� ���� ������ �� �ִ� Ÿ���� ������ �Լ� �����Ͷ�� �Ѵ�. ����ϴ� ����� �Ʒ��� ����.
		//void Add() �Լ��� �ִ� -> void (*Func1)(); -> Func1=Add;
		//�⺻ ���´� "��ȯ�� �Լ���(�Ű�����...)" ������ �Լ��� ������ �Լ� �����ʹ� "��ȯ�� (*�����͸�)(�Ű����� Ÿ��...)"���� ���� �Ҵ��� �� "�����͸�=�Լ���"���� �Ѵ�.

		//�Լ� �����͸� ������ ������ �ִϸ��̼��� �ִϸ��̼Ǹ� �ִ� �� �ƴ϶� �̿� �����ϴ� �̺�Ʈ�� �ֱ� �����̴�.
		//���� ��� ���ӿ��� ���� �ĸ� ���� �� ������ ������ �ϰ� �뿡 ���� �ָ� ���� ������ ���� ���� ���۰� ���õ� �̺�Ʈ�� �ִ�. �׸��� �� �̺�Ʈ���� ����ϴ� �Լ����� ���� ���̴�.
		//�׸��� �츮�� �װ��� �Լ� �����͸� �̿��Ͽ� �� �̺�Ʈ���� ó���Ϸ��� �Ѵ�.
	}

	PlayerScript::~PlayerScript()
	{
	}
}