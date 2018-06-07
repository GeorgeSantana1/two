//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Strung.h>
#include <math/Vec.h>
#endif
#include <ui/Generated/Forward.h>

namespace mud
{
	export_ struct refl_ MUD_UI_EXPORT Image
	{
	public:
		Image(cstring name = "", cstring path = "", const uvec2& size = {})
			: d_name(name), d_path(path), d_size(size)
		{}

		/*attr_*/ string d_name;
		/*attr_*/ string d_path;
		uvec2 d_size;
		uvec2 d_coord = uvec2(0U);

		int d_handle = -1;
		ImageAtlas* d_atlas = nullptr;

		bool d_tile = false;
		bool d_stretch = false;
		bool d_filtering = true;
	};

}
