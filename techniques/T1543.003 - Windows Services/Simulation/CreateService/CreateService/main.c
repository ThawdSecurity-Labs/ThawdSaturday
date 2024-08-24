
#include <windows.h>
#include <sddl.h>

#include <stdio.h>


void CreateMyService() {
    SC_HANDLE schSCManager;
    SC_HANDLE schService;
    SERVICE_DESCRIPTION sd;

    // Open the SCManager
    schSCManager = OpenSCManagerA(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_CREATE_SERVICE);  // full access rights

    if (schSCManager == NULL) {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }

    // Create the service
    schService = CreateServiceA(
        schSCManager,              // SCM database 
        "Thawd_WinApi",               // name of service 
        "Thawd_WinApi",       // service name to display 
        SERVICE_ALL_ACCESS,        // desired access 
        SERVICE_WIN32_OWN_PROCESS, // service type 
        SERVICE_DEMAND_START,      // start type 
        SERVICE_ERROR_NORMAL,      // error control type 
        "C:\\Path\\To\\Binary.exe", // path to service's binary 
        NULL,                      // no load ordering group 
        NULL,                      // no tag identifier 
        NULL,                      // no dependencies 
        NULL,                      // LocalSystem account 
        NULL);                     // no password

    if (schService == NULL) {
        printf("CreateService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }
    else {
        printf("Service created successfully.\n");
    }
    // Set the service description
    sd.lpDescription = "This is a custom service created by adding win api entries.";
    if (!ChangeServiceConfig2A(
        schService,                 // handle to service
        SERVICE_CONFIG_DESCRIPTION, // change: service description
        &sd)) {                     // description
        printf("ChangeServiceConfig2 failed (%d)\n", GetLastError());
    }

    // Cleanup
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

int main() {
    CreateMyService();
    return 0;
}
