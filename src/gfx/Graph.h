//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Graph/Node.h>
#endif
#include <gfx/Generated/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Light.h>

namespace mud
{
	class SoundManager;
	class Sound;

	export_ class refl_ MUD_GFX_EXPORT Gnode : public Graph<Gnode>
	{
	public:
		Gnode();
		Gnode(Scene& scene, SoundManager* sound_manager = nullptr);
		Gnode(Gnode* parent, void* identity);
		~Gnode();
		
		meth_ Gnode& begin();

		Scene* m_scene = nullptr;
		Node3* m_attach = nullptr;
		Node3* m_node = nullptr;
		Item* m_item = nullptr;
		Animated* m_animated = nullptr;
		Particles* m_particles = nullptr;
		Light* m_light = nullptr;
		//GIProbe* m_gi_probe = nullptr;
		SoundManager* m_sound_manager = nullptr;
		Sound* m_sound = nullptr;
	};
}
