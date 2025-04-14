#include "oepSpriteRenderer.h"
#include "oepGameObject.h"
#include "oepTransform.h"
#include "oepTexture.h"
#include "oepRenderer.h"
#include "oepCamera.h"

namespace oep {
	SpriteRenderer::SpriteRenderer() : Component(enums::eComponentType::SpriteRenderer), mTexture(nullptr), mSize(math::Vector2::One)
	{
		
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::LateUpdate()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr) { 
			assert(false);  
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();	
		Vector2 pos = tr->GetPosition();  //오브젝트의 위치 정보
		float rotation = tr->GetRotation();  //오브젝트의 각도
		Vector2 scale = tr->GetScale();  //오브젝트의 크기

		pos = renderer::mainCamera->CalculatePosition(pos);  //카메라가 이동한 만큼 오브젝트들도 모두 이동

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp) {  //이미지 파일이 bmp인 경우
			//https://blog.naver.com/power2845/50147965306
			if (mTexture->IsAlpha()) {
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 225;  //0(transparent-투명) ~ 255(Opaque-불투명) 의 값으로 설정 가능

				AlphaBlend(hdc, pos.x, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y, mTexture->GetHdc()
					, 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), func);
			}
			else {
				TransparentBlt(hdc, pos.x, pos.y, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y
					, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png) {  //이미지 파일이 png인 경우
			//애니메이션이 투명화를 할 수 있게 설정했으니 스프라이트렌더러도 투명화가 가능하도록 설정
			Gdiplus::ImageAttributes imgAttributes = {};  //이미지의 속성을 저장하는 구조체

			imgAttributes.SetColorKey(Gdiplus::Color(100, 100, 100), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);  

			//이미지를 각도만큼 돌리도록 하는 설정
			graphics.TranslateTransform(pos.x, pos.y);  //회전할 때 중심이 되는 좌표 설정
			graphics.RotateTransform(rotation);  //인자로 전해지는 값이 각도로 인자 값만큼 회전
			graphics.TranslateTransform(-pos.x, -pos.y);

			//graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));
			//파일을 투명화하고 출력할 수 있도록 위의 코드를 수정
			//화면에 출력하는 사이즈와 이미지의 사이즈도 함께 곱해주어 화면에 출력시켜준다.(텍스쳐의 크기와 출력 크기는 별개)
			graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y)
				, 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), Gdiplus::UnitPixel, nullptr);
		}
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}