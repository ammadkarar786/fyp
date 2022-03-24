import pyttsx3
engine = pyttsx3.init()
rate = engine.getProperty('rate')   
print (rate)                        
engine.setProperty('rate', 50)  


engine.say("A")
engine.runAndWait()

engine.say("P")
engine.runAndWait()


engine.say("P")
engine.runAndWait()


engine.say("L")
engine.runAndWait()

engine.say("E")
engine.runAndWait()

engine.say("APPLE")
engine.runAndWait()