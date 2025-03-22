#pragma once
#include "oepEntity.h"
#include "CommonInclude.h"
#include "oepGameObject.h"

namespace oep {
	class Layer
	{
	public:
		Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameObj);

		~Layer();

	private:
		std::vector<GameObject*> mGameObjects;  //�� ���̾ ��ġ�� ���� ������Ʈ�� �����ϴ� ����
	};
}
