#include <windows.h>
#include <iostream>
#include <xfsapi.h>

using namespace std;

void DisplayDeviceStatus(HSERVICE hService) {
    LPWFSRESULT lpResult = nullptr;

    HRESULT hResult = WFSGetInfo(hService, WFS_SYSE_DEVICE_STATUS, NULL, 10000, &lpResult);
    if (hResult != WFS_SUCCESS) {
        cerr << "Error getting device status: " << hResult << endl;
        return;
    }

    WFSDEVSTATUS* devStatus = (WFSDEVSTATUS*)lpResult->lpBuffer;

    switch (devStatus->dwState)
    {
    case WFS_STAT_DEVONLINE:
        cout << "Device status: Online" << endl;
        break;
    case WFS_STAT_DEVOFFLINE:
        cout << "Device status: Offline" << endl;
        break;
    case WFS_STAT_DEVPOWEROFF:
        cout << "Device status: Power off" << endl;
        break;
    case WFS_STAT_DEVNODEVICE:
        cout << "Device status: No device" << endl;
        break;
    case WFS_STAT_DEVHWERROR:
        cout << "Device status: Hardware error" << endl;
        break;
    case WFS_STAT_DEVUSERERROR:
        cout << "Device status: User error" << endl;
        break;
    case WFS_STAT_DEVBUSY:
        cout << "Device status: Busy" << endl;
        break;
    default:
        cout << "Device status: Unknown" << endl;
        break;
    }
    WFSFreeResult(lpResult);
}

int main() {
    HRESULT hResult = WFSStartUp(0x00030003, NULL);
    if(hResult != WFS_SUCCESS) {
        cerr << "Error starting up: " << hResult << endl;
        return 1;
    }

    HSERVICE hService = NULL; // Assuming you have a valid service handle
    DisplayDeviceStatus(hService);

    WFSCleanUp();
}