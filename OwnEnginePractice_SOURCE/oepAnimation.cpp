#include "oepAnimation.h"
#include "oepAnimator.h"
#include "oepTime.h"
#include "oepTransform.h"
#include "oepGameObject.h"
#include "oepRenderer.h"

namespace oep {
	Animation::Animation() 
		: Resource(enums::eResourceType::Animation), mAnimator(nullptr), mTexture(nullptr), mAnimationSheet{}, mIndex(0), mTime(0.0f), mbComplete(false)
	{
		
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

		GameObject* gameObject = mAnimator->GetOwner();  //애니메이션이 있는 애니메이터 컴포넌트가 속한 오브젝트
		Transform* tr = gameObject->GetComponent<Transform>();  //오브젝트의 위치 컴포넌트
		Vector2 pos = tr->GetPosition();  //오브젝트의 위치 정보
		float rotation = tr->GetRotation();  //오브젝트의 각도
		Vector2 scale = tr->GetScale();  //오브젝트의 크기

		if (renderer::mainCamera) {
			pos = renderer::mainCamera->CalculatePosition(pos);
		}

		Sprite sprite = mAnimationSheet[mIndex];

		//이미지 파일이 png와 bmp로 2개이기 때문에 두 개 다 사용할 수 있도록 수정
		graphics::Texture::eTextureType type = mTexture->GetTextureType();  //텍스쳐의 이미지 파일의 형태를 가져온다.

		if (type == graphics::Texture::eTextureType::Bmp) {
			//이전 커밋에서 만들었던 동작은 텍스쳐 안에서 또 나누어서 사용하는 스프라이트 방식의 경우 사용할 수 있는 방식이기 때문에 
			//텍스쳐 타입이 bmp 파일인 경우에만 동작할 수 있기 때문에 텍스쳐 타입이 bmp인 경우에만 동작하도록 수정
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 225;  //0(transparent-투명) ~ 255(Opaque-불투명) 의 값으로 설정 가능

			//Sprite sprite = mAnimationSheet[mIndex];
			HDC imgHdc = mTexture->GetHdc();

			AlphaBlend(hdc, pos.x - (sprite.size.x / 2.0f), pos.y - (sprite.size.y / 2.0f)
				, sprite.size.x * scale.x, sprite.size.y * scale.y, imgHdc
				, sprite.leftTop.x, sprite.leftTop.y, sprite.size.x, sprite.size.y, func);
		}
		else if (type == graphics::Texture::eTextureType::Png) {  //png파일인 경우는 동작이 다르기 때문에 구분하고 새로 동작 추가
			//bmp 파일은 기본적으로 알파 값이 없는 24비트 파일인데 임의적으로 알파 채널을 추가해서 사용할 수는 있으나 png 파일은 기본적으로 알파 값을 가지고 있고 더 나아가
			//각 픽셀마다 알파 값이 있기 때문에 이펙트같은 효과를 주기 위해서는 png 파일을 써야하므로 png도 추가해주어야 한다.

			//이펙트는 보통 gif 파일로 되어 있는데 이 파일을 여기서 가져와서 사용하지 못하니 이펙트를 하나하나씩 나눠서 사용해야 한다.
			//그 방법으로는 구글에 gif to sprite라 검색 후 맨 위에 나오는 사이트에 접속하여 원하는 이펙트 gif 파일을 업로드하면 스프라이트를 나누어서 png 파일로 저장할 수 있다.
			//이때 스프라이트가 한 줄로 되도록 설정 후 저장하여야 사용하기 쉽다. 안 그러면 또 설정을 해야 할 수도 있고 사용을 못할 수도 있다.

			//내가 원하는 픽셀을 투명화시킬 때 사용한다.
			Gdiplus::ImageAttributes imgAttributes = {};  //이미지의 속성을 저장하는 구조체

			//투명화시킬 픽셀의 색 범위 지정
			//1번째 인자의 색 ~ 2번째 인자의 색 -> 이 범위의 모든 색을 투명화시키는 함수
			//imgAttributes.SetColorKey(Gdiplus::Color(100, 100, 100), Gdiplus::Color(255, 255, 255));

			imgAttributes.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			//Gdiplus로 이미지를 출력할 때 사용(이미지 파일 출력할 때 설정해봤던 것과 동일)
			Gdiplus::Graphics graphics(hdc);

			//이미지를 각도만큼 돌리도록 하는 설정
			graphics.TranslateTransform(pos.x, pos.y);  //회전할 때 중심이 되는 좌표 설정
			graphics.RotateTransform(rotation);  //인자로 전해지는 값이 각도로 인자 값만큼 회전
			graphics.TranslateTransform(-pos.x, -pos.y);

			//Gdiplus::UnitPixel -> 투명화를 시키겠다는 옵션
			//graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, sprite.size.x, sprite.size.y)
			//	, sprite.leftTop.x, sprite.leftTop.y, sprite.size.x, sprite.size.y
			//	, Gdiplus::UnitPixel, nullptr);

			//실제로 투명화시킬 색을 설정한 것을 적용하려면 마지막 인자에 투명색을 설정한 이미지 속성 구조체의 주소를 넣으면 된다.
			//동시에 오브젝트의 위치 좌표가 오브젝트의 중앙을 의미할 수 있도록 수정(이는 임의로 설정한 것이고 발밑이 좋다 혹은 머리 중앙이 좋다 등의 원하는 위치로 값을 바꾸면 설정 가능)
			graphics.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect(pos.x - (sprite.size.x / 2.0f), pos.y - (sprite.size.y / 2.0f), sprite.size.x * scale.x, sprite.size.y * scale.y)
				, sprite.leftTop.x, sprite.leftTop.y, sprite.size.x, sprite.size.y
				, Gdiplus::UnitPixel, &imgAttributes);
		}																			   
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
			sprite.leftTop.x = leftTop.x + size.x * i; 
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