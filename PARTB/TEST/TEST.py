
import PySimpleGUI as sg



layout =[
    
    [sg.Text('Hello World')],
    [sg.Button('Gesture Paint')],
    [sg.Button('Flash Card')],
    [sg.Cancel()]
    ]

window= sg.Window('My First Window',layout,size=(600,600))

event,value =window.read()
print(event)
window.close()