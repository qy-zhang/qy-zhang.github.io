import sys
import string
import os
import os.path

filePath = 'E:\\Learning\\Code\\workspace\\tmpHpy\\tempH';
files = os.listdir(filePath)
# 对数组每个元素x取从第5个到末尾的int型数字作为key
files.sort(key = lambda x:int(x[5:]))
print files

# tmpFile = open(filePath, "r")

# arr = []
# for line in tmpFile.readlines():
# 	line = line.strip('\n')
# 	arr.append(line)

# tmpFile.close()

# print arr