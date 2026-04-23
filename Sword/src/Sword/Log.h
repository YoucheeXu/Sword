#ifndef LOG_H
#define LOG_H

#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

#include <memory>

namespace Sword {

class SWORD_API Log {
   public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
        return s_CoreLogger;
    }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
        return s_ClientLogger;
    }

   private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}  // namespace Sword

// Core log macros
#define SW_CORE_TRACE(...) ::Sword::Log::GetCoreLogger()->trace(__VA__ARGS__)
#define SW_CORE_INFO(...)  ::Sword::Log::GetCoreLogger()->info(__VA__ARGS__)
#define SW_CORE_WARN(...)  ::Sword::Log::GetCoreLogger()->warn(__VA__ARGS__)
#define SW_CORE_ERROR(...) ::Sword::Log::GetCoreLogger()->error(__VA__ARGS__)
#define SW_CORE_FATAL(...) ::Sword::Log::GetCoreLogger()->fatal(__VA__ARGS__)

// Cliene log marcos
#define SW_TRACE(...) ::Sword::Log::GetClientLogger()->trace(__VA__ARGS__)
#define SW_INFO(...)  ::Sword::Log::GetClientLogger()->info(__VA__ARGS__)
#define SW_WARN(...)  ::Sword::Log::GetClientLogger()->warn(__VA__ARGS__)
#define SW_ERROR(...) ::Sword::Log::GetClientLogger()->error(__VA__ARGS__)
#define SW_FATAL(...) ::Sword::Log::GetClientLogger()->fatal(__VA__ARGS__)

#endif