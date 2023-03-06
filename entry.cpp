#include "interfaces.h"
#include "netvars.h"
#include "gui.h"
#include "hooks.h"
#include <Windows.h>
#include <iostream>

void MainThread(HMODULE instance) {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);

    std::cout << "[*] welcome to nova!" << std::endl;

    try {
        std::cout << "[+] setting up interface manager" << std::endl;
        interfaces::Setup();

        std::cout << "[+] setting up netvar manager" << std::endl;
        netvars::Setup();

        std::cout << "[+] setting up gui" << std::endl;
        gui::Setup();

        std::cout << "[+] setting up hooks" << std::endl;
        hooks::Setup();

        std::cout << "[*] sucessfully initialized nova :D" << std::endl;
    }
    catch (std::exception& error) {
        std::cout << "[-] nova crashed :( " << std::endl << std::endl << error.what() << std::endl;

        MessageBeep(MB_ICONERROR);
        MessageBox(
            0,
            error.what(),
            "nova",
            MB_OK | MB_ICONEXCLAMATION
        );

        goto UNLOAD;
    }

    while (!GetAsyncKeyState(VK_END))
        Sleep(200);

UNLOAD:
    g_InputSystem->EnableInput(true);
    hooks::Destroy();
    gui::Destroy();
    if (file) fclose(file);
    FreeConsole();
    FreeLibraryAndExitThread(instance, 0);
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved
) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);

        HANDLE thread = CreateThread(
            nullptr,
            0,
            (LPTHREAD_START_ROUTINE)(MainThread),
            hinstDLL,
            0,
            nullptr
        );

        if (thread)
            CloseHandle(thread);
    }

    return TRUE;
}