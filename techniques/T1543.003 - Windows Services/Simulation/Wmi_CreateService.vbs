Dim objService
Dim objInParam

' Obtain the definition of the Win32_Service class.
Set objService = GetObject("winmgmts:root\cimv2").Get("Win32_Service")

' Obtain an InParameters object specific to the Win32_Service.Create method.
Set objInParam = objService.Methods_("Create").inParameters.SpawnInstance_()

' Add the input parameters.
objInParam.Properties_.item("Name") = "Thawd_Wmi"
objInParam.Properties_.item("DisplayName") = "Thawd_Wmi"
objInParam.Properties_.item("PathName") = "C:\Thawd.exe"
objInParam.Properties_.item("ServiceType") = 16
objInParam.Properties_.item("ErrorControl") = 0
objInParam.Properties_.item("StartMode") = "Manual"
objInParam.Properties_.item("DesktopInteract") = False

' Execute the method and obtain the return status.
CreateFakeService = objService.ExecMethod_("Create", objInParam).ReturnValue