#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <geom/Generated/Module.h>
#endif

#ifdef MUD_GEOM_REFLECT
#ifndef MUD_MODULES
#include <geom/Generated/Convert.h>
#endif
#define MUD_GEOM_REFLECTION_IMPL
#include <geom/Generated/Meta.h>
#endif

namespace mud
{
	mudgeom::mudgeom()
		: Module("mud::geom")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudmath::m();

#ifdef MUD_GEOM_REFLECT
        // setup reflection meta data
		mudgeom_meta(*this);
#endif
	}
}

#ifdef MUD_GEOM_MODULE
extern "C"
MUD_GEOM_EXPORT Module& getModule()
{
	return mudgeom::m();
}
#endif
