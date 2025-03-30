#pragma once

#include "..\OwnEnginePractice_SOURCE\oepResources.h"
#include "..\OwnEnginePractice_SOURCE\oepTexture.h"

namespace oep {
	void LoadResources() {
		Resources::Load<graphics::Texture>(L"MAP", L"..\\Resources\\img\\map\\map_pure.png");
		Resources::Load<graphics::Texture>(L"PACMAN0", L"..\\Resources\\img\\pacman\\0.png");
		Resources::Load<graphics::Texture>(L"CHICKEN", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<graphics::Texture>(L"BUBBLE", L"..\\Resources\\Bubble.png");
		Resources::Load<graphics::Texture>(L"MapleEffect", L"..\\Resources\\ezgif.com-gif-maker.png");
	}
}