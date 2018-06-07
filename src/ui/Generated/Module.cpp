#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Generated/Module.h>
#endif

#ifdef MUD_UI_REFLECT
#ifndef MUD_MODULES
#include <ui/Generated/Convert.h>
#endif
#define MUD_UI_REFLECTION_IMPL
#include <ui/Generated/Meta.h>
#endif

namespace mud
{
	mudui::mudui()
		: Module("mud::ui")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();
        mudctx::m();

#ifdef MUD_UI_REFLECT
        // setup reflection meta data
		mudui_meta(*this);
#endif
	}
}

#ifdef MUD_UI_MODULE
extern "C"
MUD_UI_EXPORT Module& getModule()
{
	return mudui::m();
}
#endif
