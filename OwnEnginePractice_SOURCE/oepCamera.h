#pragma once
#include "oepComponent.h"
//#include "oepGameObject.h"  //컴포넌트와 게임 오브젝트는 서로 참조를 하고 있기 때문에 동시에 참조하면 순환 참조가 발생
//그래서 이 카메라는 컴포넌트이기 때문에 게임 오브젝트 참조를 하는 대신 전방 선언으로 이 클래스의 존재만 알려주는 방식으로 진행

namespace oep {
	using namespace oep::math;

	//Camera 클래스 - 화면에 출력되는 부분을 지정할 컴포넌트 클래스
	//게임을 하다보면 전체 화면을 보여주고 플레이를 하는 게임들도 있지만 마리오나 메이플같은 게임들을 보면 화면에 배경 전체를 띄워주는 것이 아니라
	//캐릭터를 중심으로 캐릭터를 따라다니면서 캐릭터의 주변을 화면에 출력해주고 있다. 그 역할을 하는 것이 카메라 컴포넌트이다.
	//영화에서 주인공을 중심으로 혹은 어떤 사물을 비추다가 전체 화면을 비추는 움직임을  게임에서도 비슷한 역할을 해야 하는 것이 있어야 하기 때문에 만드는 컴포넌트이다.
	class Camera : public Component
	{
	public:
		Camera();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//오브젝트의 위치 정보를 인자로 받아 카메라의 이동 거리를 빼서 카메라와 오브젝트의 거리를 구하는 함수
		Vector2 CalculatePosition(Vector2 pos) {
			//카메라의 특징으로는 카메라의 이동 방향과 반대로 오브젝트들이 이동한다는 것이다. 
			//그렇기 때문에 오브젝트의 위치에서 카메라와의 거리를 빼주는 것이다.(정방향은 + 연산을 역방향은 - 연산을 해주어야 한다.)
			return pos - mDistance;
		}

		~Camera();

	private:
		class GameObject* mTarget;  //카메라가 따라다닐 타겟(순환 참조를 방지하는 전방 선언)

		Vector2 mDistance;  //카메라와 카메라가 비추는 대상의 거리
		Vector2 mResolution;  //화면 해상도
		Vector2 mLookPosition;  //카메라가 바라보는 위치 정보
	};
}
