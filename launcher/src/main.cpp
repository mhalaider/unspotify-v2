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
        goto END;
    }

    std::printf("[main] injecting spot-module.dll\n");
    if (!injector::inject(pi.hProcess, "spot-module.dll")) {
        std::printf("[main] unable to inject module, error code: %d\n", GetLastError());
        TerminateProcess(pi.hProcess, 0x0);
        system("pause");
        goto END;
    }

    ResumeThread(pi.hThread);

END:
    return EXIT_SUCCESS;
}