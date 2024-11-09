
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define SVCNAME TEXT("Thawd_Svchost")

SERVICE_STATUS serviceStatus;
SERVICE_STATUS_HANDLE serviceStatusHandle;
HANDLE stopEvent = NULL;

VOID UpdateServiceStatus(DWORD currentState)
{
    serviceStatus.dwCurrentState = currentState;
    serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    serviceStatus.dwCurrentState = currentState;
    SetServiceStatus(serviceStatusHandle, &serviceStatus);
}
DWORD ServiceHandler(DWORD controlCode, DWORD eventType, LPVOID eventData, LPVOID context)
{
    switch (controlCode)
    {
    case SERVICE_CONTROL_STOP:
        UpdateServiceStatus(SERVICE_STOPPED);
        SetEvent(stopEvent);
    case SERVICE_CONTROL_SHUTDOWN:
        UpdateServiceStatus(SERVICE_STOPPED);
        SetEvent(stopEvent);
        return NO_ERROR;
    case SERVICE_CONTROL_PAUSE:
        UpdateServiceStatus(SERVICE_PAUSED);
        return NO_ERROR;
    case SERVICE_CONTROL_CONTINUE:
        UpdateServiceStatus(SERVICE_RUNNING);
        return NO_ERROR;
    case SERVICE_CONTROL_INTERROGATE:
        UpdateServiceStatus(serviceStatus.dwCurrentState);
        return NO_ERROR;
    default:
        break;
    }

    return ERROR_CALL_NOT_IMPLEMENTED;
}

VOID ExecuteServiceCode()
{
    stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    UpdateServiceStatus(SERVICE_RUNNING);

    // Example: Write file logic here
    HANDLE hFile = CreateFile(TEXT("C:\\windows\\temp\\thawd_lab.txt"),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        const char* data = "thawd lab from svchost";
        DWORD bytesWritten;
        WriteFile(hFile, data, strlen(data), &bytesWritten, NULL);
        CloseHandle(hFile);
    }


}


__declspec(dllexport) VOID WINAPI ServiceMain(DWORD argC, LPWSTR* argV)
{
    serviceStatusHandle = RegisterServiceCtrlHandler(SVCNAME, (LPHANDLER_FUNCTION)ServiceHandler);

    serviceStatus.dwServiceType = SERVICE_WIN32_SHARE_PROCESS;
    serviceStatus.dwServiceSpecificExitCode = 0;

    ExecuteServiceCode();
}