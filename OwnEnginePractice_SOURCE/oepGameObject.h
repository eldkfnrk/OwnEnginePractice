#pragma once
#include "CommonInclude.h"
#include "oepComponent.h"
//#include "oepObject.h"

//���� ���� oepObject.h ������ �������� �ʰ� ���� ���� �����̽����ٰ� ���� �ϴ� ������ �̹� �ش� ������ �� Ŭ������ ����ִ� ������ �����ϰ� �ֱ� ������ ��ȯ ������ 
//�߻��ϴ� ���� ���� �Ʒ��� ���� Ŭ���� ���� friend ������ �� �� �ֵ��� �ϱ� ���ؼ��̴�.
namespace oep::object {
	//static �ƴϸ� ������ �߻��Ѵ�.(������ �𸣰ڴ�.)
	static void Destroy(GameObject* gameObj);
}

namespace oep {
	class GameObject
	{
	public:
		//friend������ �ش� Ŭ���� �ܺ��� �Լ��� ��ü ���� �ش� Ŭ���� ������ private ��������� ���� ������ �����ϴٰ� �����ϴ� ���̴�.
		//�׷��� �Ʒ��� �Լ��� ���� �� Ŭ������ private ������� ���� ������ �����ѵ� �� ��� ��ü������ ĸ��ȭ�� �������� ������ ���� �ʿ��� ��� ���� �������� �ʾƾ� �Ѵ�.
		friend void object::Destroy(GameObject* gameObj);

		enum class eState {
			Active,  //������Ʈ Ȱ��ȭ ����
			Paused,  //������Ʈ ��Ȱ��ȭ ����(�� ����� �� �ֵ��� �������� �ʴ� ����)
			Dead,  //������Ʈ ��Ȱ��ȭ ����(���� ���)
			End,
		};

		GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent() {
			T* comp = new T();
			comp->SetOwner(this);

			mComponents[(UINT)comp->GetType()] = comp;  //���� puch_back ��� ������ ��ġ�� ���ҿ� ����
			//mComponents.push_back(comp);

			return comp;
		}

		template <typename T>
		T* GetComponent() {
			T* comp = nullptr;
			for (Component* component : mComponents) {
				comp = dynamic_cast<T*>(component); 
				if (comp) {  
					break;
				}
			}

			return comp;
		}

		eState GetState() {
			return mState;
		}

		void SetActive(bool power) {
			//������Ʈ�� Ȱ��ȭ�� �������� ���ڷ� �޾� true�̸� Active���·� false��� Paused���·� ���� 
			if (power == true) {
				mState = eState::Active;
			}
			if (power == false) {
				mState = eState::Paused;
			}
		}

		bool IsActive() {
			return mState == eState::Active;
		}
		//void Death() {  //������Ʈ�� ���¸� Dead�� �ٲٴ� �Լ�
		//	mState = eState::Dead;
		//}

		~GameObject();

	private:
		void initializeTransform();
		void death() {  //������Ʈ�� ���¸� Dead�� �ٲٴ� �Լ�
			mState = eState::Dead;
		}

	private:
		std::vector<Component*> mComponents;
		eState mState;  //������Ʈ�� ����
	};
}
