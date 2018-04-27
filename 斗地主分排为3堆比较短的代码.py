# -*- coding: utf-8 -*-
"""
Created on Fri Apr 27 09:42:10 2018

@author: ArcherX
"""
from random import shuffle  
from random import choice    
values = list(range(2, 11)) + 'J Q K A'.split()  
suits = '菱形 梅花 红桃 黑桃'.split()  
king = ['大王','小王']
deck = ['%s%s' % (s, v) for s in suits for v in values]  
c = king + deck 
shuffle(c)  
P = Q = L = []
count=0  
while c:   
    randomCard = choice(c)  
    L.append(randomCard)
    c.remove(randomCard)
    count+=1
    while count == 17:    
        print(L)
        print(c[0:17])
        print(c[17:37])
        break
