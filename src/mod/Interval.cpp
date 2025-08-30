#include "Interval.h"
#include "Config.h"
#include "Entry.h"
#include "GenerateMap.h"
#include "ll/api/chrono/GameChrono.h"
#include "ll/api/coro/CoroTask.h"
#include "ll/api/thread/ServerThreadExecutor.h"
#include "mod/Entry.h"
#include <chrono>

namespace world_map_unmined {
bool isRunning = false;

std::chrono::seconds GetNow() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
}

void IntervalOnCallbackFinished() {
    config.lastGenerateDate = GetNow().count();
    saveConfig();
}

void StartInterval() {
    int intervalHours = config.intervalHours;
    if (intervalHours == 0) {
        // Interval not set
        return;
    };

    isRunning = true;

    logger.info("Interval is set to run each {} hours", intervalHours);

    ll::coro::keepThis([intervalHours]() -> ll::coro::CoroTask<> {
        while (isRunning) {
            auto lastBackupTime    = config.lastGenerateDate;
            auto lastBackupSeconds = std::chrono::seconds(lastBackupTime);

            // Seconds
            ll::chrono::game::ticks waitTime = (lastBackupSeconds + std::chrono::hours(intervalHours)) - GetNow();
            co_await (waitTime);

            if (!isRunning) co_return;

            if (!isWorking) {
                logger.info("Generating map in interval...");
                GenerateMap([]() { logger.info("Interval done"); }, [](const std::string& msg) { logger.info(msg); });
            } else {
                logger.info("Map is already generating, skipping interval...");
            }

            co_await ll::chrono::game::ticks(20);
        }
    }).launch(ll::thread::ServerThreadExecutor::getDefault());
}

void StopInterval() { isRunning = false; };

} // namespace world_map_unmined