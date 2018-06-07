-- mud library
-- mud db module

function mud_db(as_project)
    mud.db = mud_module(as_project, "mud", "db", MUD_SRC_DIR, "db", { mud.obj, mud.util })

    includedirs {
        path.join(MUD_3RDPARTY_DIR, "sqlite3"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "sqlite3", "*.c"),
    }
end
