
import PySimpleGUI as sg



layout =[
    
    [sg.Text('Pocobot Menu')],
    [sg.Button('Gesture Paint')],
    [sg.Button('Flash Card')],
    [sg.Cancel()]
    ]

window= sg.Window('My First Window',layout,size=(200,200))


while True:

    event,value =window.read()
    if event=='Gesture Paint':
    
        exec(open("AI.py").read())
        
    if event=='Cancel':
        window.close()
        break
        

    print(event)