# -*- coding: utf-8 -*-
"""
Created on Thu Apr  6 19:11:39 2023

@author: teren
"""

n = int(input())

def distinct_list(lst):
    # lst is the list of list
    print("sorting")
    if lst == [[]]:
        return lst[1]
    lst = sorted([sorted(x) for x in lst])
    res = []
    item=0
    for x in lst:
        if res == []:
            res.append(x)
            item+=1
            print(f"Found item {item}")
        elif x != res[-1]:
            res.append(x)
            item+=1
            print(f"Found item {item}")
    return res

def add1toeachnum_inlist(lst):
    # lst is the list of list
    res = []
    for a in lst:
        res += [[a[i]+1]+a[i+1:] if i==0 else a[:i]+[a[i]+1]+a[i+1:] for i in range(len(a))]
    return res


def split_nums(n):
    if n <= 0:
        return None
    if n == 1:
        return [[1]]
    dp = dict()
    for i in range(2, n+1):
        if i == 2:
            dp[i] = [[1,1]]
        else:
            dp[i] = distinct_list([[1]+x for x in dp[i-1]] + add1toeachnum_inlist(dp[i-1]))
        print(f"finished round {i} / {n}")
    return dp[n]

res = split_nums(n)
for r in res:
    print(f"{n}="+"+".join([str(x) for x in r]))
