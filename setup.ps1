# 前面加A，并且用减号连接。
$numOfArgs = $args.Length
$str = "A$($args[0])"
for ($i=1; $i -lt $numOfArgs; $i++)
{
   $str = "$str-$($args[$i])"
}
write-host "$str"

mkdir $str
cd $str
copy ..\template.cpp .\main.cpp
New-Item -Name input.txt -ItemType File
cd ..