#include "oepCollider.h"
#include "oepScript.h"
#include "oepGameObject.h"

namespace oep {
	UINT32 Collider::mCollisionID = 1;

	Collider::Collider(eColliderType type) : Component(eComponentType::Collider)
		, mID(mCollisionID++), mOffset(Vector2::Zero), mSize(Vector2::One), mType(type) {
		
	}

	void Collider::Initialize() {

	}

	void Collider::Update() {

	}

	void Collider::LateUpdate() {

	}

	void Collider::Render(HDC hdc) {

	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionExit(other);
	}

	Collider::~Collider() {

	}
}