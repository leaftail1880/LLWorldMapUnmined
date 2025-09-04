#include "Command.h"
#include "Entry.h"
#include "GenerateMap.h"
#include "ll/api/command/CommandHandle.h"
#include "ll/api/command/CommandRegistrar.h"
#include "mc/server/commands/CommandOutput.h"
#include "mc/server/commands/CommandPermissionLevel.h"
#include "mod/Config.h"


namespace world_map_unmined {
void RegisterCommand() {
    if (!config.commandEnabled) return;

    using ll::command::CommandRegistrar;
    auto& command = ll::command::CommandRegistrar::getInstance()
                        .getOrCreateCommand("mapgen", "Generate map", CommandPermissionLevel::Admin);

    command.overload().execute([&](CommandOrigin const& origin, CommandOutput& output) {
        if (isWorking) {
            output.error("Already generating...");
            return;
        }

        logger.info("Generating map by command request from {}...", origin.getName());

        GenerateMap(
            [&output]() { output.addMessage("Map generate finish", {}, ::CommandOutputMessageType::Success); },
            [&output](const std::string& msg) { output.addMessage(msg, {}, ::CommandOutputMessageType::Success); }
        );


        ++output.mSuccessCount;
    });
}
} // namespace world_map_unmined