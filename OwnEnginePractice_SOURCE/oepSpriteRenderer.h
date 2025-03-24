#pragma once
#include "oepComponent.h"
#include "oepTexture.h"  

namespace oep {
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		
		void SetTexture(graphics::Texture* texture) {
			mTexture = texture;
		}

		void SetSize(math::Vector2 size) {
			mSize = size;
		}

		~SpriteRenderer();

	private:
		graphics::Texture* mTexture;  //������Ʈ�� ���� �ؽ���
		math::Vector2 mSize;  //���ҽ� �̹����� ũ��
	};
}
