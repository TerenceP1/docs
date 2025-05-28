# -*- coding: utf-8 -*-
"""
Created on Thu Dec  7 21:00:18 2023

@author: teren
"""

import numpy 
import matplotlib.pyplot as plt
import wave
from threading import Thread
from pysine import sine
import math
import time
import pyaudio
wave=[numpy.sin(i/numpy.pi/2/1000) for i in range(44100)]
def get_sound():

   CHUNK = 1024
   FORMAT = pyaudio.paInt16
   CHANNELS = 1
   RATE = 44100
   pa = pyaudio.PyAudio()
   stream = pa.open(format=FORMAT,
                     channels=CHANNELS,
                     rate=RATE,
                     input=True,
                     frames_per_buffer=CHUNK)
   buffer = []
   wave=[]
   for _ in range(1000):
      string_audio_data = stream.read(CHUNK) 
      audio_data = numpy.frombuffer(string_audio_data, numpy.int16)
      volume_norm = numpy.linalg.norm(audio_data)*10
      dfft = 10.*numpy.log10(abs(numpy.fft.rfft(audio_data)))
      wave.append(int(volume_norm))
sampleRate=44100
plt.xlabel("frequency")  # add X-axis label 
plt.ylabel("ampletude")  # add Y-axis label 
plt.title("Fourier Transform result")  # add title 
def transform():
    N=44100
    res=[];
    for k in range(16384):
        if k/163-k//163==0:
            print(k/163)
            #plt.plot(numpy.array(list(range(k))),numpy.array(res))
            #plt.show()
        s=0
        for n in range(N):
            s+=wave[n]*numpy.cos(-2*numpy.pi*k*n/N)/N
        res.append(s)
    return res
#get_sound()
plt.plot(numpy.array(list(range(20000))),numpy.array(transform()))
plt.xlabel("frequency")  # add X-axis label 
plt.ylabel("ampletude")  # add Y-axis label 
plt.title("Fourier Transform result")  # add title 
plt.show()