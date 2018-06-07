
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <srlz/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <gfx/Generated/Module.h>
#endif
        
#include <gfx-obj/Generated/Forward.h>
#include <gfx-obj/Generated/Types.h>
#include <gfx-obj/Api.h>

#include <gfx-obj/Generated/Convert.h>

namespace mud
{
	export_ class MUD_GFX_OBJ_EXPORT mudgfxobj : public Module
	{
	private:
		mudgfxobj();

	public:
		static mudgfxobj& m() { static mudgfxobj instance; return instance; }
	};
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
MUD_GFX_OBJ_EXPORT Module& getModule();
#endif
