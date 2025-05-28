# -*- coding: utf-8 -*-
"""
Created on Fri Nov 11 19:14:00 2022

@author: teren
"""

import json

nums = []
num = 0
print("please write a number\ntype q to quit")
while True:
    try:
        x = input("number: ")
        if x == 'q':
            break
        else:
            num = float(x)
    except ValueError as e:
        print(f"that was a error):\nValueError: {e}\ntry again")
    else:
        nums += [num]
print("what do you want to save your numbers as?")
filename=input("filename: ")+'.json'
with open('numbers.json','w') as f:
    json.dump(nums,f)
print('I saved your numbers!\nrun number_reader.py to see the numbers!')
