# -*- coding: utf-8 -*-
"""
Created on Sun Dec 10 15:28:50 2023

@author: teren
"""
temp=input().split()
vals=[int(i) for i in temp]
def combine(x):
    res=''
    for i in x:
        res+=i
    return res
def pour(ox,a,b):
    x=list(ox)
    while x[a]>=0 and x[b]<=vals[b]:
        x[a]-=1
        x[b]+=1
    x[a]+=1
    x[b]-=1
    return x
def slv(x,pvals,ms=False):
    res=[]
    if ms:
        print(x)
    if x[0]==0:
        print(x[2])
        res.append(x[2])
    pvals.append(x)
    if ms:print(pvals)
    for i in range(3):
        for j in range(3):
            if i!=j:
                if ms:
                    print(f"slv({x}) is testing i={i} j={j}")
                fin=pour(x,i,j)
                if ms:
                    print(f"fin result is {fin}")
                if not fin in pvals:
                    tempog=slv(fin,pvals)
                    pvals=tempog[0]
                    res+=tempog[1]
    return [pvals,res]
print(combine([f"{i} " for i in sorted(slv([0,0,vals[2]],[])[1])]))