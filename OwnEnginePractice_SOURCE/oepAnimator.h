#pragma once
#include "oepComponent.h"
#include "oepAnimation.h"

namespace oep {
	//Animator 클래스 - 애니메이션들을 유기적으로 묶어주는 클래스
	//게임의 경우 플레이어 캐릭터가 가만히 서 있을 때도 그에 맞는 애니메이션이 있고 키 입력에 따라 이동과 점프, 공격 등의 동작들이 있게 되는데 이 모든 동작들에 맞는 애니메이션을
	//만들어 캐릭터가 가지고 있게 한다. 이때 가만히 있다가 이동 키 입력 시 이동 애니메이션을 출력하고 키를 떼면 가만히 있고 이동 중에 공격 키 입력 시 공격 애니메이션을 출력하는 등의
	//애니메이션이 왔다갔다 하면서 출력되게 해주는 역할을 하는 것이 바로 Animator이다.
	class Animator : public Component
	{
	public:
		Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//애니메이터에서 애니메이션을 만들어서 트리에 저장하는 함수
		//인자들은 애니메이션의 키값, 애니메이션에 사용할 그림을 모아놓은 스프라이트 시트(비트맵 파일), 애니메이션에 사용할 그림의 시작 위치, 그림의 크기,
		//그림의 중앙 위치, 애니메이션에 사용할 스프라이트의 길이, 그림이 다음 장으로 넘어가는 시간을 의미한다.
		//지금까지는 게임 오브젝트의 시작 위치를 오브젝트의 위치로 사용했지만 이러면 문제점이 우리가 생각하는 오브젝트의 위치와 실제 컴퓨터가 인지하는 위치의 차이가 있다는 것이다.
		//이를 알고 있는 상태라면 문제가 없지만 보통 위치라고 하면 오브젝트의 바닥에서 좌우의 중앙을 생각한다. 그렇기 때문에 이를 따로 정의해주어야 한다. 이를 offset으로 정의하였다.
		void CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration);

		//애니메이션을 찾는 함수(재생하기 전에 어떤 애니메이션을 재생할지를 찾아야 하기 때문에 함수 정의)
		Animation* FindAnimation(const std::wstring& name);

		//애니메이션을 재생하는 함수
		//보통 애니메이션은 반복하는 것이 기본 값이니 매개변수에 디폴트 값 true를 넣어줌으로써 반복하지 않을 것만 값을 넣으면 되도록 설정
		void PlayAnimation(const std::wstring& name, bool loop = true);

		~Animator();

	private:
		//보통 게임에는 최소 20개에서 트리플 A급의 대형 게임같은 경우 수 백개에 달하는 애니메이션이 있는데 이를 저장하기 위해 트리 사용
		//왜냐하면 Animator는 애니메이션 간의 이동이 잦은데 이때 벡터에 저장한 경우 애니메이션을 찾는데 많은 시간을 소비하게 되니 키값을 주고 찾을 수 있는 트리를 사용
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;  //현재 실행 중인 애니메이션

		//애니메이션이 계속 반복되어야 하는지 아니면 애니메이션이 동작한 후 끝나야하는지를 정하는 bool 변수
		//애니메이션이 계속 반복되어야 자연스러운 경우가 있고 애니메이션이 한 번만 보여지고 끝나야 자연스러운 경우가 있으니 이를 정확히 파악하고 루프를 시킬지를 정해야 한다.
		bool mbLoop;
	};
}