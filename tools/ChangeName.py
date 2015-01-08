# coding=gbk
__author__ = 'Administrator'

import sys
import os

import shutil


#rootDir = 'F:\OurGames\\trunk\\res\\123'
def main(rootDir):

    for root,dirs,files in os.walk(rootDir):
        for filespath in files:
            print filespath
            fileList = filespath.split("0")
            print fileList[0]
            filePre = fileList[0][0:-1]
            print rootDir+"\\"+filespath
            targetDir = rootDir+"\\"+filePre
            if not os.path.exists(targetDir):
                os.makedirs(targetDir)
            shutil.copy(rootDir+"\\"+filespath,targetDir)

# def Test2(rootDir):
#     for lists in os.listdir(rootDir):
#         path = os.path.join(rootDir, lists)
#         print path
#         if os.path.isdir(path):
#             Test2(path)

if __name__ == "__main__":
    filepath = sys.argv[1];
    #filepath = "E:\cocos2d-x-2.2.2\kof\OpenMugen\Resource\chars\IORI YAGAMI\Iori_Yagami-H.cns"

    main(filepath)
