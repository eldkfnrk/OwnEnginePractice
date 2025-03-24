#pragma once
#include "oepComponent.h"

namespace oep {
	//Script 클래스 - 컴포넌트 중 하나로 작성한 로직을 실행시키는 컴포넌트
	//오브젝트들 중에서 게임 플레이에 직접적인 영향을 주는 오브젝트들은 저마다의 행동이 있어야 한다. 플레이어는 게임에 맞는 움직임을 가져야 하고 만약 rpg나 메트로베니아같은 게임은
	//플레이어를 공격하는 적도 있고 게임을 클리어할 때 사용해야 하는 사물 등이 저마다의 동작을 하고 있어야 한다. 이를 저마다 알맞게 적절한 로직을 만들어 주어야 한다.
	//그리고 그렇게 만든 로직에 맞게 오브젝트가 동작해야 하는데 이때 이 로직을 실행해주는 컴포넌트가 Script 컴포넌트다.
	
	//이 클래스 하나로는 모든 오브젝트의 로직을 구현할 수도 없고 그렇게 해서도 안 되기 때문에 이 클래스는 기본 클래스로 여러 파생 클래스를 만들어 각 클래스마다 각 오브젝트의
	//로직을 구현하는 방식으로 이 컴포넌트는 사용된다.(씬과 오브젝트 클래스와 같다고 볼 수 있다.)
	class Script : public Component
	{
	public:
		Script();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~Script();

	private:

	};
}
