# coding=gbk
__author__ = 'Administrator'

import sys
import os

import shutil
import pprint


#rootDir = 'F:\OurGames\\trunk\\res\\123'
def main(rootDir, dstDir, nameDir):
    pngList = []
    for root,dirs,files in os.walk(rootDir):
        for filename in files:
            fullName = root + os.sep + filename
            pngList.append(fullName)

    nameList = getNameList(nameDir)
    
    srcCnt = len(pngList)
    dstCnt = len(nameList)
    if srcCnt != dstCnt:
        print "error: file count is not match!"
        print "src=%d dst=%s"%(srcCnt, dstCnt)
        return

    if not os.path.isdir(dstDir):
        os.makedirs(dstDir)

    for inx in range(len(pngList)):
        fullName = pngList[inx]
        #srcDir, srcName = os.path.split(fullName)
        #filename, fileext = os.path.splitext(srcName)
        dstName = dstDir + os.sep + nameList[inx] + ".pcx"
        shutil.copyfile(fullName, dstName)

    print "total=%s"%srcCnt


def getNameList(nameDir):
    tmpList = []
    nameList = []
    for root,dirs,files in os.walk(nameDir):
        for filename in files:
            name, fileExt = os.path.splitext(filename)
            if fileExt != ".pcx":
                continue
            
            heroName, partNum = name.split("-", 1)
            num1, num2 = partNum.split(",", 1)
            nameTuple = (heroName, int(num1), int(num2))
            tmpList.append(nameTuple)

    tmpList.sort(key=lambda x:x[2])
    tmpList.sort(key=lambda x:x[1])

    for inx in range(len(tmpList)):
        nameList.append("%s-%s,%s"%tmpList[inx])

    #pprint.pprint(nameList)
    return nameList
    

if __name__ == "__main__":
    rootDir = sys.argv[1];
    dstDir = sys.argv[2];
    nameDir = sys.argv[3];

    print rootDir
    print dstDir
    print nameDir
    
    #rootDir = r"E:\WorkInCaiTang\OurGames\trunk\res\拳皇\红丸\新建文件夹"
    #dstDir = r"E:\WorkInCaiTang\OurGames\trunk\res\拳皇\红丸\copyfile"
    #nameDir = r"E:\WorkInCaiTang\OurGames\trunk\res\拳皇\红丸\旧有资源\导出资源"
    main(rootDir, dstDir, nameDir)
    #getNameList(nameDir)
    print "finish";
