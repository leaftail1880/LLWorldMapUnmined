#include "mod/Entry.h"

#include "Command.h"
#include "Config.h"
#include "Entry.h"
#include "Interval.h"
#include "ll/api/Config.h"
#include "ll/api/mod/RegisterHelper.h"
#include "mc/server/PropertiesSettings.h"
#include <ll/api/service/Bedrock.h>


namespace world_map_unmined {

Config config{};

Mod& Mod::getInstance() {
    static Mod instance;
    return instance;
}

std::filesystem::path getConfigPath() { return Mod::getInstance().getSelf().getConfigDir() / "config.json"; }

bool saveConfig() {
    const auto& configFilePath = getConfigPath();
    if (!ll::config::saveConfig(config, configFilePath)) {
        logger.error("Cannot save configurations to {}", configFilePath);
        return false;
    }
    return true;
}

bool loadConfig() {
    const auto& configFilePath = getConfigPath();
    return ll::config::loadConfig(config, configFilePath);
}

bool Mod::load() { return true; }

std::string levelName;

std::string getLevelName() { return levelName; }

bool Mod::enable() const {
    auto props = ll::service::getPropertiesSettings();
    if (!props) {
        logger.error("Faield to get server properties for level name");
        return false;
    }

    levelName = props->mLevelName;

    if (!loadConfig()) {
        getSelf().getLogger().warn("Cannot load configurations from {}", getConfigPath());
        getSelf().getLogger().info("Saving default configurations");

        if (!saveConfig()) return false;
    }

    StartInterval();
    RegisterCommand();
    return true;
}

bool Mod::disable() {
    StopInterval();
    return true;
}

bool Mod::unload() { return true; }


} // namespace world_map_unmined

LL_REGISTER_MOD(world_map_unmined::Mod, world_map_unmined::Mod::getInstance());
