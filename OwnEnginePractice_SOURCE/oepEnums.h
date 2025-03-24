#pragma once

namespace oep::enums {
	enum class eLayerType {  //레이어
		None,  //기본 타입
		BackGround,
		//필요에 따라 레이어를 추가해주면 된다.
		//Ground,
		//Tree,
		//Rock,
		//Character,
		Player,
		Max = 16,  //레이어는 너무 크게 설정하지 않고 게임에 맞게 필요한 만큼만 사용하면 된다.
	};

	enum class eResourceType {  //리소스의 종류
		//리소스 또한 마찬가지로 필요에 따라 알맞게 타입을 추가해주면 된다.
		Texture,  //이미지 파일 종류를 텍스쳐로 명명
		Audio,  //사운드 파일 종류를 오디오 클립으로 명명
		Prefab,  //데이터 저장할 때 사용
		End,
	};

	//게임을 구동할 때는 컴포넌트의 실행 순서도 중요하다. 만약 위치 정보가 바뀌었는데 이를 반영하지 못하고 화면 출력이 되었다거나 체력이 있는 게임인데 체력의 변화를 반영하지 못하고
	//게임이 진행된다거나 하면 고작 1프레임 밀리는 거지만 게임 플레이에 영향을 줄 수도 있게 되므로 컴포넌트의 실행 순서를 컴포넌트들의 특성을 생각하면서 알맞게 정해야 한다.
	//그리고 그 순서대로 호출이 되어야 하기 때문에 해당 순서를 열거형으로 정의
	enum class eComponentType {  //컴포넌트의 종류
		//컴포넌트의 종류가 늘어나면 늘어난 만큼 추가(이때 추가할 위치는 실행 순서에 알맞게 배치)
		Transform,
		SpriteRenderer,
		Script,
		Camera,
		End,
	};
}