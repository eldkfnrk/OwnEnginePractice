#pragma once
#include "oepComponent.h"
#include "oepTexture.h"  //�� ������Ʈ�� ������Ʈ�� ȭ�鿡 ����ϴ� �����̱� ������ ȭ�鿡 ���̴� �ؽ��ĸ� �������ش�.

namespace oep {
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//�� ������ ���ҽ��� ����� �̹����� �ε��ϴ� �����̾��� �� ������Ʈ�� ������Ʈ�� render���� �����ϱ� ������
		//�� ������ �̹��� ���ҽ� Ŭ������ �����ϴ� Texture Ŭ������ �̵������ش�.
		//void ImageLoad(const std::wstring& path);
		
		void SetTexture(graphics::Texture* texture) {
			mTexture = texture;
		}

		void SetSize(math::Vector2 size) {
			mSize = size;
		}

		~SpriteRenderer();

	private:
		//Gdiplus::Image* mImage;
		//UINT mWidth;
		//UINT mHeight;
		graphics::Texture* mTexture;  //������Ʈ�� ���� �ؽ���
		math::Vector2 mSize;  //���ҽ� �̹����� ũ��(�� ���� �����ŭ Ű���� ���)
	};
}
