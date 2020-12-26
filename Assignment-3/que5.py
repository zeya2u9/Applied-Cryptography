# -*- coding: utf-8 -*-
"""
Implement the plain RSA encryption scheme.
n = 64-bit
2^64 = 1,84,46,74,40,73,70,95,51,616
Max possible value - (2^64 -1) = 1,84,46,74,40,73,70,95,51,615
"""
import math
import time
import random as rm
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
    gcd =1
    r = 1
    if(x>y):
        a,b = x,y
    else:
        b,a = x,y
    #print(a,b)
    while(1):
        r = a%b
        if r==0:
            gcd = b
            break
        a = b
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


def multInverse(x,n):
    gcd = euclideanAlgo(x,n)
    if gcd!=1:
        print('Inverse does not exist')
        return 0
    a1, xx, yy = extEuclideanAlgo(x,n)
    #inverse = (xx+n)%n
    inverse = modPlus(xx,n,n)
    return inverse

def squAndmult(a,p,N):
    #print(a,p,N)
    bin_p = bin(p)
    l = len(bin_p)
    b = np.uint64(1)
    for i in range(2,l):
        b = modMult(b,b,N)
        if bin_p[i]=='1':
            b = modMult(b,a,N)  #to be replaced by modMult() function
        #print(b)
    return b

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

"""RSA - generating public private keys"""
def rsaGen():
    print('RSA GENERATION PROCESS:: public private key pairs \n')
    num = np.uint64(pow(2,16))
    #Randomly Choosing two primes p and q
    print('Choosing p randomly')
    while 1:
        p=np.uint64(rm.randint(1,num))
        val = millRab(p)
        if val ==0:
            print('First prime p: ',p)
            break    
    print('Choosing q randomly')
    while 1:
        q=np.uint64(rm.randint(1,num))
        val = millRab(q)
        if val ==0:
            print('Second prime q: ',q)
            break
    n = p*q
    phi_n = np.uint64((p-np.uint64(1))*(q-np.uint64(1)))
    print('phi_n: ',phi_n)
    """randomly choosing e s.t. GCD(e,phi_n)=1"""
    num = np.uint64(pow(2,32))
    while 1:
        e = np.uint64(rm.randint(1,num))
        val = euclideanAlgo(e,phi_n)
        if val ==1:
            print('Value of e: ',e)
            break
    """finding d=e^-1 mod phi_n"""
    d = multInverse(e,phi_n)   
    return (p,q,n,e,d)

"""RSA - Encryption"""
def rsaEnc(m,e,n):
    return squAndmult(m,e,n)

"""RSA - Decryption"""
def rsaDec(c,d,n):
    return squAndmult(c,d,n)

"""///////////////////////////////////////////////////////////////////////"""
"""main starts here"""
"""Generating public, private key using rsaGen"""
print('Constraint:: only upto 64-bit numbers are allowed')

(P,Q,N,E,D) = rsaGen()
print('Public key pair(n.e):',N,E)
print('Private key pair(p,q,d):',P,Q,D)

"""Encrypting message"""
print('Choose n - the max limit for taking messages   0<= m <= n-1')
n=np.uint64(input())

print('How many messages you want to encrypt and decrypt?')
count = np.uint64(input())
for i in range(count):
    print('M',i)
    print('Choose message m:[an integer between',0,'and',np.uint64(n-np.uint64(1)), ']')
    m = np.uint64(input())
    if m>=n: 
        print('Invalid message')
    else:
        enc = rsaEnc(m,E,N)
        print('Encrpyted message: ',enc)
        print('Now decrypting it')
        dec = rsaDec(enc,D,N)
        print('Decrpyted message: ',dec)
