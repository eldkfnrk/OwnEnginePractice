#pragma once

#include "..\OwnEnginePractice_SOURCE\oepResources.h"

//���� ���ҽ��� ���¸� �߰�(����ϴ� ���ҽ��� ������ ��� #include ���־�� �Ѵ�.)
#include "..\OwnEnginePractice_SOURCE\oepTexture.h"

namespace oep {
	//���ӿ� ���� ��� ���ҽ��� �� ���� �ε��� �� �Լ�
	void LoadResources() {
		Resources::Load<graphics::Texture>(L"BG", L"..\\Resources\\CloudOcean.png");
	}
}