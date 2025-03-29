#include "oepAnimation.h"
#include "oepAnimator.h"
#include "oepTime.h"
#include "oepTransform.h"
#include "oepGameObject.h"
#include "oepRenderer.h"

namespace oep {
	Animation::Animation() 
		: Resource(enums::eResourceType::Animation), mAnimator(nullptr), mTexture(nullptr), mAnimationSheet{}, mIndex(-1), mTime(0.0f), mbComplete(false)
	{
		//초기화는 반드시 없는 값을 넣어야 문제가 발생하지 않는다. 그래서 배열의 인덱스 값을 의미하는 변수의 값은 0이 아닌 -1을 넣어주어야 한다.
	}

	HRESULT Animation::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Animation::Update()
	{
		if (mbComplete) {
			return;
		}

		mTime += Time::DeltaTime();

		if (mAnimationSheet[mIndex].duration < mTime) {
			mTime = 0.0f;

			if (mIndex < mAnimationSheet.size() - 1) {
				mIndex++;
			}
			else {
				mbComplete = true;
			}
		}
	}

	void Animation::Render(HDC hdc)
	{
		if (mTexture == nullptr) {
			return;
		}

		GameObject* gameObject = mAnimator->GetOwner();
		Transform* tr = gameObject->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (renderer::mainCamera) {
			//카메라가 있으면 카메라 기준으로 위치를 계산해주어야 한다.(모든 오브젝트들이 카메라 기준으로 위치가 계산되어야 한다.)
			pos = renderer::mainCamera->CalculatePosition(pos);
		}

		//AlphaBlend 함수 사용 전 반드시 세팅해주어야 할 세팅 값
		//이 함수를 사용하려면 반드시 이렇게 세팅을 해주어야 하며 그 세팅은 그냥 이렇게 쓰는 걸로 정의가 내려져 있다.(
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		//이 값만은 사용자가 자신에 알맞게 값을 설정해주어야 한다.
		//이 값은 출력할 이미지의 투명도로 숫자가 낮을수록 투명해지는건데 이걸 사용하는 이유는 플레이어가 공격당했을 때 피격 모션에 들어갈 때 피격됐음을 보여주기 위해 반투명으로 변하는
		//경우처럼 이미지가 어느 정도 투명해지도록 하기 위해서 값을 설정한다.
		func.SourceConstantAlpha = 225;  //0(transparent-투명) ~ 255(Opaque-불투명) 의 값으로 설정 가능

		Sprite sprite = mAnimationSheet[mIndex];
		HDC imgHdc = mTexture->GetHdc();

		//TransParenrBlt 함수처럼 비트맵을 출력하는 함수인데 인자로 알파 값을 넣을 수 있는 함수
		//이 함수를 사용하는 이유는 투명 값을 줄 수 있기 때문으로 이미지가 투명해져야 하는 경우가 있을 수 있는 경우 TransParenrBlt 함수는 그것이 불가한데 이 함수는 가능하기 때문이다.
		//이 함수를 사용할 수 있는 조건이 있는데 그 조건이란 해당 이미지 알파 채널이 있어야 한다.(포토샵에서 이미지를 편집할 때 채널이라는 게 있는데 그때 반 투명 값을 설정한 것이 알파 채널)
		//이미지에 알파 채널이 있는지를 확인하려면 이미지 속성에 들어가서 자세히 탭의 비트 수준의 값을 보면 알 수 있다. 24는 없는 이미지 32는 있는 이미지이다.
		//TransParenrBlt 함수의 인자와 동일한데 마지막 인자만 앞에서 세팅해준 값을 전달해주는 것에 차이가 있다.
		AlphaBlend(hdc, pos.x, pos.y, sprite.size.x * 5, sprite.size.y * 5, imgHdc, sprite.leftTop.x, sprite.leftTop.y, sprite.size.x, sprite.size.y, func);
	}

	void Animation::CreateAnimation(const std::wstring& name
		, graphics::Texture* spriteSheet
		, Vector2 leftTop
		, Vector2 size
		, Vector2 offset
		, UINT spriteLength
		, float duration)
	{
		mTexture = spriteSheet;
		for (size_t i = 0; i < spriteLength; i++) {
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + size.x * i;  //스프라이트의 시작 위치는 x값만 변하고 각각 size의 x 크기만큼 차이가 나기 때문에 이와 같은 식을 사용
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mAnimationSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

	Animation::~Animation()
	{
	}
}