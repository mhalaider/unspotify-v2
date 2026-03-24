#include "pch.hpp"
#include "injector/injector.hpp"

// @note: this injector project has been stolen from "https://github.com/4wi/Unspotify"
int main() {
    STARTUPINFOA si = { .cb = sizeof(si) };
    PROCESS_INFORMATION pi = {};

    constexpr const char* exe_path = "Spotify.exe";

    std::printf("[main] spawning %s\n", exe_path);
    if (!CreateProcessA(exe_path, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        std::printf("[main] unable to create process, error code: %d\n", GetLastError());
        system("pause");
        return EXIT_FAILURE;
    }

    std::string module_name{};

#ifdef _DEBUG
    module_name = "spot-module-debug.dll";
#else
    module_name = "spot-module.dll";
#endif

    std::printf("[main] injecting %s\n", module_name.c_str());
    if (!injector::inject(pi.hProcess, module_name.c_str())) {
        std::printf("[main] unable to inject module, error code: %d\n", GetLastError());
        TerminateProcess(pi.hProcess, 0x0);
        system("pause");
        return EXIT_FAILURE;
    }

    ResumeThread(pi.hThread);
    return EXIT_SUCCESS;
}