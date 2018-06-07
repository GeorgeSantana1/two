//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Widget.h>
#include <ui/Structs/Widget.h>
#include <ui/Style/Styles.h>
#endif

namespace mud
{
namespace ui
{
	void widget_logic(Widget& self)
	{
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::Mouse, EventType::Heartbeat))
			self.enableState(HOVERED);
		else
			self.disableState(HOVERED);
	}

	Widget& widget(Widget& parent, Style& style, void* identity)
	{
		Widget& self = parent.sub(identity).init(style);
		widget_logic(self);
		return self;
	}

	Widget& widget(Widget& parent, Style& style, bool open, Dim length, Dim2<size_t> index)
	{
		Widget& self = parent.sub(&style).init(style, open, length, index);
		widget_logic(self);
		return self;
	}

	Widget& item(Widget& parent, Style& style, cstring content)
	{
		Widget& self = widget(parent, style);
		if(content != nullptr)
			self.setContent(content);
		return self;
	}

	Widget& multi_item(Widget& parent, Style& style, array<cstring> elements, Style* element_style)
	{
		Widget& self = widget(parent, style);
		for(cstring value : elements)
			item(self, element_style ? *element_style : styles().item, value);
		return self;
	}

	Widget& multi_item(Widget& parent, array<cstring> elements, Style* element_style)
	{
		return multi_item(parent, styles().row, elements, element_style);
	}

	Widget& spanner(Widget& parent, Style& style, Dim dim, float span)
	{
		Widget& self = widget(parent, style);
		self.m_frame.set_span(dim, span);
		return self;
	}
}
}
