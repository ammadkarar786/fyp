import os
import cv2
from PIL import Image
folderpath = "FLASH CARD"
mylist = os.listdir(folderpath)
mylist.sort()##sorting
print(mylist)

show=Image.open(mylist[0])
show.show()
show.Kill()
