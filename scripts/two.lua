-- two library

if _OPTIONS["cpp-modules"] and _ACTION == "gmake" then
    dofile(path.join(TWO_DIR, "scripts/3rdparty/std.lua"))
end

if not _OPTIONS["compile-only"] then
    group "3rdparty"
    dofile(path.join(TWO_DIR, "scripts/3rdparty/json11.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/base64.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/stb.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/tracy.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/lua.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/wren.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/mikktspace.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/vg.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/bgfx/bgfx.lua"))
    group "3rdparty"
    dofile(path.join(TWO_DIR, "scripts/3rdparty/meshoptimizer.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/xatlas.lua"))
    dofile(path.join(TWO_DIR, "scripts/3rdparty/fastnoise.lua"))

    if _OPTIONS["culling"] then
        dofile(path.join(TWO_DIR, "scripts/3rdparty/culling.lua"))
    else
        culling = null
    end

    if _OPTIONS["context-glfw"] then
        dofile(path.join(TWO_DIR, "scripts/3rdparty/glfw.lua"))
    end

    if _OPTIONS["sound"] then
        dofile(path.join(TWO_DIR, "scripts/3rdparty/ogg/ogg.lua"))
        dofile(path.join(TWO_DIR, "scripts/3rdparty/vorbis/vorbis.lua"))
        dofile(path.join(TWO_DIR, "scripts/3rdparty/vorbis/vorbisfile.lua"))
    end
else
    stb = {}
    json11 = null
    base64 = null
    stb.image = null
    stb.rect_pack = null
    tracy = null
    lua = null
    wren = null
    fastnoise = null
    mikktspace = null
    vg = null
    bx = null
    bimg = null
    bgfx = null
    meshoptimizer = null
    culling = null
    glfw = null
    ogg = null
    vorbis = null
    vorbisfile = null
end

os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/filter"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/pbr"))

group "lib"

two = {}

function uses_two()
    two_defines()
    
    includedirs {
        path.join(TWO_SRC_DIR),
        path.join(TWO_DIST_DIR),
        path.join(TWO_3RDPARTY_DIR, "tinystl", "include"),
    }
    
    if _OPTIONS["use-stl"] then
        configuration { "Debug" }
            defines { "USE_STL" }
            
        configuration {}
    end
    
    if _OPTIONS["profile"] then
        defines { "TRACY_ENABLE" }
    end
end

function two_infra()
    files {
        path.join(TWO_SRC_DIR, "stl", "**.h"),
        path.join(TWO_SRC_DIR, "stl", "**.hpp"),
        path.join(TWO_SRC_DIR, "stl", "**.cpp"),
    }
end

function two_jobs()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "tracy"),
    }
end

function two_srlz()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "json11"),
    }
end

function two_math()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "stb"),
        path.join(TWO_3RDPARTY_DIR, "json11"),
    }
end

function uses_two_math()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "glm"),
    }
end

function two_ui()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "json11"),
    }
end

function uses_two_ui()
    defines { "TWO_UI_DRAW_CACHE" }
end

function two_geom()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "mikkt"),
    }
end

function uses_two_noise()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "FastNoise"),
    }
end

function two_noise()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "FastNoise"),
    }
end

function two_wfc()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "json11"),
    }
end

function two_lang()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "lua"),
        path.join(TWO_3RDPARTY_DIR, "wren", "src", "include"),
    }
end

function two_snd()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "vorbis", "include"),
        path.join(TWO_3RDPARTY_DIR, "ogg", "include"),
        path.join(TWO_DIR, "scripts/3rdparty/ogg/"),
    }
end

function uses_two_snd()
    configuration { "asmjs" }
        --links { "openal" }
        
    configuration { "not asmjs" }
        links { "OpenAL32" }
        
    configuration {}
end

function two_db()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "sqlite3"),
    }
    
    files {
        path.join(TWO_3RDPARTY_DIR, "sqlite3", "*.c"),
    }
end

