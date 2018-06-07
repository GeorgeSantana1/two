#pragma once

#include <math/Generated/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Proto.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Types.h>
#include <srlz/Generated/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif

#include <math/Structs.h>

namespace mud
{
    // Exported types
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Axes>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Axis>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Clockwise>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Side>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::SignedAxis>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::SpectrumPalette>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::TrackMode>();
    export_ template <> MUD_MATH_EXPORT Type& type<std::vector<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<std::vector<mud::Colour>>();
    //export_ template <> MUD_MATH_EXPORT Type& type<std::vector<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<std::vector<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<std::vector<mud::uvec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<std::vector<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<std::vector<uint32_t>>();
    
    export_ template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<int>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Colour>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Gauge>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Image256>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Palette>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<uint32_t>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Ratio>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<uint32_t>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<uint32_t>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ivec3>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::mat4>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::quat>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::uvec2>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::uvec3>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::uvec4>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::vec2>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::vec3>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::vec4>();
}
