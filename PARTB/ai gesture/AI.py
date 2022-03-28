import cv2
import numpy as np
import time
import os
import HandTrackingModule as htm

###ACESS HEADER FOLDER

folderpath = "headers"
mylist = os.listdir(folderpath)
mylist.sort()##sorting
print(mylist)

####import images
overlayList= []
for imPath in mylist:
    image =cv2.imread(f'{folderpath}/{imPath}')
    overlayList.append(image)

print(len(overlayList))

#starting video and adding header
header= overlayList[0]
cap = cv2.VideoCapture(0)
cap.set(3,1280)
cap.set(4,720)

detector = htm.handDetector(detectionCon=0.85)
drawColour=(0,0,255)
xp,yp=0,0
imgCanvas = np.zeros((480,640,3),np.uint8)
brushThickness=15
eThickness=60

while True:
    ##import images
    success,img =cap.read()
    img =cv2.flip(img,1)
    ### 2.find hand landmarks
    img = detector.findHands(img)
    lmList =detector.findPosition(img,draw=False)
    if len(lmList)!=0:
        #print(lmlist)
        #TIP OF INDEX AND MIDDLE FINGER
        x1 ,y1 =lmList[8][1:]
        x2 ,y2 =lmList[12][1:]
        
        #3.check which finger is up
        fingers =detector.fingersUp()
        print(fingers)
        #4.Selection Mode
        if fingers[1] and fingers[2]==False and fingers[3]==False and fingers[4]==False and fingers[0]==False :
            xp,yp=0,0
            cv2.rectangle(img,(x1,y1-25),(x2,y2+25),drawColour,cv2.FILLED)
            #print("Selection Mode")
            #HEADER CHANGE
            if y1 <62:
                print(x1)
                if 150<x1<255:
                    header = overlayList[0]
                    drawColour=(0,0,255)
                    #print('red')
                elif 276<x1<360:
                    header = overlayList[1]
                    drawColour=(255,0,0)
                    #print('blue')
                elif 390<x1<480:
                    header = overlayList[2]
                    drawColour=(0,255,0)
                elif 510<x1<614:
                    header = overlayList[3]
                    drawColour=(0,0,0)
                

                    
        
        #5.Drawing mode
        if fingers[1] and fingers[2] and fingers[3]==False and fingers[4]==False and fingers[0]==False:
            cv2.circle(img,(x1,y1-15),15,drawColour,cv2.FILLED)
            print("Drawing Mode")
            if xp ==0 and yp==0:
                xp, yp= x1, y1
            if drawColour==(0,0,0):
                cv2.line(img,(xp,yp),(x1,y1),drawColour,eThickness)
                cv2.line(imgCanvas,(xp,yp),(x1,y1),drawColour,eThickness)
                
            cv2.line(img,(xp,yp),(x1,y1),drawColour,brushThickness)
            cv2.line(imgCanvas,(xp,yp),(x1,y1),drawColour,brushThickness)
            xp,yp=x1,y1
            
    imgGray = cv2.cvtColor(imgCanvas, cv2.COLOR_BGR2GRAY)
    _, imgInv = cv2.threshold(imgGray, 50, 255, cv2.THRESH_BINARY_INV)
    imgInv = cv2.cvtColor(imgInv,cv2.COLOR_GRAY2BGR)
    img = cv2.bitwise_and(img,imgInv)
    img = cv2.bitwise_or(img,imgCanvas)
#     print(img.shape)
#     print(imgCanvas.shape)
    #setting the header 
    imgCanvas[0:62,0:640] = header
#     img = cv2.addWeighted(img,0.5,imgCanvas,0.5,0)
    cv2.imshow("Image",img)
    cv2.imshow("Canvas",imgInv)
    cv2.waitKey(1)
    
    
    
    
    
    
    
