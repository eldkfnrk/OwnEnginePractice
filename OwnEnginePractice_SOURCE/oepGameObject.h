#pragma once
#include "CommonInclude.h"

namespace oep {
	//GameObject Ŭ���� - ���� ������Ʈ�� ���� �⺻ Ʋ�� �� Ŭ����
	//����Ƽ������ ������Ʈ �𸮾󿡼��� ���Ͷ�� �θ���.
	class GameObject
	{
	public:
		GameObject();

		//������ Application Ŭ������ �ִ� GameObject�� ���õ� ���۵��� ���� Application���� �����ϰ� ���� ���� GameObject �ȿ��� ������ �����ϰ�
		//�ش� �Լ��� Application������ �˸°� �����ͼ� ����� �� �ֵ��� �����ϱ� ���� �Լ���
		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		//���� ���� ������ Ŭ���� ������ ���� �����ϸ� ���� Get, Set �Լ��� ������ �ʿ䰡 ��� ���� �ٸ� Ŭ�������� ���� �����ϴ� �������� �ڵ尡
		//������� ���� ª�� ������ �� �־ ����.
		////private����� ���� ������ �� ������ ���� �����ϵ��� Get, Set �Լ� ����
		//void SetPosition(float x, float y) {
		//	mX = x;
		//	mY = y;
		//}

		//float GetPositionX() {
		//	return mX;
		//}

		//float GetPositionY() {
		//	return mY;
		//}

		~GameObject();

	private:
		//���� ������Ʈ�� ��ǥ
		float mX;
		float mY;
	};
}
