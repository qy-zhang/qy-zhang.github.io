import sys
import string
import os

filePath = 'E:\\Learning\\Code\\workspace\\data.txt';
oldFile = open(filePath, "r")
path, name = os.path.split(filePath)
#newFile = open(path + 'a' + name, "w")
resultPath = 'E:\\Learning\\Code\\workspace\\result.txt';
newFile = open(resultPath, "w");

lineStr = ""
tmpData = 1
for line in oldFile.readlines():
	line = line.strip('\n')
	# tmpData = float(line)
	# tmpData = tmpData * 32767
	# tmpData2 = int(tmpData)
	# if (tmpData2 > 0):
	# 	tmpData2 += 1
	# elif (tmpData2 < 0):
	# 	tmpData2 -= 1
	# lineStr += str(tmpData2)
	lineStr += str(line)
	lineStr += '\t'
newFile.write(lineStr)

oldFile.close()
newFile.close()