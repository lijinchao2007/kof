__author__ = 'Administrator'


import sys

def main(filepath):
    fileHandle = open(filepath)
    lineList = fileHandle.readlines()
    fileHandle.close()

    for i,line in enumerate(lineList):
        curLine = line.strip()
        print curLine
        print i;
        if(curLine.startswith("Clsn1[") or curLine.startswith("Clsn2[")):
            preString = curLine[0:11]
            numStr = curLine[11:]
            numsList = numStr.split(",")
            for j,num in enumerate(numsList):
                numsList[j] = int(int(num)*2.77)

            resultNums = str(numsList).replace("[", "").replace("]", "")
            line = preString + " "+ resultNums +"\n"

            lineList[i] = line
            print line;
        elif(len(curLine) == 0 or not curLine[0].isdigit()):
            continue
        else:
            numsList = curLine.split(",")
            for k,num in enumerate(numsList):
                if(k > 4):
                    continue
                if(k == 2 or k ==3):
                    numsList[k] = int(int(num)*2.77)
                else:
                    numsList[k] = int(num)

            resultNums = str(numsList).replace("[", "").replace("]", "").replace("'", "")
            lineList[i] = resultNums +"\n"
            print line;


    fileHandle = open ( filepath, 'w' )
    fileHandle.writelines(lineList)
    fileHandle.close()


if __name__ == "__main__":
    filepath = sys.argv[1];
    #filepath = "E:\cocos2d-x-2.2.2\kof\OpenMugen\Resource\chars\IORI YAGAMI\Iori_Yagami.air"
    main(filepath)

