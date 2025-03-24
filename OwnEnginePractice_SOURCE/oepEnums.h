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

	enum class eResourceType {  //리소스
		//리소스 또한 마찬가지로 필요에 따라 알맞게 타입을 추가해주면 된다.
		Texture,  //이미지 파일 종류를 텍스쳐로 명명
		Audio,  //사운드 파일 종류를 오디오 클립으로 명명
		Prefab,  //데이터 저장할 때 사용
		End,
	};
}