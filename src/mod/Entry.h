#pragma once

#include "ll/api/mod/NativeMod.h"

namespace world_map_unmined {

class Mod {

public:
    static Mod& getInstance();

    Mod() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    /// @return True if the mod is loaded successfully.
    bool load();

    /// @return True if the mod is enabled successfully.
    [[nodiscard]] bool enable() const;

    /// @return True if the mod is disabled successfully.
    bool disable();

    /// @return True if the mod is unloaded successfully.
    bool unload();

private:
    ll::mod::NativeMod& mSelf;
};

bool saveConfig();
bool loadConfig();

#define logger world_map_unmined::Mod::getInstance().getSelf().getLogger()

} // namespace world_map_unmined
