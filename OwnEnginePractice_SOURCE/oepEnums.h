#pragma once

//이 헤더 파일은 사용할 열거형들을 하나의 파일로 모아서 관리하기 위한 파일
//구현부가 필요없으니 대응하는 cpp파일이 없다.

namespace oep::enums {
	enum class eLayerType {  //레이어
		None,  //기본 타입
		BackGround,
		Ground,
		Tree,
		Rock,
		//Character,
		Player,
		Max = 16,  //레이어는 너무 크게 설정하지 않고 게임에 맞게 필요한 만큼만 사용하면 된다.
	};
}