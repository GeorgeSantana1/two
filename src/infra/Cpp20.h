#ifdef MUD_CPP_20
#include <infra/Config.h>
#define UNUSED(x) (void)(x)
#ifdef MUD_MODULES
#define export_ export
#define MUD_EXPORT 
#endif
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
#include <limits.h> // <climits>
//#include <math.h> // <cmath>
#include <time.h> // <ctime>
#include <string.h> // <cstring>
#include <stdio.h>
#include <stdlib.h>
import std.core;
import std.threading;
import std.regex;
#ifdef _MSC_VER
import std.memory; // std.memory exists only in Visual Studio experimental modules
#else
import std.io;
#endif
#endif