function two_clrefl()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "json11"),
    }
    
    links { "libclang" }
    
    configuration { "windows" }
        includedirs {
            "C:/Program Files (x86)/LLVM/include",
            "C:/Program Files/LLVM/include",
        }

    configuration { "windows", "x32" }
        libdirs {
            "C:/Program Files (x86)/LLVM/lib",
        }

    configuration { "windows", "x64" }
        libdirs {
            "C:/Program Files/LLVM/lib",
        }
        
    configuration {}
end

function uses_two_bgfx()
    uses_two()
    
    includedirs {
        path.join(BX_DIR,    "include"),
        path.join(BIMG_DIR,  "include"),
        path.join(BGFX_DIR,  "include"),
    }
    
    configuration { "vs*", "not orbis", "not asmjs" }
        includedirs { path.join(BX_DIR, "include/compat/msvc") }
    
    configuration {}
end

function uses_two_gfx()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "glm"),
    }
end

function two_gfx()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "json11"),
        path.join(TWO_3RDPARTY_DIR, "meshoptimizer", "src"),
    }
    
    if _OPTIONS["culling"] then
        includedirs {
            path.join(TWO_3RDPARTY_DIR, "culling"),
        }
    else
        defines { "NO_OCCLUSION_CULLING" }
    end
end

function two_gfx_pbr()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "xatlas"),
    }
end

function two_gltf()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "base64"),
        path.join(TWO_3RDPARTY_DIR, "json11"),
    }
end

-- @todo deactivate reflection for infra, tree, srlz, bgfx, gfx.obj, gfx.gltf, gfx.edit
--       and make reflection generator generate empty modules in those cases
--                       base   name        root path       sub path    self decl   usage decl      reflect     dependencies
-- core
two.infra   = two_module("two", "infra",    TWO_SRC_DIR,    "infra",    two_infra,  uses_two,       true,       { })
two.jobs    = two_module("two", "jobs",     TWO_SRC_DIR,    "jobs",     two_jobs,   uses_two,       true,       { tracy, two.infra })
two.type    = two_module("two", "type",     TWO_SRC_DIR,    "type",     nil,        uses_two,       true,       { two.infra })
two.tree    = two_module("two", "tree",     TWO_SRC_DIR,    "tree",     nil,        nil,            true,       { two.infra })
two.pool    = two_module("two", "pool",     TWO_SRC_DIR,    "pool",     nil,        nil,            true,       { two.infra, two.type })
-- refl
two.refl    = two_module("two", "refl",     TWO_SRC_DIR,    "refl",     nil,        nil,            true,       { two.infra, two.type, two.pool })
-- ecs
two.ecs     = two_module("two", "ecs",      TWO_SRC_DIR,    "ecs",      nil,        uses_two,       true,       { two.infra, two.pool, two.type })
-- srlz
two.srlz    = two_module("two", "srlz",     TWO_SRC_DIR,    "srlz",     two_srlz,   nil,            true,       { json11, two.infra, two.type, two.refl })
-- math
if TWO_STATIC then      
  two.math  = two_module("two", "math",     TWO_SRC_DIR,    "math",     two_math,   uses_two_math,  true,       { stb.rect_pack, two.infra, two.type })
else        
  two.math  = two_module("two", "math",     TWO_SRC_DIR,    "math",     two_math,   uses_two_math,  true,       { stb.image, stb.rect_pack, two.infra, two.type })
