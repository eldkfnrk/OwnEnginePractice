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
		//�ʱ�ȭ�� �ݵ�� ���� ���� �־�� ������ �߻����� �ʴ´�. �׷��� �迭�� �ε��� ���� �ǹ��ϴ� ������ ���� 0�� �ƴ� -1�� �־��־�� �Ѵ�.
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
			//ī�޶� ������ ī�޶� �������� ��ġ�� ������־�� �Ѵ�.(��� ������Ʈ���� ī�޶� �������� ��ġ�� ���Ǿ�� �Ѵ�.)
			pos = renderer::mainCamera->CalculatePosition(pos);
		}

		//AlphaBlend �Լ� ��� �� �ݵ�� �������־�� �� ���� ��
		//�� �Լ��� ����Ϸ��� �ݵ�� �̷��� ������ ���־�� �ϸ� �� ������ �׳� �̷��� ���� �ɷ� ���ǰ� ������ �ִ�.(
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		//�� ������ ����ڰ� �ڽſ� �˸°� ���� �������־�� �Ѵ�.
		//�� ���� ����� �̹����� ������ ���ڰ� �������� ���������°ǵ� �̰� ����ϴ� ������ �÷��̾ ���ݴ����� �� �ǰ� ��ǿ� �� �� �ǰݵ����� �����ֱ� ���� ���������� ���ϴ�
		//���ó�� �̹����� ��� ���� ������������ �ϱ� ���ؼ� ���� �����Ѵ�.
		func.SourceConstantAlpha = 225;  //0(transparent-����) ~ 255(Opaque-������) �� ������ ���� ����

		Sprite sprite = mAnimationSheet[mIndex];
		HDC imgHdc = mTexture->GetHdc();

		//TransParenrBlt �Լ�ó�� ��Ʈ���� ����ϴ� �Լ��ε� ���ڷ� ���� ���� ���� �� �ִ� �Լ�
		//�� �Լ��� ����ϴ� ������ ���� ���� �� �� �ֱ� �������� �̹����� ���������� �ϴ� ��찡 ���� �� �ִ� ��� TransParenrBlt �Լ��� �װ��� �Ұ��ѵ� �� �Լ��� �����ϱ� �����̴�.
		//�� �Լ��� ����� �� �ִ� ������ �ִµ� �� �����̶� �ش� �̹��� ���� ä���� �־�� �Ѵ�.(���伥���� �̹����� ������ �� ä���̶�� �� �ִµ� �׶� �� ���� ���� ������ ���� ���� ä��)
		//�̹����� ���� ä���� �ִ����� Ȯ���Ϸ��� �̹��� �Ӽ��� ���� �ڼ��� ���� ��Ʈ ������ ���� ���� �� �� �ִ�. 24�� ���� �̹��� 32�� �ִ� �̹����̴�.
		//TransParenrBlt �Լ��� ���ڿ� �����ѵ� ������ ���ڸ� �տ��� �������� ���� �������ִ� �Ϳ� ���̰� �ִ�.
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
			sprite.leftTop.x = leftTop.x + size.x * i;  //��������Ʈ�� ���� ��ġ�� x���� ���ϰ� ���� size�� x ũ�⸸ŭ ���̰� ���� ������ �̿� ���� ���� ���
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