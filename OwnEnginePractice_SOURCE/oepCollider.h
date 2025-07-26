#pragma once
#include "oepComponent.h"
#include "oepEnums.h"

namespace oep {
	using namespace enums;
	//Collider Ŭ���� - ������Ʈ�� ���� �浹 ó���� ���� Ŭ����
	//���� ������ ���÷� ���� ���� ������ �ϰ� ������ ������ �������� �޾� ü���� �پ��� ���� �� �� �ִµ� �̶� �� Ÿ�� ������ ���� �ʿ��� ���� �ٷ� 
	//���� �浹�� ó���ϴ� Collider Ŭ������ ���̴�.
	//�� Collider�� ���̵��� �ϸ� ������ �����ϱ� �������� �׷��� �Ǹ� ȭ���� Collider�� ���� ���������� ��Ȯ�� �ð� ���� ������ ������ ���� �ֱ� ������
	//�����δ� �츮 ���� �� ���̵��� ����� �ǰ� Collider�� �ݵ�� ������Ʈ�� ������ ����� �� �ʿ���� �뷫���� �ٻ�ġ ���·� ������ִ°� ȿ�����̴�.
	//�ֳ��ϸ�, �浹ü�� ���� ������ ������Ʈ�� ������ ����� ������ �׸� �� ������ ����ϰ� �����ǵ��� �� ���� ������ �� �����ؼ� ������ ���� �� �ֱ� �����̴�.
	class Collider : public Component
	{
	public:
		Collider(eColliderType type);

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);  //�� �浹ü�� �� �浹�ؼ� �پ��� �� ȣ���� �Լ�
		virtual void OnCollisionStay(Collider* other);  //�� �浹ü�� �浹 �� �������� ���� �� ��, ������ ���°� ���ӵǰ� ���� �� ȣ���� �Լ�
		virtual void OnCollisionExit(Collider* other);  //�� �浹ü�� �浹�ϴٰ� ������ ���������� �� ȣ���� �Լ�(�� �̻� �浹x)

		Vector2 GetOffset() {
			return mOffset;
		}

		void SetOffset(Vector2 offset) {
			mOffset = offset;
		}

		Vector2 GetSize() {
			return mSize;
		}

		void SetSize(Vector2 size) {
			mSize = size;
		}

		UINT32 GetID() {
			return mID;
		}

		eColliderType GetColliderType() {
			return mType;
		}

		~Collider();

	private:
		static UINT32 mCollisionID;  //�浹ü�� �����Ǹ� �ش� �浹ü���� �ο��� ID��(�����Ǵ� ������� ��ȣ�� �ο��� ���̴�.)
		UINT32 mID;  //�浹ü ������ ���� �浹ü ���� ID
		Vector2 mOffset;  //��� �浹ü�� offset�� ������.(offset = ������Ʈ�� ������)
		Vector2 mSize;
		eColliderType mType;  //�ش� �浹ü�� � ������ �浹ü���� �����ϱ� ���� ����(���⼭�� ������ ���簢�������� ����)
	};
}