end     
-- geom
two.geom    = two_module("two", "geom",     TWO_SRC_DIR,    "geom",     two_geom,   nil,            true,       { mikktspace, two.type, two.math })
-- procgen
two.noise   = two_module("two", "noise",    TWO_SRC_DIR,    "noise",    two_noise,  uses_two_noise, true,       { fastnoise, two.infra, two.type, two.math, two.geom })
two.wfc     = two_module("two", "wfc",      TWO_SRC_DIR,    "wfc",      two_wfc,    nil,            true,       { json11, two.infra, two.type, two.srlz, two.math, two.geom })
two.fract   = two_module("two", "fract",    TWO_SRC_DIR,    "fract",    nil,        nil,            true,       { json11, two.infra, two.type, two.math, two.geom })
-- lang
two.lang    = two_module("two", "lang",     TWO_SRC_DIR,    "lang",     two_lang,   nil,            true,       { lua, wren, two.infra, two.type, two.pool, two.refl })
-- ui
two.ctx     = two_module("two", "ctx",      TWO_SRC_DIR,    "ctx",      nil,        nil,            true,       { two.infra, two.type, two.math })
two.ui      = two_module("two", "ui",       TWO_SRC_DIR,    "ui",       two_ui,     uses_two_ui,    true,       { two.infra, two.type, two.math, two.ctx })
two.uio     = two_module("two", "uio",      TWO_SRC_DIR,    "uio",      nil,        nil,            true,       { two.infra, two.tree, two.type, two.ecs, two.pool, two.refl, two.math, two.lang, two.ctx, two.ui })
-- snd
two.snd     = two_module("two", "snd",      TWO_SRC_DIR,    "snd",      two_snd,    uses_two_snd,   true,       { ogg, vorbis, vorbisfile, two.type, two.math })

if _OPTIONS["context-glfw"] then
    dofile(path.join(TWO_DIR, "scripts/two_ctx_glfw.lua"))
elseif _OPTIONS["context-native"] then
    dofile(path.join(TWO_DIR, "scripts/two_ctx_native.lua"))
elseif _OPTIONS["context-wasm"] then
    dofile(path.join(TWO_DIR, "scripts/two_ctx_wasm.lua"))
end

if _OPTIONS["renderer-bgfx"] then
    dofile(path.join(TWO_DIR, "scripts/two_ui_bgfx.lua"))
else
    dofile(path.join(TWO_DIR, "scripts/two_ui_gl.lua"))
end

two.ctxbackend  = two_ctx_backend()
two.uibackend   = two_ui_backend()

--                       base   name        root path       sub path    self decl   usage decl      reflect     dependencies
-- gfx
two.bgfx    = two_module("two", "bgfx",     TWO_SRC_DIR,    "bgfx",     nil,        uses_two_bgfx,  true,       { bx, bimg, bimg.decode, bimg.encode, bgfx, two.infra, two.type, two.math, two.ctx })
two.gfx     = two_module("two", "gfx",      TWO_SRC_DIR,    "gfx",      two_gfx,    uses_two_gfx,   true,       { tracy, json11, meshopt, culling, bgfx, shaderc, two.infra, two.jobs, two.type, two.pool, two.ecs, two.math, two.geom, two.ctx, two.bgfx })
-- gltf                                                     
two.gltf    = two_module("two", "gltf",     TWO_SRC_DIR,    "gltf",     two_gltf,   nil,            true,       { json11, base64, two.infra, two.type, two.refl, two.srlz, two.math })
-- gfx exts                                                 
two.gfx.pbr = two_module("two", "gfx-pbr",  TWO_SRC_DIR,    "gfx-pbr",  two_gfx_pbr,nil,            true,       { xatlas, two.infra, two.type, two.math, two.geom, two.gfx })
two.gfx.obj = two_module("two", "gfx-obj",  TWO_SRC_DIR,    "gfx-obj",  nil,        nil,            true,       { two.infra, two.type, two.srlz, two.math, two.geom, two.gfx })
two.gfx.gltf= two_module("two", "gfx-gltf", TWO_SRC_DIR,    "gfx-gltf", two_gltf,   nil,            true,       { json11, two.infra, two.type, two.refl, two.srlz, two.math, two.geom, two.gfx, two.gltf, two.gltf.refl })
two.gfx.ui  = two_module("two", "gfx-ui",   TWO_SRC_DIR,    "gfx-ui",   nil,        nil,            true,       { two.infra, two.tree, two.type, two.math, two.geom, two.ctx, two.ui, two.gfx })
two.gfx.edit= two_module("two", "gfx-edit", TWO_SRC_DIR,    "gfx-edit", nil,        nil,            true,       { two.infra, two.type, two.refl, two.srlz, two.math, two.geom, two.ui, two.uio, two.gfx, two.gfx.pbr })
-- tool                                                     
two.tool    = two_module("two", "tool",     TWO_SRC_DIR,    "tool",     nil,        nil,            true,       { two.infra, two.tree, two.type, two.refl, two.srlz, two.lang, two.math, two.geom, two.ctx, two.ui, two.uio, two.gfx, two.gfx.pbr, two.gfx.ui, two.gfx.edit })
-- wfc                                                      
two.wfc.gfx = two_module("two", "wfc-gfx",  TWO_SRC_DIR,    "wfc-gfx",  nil,        nil,            true,       { json11, two.infra, two.tree, two.type, two.srlz, two.math, two.geom, two.wfc, two.ctx, two.ui, two.uio, two.gfx, two.gfx.ui })
-- frame                                                    
two.frame   = two_module("two", "frame",    TWO_SRC_DIR,    "frame",    nil,        nil,            true,       { two.gfx, two.gfx.ui, two.ctxbackend, two.uibackend })

