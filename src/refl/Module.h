//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <refl/Forward.h>

#include <stdint.h>

namespace mud
{
	export_ using cstring = const char*;
	
	export_ class refl_ MUD_REFL_EXPORT Module
	{
	public:
		Module(cstring name, vector<Module*> deps);

		attr_ cstring m_name;
		attr_ vector<Module*> m_deps;
		attr_ vector<Type*> m_types;
		attr_ vector<Function*> m_functions;

		attr_ cstring m_path;
		void* m_handle;
		uint64_t m_last_modified;
	};

#ifdef _WIN32
	typedef Module& (__cdecl *GetModule)(void);
#else
	typedef Module& (*GetModule)(void);
#endif
}
