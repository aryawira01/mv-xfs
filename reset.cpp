#include <iostream>
#include <xfsapi.h>
#include <windows.h>

using namespace std;

void resetATMMachine() {
    HRESULT hResult;
    HSERVICE hService;
    WFSVERSION wfsVersion;
    WFSVERSION spVersion;
    REQUESTID requestID;

    // Initialize XFS Manager
    hResult = WFSStartUp(0x00030000, &wfsVersion);
    if (hResult != WFS_SUCCESS) {
        cerr << "Failed to start XFS Manager: " << hResult << endl;
        return;
    }

    // Open a connection to the ATM service
    hResult = WFSOpen("ATM", WFS_DEFAULT_HAPP, "ATMApp", 0, 0, 0, 0, &spVersion, &hService);
    if (hResult != WFS_SUCCESS) {
        cerr << "Failed to open ATM service: " << hResult << endl;
        WFSCleanUp();
        return;
    }

    // Reset the ATM machine
    hResult = WFSAsyncExecute(hService, WFS_ERR_ACT_RESET, NULL, 0, NULL, &requestID);
    if (hResult != WFS_SUCCESS) {
        cerr << "Failed to reset ATM machine: " << hResult << endl;
    } else {
        cout << "ATM machine reset successfully." << endl;
    }

    // Close the connection to the ATM service
    hResult = WFSAsyncClose(hService, NULL, &requestID);
    if (hResult != WFS_SUCCESS) {
        cerr << "Failed to close ATM service: " << hResult << endl;
    }

    // Clean up XFS Manager
    WFSCleanUp();
}