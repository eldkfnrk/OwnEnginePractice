#pragma once

#include "..\OwnEnginePractice_SOURCE\oepResources.h"
#include "..\OwnEnginePractice_SOURCE\oepTexture.h"

namespace oep {
	void LoadResources() {
		Resources::Load<graphics::Texture>(L"BG", L"..\\Resources\\CloudOcean.png");
	}
}