#include "pch.hpp"
#include "hooks/hooks.hpp"

void on_attach()
{
    // @note: extra check
    while (!GetModuleHandleA("Spotify.dll"))
    {
        Sleep(100);
    }

    // @note: just sleep. why not
    Sleep(1000);

#ifdef _DEBUG
	AllocConsole();
    auto _old_out = GetStdHandle(STD_OUTPUT_HANDLE);
	FILE* cout_stream = nullptr;
	freopen_s(&cout_stream, "CONOUT$", "w", stdout);

	SetConsoleTitleA("unspotify v2 by @mhalaider");
#endif

	g_hooks->init();

#ifdef _DEBUG
    std::printf("[main] you can close this console window!\n");
    FreeConsole();
    if(_old_out)
    {
        SetStdHandle(STD_OUTPUT_HANDLE, _old_out);
    }
#endif
}

BOOL WINAPI DllMain(HINSTANCE base, DWORD param, LPVOID reserved)
{
    if(param == DLL_PROCESS_ATTACH)
    {
        std::jthread([]()
        {
        	on_attach();
        }).detach();
    }

    return TRUE;
}