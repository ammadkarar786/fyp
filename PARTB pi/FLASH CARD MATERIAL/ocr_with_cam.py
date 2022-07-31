import cv2 
import pytesseract

from text2speech import Speak_out
import os
from PIL import Image

##camera set up



##checking the text scanned
def check_spell(text,mylist):
    if text=='APPLE':
        cv2.destroyAllWindows()
        show=Image.open(mylist[0])
        show.show()

        #cv2.waitKey(1)
        Speak_out(text)
        Speak_out(text)
        Speak_out(text)
        show.close()
    elif text=='CHERRY':
        cv2.destroyAllWindows()
        show=Image.open(mylist[1])
        show.show()

        #cv2.waitKey(1)
        Speak_out(text)
        Speak_out(text)
        Speak_out(text)
    
    elif text=='PEAR':
        cv2.destroyAllWindows()
        show=Image.open(mylist[2])
        show.show()

        #cv2.waitKey(1)
        Speak_out(text)
        #Speak_out(text)
        #Speak_out(text)
##import images
folderpath = "FLASH CARD"
mylist = os.listdir(folderpath)
mylist.sort()##sorting
print(mylist)        

if __name__ == '__main__':
    
   
    image = frame.array
    cv2.imshow("Frame", image)
    key = cv2.waitKey(1)
    rawCapture.truncate(0)
       
    if key == ord("s"):
        text = pytesseract.image_to_string(image)
        print(text)
        cv2.imshow("Frame", image)
        cv2.waitKey(1)
            
        check_spell('CHERRY',mylist)
        
        
    cv2.destroyAllWindows()
    
