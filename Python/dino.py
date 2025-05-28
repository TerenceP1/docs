import pyautogui
import keyboard
import numpy as np
keyboard.wait("F2")

# pos=pyautogui.position()
# keyboard.wait("F2")
pos2=pyautogui.position()
keyboard.wait("F2")
while True:
    px=pyautogui.screenshot(region=(pyautogui.position()[0]-40,pyautogui.position()[1]-40,80,80))
    px2=pyautogui.pixel(pos2[0],pos2[1])
    if (px.getextrema()[0][0]<128 or px2[0]<128):
        keyboard.press_and_release("space")