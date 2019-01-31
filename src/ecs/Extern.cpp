#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ecs;
#else
#include <stl/vector.hpp>
#include <ecs/Extern.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_ECS_EXPORT vector<Buffer*>;
	template class MUD_ECS_EXPORT vector<EntityData>;
	template class MUD_ECS_EXPORT vector<EntityStream>;
	template class MUD_ECS_EXPORT vector<unique<Buffer>>;
}
