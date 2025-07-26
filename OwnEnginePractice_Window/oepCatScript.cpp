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

		//고양이를 총알 대신으로 하고 마우스의 방향에 맞게 총알 발사 각도의 변화에 대한 예제
		//이는 벡터의 뺄셈을 활용해야 하는데 플레이어의 위치에서 마우스 클릭 시 해당 마우스의 방향으로 발사되면 해당 벡터는 나로부터 마우스 클릭 방향으로 
		//향하는 벡터이기 때문에 해당 벡터를 구하는 방법은 (마우스 벡터 - 나 벡터) 즉, 벡터의 뺄셈을 사용하게 된다.
		////position.x -= 100.0f * Time::DeltaTime();  
		////지금까지는 위와 같은 방식으로 이동을 해왔지만 이제는 상하좌우는 다음과 같이 간편하게 변환할 수 있다.
		////position += Vector2::Left * 100.0f * Time::DeltaTime();  //100.0f는 속도
		//		
		////플레이어가 발사하는 것이기 때문에 플레이어로부터 발사되도록 플레이어의 위치를 알아야 한다.
		//Transform* playerTr = mPlayer->GetComponent<Transform>();

		////이렇게 하면 마우스 총알(고양이)이 마우스의 위치를 따라다니게 된다.
		////왜냐하면, 마우스의 위치 정보를 실시간으로 받기 때문으로 유도 미사일같은 시스템을 사용하려면 다음과 같은 방식을 이용하면 된다.
		////Vector2 mousePos = Input::GetMousePosition();
		////Vector2 dest = mousePos - playerTr->GetPosition();  //발사하는 주체에서부터 마우스 클릭이 이루어진 지점과의 벡터를 구한다.

		////총알(고양이)을 쏘면 마우스를 클릭한 방향으로만 이동하게 하려면 쐈을 때의 마우스 클릭 위치만 알면 된다.
		//Vector2 dest = mDest - playerTr->GetPosition();

		////position += dest * 1.0f * Time::DeltaTime();  //방향에 벡터를 넣으면 벡터의 방향으로 이동하게 된다.
		////그러나 위에처럼 동작시키면 마우스 클릭을 내 위치에 따라 벡터의 크기가 커지기 때문에 마우스의 위치에 따라 속도가 달라지는 문제가 생길 수 있다.
		////여기서 벡터는 방향을 정하는 역할이기 때문에 벡터의 크기는 항상 동일한 값을 가지도록 하여야 하고 그 값은 1이어야 한다.(그래야 속도 조절이 수월하다.)
		////그렇기 때문에 벡터의 크기를 1로 바꾸는 일반화 작업을 하고 해당 벡터를 사용하여야 동일한 속도를 출력할 수 있다. 
		//position += dest.Normalize() * 100.0f * Time::DeltaTime(); 

		
		//삼각 함수를 통한 이동 예제
		//삼각 함수를 사용하도록 정의한 함수의 매개 변수는 각도(라디안)으로 이것은 호도법을 의미한다.
		//cos의 값은 -1 ~ 1 의 값을 가지기 때문에 물결 모양으로 움직일 것이다.
		//절대값을 주고 싶으면 abs() 함수를 이용하면 되고 파동을 크게 가지고 가고 싶으면 cos 값에 크기를 키워주면 된다.(곱해서 크기 변환)
		//mRadian += 5.0f * Time::DeltaTime();  //배수를 해주면 해준 값만큼 값의 크기 변환이 커지므로 진동 속도를 조절할 수 있다.
		//position += Vector2(1.0f, 2.0f * cosf(mRadian)) * 100.0f * Time::DeltaTime();  


		//마우스 위치 방향으로 회전 후 마우스 위치 이동(내적 활용)
		//지금까지는 마우스 위치 방향으로 총알(고양이)를 이동시키는 것은 했지만 그림은 그대로 출력되었는데 이제는 클릭한 벡터의 방향으로 회전시켜 출력되도록 한다는 의미
		//Transform* playerTr = mPlayer->GetComponent<Transform>();
		//Vector2 playerPosition = playerTr->GetPosition();
		//Vector2 dest = mDest - playerPosition;
		//dest = dest.Normalize();

		//이미지를 회전시키기 위해서는 회전각을 알아야 한다. 이때 기본 이미지는 오른쪽을 바라보는 것을 기준으로 한다.(즉, 기본 이미지는 오른쪽 벡터를 가지고 있는 것이다.)
		//그러면 우리는 오른쪽으로 향하는 벡터와 마우스가 클릭한 위치를 향하는 벡터의 각을 구하면 되고 그 값은 내적을 활용하여 구할 수 있다.
		//float rotDegree = Vector2::Dot(dest, Vector2::Right);  //내적한 값은 cosθ 값이 된다.
		//rotDegree = acosf(rotDegree);  //acos은 아크 코사인이라는 뜻으로 cos의 역함수를 의미하고 이는 라디안 값을 반환한다.
		
		//그러나 이 값은 0~180도 밖에 확인하지 못하는데 그 이유는 우리는 좌표의 사분면을 기준으로 각도를 확인하지만 컴퓨터는 그렇지 않기 때문에 그렇다.
		//그래서 이것은 직접 기준이 되는 물체를 (0,0)이라 생각하고 사분면을 나눠서 0~360도의 값을 가질 수 있도록 수정해주어야 한다.
		//rotDegree = ConvertDegree(rotDegree);  //이 함수는 라디안을 degree 각도로 변환시켜주는 함수로 실제 각도 θ값을 반환한다.

		//0~360도의 값을 가질 수 있도록 추가 계산(플레이어를 (0,0)이라고 가정하고 계산)
		//여기서 주의해야 할 점은 우리가 보는 좌표는 위가 +, 아래가 -이지만 컴퓨터 좌표 상으로는 위가 아래보다 크기 때문에 이에 맞춰서 위가 - 아래가 +여야 한다.
		//이렇게 하여서야 그림을 벡터의 방향에 알맞게 회전시킬 수 있다.
		//if (mDest.y <= playerPosition.y) {  //제1, 2사분면인 경우
		//	rotDegree = ConvertDegree(rotDegree);
		//}
		//else if (mDest.y > playerPosition.y) {  //제3, 4사분면인 경우
		//	rotDegree = 360.0f - ConvertDegree(rotDegree);
		//}

		//지금은 그냥 우리가 여기를 바라보고 있다고 정하였지만 상용 엔진인 유니티 등의 경우 물체가 기본적으로 자신이 바라보고 있는 방향 벡터를 가지고 있다.
		//이것을 유니티에서는 forward 벡터라고 한다. 말 그대로 앞을 바라보고 있는 벡터라는 뜻이다.

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