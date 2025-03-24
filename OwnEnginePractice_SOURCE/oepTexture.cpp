#include "oepTexture.h"
#include "oepApplication.h"

//이렇게 하지 않으면 전역 변수 사용이 불가능하다.
extern oep::Application application;  //이 파일에서는 main 함수에 선언된 전역 변수를 모르기 때문에 extern 키워드를 통해 이 전역 변수가 있음을 이 파일에 알려준다.


namespace oep::graphics {
	Texture::Texture() : Resource(enums::eResourceType::Texture), mType(eTextureType::None), mImage(nullptr), mBitmap(nullptr), mHdc(nullptr), mWidth(0), mHeight(0)
	{
		//부모 클래스에 디폴트 생성자 없이 따로 정의한 생성자가 있다면 부모 생성자를 따로 호출해주어야 하는데 그 호출은 변수의 초기화 부분에서 이루어지면 된다.(정의 부분에서 해도 된다.)
	}

	//void Texture::ImageLoad(const std::wstring& path)
	//{
	//	mImage = Gdiplus::Image::FromFile(path.c_str());  //이 동작으로 이미지 파일을 우리 프로그램의 메모리 영역에 올려준다.
	//	mWidth = mImage->GetWidth();
	//	mHeight = mImage->GetHeight();
	//}

	HRESULT Texture::Load(const std::wstring& path)
	{
		//경로의 확장자명을 가지고 와서 저장(확장자명을 통해 이 이미지 파일의 종류가 무엇인지 알 수 있기 때문에 이를 가져와야 한다.)
		//substr 함수는 문자열의 일부를 가져오는 함수이다.
		//그리고 find_last_of 함수는 문자열의 맨 뒤부터 인자로 전달받은 문자를 찾는 함수이다.(동일한 문자가 몇 개이든 맨 뒤에서부터 찾아서 가장 먼저 찾은 문자에서 멈춘다.)
		//그러니 path.substr(path.find_last_of(L".")); 의 뜻은 문자열(path)의 뒤부터 문자 "."을 찾은 후 그 문자부터 문자열 끝까지 가져온다는 의미이다.
		//여기서 +1은 무슨 의미냐 하면 find_last_of 함수를 통해 "."을 찾으면 "." 바로 다음 문자를 찾으라는 의미이다.
		//즉, path.find_last_of(L".") + 1 은 맨 뒤에서부터 문자 "."을 찾고 그 문자의 바로 뒤에 있는 문자를 반환한다는 의미이다.
		//그래서 path.substr(path.find_last_of(L".") + 1); 는 경로에서 "." 바로 뒤 문자부터 가져오니 확장자명을 가져올 수 있는 것이다.
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		if (ext == L"bmp") {  //bmp일 경우
			mType = eTextureType::Bmp;

			//LoadImageW는 경로에 있는 비트맵 파일의 이미지를 가져오는 함수이다.
			//1번째 인자는 인스턴스로 그냥 nullptr을 넣어주면 되고 2번째 인자는 경론데 자료형이 wchar_t의 포인터 즉, 지금까지 wstring을 사용했을 때 실제로는 Wchar_t의 배열을
			//저장한 객체를 사용한 것이기 때문에 해당 객체에 저장된 문자 배열의 주소를 넣어주면 된다. 그리고 3번째 인자는 가져올 이미지 타입인데 이는 간단히 IMAGE_BITMAP를 넣어준다.
			//4~5번째 인자는 어디서부터 가져올지를 설정하는 것으로 이번엔 전부 가져올 것이기 때문에 0,0에서 부터 가져오도록 0을 전달한다. 마지막 인자는 그냥 이거라고 기억만 하자.
			//이 함수는 반환형이 HANDLE이기 때문에 비트맵 자료형에 맞게 형 변환을 해주어야 한다.
			//이미지가 잘 로드되었다면 문제가 없었을테지만 로드가 안 됐다면 즉, 로드가 실패했다면 함수는 nullptr을 반환한다.
			//이렇게 비트맵 사용은 복잡하지만 png파일보다 속도는 약간 빠르다.
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr) {
				return S_FALSE;  //false와 같은 값인데 HRESULT형의 값을 반환해야 하기 때문에 S_FALSE를 반환
				//이 자료형은 S_OK와 S_FALSE라는 값을 갖는데 S_OK는 0, S_FALSE는 1을 가지고 있다.(기존의 true, false와 반대이다.)
			}

			BITMAP info = {};  //가져온 비트맵의 정보를 저장할 객체

			//비트맵의 정보를 저장
			//HBITMAP에서 BITMAP의 크기만큼 데이터를 가져와서 info의 포인터에다가 저장(포인터를 가져가는 것이니 내부에서 값이 바뀌면 해당 포인터의 값도 바뀌는 것을 활용한다는 것을 알 수 있다.)
			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			//비트맵은 반드시 dc와 짝을 이루기 때문에 비트맵 개수만큼 dc도 있어야 한다.
			//그러니 비트맵에 대응하는 dc를 반드시 생성하고 연결하여야 한다.
			HDC mainDC = application.GetHdc();

			//dc를 만들기 위해선 원본 dc가 필요하기 때문에 이 프로그램의 메인 dc를 가져와서 새 dc 생성
			mHdc = CreateCompatibleDC(mainDC);  //이렇게 dc를 만들면 그 dc 안에는 디폴트 비트맵(새하얀 도화지)가 같이 만들어진다.

			//디폴트 비트맵이 있기 때문에 이를 지우고 가져온 비트맵과 연결시켜주어야 한다.
			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);  //SelectObject를 하면 기존에 가지고 있던 오브젝트는 뱉어준다.
			DeleteObject(oldBitmap);  //이를 메모리 상에서 지워주지 않으면 메모리 릭이 발생. 그러니 안 쓸거라면 반드시 지워줘야 한다.
		} 
		else if (ext == L"png") {  //png일 경우
			mType = eTextureType::Png;

			//png일 경우 단순하게 SpriteRenderer 컴포넌트에서 기존에 이미지를 로드하던 방법 그대로 로드하면 된다.
			mImage = Gdiplus::Image::FromFile(path.c_str());  //이 동작으로 이미지 파일을 우리 프로그램의 메모리 영역에 올려준다.

			if (mImage == nullptr) {
				return S_FALSE;
			}

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		
		return S_OK;  //문제없이 파일이 로드되었다면 S_OK를 반환
	}

	Texture::~Texture()
	{
	}
}