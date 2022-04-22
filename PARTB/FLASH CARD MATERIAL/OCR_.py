import os
import cv2
folderpath = "FLASH CARD"
mylist = os.listdir(folderpath)
mylist.sort()##sorting
print(mylist)

show=cv2.imread(mylist[2],1)
bigger = cv2.resize(show, (600, 600))##resizimg the image
cv2.imshow('image',bigger)
