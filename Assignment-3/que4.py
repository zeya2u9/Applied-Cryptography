# -*- coding: utf-8 -*-
"""
Implement the Solovay-Strassen and the Miller-Rabin algorithm for primality testing.
Choose a such that 1 < a < n-1
n = 64-bit
2^64 = 1,84,46,74,40,73,70,95,51,616
Max possible value - (2^64 -1) = 1,84,46,74,40,73,70,95,51,615
"""
import math
import time
import random as rm
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
    #print('x=',x,'y=',y,'N=',N)
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
    
"""Square and multiply"""
def squAndmult(a,p,N):
    #print(a,p,N)
    bin_p = bin(p)
    l = len(bin_p)
    b = np.uint64(1)
    for i in range(2,l):
        b = modMult(b,b,N)
        if bin_p[i]=='1':
            b = modMult(b,a,N)  
        #print(b)
    return b

"""jacobi"""
def jacFunc(n, k):
    if (np.uint64(k) <= np.uint64(0)) or (np.uint64(k)%np.uint64(2) == np.uint64(0)):
        print('N is invalid. Output = -2 indicates invalid output')
        return -2
    k = np.uint64(k)
    n = np.uint64(n)
    n = n % k
    t = 1
    while n != np.uint64(0) :
        while n % np.uint64(2) == np.uint64(0):
            n = np.uint64(n // np.uint64(2))
            r = np.uint64(k % np.uint64(8))
            if r == np.uint64(3) or r == np.uint64(5):
                t = -t
        n, k = k, n
        if n % np.uint64(4) == np.uint64(3) and k % np.uint64(4) == np.uint64(3):
            t = -t
        n = n % k
    if k == np.uint64(1):
        return t
    else:
        return 0

"""Solovay Strassen method for primality Testing"""
def solStr(n):
    n_1 = np.uint64(n-np.uint64(1))
    #print('Choose a such that 1 <= a <=',n_1 )
    #a = np.uint64(input())
    a = np.uint64(rm.randint(1,n_1))
    x = jacFunc(a,n)
    if x==0:
        return 1
    pw = np.uint64(n_1/np.uint64(2))
    y = squAndmult(a,pw,n)
    if (x%n)==(y%n):
        return 0
    else:
        return 1
    
"""Miller Rabin method for primality Testing"""
def millRab(n):
    n_1 = np.uint64(n-np.uint64(1))
    #print('Choose a such that 1 <= a <=',n_1 )
    #a = np.uint64(input())
    a = np.uint64(rm.randint(1,n_1))
    #converting n to n-1=2^k * m
    k=0
    while n_1%np.uint64(2)==np.uint64(0):
        n_1 = np.uint64(n_1//np.uint64(2))
        k = k+1
    m = np.uint64(n_1)
    b = squAndmult(a,m,n)  
    if b%n == np.uint64(1):
        return 0
    nn = np.uint64(n-np.uint64(1))
    for i in range(k):
        if b==nn:
            return 0
        else:
            b = squAndmult(b,np.uint64(2),n) 
    return 1

"""Main starts here"""
print('Constraint:: only upto 64-bit numbers are allowed')

print('Solovay strassen Method')
print('Choose n')
n = np.uint64(input())
if n%np.uint64(2)==0:
    print('Not prime')
else:
    out = solStr(n)    
    if out==1:
        print(n,'is Composite')
    else:
        print(n,'is Prime')
    
"""Miller rabin method"""
print('Miller rabin method')
print('Choose n')
n = np.uint64(input())
if n%np.uint64(2)==0:
    print('Not prime')
else:
    out = millRab(n)    
    if out==1:
        print(n,'is Composite')
    else:
        print(n,'is Prime')   
