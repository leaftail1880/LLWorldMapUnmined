#include "Command.h"
#include "Entry.h"
#include "GenerateMap.h"
#include "ll/api/command/CommandHandle.h"
#include "ll/api/command/CommandRegistrar.h"
#include "mc/server/commands/CommandOutput.h"
#include "mc/server/commands/CommandPermissionLevel.h"


namespace world_map_unmined {
void RegisterCommand() {
    using ll::command::CommandRegistrar;
    auto& command = ll::command::CommandRegistrar::getInstance()
                        .getOrCreateCommand("worldmapunmined", "Generate map", CommandPermissionLevel::Admin);

    command.overload().execute([&](CommandOrigin const& origin, CommandOutput& output) {
        if (isWorking) {
            output.error("Already generating...");
            return;
        }

        logger.info("Generating map by command request from {}...", origin.getName());

        GenerateMap(
            [&output]() { output.addMessage("Finish", {}, ::CommandOutputMessageType::Success); },
            [&output](const std::string& msg) { output.addMessage(msg, {}, ::CommandOutputMessageType::Success); }
        );


        ++output.mSuccessCount;
    });
}
} // namespace world_map_unmined