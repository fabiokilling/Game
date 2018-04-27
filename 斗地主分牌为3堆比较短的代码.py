# -*- coding: utf-8 -*-
from random import shuffle, choice      
values = list(range(2, 11)) + 'J Q K A'.split()  
suits = '菱形 梅花 红桃 黑桃'.split()  
king = ['大王','小王']
deck = ['%s%s' % (s, v) for s in suits for v in values]  
c = king + deck 
shuffle(c)  
L = []
count=0  
while c:   
    randomCard = choice(c)  
    L.append(randomCard)
    c.remove(randomCard)
    count+=1
    while count == 17:    
        print('农民1\n',L,'\n','农民2\n',c[0:17],'\n','地主\n',c[17:37])
        break
