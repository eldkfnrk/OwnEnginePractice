#pragma once
#include "oepComponent.h"
#include "oepTexture.h"  //이 컴포넌트는 오브젝트를 화면에 출력하는 역할이기 때문에 화면에 보이는 텍스쳐를 가져와준다.

namespace oep {
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//이 동작은 리소스에 사용할 이미지를 로드하는 동작이었고 이 컴포넌트는 오브젝트의 render만을 관리하기 때문에
		//이 동작은 이미지 리소스 클래스를 관리하는 Texture 클래스로 이동시켜준다.
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
		graphics::Texture* mTexture;  //오브젝트에 사용된 텍스쳐
		math::Vector2 mSize;  //리소스 이미지의 크기(이 값에 배수만큼 키워서 사용)
	};
}
