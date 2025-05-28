$bDate=Get-Date
$bTime= ([DateTimeOffset]$bDate).ToUnixTimeSeconds()
Write-Output "Timeing now."
.\MD4-ahhh
$eDate=Get-Date
$eTime=([DateTimeOffset]$eDate).ToUnixTimeSeconds()
$res=$eTime-$bTime
Write-Output "That took about $res seconds!"