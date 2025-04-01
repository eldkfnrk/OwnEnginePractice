#pragma once
#include "oepComponent.h"
#include "oepAnimation.h"

namespace oep {
	class Animator : public Component
	{
	public:
		struct Event  //�̺�Ʈ ���õ� �͵��� ��Ƴ��� ����ü
		{
			//���� ������ ���� �׳� =�����ڸ� ���� ���� �ƴ϶� std::move()�� �̿��Ͽ� �־��־�� �Ѵ�. �׷��� �Ź� �̸� ���ֱ�� �������� �� ������ ������ �����ε��Ͽ�
			//���� �����ڸ� ����� ���⿡�� ���ϰ� ���� ����� �� �ֵ��� =������ �����ε��� ���ش�.
			void operator=(std::function<void()> func) {
				mEvent = std::move(func);
			}

			//���� �Ʒ��� ���� ������ ��ü�� �׳� �̸��� ������ ����Ѵ�. �׷��� �� ��ü�� �Լ�ó�� ����ϸ� �� �� ���ϰ� ����� �� ���� ���̴�.
			//�׷��� ������ �Լ� �����͸� ����� �� �Լ�ó�� ����� �� �ֵ��� ()�����ڸ� �����ε� ���ش�. 
			//�ͼ����� �ʰų� �����Ǽ� ����� ��� ������ ������ �� ������ �Լ��� ���� ��Ȯ�� �����ֱ� ���� ����ϴ� �͵� �ִ�.
			void operator()() {
				//�Լ� �����Ϳ� ����� �Լ��� ���� ���� �����ؾ� �Ѵ�.
				if (mEvent) {  
					mEvent;  //�Լ�ó�� ���۽�ų �� �����δ� �̿� ���� �����ϴ� ���̴�.
				}
			}

			//STL���� �Լ� �����͸� ����ϴ� ���(�Լ� �����͸� STL�� ��üȭ ���ѳ��� ��)
			//<>�ȿ� �Լ� �������� �ڷ����� ���� Ÿ���� �־��ִ� ���̴�.(���� ���ӿ��� ������ ���޺��ٴ� �� ���� ������ ���Ƽ� �ַ� void���� ����� ������ ����)
			std::function<void()> mEvent;  //void (*StartEvent)(); �� �Լ� �����Ϳ� �����ѵ� STL�� �̿��ϴ� ���� �� �� �������� ����.(������ ����ϸ� �ȴ�.)
		};

		struct Events
		{
			Event mStartEvent;  //���� �̺�Ʈ
			Event mCompleteEvent;  //�Ϸ� �̺�Ʈ
			Event mEndEvent;  //���� �̺�Ʈ
		};

		Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		bool IsComplete() {
			return mActiveAnimation->IsComplete();
		}

		~Animator();

	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;  //���� ���� ���� �ִϸ��̼�

		bool mbLoop;  //�ִϸ��̼��� ��� �ݺ� ������� ����

		//�̺�Ʈ
		//�� �ִϸ��̼Ǹ��� �̺�Ʈ���� ������ �־�� �ϱ� ������ ������ Ű ���� ������ Ʈ���� �ִϸ��̼Ǹ����� �̺�Ʈ ����
		std::map<std::wstring, Events> mEvents;
	};
}