#include <iostream>
#include <windows.h>
#include "xfsapi.h"

typedef HRESULT(WINAPI* LPWFSStartUp)(DWORD, LPWFSVERSION);
typedef HRESULT(WINAPI* LPWFSOpen)(
    LPCSTR, HSERVICE*, HWND, DWORD, DWORD, LPWFSVERSION, LPWFSVERSION, DWORD);
typedef HRESULT(WINAPI* LPWFSGetInfo)(
    HSERVICE, DWORD, LPVOID, DWORD, LPWFSRESULT*);
typedef HRESULT(WINAPI* LPWFSCleanUp)();

int main() {
    // Load msxfs.dll
    HMODULE hXfsDll = LoadLibrary("msxfs.dll");
    if (!hXfsDll) {
        std::cerr << "Failed to load msxfs.dll. Error: " << GetLastError() << std::endl;
        return -1;
    }

    // Load WFSStartUp function
    LPWFSStartUp WFSStartUp = (LPWFSStartUp)GetProcAddress(hXfsDll, "WFSStartUp");
    if (!WFSStartUp) {
        std::cerr << "Failed to find WFSStartUp in msxfs.dll. Error: " << GetLastError() << std::endl;
        FreeLibrary(hXfsDll);
        return -1;
    }

    // Start XFS
    WFSVERSION versionRequested = { 0 };
    versionRequested.wVersion = 0x0300; // XFS 3.0.0
    WFSVERSION versionReturned;
    HRESULT hr = WFSStartUp(0x0300, &versionReturned);
    if (hr != WFS_SUCCESS) {
        std::cerr << "WFSStartUp failed. HRESULT: " << hr << std::endl;
        FreeLibrary(hXfsDll);
        return -1;
    }
    std::cout << "WFSStartUp succeeded. Version: " << versionReturned.wVersion << std::endl;

    // Load WFSOpen function
    LPWFSOpen WFSOpen = (LPWFSOpen)GetProcAddress(hXfsDll, "WFSOpen");
    if (!WFSOpen) {
        std::cerr << "Failed to find WFSOpen in msxfs.dll. Error: " << GetLastError() << std::endl;
        FreeLibrary(hXfsDll);
        return -1;
    }

    // Open connection to Card Reader (example logical name: "ATMCardReader")
    HSERVICE hService = NULL;
    hr = WFSOpen("ATMCardReader", &hService, NULL, 0, 0, &versionRequested, &versionReturned, 0);
    if (hr != WFS_SUCCESS) {
        std::cerr << "WFSOpen failed. HRESULT: " << hr << std::endl;
    } else {
        std::cout << "WFSOpen succeeded. Connected to Card Reader!" << std::endl;
    }

    // Clean up XFS session
    LPWFSCleanUp WFSCleanUp = (LPWFSCleanUp)GetProcAddress(hXfsDll, "WFSCleanUp");
    if (WFSCleanUp) {
        WFSCleanUp();
    }
    FreeLibrary(hXfsDll);

    return 0;
}
