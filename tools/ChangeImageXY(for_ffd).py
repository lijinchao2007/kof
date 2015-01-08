
#!/usr/bin/python
# URL that generated this code:
# http://www.txt2re.com/index-python.php3?s=%20Clsn2[0]%20=%20%20-9,-82,%2046,-48&-4&32&31&63&60&45&46&47&11&10&12&17&16&15&62

import sys
import os
import struct


fileNameArr = []
oldHeightDict = {}
newHeightDict = {}

oldWidthDict = {}
newWidthDict = {}

def getImgSize(rootDir,filespath):
    global oldHeightDict
    fileHandle = open(rootDir + filespath, "rb")
    first = struct.unpack("4b4h", fileHandle.read(12))
    fileHandle.close()
    oldHeightDict[filespath] = first[7]


def getImgSizeNew(rootDir,filespath):
    global newHeightDict
    fileHandle = open(rootDir + filespath, "rb")
    first = struct.unpack("4b4h", fileHandle.read(12))
    fileHandle.close()
    newHeightDict[filespath] = first[7]


def getSize(oldRootDir, newRootDir):
    for root,dirs,files in os.walk(oldRootDir):
        for filespath in files:
            #print oldRootDir + filespath
            getImgSize(oldRootDir,filespath)

    for root,dirs,files in os.walk(newRootDir):
        for filespath in files:
            #print newRootDir + filespath
            getImgSizeNew(newRootDir,filespath)


def main(filepath, fixSize):
    global fileNameArr
    fileHandle = open(filepath)
    lineList = fileHandle.readlines()
    fileHandle.close()
    curImgIndex = 0;

    for i,line in enumerate(lineList):
        curLine = line.lstrip()
        if(curLine.startswith("pcximage")):
            filename = curLine[11:].strip()
            fileNameArr.append(filename)

    for i,line in enumerate(lineList):

        curLine = line.lstrip()
        if(curLine.startswith("xaxis")):
            oh = oldHeightDict[fileNameArr[curImgIndex]]
            nh = newHeightDict[fileNameArr[curImgIndex]]
            if(oh == nh):
                continue
            preString = curLine[0:7]
            numStr = curLine[7:]
            line = preString + " " + str(int(int(numStr)*2.77)) +"\n"
            lineList[i] = line

        if(curLine.startswith("yaxis")):

            oh = oldHeightDict[fileNameArr[curImgIndex]]
            nh = newHeightDict[fileNameArr[curImgIndex]]
            if(oh == nh):
                curImgIndex += 1
                continue

            preString = curLine[0:7]
            numStr = curLine[7:]
            h = oldHeightDict[fileNameArr[curImgIndex]]

            if(h - int(numStr) < 6 and h - int(numStr) > -6):
                line = preString + " " + str(newHeightDict[fileNameArr[curImgIndex]] - int(fixSize) + 1) +"\n"
            else:
                line = preString + " " + str(int(int(numStr)*2.77)) +"\n"
            lineList[i] = line
            #print str(h) + ":" + str(newHeightArr[curImgIndex] - 5);
            curImgIndex += 1

    fileHandle = open(filepath, 'w')
    fileHandle.writelines(lineList)
    fileHandle.close()


if __name__ == "__main__":
    filepath = sys.argv[1];
    print filepath
    oldRootDir = sys.argv[2];
    print oldRootDir
    newRootDir = sys.argv[3];
    print newRootDir
    fixSize = sys.argv[4];
    print fixSize

    getSize(oldRootDir, newRootDir)
    main(filepath, fixSize)

    #getSize("C:\Users\Administrator\Desktop\\test\pic_old\\", "C:\Users\Administrator\Desktop\\test\pic_old\\");