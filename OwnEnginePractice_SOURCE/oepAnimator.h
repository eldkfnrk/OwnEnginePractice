#pragma once
#include "oepComponent.h"
#include "oepAnimation.h"

namespace oep {
	class Animator : public Component
	{
	public:
		struct Event  
		{
			void operator=(std::function<void()> func) {
				mEvent = std::move(func);
			}

			void operator()() {
				if (mEvent) {  
					mEvent();  //�Լ� ȣ��(()�� ������ ��ü ȣ��)
				}
			}

			std::function<void()> mEvent;  
		};

		struct Events
		{
			Event startEvent;  //���� �̺�Ʈ
			Event completeEvent;  //�Ϸ� �̺�Ʈ
			Event endEvent;  //���� �̺�Ʈ
		};

		Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration);

		//�ִϸ��̼��� ���� ���� ���ݱ��� ��� �׷��� �ִ� ��������Ʈ ��Ʈ�� ������ �ͼ� ����� �ߴµ� �� ��� ���� �ִϸ��̼ǿ� ���õ� �̹������� �� ������ ��Ƽ�
		//����ϴ� �ִϸ��̼� ���� ������ �߰��ؼ� ����� �� �ֵ��� �� ���̴�.
		//���ڷ� �ִϸ��̼� �̸�, �ҷ��� �ִϸ��̼� ���� ���, ������, ���� ������ �ѱ� �ֱ⸦ ���� ���̴�.
		void CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, Vector2 offset, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		bool IsComplete() {
			return mActiveAnimation->IsComplete();
		}

		Events* FindEvents(const std::wstring& name);

		std::function<void()>& GetStartEvent(const std::wstring& name);  //&�� ����ϴ� ���� ���簡 �ƴ� ���� ��, ������ ������ ���� ���ؼ� �������� ����ϴ� ���̴�.
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

		~Animator();

	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;  //���� ���� ���� �ִϸ��̼�

		bool mbLoop;  //�ִϸ��̼��� ��� �ݺ� ������� ����

		std::map<std::wstring, Events*> mEvents;
	};
}