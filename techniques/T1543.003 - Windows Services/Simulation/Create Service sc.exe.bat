@echo off
REM Service name
set SERVICE_NAME=Thawd_Sc

REM Path to the executable
set SERVICE_EXECUTABLE=C:\Thawd.exe

REM Create the service
sc create %SERVICE_NAME% binPath= "%SERVICE_EXECUTABLE%" start= auto