#include "oepSpriteRenderer.h"
#include "oepGameObject.h"
#include "oepTransform.h"
#include "oepTexture.h"

namespace oep {
	SpriteRenderer::SpriteRenderer() : mTexture(nullptr), mSize(math::Vector2::One) /* mImage(nullptr), mWidth(0), mHeight(0)*/
	{
		//mSize를 1.0f, 1.0f로 초기 값을 준 이유는 아무 값도 주지 않으면 0.0f, 0.0f의 값을 갖고 있기 때문에 이미지 출력이 안 될 것이기 때문이다.
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
		if (mTexture == nullptr) {  //텍스처 세팅인 안 된 경우(여기에 걸리면 텍스처 세팅이 안 된 것이니 텍스처 세팅을 확인해야 한다.)
			assert(false);  //return;으로 함수 종료를 해도 되지만 그러면 디버깅 시 무슨 문제가 발생한지 파악이 어렵기 때문에 assert를 사용
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		//이 동작을 이제는 아래에서 진행
		//Gdiplus::Graphics graphics(hdc);
		//graphics.DrawImage(mTexture->mImage(, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp) {  //이미지 파일이 bmp인 경우
			//이 함수는 비트맵을 화면에 출력할 때 사용하는 함수로 인자에 대한 정확한 정보는 아래 링크의 블로그를 통해 알 수 있다.
			//https://blog.naver.com/power2845/50147965306
			//bmp 파일은 투명 값이 없다. 이게 무슨 의미이냐 하면 비트맵 이미지는 반드시 배경색이 있어서 그냥 출력하면 배경까지 같이 출력된다는 의미이다.
			//예를 들어 마리오가 있다고 가정해보자 이때 마리오가 bmp 파일이고 배경색이 흰색인데 배경색을 냅두고 그냥 출력했다하면 마리오 이미지 파일의 배경색이 같이 출력된다.
			//그러면 화면에 마리오만 나와야 하는데 뒤에 흰색 배경도 같이 나오게 되어서 게임 플레이에 지장을 주게 된다. 그래서 bmp 파일을 출력할 땐 이 배경색을 투명화시키고 출력한다.
			//그리고 이 함수의 마지막 인자는 bmp 파일에서 투명화시킬 색을 지정하는 것으로 그러면 해당 색깔은 출력 시 모두 투명화된다.
			//그래서 보통 bmp파일의 배경색은 사용할 리소스 이미지에서 사용하지 않는 색으로 설정해 놓는다.
			//그래서 보통 비트맵 파일의 배경색을 실제로 리소스 이미지에 잘 사용하지 않는 RGB(255, 0, 255) 마젠타 색을 많이 쓴다.
			TransparentBlt(hdc, pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
		}
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png) {  //이미지 파일이 png인 경우
			Gdiplus::Graphics graphics(hdc);  
			graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));
		}
	}

	//void SpriteRenderer::ImageLoad(const std::wstring& path)
	//{
	//	mImage = Gdiplus::Image::FromFile(path.c_str());  //이 동작으로 이미지 파일을 우리 프로그램의 메모리 영역에 올려준다.
	//	mWidth = mImage->GetWidth();  
	//	mHeight = mImage->GetHeight(); 
	//}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}