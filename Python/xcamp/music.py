# -*- coding: utf-8 -*-
"""
Created on Sat Dec 23 13:07:50 2023

@author: teren
"""

import wave
import numpy as np
out=wave.open(r"c:\Users\teren\Documents\music.wav",'wb')
out.setframerate(14400)
anotes=[220,246.94,261.63,293.66,329.63,349.23,392,440]
ind=0
res=[]
cont=0
length=0
dr=1
for _ in range(20):
    print(ind)
    if length==0:
        dr=1/int(np.random.random()*2+1)
        length=int(1/dr)
    length-=1
    ind+=2*(np.random.random()>0.5)-1
    if ind<0:
        ind=1
    elif ind>7:
        ind=6
    for i in range(int(14400*dr)):
        res.append(int(np.sin(2/2*np.pi*i/14400*anotes[ind]/anotes[ind])*256))
out.setnframes(len(res))
out.setsampwidth(1)
out.setnchannels(1)
out.writeframes(np.array(res))
print(out.close())