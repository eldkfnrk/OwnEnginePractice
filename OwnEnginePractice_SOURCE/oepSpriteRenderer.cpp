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
		Vector2 pos = tr->GetPosition();

		pos = renderer::mainCamera->CalculatePosition(pos);  //카메라가 이동한 만큼 오브젝트들도 모두 이동

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp) {  //이미지 파일이 bmp인 경우
			//https://blog.naver.com/power2845/50147965306
			TransparentBlt(hdc, pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
		}
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png) {  //이미지 파일이 png인 경우
			Gdiplus::Graphics graphics(hdc);  
			graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));
		}
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}