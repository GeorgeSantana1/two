//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/memory.h>
#include <stl/map.h>
#endif
#include <lang/Forward.h>
#include <lang/Script.h>

namespace mud
{
	class WrenContext;

	struct WrenFunctionDecl
	{
		string functions;
		string bind;
	};

	export_ class refl_ MUD_LANG_EXPORT WrenInterpreter final : public Interpreter
	{
	public:
		WrenInterpreter(bool import_symbols);
		~WrenInterpreter();

		virtual void declare_types() final;

		virtual const Var& get(const string& name, Type& type) final;
		virtual void set(const string& name, const Var& value) final;

		virtual const Var& getx(array<cstring> path, Type& type) final;
		virtual void setx(array<cstring> path, const Var& value) final;

		virtual void call(const string& code, Var* result = nullptr) final;
		virtual void virtual_call(Method& method, Ref object, array<Var> args) final;

		unique<WrenContext> m_context;

		void create_virtual(Ref object);

		map<void*, const TextScript*> m_virtual_scripts;
	};
}
