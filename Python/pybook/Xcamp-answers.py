# -*- coding: utf-8 -*-
"""
Created on Thu Apr  6 08:13:20 2023

@author: teren
"""

# 1 remander

a=int(input())
b=int(input())
print(a%b)
#2 print even

n,m=map(int,input().split())
m=m - m%2
n=n%2 + n
res=""
for i in range(n,m+1,2):
    res+=str(i)+" "
print(res.strip())
    
#3 List of Prime Numbers

n=int(input())

res=""
for i in range(2,n):
    isprime=True
    for j in range(2,i):
        if i%j==0:
            isprime=False
    if isprime:
        res+=str(i)+" "
print(res.strip())

#4 Character amout Counting

s=input()

abc="abcdefghijklmnopqrstuvwxyz"
res=""
for i in abc:
    num=0
    for j in s:
        if j==i:
            num+=1
    res+=str(num)+" "
print(res.strip())

#5 Odd-even sort
nums=[i for i in map(int,input().split())]
odd=[]
even=[]
for i in nums:
    if i%2==1:
        odd.append(i)
    else:
        even.append(i)
odd=sorted(odd,reverse=True)
even=sorted(even)
res=""
for i in odd:
    res+=str(i)+" "
for i in even:
    res+=str(i)+" "
print(res.strip())

#6 Friendly Pair

n,m=list(map(int,input().split()))
array=[]
for _ in range(n):
    array.append(list(map(int,input().split())))
res=0
for i in array:
    for j in range(m-1):
        if i[j]==i[j+1]:
            res+=1
for i in range(m):
    for j in range(n-1):
        if array[j][i]==array[j+1][i]:
            res+=1
print(res)

#Linear iteration I

x=int(input())
if x<2:
    print(1)
else:
    a,b=1,1
    for _ in range(x-1):
        a,b=b,b+a
    print(b%1000000007)
    
#Walk on a grid

n,m=map(int,input().split())
res=1
for i in range(n+1,n+m+1):
    res*=i
for i in range(1,m+1):
    res/=i
print(int(res))

#Hanoi tower 2

n=int(input())
def hanoi(n,s,e):
    if n==1:
        return f"{s}->{e}\n"
    else:
        o=None
        for i in "ABC":
            if i!=s and i!=e:
                o=i
        return f"{hanoi(n-1,s,o)}{s}->{e}\n{hanoi(n-1,o,e)}"
    
#Combinational Sum

res=False
n,k=map(int,input().split())
nums=list(map(int,input().split()))
for i in range(1,(2**n)):
    test="0"*(n-len(bin(i))+2)+bin(i)[2:]
    sum=0
    for j in range(n):
        sum+=int(test[j])*nums[j]
    if sum==k:
        res=True
        break
print({True:"Yes",False:"No"}[res])

#Territory

n,m=map(int,input().split())
array=[["_" for _ in range(m+2)]]

for _ in range(m):
    array.append([i for i in f"_{input()}_"])
array+=[["_" for _ in range(m+2)]]
res=0
while True:
    end=True
    for i in range(1,m+2):
        for j in range(1,n+2):
            if not array[i][j] in "#@_":
                if "@" in [array[i-1][j],array[i+1][j],array[i][j+1],array[i][j-1]]:
                    end=False
                    array[i][j]="@"
                    res+=1
    if end:
        break
print(res+1)

#12 Splitting of natural numbers

n = int(input())
#mem = {}


def split(n,mem={}):
    if n == 1:
        return [[1]]
    else:
        if n in mem:
            return mem[n]
        else:
            res = []
            for i in range(1, n):
                f = []
                for j in split(n-i,mem):
                    f += [[i]+j]
                res += f
            mem[n] = res+[[n]]
            print(f"finished round {n}")
            return res+[[n]]

def test(n):
    item=0
    rep = []
    res = []
    for i in split(n)[:-1]:
        f = f"{n}="
        if not sorted(i) in rep:
            for j in sorted(i)[:-1]:
                f += f"{j}+"
            f += str(sorted(i)[-1])
            rep += [sorted(i)]
            res+=[f]
            item+=1
            print(f"found item {item}")
    return sorted(res)
        
#13 Knight Moves

