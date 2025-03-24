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
		graphics::Texture* mTexture;  //오브젝트에 사용된 텍스쳐
		math::Vector2 mSize;  //리소스 이미지의 크기
	};
}
