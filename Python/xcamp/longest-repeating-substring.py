# -*- coding: utf-8 -*-
"""
Created on Sat Jan 13 20:44:12 2024

@author: teren
"""

x=input()
tst=''
t=[]
for i in range(len(x)):
    tst+=x[i]
    for j in range(len(t)):
        if t[j][3]:
            if tst[t[j][0]+t[j][2]]==x[i]:
                t[j][2]+=1
            else:
                t[j][3]=False
                print(tst[t[j][0]:t[j][0]+t[j][2]+1])
    for j in range(0,i):
        if tst[j]==x[i]:
            t.append([j,i,1,True])
    print (t)
print ('\n\n\n\n\n\n\n\n')
for j in range(len(t)):
    print(tst[t[j][0]:t[j][0]+t[j][2]])
print('\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n')
hs=[0,0,0,True]
for i in range(len(t)):
    if t[i][2]>hs[2]:
        hs=t[i]
print(tst[hs[0]:hs[0]+hs[2]])
print('\n\n\n')
print(tst)
print(" "*hs[0]+'^'*hs[2])
print("")
print(tst)
print(" "*hs[1]+'^'*hs[2])