n=int(input())
sx,sy=map(int,input().split())
ex,ey=map(int,input().split())
array=[[i for i in '_'*(n+4)]]*2 + [[i for i in ("__"+"?"*n+"__")]]*n + [[i for i in '_'*(n+4)]]*2
#^
#|
#|
#|
#y
#x ----->
#[[x]]
#[[y,_,_],[y,_,_]]
array[sy+2]=array[sy+2][:sx+2]+["s"]+array[sy+2][sx+3:]
array[ey+2]=array[ey+2][:ex+2]+["e"]+array[ey+2][ex+3:]
while array[ey+2][ex+2]=='e':
    for y in range(2,n+2):
        for x in range(2,n+2):
            if array[y][x]!="s" and not isinstance(array[y][x],int):
                res='?'
                if isinstance(array[y+2][x+1],int):
                    if isinstance(res,int):
                        if array[y+2][x+1] + 1 < res:
                            res=array[y+2][x+1] + 1
                    else:
                        res=array[y+2][x+1] + 1
                elif array[y+2][x+1]=='s':
                    res=1
                if isinstance(array[y+2][x-1],int):
                    if isinstance(res,int):
                        if array[y+2][x-1] + 1 < res:
                            res=array[y+2][x-1] + 1
                    else:
                        res=array[y+2][x-1] + 1
                elif array[y+2][x-1]=='s':
                    res=1
                if isinstance(array[y-2][x+1],int):
                    if isinstance(res,int):
                        if array[y-2][x+1] + 1 < res:
                            res=array[y-2][x+1] + 1
                    else:
                        res=array[y-2][x+1] + 1
                elif array[y-2][x+1]=='s':
                    res=1
                if isinstance(array[y-2][x-1],int):
                    if isinstance(res,int):
                        if array[y-2][x-1] + 1 < res:
                            res=array[y-2][x-1] + 1
                    else:
                        res=array[y-2][x-1] + 1
                elif array[y-2][x-1]=='s':
                    res=1
                if isinstance(array[y+1][x+2],int):
                    if isinstance(res,int):
                        if array[y+1][x+2] + 1 < res:
                            res=array[y+1][x+2] + 1
                    else:
                        res=array[y+1][x+2] + 1
                elif array[y+1][x+2]=='s':
                    res=1
                if isinstance(array[y-1][x+2],int):
                    if isinstance(res,int):
                        if array[y-1][x+2] + 1 < res:
                            res=array[y-1][x+2] + 1
                    else:
                        res=array[y-1][x+2] + 1
                elif array[y-1][x+2]=='s':
                    res=1
                if isinstance(array[y+1][x-2],int):
                    if isinstance(res,int):
                        if array[y+1][x-2] + 1 < res:
                            res=array[y+1][x-2] + 1
                    else:
                        res=array[y+1][x-2] + 1
                elif array[y+1][x-2]=='s':
                    res=1
                if isinstance(array[y-1][x-2],int):
                    if isinstance(res,int):
                        if array[y-1][x-2] + 1 < res:
                            res=array[y-1][x-2] + 1
                    else:
                        res=array[y-1][x-2] + 1
                elif array[y-1][x-2]=='s':
                    res=1
                if isinstance(res,int):
                    array[y]=array[y][:x]+[res]+array[y][x+1:]
print(array[ey+2][ex+2])

#14 UP and DOWN
try:
    n,a,b=map(int,input().split())
    k=list(map(int,input().split()))
    assert int(input())==0
    sol=[None for _ in range(n)]
    sol[a-1]=0
    end=False
    while end==False:
        change=False
        for i in range(n):
            if isinstance(sol[i],int):
                if i-k[i]>=0:
                    if sol[i-k[i]]==None:
                        sol[i-k[i]]=sol[i]+1
                        change=True
                if i+k[i]<=n-1:
                    if sol[i+k[i]]==None:
                        sol[i+k[i]]=sol[i]+1
                        change=True
        if change==False or sol[b-1]!=None:
            end=True
    if sol[b-1]==None:
        print(-1)
    else:
        print(sol[b-1])
except:
    print(-1)
    
#15 01 Maze

n,m=map(int,input().split())
array=[[i for i in input()] for _ in range(n)]
r,c=[],[]
for _ in range(m):
    x=map(input().split())
    a,b=map(int,input().split())
    r+=a
    c+=b
for i in range(m):
    for y in range(n):
        for x in range(n):
            