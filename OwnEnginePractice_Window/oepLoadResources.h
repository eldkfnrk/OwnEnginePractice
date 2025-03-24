#pragma once

#include "..\OwnEnginePractice_SOURCE\oepResources.h"

//사용될 리소스의 형태를 추가(사용하는 리소스의 종류를 모두 #include 해주어야 한다.)
#include "..\OwnEnginePractice_SOURCE\oepTexture.h"

namespace oep {
	//게임에 사용될 모든 리소스를 한 번에 로드해 줄 함수
	void LoadResources() {
		Resources::Load<graphics::Texture>(L"BG", L"..\\Resources\\CloudOcean.png");
	}
}