#pragma once

namespace oep::enums {
	enum class eLayerType {  //레이어
		None,  //기본 타입
		BackGround,
		//Ground,
		//Tree,
		//Rock,
		Animal,
		Player,
		Particle,  //이펙트
		Max = 16,  //레이어는 너무 크게 설정하지 않고 게임에 맞게 필요한 만큼만 사용하면 된다.
	};

	enum class eResourceType {  //리소스의 종류
		Texture,  //이미지 파일
		Audio,  //사운드 파일
		Animation,  //애니메이션
		Prefab,  //게임 오브젝트를 저장할 데이터를 유니티에서 프리팹이라 한다.(언리얼에선 블루프린트라 한다.)
		End,
	};

	enum class eComponentType {  //컴포넌트의 종류
		//컴포넌트의 종류가 늘어나면 늘어난 만큼 추가(이때 추가할 위치는 실행 순서에 알맞게 배치)
		Transform,
		SpriteRenderer,
		Script,
		Animator,
		Camera,
		End,
	};
}