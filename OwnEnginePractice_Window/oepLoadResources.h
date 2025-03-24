#pragma once

#include "..\OwnEnginePractice_SOURCE\oepResources.h"
#include "..\OwnEnginePractice_SOURCE\oepTexture.h"

namespace oep {
	void LoadResources() {
		//Resources::Load<graphics::Texture>(L"BG", L"..\\Resources\\CloudOcean.png");  //�׽�Ʈ�� �ؽ���
		Resources::Load<graphics::Texture>(L"MAP", L"..\\Resources\\img\\map\\map_pure.png");
		Resources::Load<graphics::Texture>(L"PACMAN0", L"..\\Resources\\img\\pacman\\0.png");
	}
}