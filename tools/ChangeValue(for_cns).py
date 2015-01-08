__author__ = 'Administrator'

import sys
import os

#gKeyword = ".velocity"

def main(filepath, keyword):
    fileHandle = open(filepath)
    lineList = fileHandle.readlines()
    fileHandle.close()

    try:
        for i,line in enumerate(lineList):
            curLine = line.lstrip()
            if(curLine.find(keyword) >= 0):
                chInx = curLine.find(keyword) + len(keyword)
                preString = curLine[0:chInx]
                contentStr = curLine[chInx:]
                if (contentStr.find(';') == -1):
                    numStr = curLine[chInx:].strip()
                    remStr = ''
                else:
                    numStr, remStr = curLine[chInx:].strip().split(';', 1)
                    remStr = '  ;' + remStr
                numsList = getNumList(numStr)

                resultStr = ''    
                for j, num in enumerate(numsList):
                    if (num.find('(') == -1):
                        resultStr += str(float(num) * 2.77)
                    else:
                        resultStr += "floor((" + num.strip() + ")*2.77)".strip()
                    if (j < len(numsList) - 1):
                        resultStr += ','

                line = preString + " " + resultStr + remStr + "\n"
                lineList[i] = line
                print line;
    except:
        print "error: keyword=%s lineNo=%d"%(keyword, i+1)

    fileHandle = open(filepath, 'w')
    fileHandle.writelines(lineList)
    fileHandle.close()


def getNumList(txt):
    numList = []
    flag = 0
    iStart = -1;
    
    for i in range(len(txt)):
        ch = txt[i]
        if (i == len(txt) - 1 and ch != ','):
            numList.append(txt[iStart+1:])
        elif(ch == '('):
            flag += 1;
        elif (ch == ')'):
            flag -= 1;
        elif (ch == ',' and flag == 0):
            numList.append(txt[iStart+1:i])
            iStart = i
            
    return numList


if __name__ == "__main__":
    global gKeyword
    filepath = sys.argv[1];
    keywordList = [".velocity =", "yaccel ="]
    for keyword in keywordList:
        print "==========start=========="
        print "keyword=%s"%keyword    
        #filepath = r"E:\WorkInCaiTang\OurGames\trunk\code\client\KOF\trunk\OpenMugen\Resource\chars\benimaru\benimaru.cns"
        main(filepath, keyword)
        print "==========finish=========="

    
