#include <windows.h>
#include <iostream>
#include <xfsapi.h>
#include <xfscdm.h>

using namespace std;

void DisplayCDMStatus(HSERVICE hService) {
    LPWFSRESULT lpResult = nullptr;

    HRESULT hResult = WFSGetInfo(hService, WFS_INF_CDM_STATUS, NULL, 10000, &lpResult);

    WFSCDMSTATUS* cdmStatus = (WFSCDMSTATUS *)lpResult->lpBuffer;

    switch (cdmStatus->fwDevice)
    {
    case WFS_CDM_DEVONLINE:
        cout << "Device status: Online" << endl;
        break;
    case WFS_CDM_DEVOFFLINE:
        cout << "Device status: Offline" << endl;
        break;
    case WFS_CDM_DEVPOWEROFF:
        cout << "Device status: Power off" << endl;
        break;
    case WFS_CDM_DEVNODEVICE:
        cout << "Device status: No device" << endl;
        break;
    case WFS_CDM_DEVHWERROR:
        cout << "Device status: Hardware error" << endl;
        break;
    case WFS_CDM_DEVUSERERROR:
        cout << "Device status: User error" << endl;
        break;
    case WFS_CDM_DEVBUSY:
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

    HSERVICE hService = NULL;
    hResult = WFSOpen("CDM", WFS_DEFAULT_HAPP, "test", 0, 0, 0, 0, &hService);
}