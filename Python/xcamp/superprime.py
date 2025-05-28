# -*- coding: utf-8 -*-
"""
Created on Sun Dec 10 18:21:52 2023

@author: teren
"""

n=int(input())
digits=[1,2,3,4,5,6,7,8,9]
superprimes=[0]
def isPrime(x):
    res=True
    if x==1:
        return False;
    for i in range(2,int(x**0.5)):
        if x/i==x//i:
            res=False
    return res;
ml=1
for _ in range(n):
    nsp=[]
    for i in superprimes:
        temp=[i+ml*j for j in digits]
        for j in temp:
            if isPrime(j):
                nsp.append(j)
    superprimes=nsp
    ml*=10
ans=''
for i in superprimes:
    ans+=f"{i} "
print(ans)