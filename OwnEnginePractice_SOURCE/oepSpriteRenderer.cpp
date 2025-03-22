#include "oepSpriteRenderer.h"
#include "oepGameObject.h"
#include "oepTransform.h"

namespace oep {
	SpriteRenderer::SpriteRenderer() : mImage(nullptr), mWidth(0), mHeight(0)
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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Gdiplus::Graphics graphics(hdc);  
		graphics.DrawImage(mImage, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));
	}

	void SpriteRenderer::ImageLoad(const std::wstring& path)
	{
		mImage = Gdiplus::Image::FromFile(path.c_str());  
		mWidth = mImage->GetWidth();  
		mHeight = mImage->GetHeight(); 
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}