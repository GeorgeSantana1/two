//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Unique.h>
#endif
#include <ui/Forward.h>

namespace mud
{
	using cstring = const char*;

	using LayoutDef = void(*)(Layout&);
	using InkStyleDef = void(*)(InkStyle&);

	export_ class refl_ MUD_UI_EXPORT Style
	{
	public:
		Style(cstring name, Style* base, LayoutDef layout, InkStyleDef skin = nullptr);
		Style(cstring name, Style& base, LayoutDef layout, InkStyleDef skin = nullptr) : Style(name, &base, layout, skin) {}
		~Style();

		Style(const Style& other);
		Style& operator=(const Style& other);
		
		void prepare();

		InkStyle& state_skin(WidgetState state);
		InkStyle& decline_skin(WidgetState state);

		attr_ Style* m_base;
		attr_ cstring name();
		attr_ Layout& layout();
		attr_ InkStyle& skin();
		
		struct Impl;
		unique_ptr<Impl> m_impl;

		LayoutDef m_layout_def = nullptr;
		InkStyleDef m_skin_def = nullptr;
		bool m_defined;
	};
}
