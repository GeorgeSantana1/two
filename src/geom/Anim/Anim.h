//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Var.h>
#include <obj/Util/Timer.h>
#include <math/Interp.h>
#endif
#include <geom/Generated/Forward.h>

namespace mud
{
	export_ struct MUD_GEOM_EXPORT Anim
	{
		Ref m_object;
		Member* m_member;
		Var m_source_value;
		Var m_target_value;
		float m_duration;
		float m_cursor;
		// Interpolation m_interpolation = LINEAR;
		// Easing m_easing;
	};

	export_ class MUD_GEOM_EXPORT Animator : public Global<Animator>
	{
	public:
		Animator();

		void next_frame(size_t tick, size_t delta);
		void animate(Ref object, Member& member, Var value, float duration);

		Clock m_clock;
		std::vector<Anim> m_animations;
	};

	inline void animate(Ref object, Member& member, Var value, float duration)
	{
		Animator::me().animate(object, member, value, duration);
	}
}
