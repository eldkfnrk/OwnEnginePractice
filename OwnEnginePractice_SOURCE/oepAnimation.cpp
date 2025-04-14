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
			HDC imgHdc = mTexture->GetHdc();

			//알파 채널이 있으면 32비트짜리 비트맵이고 없으면 24비트짜리 비트맵이다.
			if (mTexture->IsAlpha()) {
				//32비트짜리 알파 채널이 있는 비트맵을 화면에 출력
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255;  //0(transparent-투명) ~ 255(Opaque-불투명) 의 값으로 설정 가능

				AlphaBlend(hdc, pos.x - (sprite.size.x / 2.0f) + sprite.offset.x, pos.y - (sprite.size.y / 2.0f) + sprite.offset.y
					, sprite.size.x * scale.x, sprite.size.y * scale.y, imgHdc
					, sprite.leftTop.x, sprite.leftTop.y, sprite.size.x, sprite.size.y, func);
			}
			else {
				//24비트짜리 알파 채널이 없는 기본 비트맵을 화면에 출력
				TransparentBlt(hdc, pos.x - (sprite.size.x / 2.0f) + sprite.offset.x, pos.y - (sprite.size.y / 2.0f) + sprite.offset.y
					, sprite.size.x * scale.x, sprite.size.y * scale.y
					, imgHdc, sprite.leftTop.x, sprite.leftTop.y, sprite.size.x, sprite.size.y, RGB(255, 0, 255));
			}
		}
		else if (type == graphics::Texture::eTextureType::Png) {
			Gdiplus::ImageAttributes imgAttributes = {};  //이미지의 속성을 저장하는 구조체

			imgAttributes.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			//Gdiplus로 이미지를 출력할 때 사용(이미지 파일 출력할 때 설정해봤던 것과 동일)
			Gdiplus::Graphics graphics(hdc);

			//이미지를 각도만큼 돌리도록 하는 설정
			graphics.TranslateTransform(pos.x, pos.y);  //회전할 때 중심이 되는 좌표 설정
			graphics.RotateTransform(rotation);  //인자로 전해지는 값이 각도로 인자 값만큼 회전
			graphics.TranslateTransform(-pos.x, -pos.y);

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