__author__ = 'Administrator'

import sys

def main(filepath):
    fileHandle = open(filepath)
    lineList = fileHandle.readlines()
    fileHandle.close()

    for i,line in enumerate(lineList):
        curLine = line.lstrip()
        if(curLine.startswith("sparkxy")):
            preString = curLine[0:10]
            numStr = curLine[10:]
            kuohaoNum = 0;
            strList = list(numStr)
            daohaoIndex = 0
            for k,curStr in enumerate(strList):
                if(curStr == "("):
                    kuohaoNum += 1
                if(curStr == ")"):
                    kuohaoNum -= 1
                if(curStr == ","):
                    if(kuohaoNum > 0):
                        continue
                    else:
                        daohaoIndex = k
                        break

            xStr = numStr[0:daohaoIndex]
            yStr = numStr[daohaoIndex+1:-1]

            xStr = "floor((" + xStr.strip() + ")*2.77)".strip()
            yStr = "floor((" + yStr.strip() + ")*2.77)".strip()
            # for j,num in enumerate(numsList):
            #     if(j > 1):
            #         break
            #     # if(num.startswith("floor")):
            #     #     numsList[j] = "floor("+num+" pos y))*2.77)"
            #     # else:
            #     #     numsList[j] = int(int(num)*2.77)
            #     if(len(numsList) > 2 and j == 1):
            #         numsList[j] = "floor((" + num.strip() + "," + numsList[2].strip() + ")*2.77)".strip()
            #     else:
            #         numsList[j] = "floor((" + num.strip() + ")*2.77)".strip()
            #  resultNums = numsList[0] + "," + numsList[1]

            resultNums = xStr + "," + yStr
            line = preString + " "+ resultNums + "\n"
            lineList[i] = line
            print line;


    fileHandle = open(filepath, 'w')
    fileHandle.writelines(lineList)
    fileHandle.close()

import  os
if __name__ == "__main__":
    filepath = sys.argv[1];
    # filepath = "E:\cocos2d-x-2.2.2\kof\OpenMugen\Resource\chars\\benimaru\\benimaru.cns"

    main(filepath)
    os.system("pause")