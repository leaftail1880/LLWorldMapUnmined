#pragma once

#include <string>

namespace world_map_unmined {
struct Config {
    int         version    = 1;
    std::string execParams = R"(image render --trim --world="%1" --output="plugins\WorldMapUnmined\map.png")";
    std::string execFile   = R"(plugins\WorldMapUnmined\unmined\unmined-cli.exe)";
    int         openMode   = 0;
    int         intervalHours;
    long long   lastGenerateDate;
    int         maxTimeoutMs = 15000;
};

extern Config config;

} // namespace world_map_unmined