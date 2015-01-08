
#!/usr/bin/python
# URL that generated this code:
# http://www.txt2re.com/index-python.php3?s=%20Clsn2[0]%20=%20%20-9,-82,%2046,-48&-4&32&31&63&60&45&46&47&11&10&12&17&16&15&62

import sys
import os
def main(filepath):
    fileHandle = open(filepath)
    lineList = fileHandle.readlines()
    fileHandle.close()

    beginStr = "prevpalette"
    strSize = len(beginStr) + 3
    for i,line in enumerate(lineList):
        curLine = line.lstrip()
        if(curLine.startswith(beginStr)):
            preString = curLine[0:strSize]
            numStr = curLine[strSize:]
            line = preString + "0" +"\n"
            lineList[i] = line
            print line;


    fileHandle = open(filepath, 'w')
    fileHandle.writelines(lineList)
    fileHandle.close()


if __name__ == "__main__":
    filepath = sys.argv[1];
    main(filepath)
    os.system("pause")
