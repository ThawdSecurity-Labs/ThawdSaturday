@echo off

REM Stop and delete services

echo Stopping and deleting services...

sc stop Thawd_Registry
sc delete Thawd_Registry

sc stop Thawd_Svchost
sc delete Thawd_Svchost

sc stop Thawd_WinApi
sc delete Thawd_WinApi

sc stop Thawd_Powershell
sc delete Thawd_Powershell

sc stop Thawd_Wmi
sc delete Thawd_Wmi

sc stop Thawd_Sc
sc delete Thawd_Sc

echo Services stopped and deleted.

pause