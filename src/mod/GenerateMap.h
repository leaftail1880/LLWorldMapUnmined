#pragma once

#include <atomic>
#include <functional>
#include <string>


namespace world_map_unmined {
extern std::atomic_bool isWorking;

using Feedback = std::function<void(const std::string&)>;
using OnFinish = std::function<void()>;

void GenerateMap(const OnFinish& onFinish, const Feedback& feedback);
} // namespace world_map_unmined