{
	"project": "${ module.namespace }${ module.name }.h",
	"target": "${ module.namespace }${ module.name }.h",
	"sources": [
% for h in module.headers :
		"${ module.subdir }/${ h }"${ "," if not loop.last else "" }
% endfor
	],
	"include_paths": [
		""
	],
	"includes_map": {
% for m in module.dependencies :
		"${ m.name }/": "${ m.namespace }${ m.name }.h"${ "," if not loop.last else "" }
% endfor
	},
	"ignore": [
		"Generated"
	],
	"clean_strings": [
		"//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net",
		"//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.",
		"//  This notice and the license may not be removed or altered from any source distribution.",
		"/* mud */"
	]
}

