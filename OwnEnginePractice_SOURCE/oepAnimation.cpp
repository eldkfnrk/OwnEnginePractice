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

		GameObject* gameObject = mAnimator->GetOwner();  //�ִϸ��̼��� �ִ� �ִϸ����� ������Ʈ�� ���� ������Ʈ
		Transform* tr = gameObject->GetComponent<Transform>();  //������Ʈ�� ��ġ ������Ʈ
		Vector2 pos = tr->GetPosition();  //������Ʈ�� ��ġ ����
		float rotation = tr->GetRotation();  //������Ʈ�� ����
		Vector2 scale = tr->GetScale();  //������Ʈ�� ũ��

		if (renderer::mainCamera) {
			pos = renderer::mainCamera->CalculatePosition(pos);
		}

		Sprite sprite = mAnimationSheet[mIndex];

		//�̹��� ������ png�� bmp�� 2���̱� ������ �� �� �� ����� �� �ֵ��� ����
		graphics::Texture::eTextureType type = mTexture->GetTextureType();  //�ؽ����� �̹��� ������ ���¸� �����´�.

		if (type == graphics::Texture::eTextureType::Bmp) {
			HDC imgHdc = mTexture->GetHdc();

			//���� ä���� ������ 32��Ʈ¥�� ��Ʈ���̰� ������ 24��Ʈ¥�� ��Ʈ���̴�.
			if (mTexture->IsAlpha()) {
				//32��Ʈ¥�� ���� ä���� �ִ� ��Ʈ���� ȭ�鿡 ���
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255;  //0(transparent-����) ~ 255(Opaque-������) �� ������ ���� ����

				AlphaBlend(hdc, pos.x - (sprite.size.x / 2.0f) + sprite.offset.x, pos.y - (sprite.size.y / 2.0f) + sprite.offset.y
					, sprite.size.x * scale.x, sprite.size.y * scale.y, imgHdc
					, sprite.leftTop.x, sprite.leftTop.y, sprite.size.x, sprite.size.y, func);
			}
			else {
				//24��Ʈ¥�� ���� ä���� ���� �⺻ ��Ʈ���� ȭ�鿡 ���
				TransparentBlt(hdc, pos.x - (sprite.size.x / 2.0f) + sprite.offset.x, pos.y - (sprite.size.y / 2.0f) + sprite.offset.y
					, sprite.size.x * scale.x, sprite.size.y * scale.y
					, imgHdc, sprite.leftTop.x, sprite.leftTop.y, sprite.size.x, sprite.size.y, RGB(255, 0, 255));
			}
		}
		else if (type == graphics::Texture::eTextureType::Png) {
			Gdiplus::ImageAttributes imgAttributes = {};  //�̹����� �Ӽ��� �����ϴ� ����ü

			imgAttributes.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			//Gdiplus�� �̹����� ����� �� ���(�̹��� ���� ����� �� �����غô� �Ͱ� ����)
			Gdiplus::Graphics graphics(hdc);

			//�̹����� ������ŭ �������� �ϴ� ����
			graphics.TranslateTransform(pos.x, pos.y);  //ȸ���� �� �߽��� �Ǵ� ��ǥ ����
			graphics.RotateTransform(rotation);  //���ڷ� �������� ���� ������ ���� ����ŭ ȸ��
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