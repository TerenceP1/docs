cls
$totl=0
$corr=0
foreach ($file in Get-Childitem -Name -Filter "stdin*.txt"){
$totl=$totl+1
$LastExitCode = 0
Write-Output "`n`n`nUsing $file"
Write-Output "Running program..."
$pr=$file.substring(5,$file.length-9)
$out="stdout$pr.txt"
$start=(New-TimeSpan -Start (Get-Date "01/01/1970") -End (Get-Date)).TotalSeconds
Get-Content $file | .\pioneers.exe | out-file $out -encoding utf8
$end=(New-TimeSpan -Start (Get-Date "01/01/1970") -End (Get-Date)).TotalSeconds
$tm=$end-$start
Write-Output "Exit code: $LastExitCode"
Write-Output "Execution time: $tm seconds"
Write-Output "Checking answer..."
$x=( Get-Content $out -Encoding Byte -TotalCount 3 )
$hasbom= "$x" -eq "239 187 191"
if ($hasBom) {
Write-Output "Removing BOM..."
Get-Content $out -Encoding Byte -Tail ((Get-Item $out).length - 3) | Set-Content -Path tmp.txt -Encoding Byte
xcopy tmp.txt $out /y /q
Write-Output "Removed BOM"
}else{
Write-Output "No BOM"
}
$pass=comp "correct$pr.txt" "stdout$pr.txt" /m
if ("$pass" -eq "Comparing correct$pr.txt and stdout$pr.txt... Files compare OK "){
Write-Output "Correct"
if ($LastExitCode -eq 0){
$corr=$corr+1
}
}else{
Write-Output "Incorrect"
$outp=Get-Item "stdout$pr.txt"
$exoutp=Get-Item "correct$pr.txt"
if ($outp.Length -lt 30){
if ($exoutp.Length -lt 30){
Write-Output "Program output:"
Get-Content -Raw "stdout$pr.txt"
Write-Output "Expected:"
Get-Content -Raw "correct$pr.txt"
}
}
}
}
$score=$corr/$totl*100
Write-Output "`n`n`nYour score: $score%`n`n"
