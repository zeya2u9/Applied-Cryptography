# -*- coding: utf-8 -*-
"""
Created on Wed Dec  9 18:44:22 2020
@author: zeyau
Write programs to implement the following for 64-bit numbers.
a. Euclidean algorithm 
b. Extended euclidean algorithm 
c. Multiplicative inverse algorithm 
d. Square and Multiply algorithm
"""
import math
import time
import numpy as np
"""modPlus - to calculate (x+y)mod N"""
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

"""modMult - to calculate (x*y)mod N"""
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

"""Euclidean Algorithm - finding gcd of two given numbers"""
def euclideanAlgo(x,y):
    gcd =1 #initializing gcd
    r = 1  #initializing variable remainder as r
    if(x>y):
        a,b = x,y  #fixing a as the bigger value
    else:
        b,a = x,y
    print(a,b)
    while(1):#keep diving a by b until the remainder is zero
        r = a%b   #taking remainder in r
        if r==0:  #checking if further division is needed
            gcd = b
            break
        a = b  #keep updating a by b and b by the remainder r
        b = r    
    return gcd

"""Extended Euclidean Algorithm for finding the inverse of a number mod N"""
""" Input: Integers a, b with a ≥ b > 0
    Output: (d,X, Y ) with d = gcd(a, b) and Xa + Y b = d"""
def extEuclideanAlgo(x,y):
    s,old_s = 0,1
    t,old_t = 1,0
    r,old_r = y,x
    
    while r!=0:
        q = old_r//r
        old_r, r = r, (old_r - q * r)
        old_s, s = s, (old_s - q * s)
        old_t, t = t, (old_t - q * t) 
    #print("quotients by the gcd:", t, s)
    
    return old_r,old_s,old_t

"""Multiplicative inverse algorithm """
def multInverse(x,n):
    gcd = euclideanAlgo(x,n)  
    if gcd!=1:  #checking if x and n are coprime to each other
        print('Inverse does not exist')
        return 0
    a1, xx, yy = extEuclideanAlgo(x,n) #to get the coefficients
    #inverse = (xx+n)%n
    inverse = modPlus(xx,n,n) #ax = 1 mod n
    return inverse

"""Square and Multiply algorithm"""
def squAndmult(a,p,N):
    print(a,p,N)
    bin_p = bin(p) #converting into binary
    l = len(bin_p)
    b = np.uint64(1)
    for i in range(2,l): #iterating upto the total bits of converted binary number
        #input();print(bin_p[i])
        b = modMult(b,b,N) #with each increasing bit power of 2 is also increasing so b will be doubled
        if bin_p[i]=='1':  
            b = modMult(b,a,N)  
        #print(b)
    return b
    
"""////////////////////Function calls start from here/////////////////"""
print('Constraint:: only upto 64-bit numbers are allowed')
print('Some examples::')
num = np.uint64(18446744073709551614)  #maximum possible value to cause overflow
x1 = np.uint64(num)
x2 = np.uint64(num//np.uint64(2))
C = np.uint64(num+np.uint64(1))

#a Euclidean Algorithm
call = euclideanAlgo(x1,x2)
print('x=',x1,'y=',x2)
print('GCD(x,y) = ',call)

#b Extended Euclidean Algorithm
#coefficients might be negative integers, that is the reason to take np.int64()
x1 = np.int64(1432)
x2 = np.int64(123211)
call2, b1, b2 = extEuclideanAlgo(x1,x2)
print('x=',x1,'y=',x2)
print('GCD(x,y) = ',call2)
print("Bézout coefficients:", b1, b2)

#c Multiplicative Inverse using Extended Euclidean ALgorithm  xa = 1 mod n, here a is the final naswer
x1 = np.int64(15)
x3 = np.int64(26)
call3 = multInverse(x1,x3)
print('x=',x1,'n=',x3)
print('Multiplicative Inverse( 0 - indicates Inverse does not exist) = ',call3)
    
#d Square and Multiply method  a^p mod N
x1 = np.uint64(670000)
x2 = np.uint64(9)
x3 = np.uint64(68000)
call4 = squAndmult(x1,x2,x3)
print('\n')
print('a=',x1,'p=',x2,'N',x3)
print('a^p mod N = ',call4)

#taking inputs from user
print('Enter x,y and N(keep hitting Enter key after each input):')
x1 = np.uint64(input())
x2 = np.uint64(input())
x3 = np.uint64(input())

call = euclideanAlgo(x1,x2)
call2, b1, b2 = extEuclideanAlgo(x1,x2)
call3 = multInverse(x1,x3)
call4 = squAndmult(x1,x2,x3)
print('\n x=',x1,'y=',x2,'N=',x3)
print('GCD(x,y) using Euclidean algorithm = ',call)
print('GCD(x,y) using Extended Euclidean algorithm= ',call2)
print('Bézout coefficients:', b1, b2)
print('Multiplicative Inverse(x,N)( 0 - indicates Inverse does not exist) = ',call3)
print('x^y mod N = ',call4)
