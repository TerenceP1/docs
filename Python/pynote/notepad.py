# Pygame notepad :)
import pygame
import json
import time
import ctypes
MessageBox = ctypes.windll.user32.MessageBoxW
pygame.init()
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
GRAY = (200, 200, 200)
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True
pygame.display.set_caption('PyNote (Python notepad)')
Icon = pygame.image.load(r"C:\Users\teren\Downloads\BCO.1027d0ab-f96e-42cb-bd51-c6a8429e9c9b.png")
paper = pygame.image.load(r"C:\Users\teren\Downloads\paper.jpg")
pygame.display.set_icon(Icon)
font = pygame.font.SysFont("Courier New", 24)
txt="Text here..."
img = font.render("Text here...", True, RED)
txt=""
with open("text.txt",'r') as file:
    txt=file.read()
saved=True
dat={"data":txt,"unsaved":False}
odat={}
with open("autosave.json",'r') as file:
    odat=json.load(file)
if odat["unsaved"]:
    res=MessageBox(None, 'You can recover data from last auto save. Would you like to?', 'Recovery', 4)
    if res==6:
        dat=odat
        txt=odat["data"]
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            if (not saved):
                res=MessageBox(None, 'You have unsaved changes. Are you sure?', 'Unsaved changes', 4)
                if res==7:
                    continue
                else:
                    dat["unsaved"]=True
                    with open("autosave.json",'w') as file:
                        json.dump(dat,file)
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key==pygame.K_BACKSPACE:
                if len(txt)>0:
                    txt=txt[:-1]
                    print("Backspace")
                    saved=False
                    dat["data"]=txt
                    dat["unsaved"]=True
                    with open("autosave.json",'w') as file:
                        json.dump(dat,file)
            elif event.key==pygame.K_RETURN:
                txt+='\n'
                print("Enter key")
                saved=False
                dat["data"]=txt
                dat["unsaved"]=True
                with open("autosave.json",'w') as file:
                    json.dump(dat,file)
            else:
                if event.key==pygame.K_s and (event.mod & pygame.KMOD_CTRL):
                    print("save")
                    with open("text.txt",'w') as file:
                        file.write(txt)
                    saved=True
                    dat["unsaved"]=False
                    with open("autosave.json",'w') as file:
                        json.dump(dat,file)
                else:
                    txt+=event.unicode
                    print("Other key")
                    saved=False
                    dat["data"]=txt
                    dat["unsaved"]=True
                    with open("autosave.json",'w') as file:
                        json.dump(dat,file)
    bigpaper = pygame.transform.scale(paper, screen.get_size())
    screen.blit(bigpaper, screen.get_rect())
    ntxt=[""]
    ctr=0
    for i in range(len(txt)):
        
        if txt[i]=='\n':
            ntxt.append("")
            print("Enter")
            ctr=0
            continue
        ntxt[-1]+=txt[i]
        if ctr%88==87:
            ntxt.append("")
        ctr+=1
    #screen.fill(GRAY)
    yval=20
    for i in ntxt:
        img = font.render(i, True, BLACK)
        rect = img.get_rect()
        rect.topleft = (20, yval)
        rect.size=img.get_size()
        screen.blit(img, rect)
        yval+=28
    cursor=pygame.Rect(rect.topright, (1, rect.height))
    cursor.topleft = rect.topright
    if time.time() % 1 > 0.5:
        pygame.draw.rect(screen, BLACK, cursor)
    pygame.display.update()
    if saved:
        pygame.display.set_caption('PyNote (Python notepad)')
    else:
        pygame.display.set_caption('PyNote (Python notepad) - Unsaved work')