if _OPTIONS["tools"] then
  two.clrefl = two_module("two", "clrefl",  TWO_SRC_DIR,    "clrefl",   two_clrefl, nil,            false,      { json11, two.infra })
  two.amalg  = two_module("two", "amalg",   TWO_SRC_DIR,    "amalg",    nil,        nil,            false,      { json11, two.infra })
end

--two_sys(true)
--two_vec(true)
--two.db = two_module("two", "db", TWO_SRC_DIR, "db", { two.type, two.util })

two.two = { two.infra, two.jobs, two.type, two.tree, two.pool, two.refl, two.ecs, two.srlz, two.math, two.geom, two.lang, two.ctx, two.ui, two.uio, two.bgfx, two.gfx, two.gfx.ui,
            two.ctxbackend, two.uibackend, two.frame }
two.opts = { two.noise, two.wfc, two.fract, two.gfx.pbr, two.gfx.obj, two.gltf, two.gfx.gltf, two.gfx.edit, two.tool, two.wfc.gfx }

if _OPTIONS["sound"] then
    table.insert(two.two, two.snd)
end

two.all = table.union(two.two, two.opts)

if _OPTIONS["as-libs"] then
    FORCE_REFL_PROJECTS = true
end

local lgfx = {}

if _OPTIONS["renderer-gl"] then
    lgfx = { two.gl, two.uibackend }
elseif _OPTIONS["renderer-bgfx"] then
    lgfx = { two.bgfx, two.uibackend }
end

table.insert(lgfx, two.frame)

if _OPTIONS["unity"] then
    for _, m in pairs(two.all) do
        two_unity(m)
    end
end

if _OPTIONS["as-libs"] then
    group "lib/two"
        two_libs(two.all, "StaticLib")
    group "lib"
else
    two.lib = two_lib("two", two.all, "StaticLib")
    
        --files {
        --    path.join(TWO_SRC_DIR, "two", "**.h"),
        --}
        
        configuration { "vs*", "not asmjs", "Release" }
            buildoptions {
                "/bigobj",
            }
            
        configuration {}
end

--group "lib/two-opts"
--two_libs(two.opts, "StaticLib")

if _OPTIONS["tools"] then
    two_lib("two_clrefl", { two.clrefl }, "StaticLib", {}, true)
    two_lib("two_amalg", { two.amalg }, "StaticLib", {}, true)
end

function two_binary(name, modules, deps)
    two_lib(name, modules, "ConsoleApp", deps)
    defines { "_" .. name:upper() .. "_EXE" }
    two_binary_config()
end

function two_js(name, modules)
    local lib = two_lib(name, {}, "ConsoleApp", modules)
    two_glue_js(table.inverse(lib.deps))
    linkoptions {
        "-s EXPORT_NAME=\"'" .. name .. "'\"",
        --"-s MODULARIZE=1",
    }
    two_binary_config()
end