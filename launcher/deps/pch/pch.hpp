#pragma once

// STL
#include <cstdio>
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <format>
#include <thread>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <format>

// WinSockets
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "ntdll.lib" )

// WinApi
#include <Windows.h>
#include <memory>
#include <psapi.h>
#include <TlHelp32.h>
#include <unordered_map>
#include <winternl.h>