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
		//HBRUSH randomBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand()%255));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randomBrush);

		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Ellipse(hdc, tr->GetX(), tr->GetY(), 100 + tr->GetX(), 100 + tr->GetY());
		//
		//SelectObject(hdc, oldBrush);
		//
		//DeleteObject(randomBrush); 

		//지금까지는 화면에 도형을 그리는 것으로 오브젝트를 대용하여 사용하였는데 이제는 오브젝트가 이미지 리소스를 가지고 있고 이를 출력할 수 있도록 변경
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Gdiplus::Graphics graphics(hdc);  //이미지를 화면에 그리기 위한 dc설정
		graphics.DrawImage(mImage, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));  //화면에 이미지를 그리는 함수 사용(2번째 인자로 이미지의 형태로 여기선 네모 형태에 오브젝트 시작 좌표부터 너비, 높이 크기로 이미지 출력)
	}

	void SpriteRenderer::ImageLoad(const std::wstring& path)
	{
		mImage = Gdiplus::Image::FromFile(path.c_str());  //경로의 이미지 파일을 포인터로 저장
		mWidth = mImage->GetWidth();  //이미지의 너비를 그대로 너비로 사용
		mHeight = mImage->GetHeight();  //이미지의 높이를 그대로 너비로 사용
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}