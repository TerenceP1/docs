import asyncio
import edge_tts
import pygame
pygame.mixer.init()

async def speak():
    tts = edge_tts.Communicate(text="Intruder alert! Intruder alert!", voice="en-US-AriaNeural")
    await tts.save("intruder.mp3")

asyncio.run(speak())

pygame.mixer.music.load("voice.mp3")  # works with MP3 and WAV
pygame.mixer.music.play()

while pygame.mixer.music.get_busy():
    continue