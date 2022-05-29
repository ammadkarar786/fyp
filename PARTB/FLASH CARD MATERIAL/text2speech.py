import pyttsx3
engine = pyttsx3.init()
rate = engine.getProperty('rate')                           
engine.setProperty('rate', 50)

fruit ='pear'
def Speak_out (fruit,speed=50):
    ##intilize the libaray
    engine = pyttsx3.init()
    rate = engine.getProperty('rate')                           
    engine.setProperty('rate', speed)
    for speak in fruit: ##sperate
        print(speak)
        engine.say(speak)
        engine.runAndWait()


    engine.say(fruit)
    engine.runAndWait()



# 
# for speak in fruit: ##sperate
#     print(speak)
#     engine.say(speak)
#     engine.runAndWait()
# 
# 
# engine.say(fruit)
# engine.runAndWait()

Speak_out("usaid",200)


    
