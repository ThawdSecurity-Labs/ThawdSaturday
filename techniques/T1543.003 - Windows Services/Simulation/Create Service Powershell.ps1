# Service name
$serviceName = "Thawd_Powershell"

# Path to the executable
$exePath = "C:\Thawd.exe"

# Service display name
$displayName = "Thawd_Powershell"

# Service description
$description = "This is a custom service created by PowerShell."

# Create the service
New-Service -Name $serviceName -BinaryPathName $exePath -DisplayName $displayName -Description $description -StartupType Automatic

