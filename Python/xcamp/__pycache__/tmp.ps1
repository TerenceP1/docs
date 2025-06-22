Add-Type -AssemblyName System.Windows.Forms

while ($true) {
    [System.Windows.Forms.SendKeys]::SendWait("s")
    Start-Sleep -Seconds 1
}
