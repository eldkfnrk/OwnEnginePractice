#include "oepCatScript.h"
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"
#include "..\OwnEnginePractice_SOURCE\oepAnimator.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepTime.h"
#include "..\OwnEnginePractice_SOURCE\oepObject.h"
#include "..\OwnEnginePractice_SOURCE\CommonInclude.h"

namespace oep {
	CatScript::CatScript() : mState(eState::SitDown), mAnimator(nullptr)
		, mTime(0.0f), mDirection(eDirection::End), mDeathTime(0.0f), mPlayer(nullptr), mDest(Vector2::Zero), mRadian(0.0f)
	{
	}

	void CatScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mPlayer = GetOwner();
		
	}

	void CatScript::Update()
	{
		mDeathTime += Time::DeltaTime();

		if (mDeathTime > 6.0f) {  
			//object::Destroy(GetOwner());
		}

		if (mAnimator == nullptr) {
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

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

		if (mTime > 2.5f) {
			//object::Destroy(GetOwner());
		}

		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();  

		//����̸� �Ѿ� ������� �ϰ� ���콺�� ���⿡ �°� �Ѿ� �߻� ������ ��ȭ�� ���� ����
		//�̴� ������ ������ Ȱ���ؾ� �ϴµ� �÷��̾��� ��ġ���� ���콺 Ŭ�� �� �ش� ���콺�� �������� �߻�Ǹ� �ش� ���ʹ� ���κ��� ���콺 Ŭ�� �������� 
		//���ϴ� �����̱� ������ �ش� ���͸� ���ϴ� ����� (���콺 ���� - �� ����) ��, ������ ������ ����ϰ� �ȴ�.
		////position.x -= 100.0f * Time::DeltaTime();  
		////���ݱ����� ���� ���� ������� �̵��� �ؿ����� ������ �����¿�� ������ ���� �����ϰ� ��ȯ�� �� �ִ�.
		////position += Vector2::Left * 100.0f * Time::DeltaTime();  //100.0f�� �ӵ�
		//		
		////�÷��̾ �߻��ϴ� ���̱� ������ �÷��̾�κ��� �߻�ǵ��� �÷��̾��� ��ġ�� �˾ƾ� �Ѵ�.
		//Transform* playerTr = mPlayer->GetComponent<Transform>();

		////�̷��� �ϸ� ���콺 �Ѿ�(�����)�� ���콺�� ��ġ�� ����ٴϰ� �ȴ�.
		////�ֳ��ϸ�, ���콺�� ��ġ ������ �ǽð����� �ޱ� �������� ���� �̻��ϰ��� �ý����� ����Ϸ��� ������ ���� ����� �̿��ϸ� �ȴ�.
		////Vector2 mousePos = Input::GetMousePosition();
		////Vector2 dest = mousePos - playerTr->GetPosition();  //�߻��ϴ� ��ü�������� ���콺 Ŭ���� �̷���� �������� ���͸� ���Ѵ�.

		////�Ѿ�(�����)�� ��� ���콺�� Ŭ���� �������θ� �̵��ϰ� �Ϸ��� ���� ���� ���콺 Ŭ�� ��ġ�� �˸� �ȴ�.
		//Vector2 dest = mDest - playerTr->GetPosition();

		////position += dest * 1.0f * Time::DeltaTime();  //���⿡ ���͸� ������ ������ �������� �̵��ϰ� �ȴ�.
		////�׷��� ����ó�� ���۽�Ű�� ���콺 Ŭ���� �� ��ġ�� ���� ������ ũ�Ⱑ Ŀ���� ������ ���콺�� ��ġ�� ���� �ӵ��� �޶����� ������ ���� �� �ִ�.
		////���⼭ ���ʹ� ������ ���ϴ� �����̱� ������ ������ ũ��� �׻� ������ ���� �������� �Ͽ��� �ϰ� �� ���� 1�̾�� �Ѵ�.(�׷��� �ӵ� ������ �����ϴ�.)
		////�׷��� ������ ������ ũ�⸦ 1�� �ٲٴ� �Ϲ�ȭ �۾��� �ϰ� �ش� ���͸� ����Ͽ��� ������ �ӵ��� ����� �� �ִ�. 
		//position += dest.Normalize() * 100.0f * Time::DeltaTime(); 

		
		//�ﰢ �Լ��� ���� �̵� ����
		//�ﰢ �Լ��� ����ϵ��� ������ �Լ��� �Ű� ������ ����(����)���� �̰��� ȣ������ �ǹ��Ѵ�.
		//cos�� ���� -1 ~ 1 �� ���� ������ ������ ���� ������� ������ ���̴�.
		//���밪�� �ְ� ������ abs() �Լ��� �̿��ϸ� �ǰ� �ĵ��� ũ�� ������ ���� ������ cos ���� ũ�⸦ Ű���ָ� �ȴ�.(���ؼ� ũ�� ��ȯ)
		//mRadian += 5.0f * Time::DeltaTime();  //����� ���ָ� ���� ����ŭ ���� ũ�� ��ȯ�� Ŀ���Ƿ� ���� �ӵ��� ������ �� �ִ�.
		//position += Vector2(1.0f, 2.0f * cosf(mRadian)) * 100.0f * Time::DeltaTime();  


		//���콺 ��ġ �������� ȸ�� �� ���콺 ��ġ �̵�(���� Ȱ��)
		//���ݱ����� ���콺 ��ġ �������� �Ѿ�(�����)�� �̵���Ű�� ���� ������ �׸��� �״�� ��µǾ��µ� ������ Ŭ���� ������ �������� ȸ������ ��µǵ��� �Ѵٴ� �ǹ�
		//Transform* playerTr = mPlayer->GetComponent<Transform>();
		//Vector2 playerPosition = playerTr->GetPosition();
		//Vector2 dest = mDest - playerPosition;
		//dest = dest.Normalize();

		//�̹����� ȸ����Ű�� ���ؼ��� ȸ������ �˾ƾ� �Ѵ�. �̶� �⺻ �̹����� �������� �ٶ󺸴� ���� �������� �Ѵ�.(��, �⺻ �̹����� ������ ���͸� ������ �ִ� ���̴�.)
		//�׷��� �츮�� ���������� ���ϴ� ���Ϳ� ���콺�� Ŭ���� ��ġ�� ���ϴ� ������ ���� ���ϸ� �ǰ� �� ���� ������ Ȱ���Ͽ� ���� �� �ִ�.
		//float rotDegree = Vector2::Dot(dest, Vector2::Right);  //������ ���� cos�� ���� �ȴ�.
		//rotDegree = acosf(rotDegree);  //acos�� ��ũ �ڻ����̶�� ������ cos�� ���Լ��� �ǹ��ϰ� �̴� ���� ���� ��ȯ�Ѵ�.
		
		//�׷��� �� ���� 0~180�� �ۿ� Ȯ������ ���ϴµ� �� ������ �츮�� ��ǥ�� ��и��� �������� ������ Ȯ�������� ��ǻ�ʹ� �׷��� �ʱ� ������ �׷���.
		//�׷��� �̰��� ���� ������ �Ǵ� ��ü�� (0,0)�̶� �����ϰ� ��и��� ������ 0~360���� ���� ���� �� �ֵ��� �������־�� �Ѵ�.
		//rotDegree = ConvertDegree(rotDegree);  //�� �Լ��� ������ degree ������ ��ȯ�����ִ� �Լ��� ���� ���� �谪�� ��ȯ�Ѵ�.

		//0~360���� ���� ���� �� �ֵ��� �߰� ���(�÷��̾ (0,0)�̶�� �����ϰ� ���)
		//���⼭ �����ؾ� �� ���� �츮�� ���� ��ǥ�� ���� +, �Ʒ��� -������ ��ǻ�� ��ǥ �����δ� ���� �Ʒ����� ũ�� ������ �̿� ���缭 ���� - �Ʒ��� +���� �Ѵ�.
		//�̷��� �Ͽ����� �׸��� ������ ���⿡ �˸°� ȸ����ų �� �ִ�.
		//if (mDest.y <= playerPosition.y) {  //��1, 2��и��� ���
		//	rotDegree = ConvertDegree(rotDegree);
		//}
		//else if (mDest.y > playerPosition.y) {  //��3, 4��и��� ���
		//	rotDegree = 360.0f - ConvertDegree(rotDegree);
		//}

		//������ �׳� �츮�� ���⸦ �ٶ󺸰� �ִٰ� ���Ͽ����� ��� ������ ����Ƽ ���� ��� ��ü�� �⺻������ �ڽ��� �ٶ󺸰� �ִ� ���� ���͸� ������ �ִ�.
		//�̰��� ����Ƽ������ forward ���Ͷ�� �Ѵ�. �� �״�� ���� �ٶ󺸰� �ִ� ���Ͷ�� ���̴�.

		//position += dest * 100.0f * Time::DeltaTime();

		//transform->SetPosition(position);

		//if (mTime > 1.5f) {
		//	mState = eState::Move;
		//	int direction = rand() % 4;  
		//	mDirection = (eDirection)direction;

		//	playWalkAnimationByDirection(mDirection);

		//	mTime = 0.0f;
		//}
	}

	void CatScript::move()
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.5f) {
			int isSleep = rand() % 2;  
			
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