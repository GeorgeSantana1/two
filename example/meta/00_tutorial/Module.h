
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#endif
        
#include <00_tutorial/Forward.h>
#include <00_tutorial/Types.h>
#include <00_tutorial/Api.h>

#include <meta/00_tutorial/Convert.h>

#ifndef _00_TUTORIAL_REFL_EXPORT
#define _00_TUTORIAL_REFL_EXPORT MUD_IMPORT
#endif

	export_ class _00_TUTORIAL_REFL_EXPORT _00_tutorial : public Module
	{
	private:
		_00_tutorial();

	public:
		static _00_tutorial& m() { static _00_tutorial instance; return instance; }
	};

#ifdef _00_TUTORIAL_MODULE
extern "C"
_00_TUTORIAL_REFL_EXPORT Module& getModule();
#endif
