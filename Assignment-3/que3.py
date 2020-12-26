"""Write a program that computes the Jacobi symbol (a/N)."""
import math
import time
import numpy as np
def jacFunc(n, k):
    #checking if N (k here) is odd or not and is greater than 0
    if (np.uint64(k) <= np.uint64(0)) or (np.uint64(k)%np.uint64(2) == np.uint64(0)):
        print('N is invalid')
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

"""main starts here"""
print('Constraint:: only upto 64-bit numbers are allowed')
print('Enter a of (a/N):')
num=input()
a = np.uint64(num)

print('Enter N of (a/N):')
num=input()
N = np.uint64(num)

j_s = jacFunc(a,N)
print('Jacobi symbol of (',a,'/',N,') [output as -2 is showing N is invalid]::',j_s)
