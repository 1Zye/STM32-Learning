param([string]$ProjectFile)
$ErrorActionPreference = 'Stop'
$root = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
if (-not $ProjectFile) {
    $projects = @(Get-ChildItem -LiteralPath (Join-Path $root 'MDK-ARM') -Filter '*.uvprojx')
    if ($projects.Count -ne 1) { throw 'Specify -ProjectFile: more than one or no Keil project found.' }
    $ProjectFile = $projects[0].FullName
}
$ProjectFile = (Resolve-Path -LiteralPath $ProjectFile).Path
if (-not $ProjectFile.StartsWith($root+'\',[StringComparison]::OrdinalIgnoreCase)) { throw 'Project must be inside this copy.' }
foreach ($f in @('Core\Src\OLED.c','Core\Inc\OLED.h','Core\Inc\OLED_Font.h')) {
    if (-not (Test-Path -LiteralPath (Join-Path $root $f))) { throw "Missing $f" }
}
[xml]$xml = Get-Content -LiteralPath $ProjectFile -Raw
foreach ($target in $xml.Project.Targets.Target) {
    # Remove only OLED entries, then add exactly one copy in a dedicated user group.
    foreach ($f in @($target.SelectNodes('.//Groups/Group/Files/File'))) {
        if ($f.FileName -in @('OLED.c','OLED.h','OLED_Font.h')) { [void]$f.ParentNode.RemoveChild($f) }
    }
    $g = $target.SelectSingleNode('Groups/Group[GroupName="User OLED"]')
    if (-not $g) {
        $g=$xml.CreateElement('Group'); $n=$xml.CreateElement('GroupName'); $n.InnerText='User OLED'; [void]$g.AppendChild($n)
        [void]$g.AppendChild($xml.CreateElement('Files')); [void]$target.Groups.AppendChild($g)
    }
    foreach ($item in @(@('OLED.c','1','..\Core\Src\OLED.c'),@('OLED.h','5','..\Core\Inc\OLED.h'),@('OLED_Font.h','5','..\Core\Inc\OLED_Font.h'))) {
        $f=$xml.CreateElement('File')
        for($i=0;$i -lt 3;$i++) { $n=$xml.CreateElement(@('FileName','FileType','FilePath')[$i]); $n.InnerText=$item[$i]; [void]$f.AppendChild($n) }
        [void]$g.SelectSingleNode('Files').AppendChild($f)
    }
    $inc=$target.SelectSingleNode('TargetOption/TargetArmAds/Cads/VariousControls/IncludePath')
    $paths=@($inc.InnerText.Split(';') | Where-Object { $_ })
    if (-not ($paths | Where-Object { $_.Replace('/','\').TrimEnd('\') -eq '..\Core\Inc' })) { $inc.InnerText=($paths + '..\Core\Inc') -join ';' }
}
$backup=$ProjectFile+'.'+(Get-Date -Format 'yyyyMMddHHmmssfff')+'.bak'
Copy-Item -LiteralPath $ProjectFile -Destination $backup
[IO.File]::WriteAllText($ProjectFile, $xml.OuterXml, [Text.UTF8Encoding]::new($false))
Write-Output "OLED references restored: $ProjectFile"
Write-Output "Backup: $backup"
