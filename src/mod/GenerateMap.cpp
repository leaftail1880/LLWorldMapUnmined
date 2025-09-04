#include "GenerateMap.h"
#include "Config.h"
#include "Entry.h"
#include "Interval.h"
#include "ll/api/utils/StringUtils.h"
#include "mod/Config.h"
#include "mod/Entry.h"
#include <atomic>


#include <filesystem>
#include <functional>
#include <windows.h>

#include <shellapi.h>
#include <string>
#include <winuser.h>


#pragma comment(lib, "Shell32.lib")

#ifdef __clang__
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#pragma clang diagnostic ignored "-Wmissing-braces"
#endif

namespace world_map_unmined {

std::atomic_bool isWorking = false;

void ControlResourceUsage(HANDLE process) {
    // Job
    HANDLE hJob = CreateJobObject(nullptr, L"UNMINED_GEN_PROGRAM");
    if (hJob) {
        JOBOBJECT_BASIC_LIMIT_INFORMATION limit = {0};
        limit.PriorityClass                     = BELOW_NORMAL_PRIORITY_CLASS;
        limit.LimitFlags                        = JOB_OBJECT_LIMIT_PRIORITY_CLASS;

        SetInformationJobObject(hJob, JobObjectBasicLimitInformation, &limit, sizeof(limit));
        AssignProcessToJobObject(hJob, process);
    }

    // CPU Limit
    SYSTEM_INFO si;
    memset(&si, 0, sizeof(SYSTEM_INFO));
    GetSystemInfo(&si);
    DWORD cpuCnt  = si.dwNumberOfProcessors;
    DWORD cpuMask = 1;
    if (cpuCnt > 1) {
        if (cpuCnt % 2 == 1) cpuCnt -= 1;
        cpuMask = int(sqrt(1 << cpuCnt)) - 1; // sqrt(2^n)-1
    }
    SetProcessAffinityMask(process, cpuMask);
}

bool Exec(const Feedback& feedback, const std::string& worldPath) {
    try {
        // Prepare command line
        char tmpParas[_MAX_PATH * 4] = {0};

        sprintf(tmpParas, config.execParams.c_str(), worldPath.c_str());

        wchar_t paras[_MAX_PATH * 4] = {0};
        ll::string_utils::str2wstr(tmpParas).copy(paras, strlen(tmpParas), 0);

        DWORD maxWait = config.maxTimeoutMs;
        if (maxWait <= 0) maxWait = 0xFFFFFFFF;
        else maxWait *= 1000;

        // Start Process
        std::wstring     zipPath = ll::string_utils::str2wstr(config.execFile);
        SHELLEXECUTEINFO sh      = {sizeof(SHELLEXECUTEINFO)};
        sh.fMask                 = SEE_MASK_NOCLOSEPROCESS;
        sh.hwnd                  = nullptr;
        sh.lpVerb                = L"open";
        sh.nShow                 = config.openMode; // SW_HIDE = 0 SW_NORMAL = 1
        sh.lpFile                = zipPath.c_str();
        sh.lpParameters          = paras;
        if (!ShellExecuteEx(&sh)) {
            feedback("Fail to start unmined process!");
            return false;
        }

        ControlResourceUsage(sh.hProcess);
        SetPriorityClass(sh.hProcess, BELOW_NORMAL_PRIORITY_CLASS);

        // Wait
        DWORD res;
        if ((res = WaitForSingleObject(sh.hProcess, maxWait)) == WAIT_TIMEOUT || res == WAIT_FAILED) {
            feedback("Unmined process timeout!");
        }
        CloseHandle(sh.hProcess);
    } catch (const std::exception& e) {
        feedback("Exception in unmined process! " + std::string(e.what()));
        return false;
    }

    return true;
}

void GenerateMap(const OnFinish& onFinish, const Feedback& feedback) {
    loadConfig();
    try {
        auto worldPath = std::filesystem::current_path() / "worlds" / getLevelName();
        Exec(feedback, worldPath.string());
        IntervalOnCallbackFinished();
        onFinish();
    } catch (const std::exception& e) {
        feedback("Exception in GenerateMap! " + std::string(e.what()));
    }
    isWorking = false;
};
} // namespace world_map_unmined
