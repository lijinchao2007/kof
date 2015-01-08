@echo off
::需要改名的资源
set srcDir="E:\WorkInCaiTang\OurGames\trunk\res\拳皇\红丸\新建文件夹"
::改名后资源的保存目录
set dstDir="E:\WorkInCaiTang\OurGames\trunk\res\拳皇\红丸\copyfile"
::参考名字目录
set nameDir="E:\WorkInCaiTang\OurGames\trunk\res\拳皇\红丸\旧有资源\导出资源"

ChangeNameEx.py %srcDir% %dstDir% %nameDir%
pause 