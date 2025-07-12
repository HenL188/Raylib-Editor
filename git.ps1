param (
    [string]$m
)

if ($m -eq $null){
    Write-Host "No commit messge"
}
else{
    git add .
    git commit -m $m
    git switch main
    git merge dev
    git push
    git switch dev
}
