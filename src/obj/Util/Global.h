//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>

namespace mud
{
	export_ template <class T>
	class Global
	{
	public:
		static T& me() { return instance; }
		static T instance;
	};

	template <class T>
	T Global<T>::instance;

	export_ template <class T>
	class LazyGlobal
	{
	public:
		static T& me() { static T instance; return instance; }
	};
}
