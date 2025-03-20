#pragma once
#include "CommonInclude.h"
#include "oepComponent.h"

namespace oep {
	//���� ������Ʈ�� ���� ��ġ�� �� �ִ� ������Ʈ�� ���Ѵ�. ���� ������Ʈ�� �̵�, ȸ��, �����ϰ� ���� Ʈ���� ���� �����ϴ� ���� Ŭ������ ���̴�.
	//��, ȭ�� �� �����ϴ� UI, ����, �÷��̾� ����� ��� ���� �����ϴ� ������� �����ϸ� �ȴ�.

	class GameObject
	{
	public:
		GameObject();

		//void Update();
		//void LateUpdate();
		//void Render(HDC hdc);

		//���� ������Ʈ�� ���� ������ �ֱ� ������ �� Ŭ������ ������� �Ļ��Ǵ� ���� ������ ������Ʈ�鿡 �����ϱ� ���� ���� �Լ��� ����� �˾Ƽ� �������ϵ��� ����
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		//void SetPosition(float x, float y) {
		//	mX = x;
		//	mY = y;
		//}

		//���� ������Ʈ�� ������Ʈ�� �߰��ϴ� �Լ�(������Ʈ�� �ڷ����� �� Ŭ������ ���̱� ������ ��� �����ϱ� ���� ���ø� �Լ��� �ۼ�)
		template <typename T>
		T* AddComponent() {
			T* comp = new T();
			comp->SetOwner(this);
			mComponents.push_back(comp);

			return comp;
		}

		//���� ������Ʈ�� ������ �ִ� ������Ʈ���� �������� �Լ�(������Ʈ�� �ڷ����� �� Ŭ������ ���̱� ������ ��� �����ϱ� ���� ���ø� �Լ��� �ۼ�)
		template <typename T>
		T* GetComponent() {
			T* comp = nullptr;
			for (Component* component : mComponents) {
				comp = dynamic_cast<T*>(component);  //dynamic_cast�� �� ��ȯ�� ��� �� �ϳ��� �⺻ Ŭ������ ���� �����ͳ� ������ �ְ� �̸� �Ļ� Ŭ������ ��ȯ�Ϸ��� ��� �ַ� ���Ǵ� ����̴�.
				//�ش� Ÿ�Կ� �´ٸ� �ش� Ÿ������ �� ��ȯ�� ��ü �ּ� ���� ��ȯ�ϰ� �ƴ϶�� nullptr�� ��ȯ���ش�.
				//���࿡ T�� �����ϴ� ������Ʈ Ŭ���� �ڷ����� �ƴ� �ٸ� ������Ʈ Ŭ���� �ڷ����� ��ü�� �� dynamic_cast�� �� ��ȯ�� �õ��ϸ� dynamic_cast�� nullptr�� ��ȯ�Ѵ�.
				if (comp) {  //comp�� nullptr�� ��� if���� �ɸ��� �ȴ�.(��, ���ϴ� �ڷ����� ������Ʈ�� �ƴϸ� for���� Ż���ϵ��� ����) 
					break;
				}
			}

			return comp;
		}

		~GameObject();

	private:
		//���� ������Ʈ�� ��ǥ
		//float mX;
		//float mY;

		//���� ���� ������Ʈ�� ��ǥ�� ���� ���� ������Ʈ�� �����ϴ� ���� �ƴ� Transform ������Ʈ�� �����ϰ� �� ���̴�.
		std::vector<Component*> mComponents;
	};
}
