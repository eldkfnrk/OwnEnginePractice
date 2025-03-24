#include "oepResource.h"

namespace oep {
	Resource::Resource(enums::eResourceType type) : mType(type), mPath(L"")
	{
	}

	Resource::~Resource()
	{
	}
}
