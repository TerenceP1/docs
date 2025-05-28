# -*- coding: utf-8 -*-
"""
Created on Sun Dec  3 19:03:11 2023

@author: teren
"""

import pandas as pd
n,m=input().split()
n=int(n)
m=int(m)
print(f"n={n}\nm={m}")
mp=[input().split() for _ in range(n)]
se=[int(i) for i in input().split()]
vm=[[False for _ in range(m)] for _ in range(n)]
print(vm)
print(se)
print(mp)
drs=[[0,1],[1,0],[0,-1],[-1,0]]
print("good so far... function definitions:")
def isValid(x,y):
    return (x>-1 and x<n)and(y>-1 and y<m)
print("isValid")
def dfs(x,y,cdir):
    if mp[x][y]=='1':
        return [m*n,cdir]
    elif vm[x][y]:
        return [m*n,cdir]
    elif se[2]-1==x and se[3]-1==y:
        return [0,cdir]
    else:
        print(f"dfs({x},{y})")
        print(pd.DataFrame(vm))
        res=[m*n,cdir]
        vm[x][y]=True;
        for j in range(4):
            i=drs[j]
            if isValid(x+i[0],y+i[1]):
                print(f"direction {j}")
                dres=dfs(x+i[0],y+i[1],j)
                print(f"direction {j} success")
                if dres[0]!=m*n:
                    if dres[1]!=cdir:
                        dres[0]+=1
                    if dres[0]<res[0]:
                        res=dres
                print(res)
        vm[x][y]=False
        return res
print("dfs")
print(dfs(se[0]-1,se[1]-1,0)[0])