#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Generated/Module.h>
#endif

#ifdef MUD_OBJ_REFLECT
#ifndef MUD_MODULES
#include <obj/Generated/Convert.h>
#endif
#define MUD_OBJ_REFLECTION_IMPL
#include <obj/Generated/Meta.h>
#endif

namespace mud
{
	mudobj::mudobj()
		: Module("mud::obj")
	{
        // ensure dependencies are instantiated

#ifdef MUD_OBJ_REFLECT
        // setup reflection meta data
		mudobj_meta(*this);
#endif
	}
}

#ifdef MUD_OBJ_MODULE
extern "C"
MUD_OBJ_EXPORT Module& getModule()
{
	return mudobj::m();
}
#endif
