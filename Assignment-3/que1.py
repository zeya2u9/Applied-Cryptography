"""
3 n-bit numbers x, y and N
n = 64-bit
2^64 = 1,84,46,74,40,73,70,95,51,616

modPlus - to calculate (x+y)mod N
modMult - to calculate (x*y)mod N
"""
import math
import time
import numpy as np

def modPlus(x,y,N):
    #print('x=',x,'y=',y,'N=',N)
    N = np.uint64(N)
    r1 = np.uint64(x%N)
    r2 = np.uint64(y%N)
    if r1>r2:
        y = np.uint64(r2)
    else:
        y = np.uint64(r1)
        r1 = r2
    #print(y,r1)
    l1 = len(bin(y)) - 3
    l2 = len(bin(r1)) - 3
    maxx = max(l1,l2)
    if maxx+1 < 64:
        #print(y,r1,y+r1)
        result = np.uint64((y+r1)%N)
        return result
    temp = np.uint64(N-r1)
    if temp>y:
        result = np.uint64((y+r1)%N)
        return result
    result = np.uint64(y-temp)

    return result

def modMult(x,y,N):
    print('x=',x,'y=',y,'N=',N)
    a1 = np.uint64(x%N)
    a2 = np.uint64(y%N)
    min_a = np.uint64( min(a1,a2) )
    max_a = np.uint64( max(a1,a2) )
    res = np.uint64(max_a)
    extra = np.uint64(0)
    l1 = len(bin(a1)) - 3
    l2 = len(bin(a2)) - 3
    
    if (l1+l2)<64:
        result = np.uint64((a1*a2) % N)
        return result
    
    while(min_a>np.uint64(1)):
        #print(max_a,min_a,res,extra)
        if (min_a % np.uint64(2))==0:
            #print('if')
            res = modPlus(max_a,max_a,N)
            min_a = np.uint64(min_a//np.uint64(2))
            max_a = np.uint64(res)
        else:
            #print('else')
            extra = modPlus(extra,res,N)
            res = modPlus(max_a,max_a,N)
            min_a = np.uint64(min_a - np.uint64(1))
            min_a = np.uint64(min_a//np.uint64(2))
            max_a = res
        
        l1 = len(bin(min_a)) - 3
        l2 = len(bin(max_a)) - 3
        if (l1+l2+1)<64:
            #print('inside final if')
            #print(max_a,min_a)
            result = np.uint64((min_a*max_a) % N)
            #print('inter result: ',result)
            result = modPlus(result,extra,N)
            return result
        #print(max_a,min_a,res,extra)
        #input()
        #print(res)
    result = res
    return result
    
"""Main Starts here"""
print('Constraint:: only upto 64-bit numbers are allowed')
print('Some examples::')
num = np.uint64(18446744073709551614)  #close to maximum possible value to cause overflow
a = np.uint64(num)
b = np.uint64(num)
C = np.uint64(num+np.uint64(1))

res = modPlus(a,b,C) 
print('x=',a,'y=',b,'N=',C)
print('(x+y)mod N = ',res)    


time_start = time.time()
res2 = modMult(a,b,C)
#res2 = modMult(18446744073709551614,2000000,18446744073709551615)
print('modMult done! Time elapsed: {} seconds'.format(time.time()-time_start))
print('x=',a,'y=',b,'N=',C)
print('(x.y)mod N = ',res2)  

#taking inputs from user
print('Enter x,y and N(keep hitting Enter key after each input): ')
a = np.uint64(input())
b = np.uint64(input())
C = np.uint64(input())
res = modPlus(a,b,C) 
res2 = modMult(a,b,C)
print('x=',a,'y=',b,'N=',C)
print('(x+y)mod N = ',res)    
print('(x.y)mod N = ',res2)  
