import math
import numpy as np
import random
import matplotlib.pyplot as plt

def crypt_xor(cipher,plain,size):
    for i in range(size):
        cipher[i] = plain[i]^cipher[i]
    return cipher
def input_white():
    for i in range(size):
        cipher[i] = plain[i]^key[i]
def output_white():
    for i in range(size):
        cipher[i] = cipher[i]^key[i]
def addRoundKey():
    for i in range(size):
        cipher[i] = cipher[i]^key[i]
def bin_to_hex(dec):
    char_set = ['0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'] 
    return char_set[dec]
def print_cipher(cipher):
    j = 0
    cipher_set = ['0']*n
    for i in range(n,0,-1):
        dec = cipher[i*4-1] * 8 + cipher[i*4-2] * 4 + cipher[i*4-3] * 2 + cipher[i*4-4] * 1 
        cipher_set[j] = bin_to_hex(dec)
        j = j+1
    print(cipher_set)
def sBoxLayer():
    j=0
    for i in range(n):
        num = cipher[j]*1 + cipher[j+1]*2 + cipher[j+2]*4 + cipher[j+3]*8        
        b = dec_to_hex[sBox[num]]
        cipher[j] = b[3]
        cipher[j+1] = b[2]
        cipher[j+2] = b[1]
        cipher[j+3] = b[0]
        j = j+4
def pLayer():
    #cipher =[i for i in range(size)]
    copy = [0]*size 
    for i in range(size):
        if i==(size-1):
            pos = size-1
        else:
            pos = (n*i) % (size-1)
        copy[pos] = cipher[i]
    cipher[0:size] = copy[0:size]
def updateKey(round_i):
    #round_i=2
    #master_key =[0 for i in range(80)]
    for i in range(61):      
        last = master_key[79];           
        for j in range(79):    
            master_key[79-j] = master_key[79-j-1]                
        master_key[0] = last
    #print(np.array(master_key))
    num = master_key[76]*1 + master_key[77]*2 + master_key[78]*4 + master_key[79]*8        
    b = dec_to_hex[sBox[num]] 
    master_key[76] = b[3] 
    master_key[77] = b[2]
    master_key[78] = b[1]
    master_key[79] = b[0]
    
    dec = master_key[15]*1 + master_key[16]*2 + master_key[17]*4 + master_key[18]*8 + master_key[19]*16
    dec1 = bin(dec^round_i)
    #making all 15,16,17,18 & 19 zero beforehand to make xored with round number
    master_key[15] =master_key[16] =master_key[17] =master_key[18] =master_key[19]=0
    for i in range(len(dec1)-2):
        master_key[15+i] = int(dec1[len(dec1)-1-i])
    #key = [0]*8
    #setKey()        
def setKey():
    p_key = [0]*64
    for i in range(64):
        p_key[63-i] = master_key[79-i]
    for i in range(size):
        key[i] = p_key[i]
def random_plain(size):
    pt = [0]*size
    ra = random.randint(0,int(math.pow(2,size))-1)
    b = bin(ra)
    for i in range(len(b)-2):
        pt[i] = int(b[len(b)-1-i])
    return pt
def sBoxLayer_inv():
    j=0
    for i in range(n):
        num = cipher[j]*1 + cipher[j+1]*2 + cipher[j+2]*4 + cipher[j+3]*8        
        for k in range(16):
            if sBox[k] == num:
                val = k
                break
        b = dec_to_hex[val]
        cipher[j] = b[3]
        cipher[j+1] = b[2]
        cipher[j+2] = b[1]
        cipher[j+3] = b[0]
        j = j+4
def pLayer_inv():
    #cipher =[i for i in range(size)]
    copy = [0]*size 
    for i in range(size):
        if i==(size-1):
            pos = size-1
        else:
            pos = (n*i) % (size-1)
        copy[i] = cipher[pos]
    cipher[0:size] = copy[0:size]
 
def generate_round_key(round_num):
    for i in range(1,round_num+1):
        updateKey(i)


"""main starts here"""
r = 10  #number of rounds
n = input("Enter n: ") #
n = int(n)
size =n*4
plain = [0]*size #plaintext
cipher = [0]*size #ciphertext
key = [0]*size    #round key
master_key = [0]*80 
sBox = [0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x02]
dec_to_hex = [[0,0,0,0],[0,0,0,1],[0,0,1,0],[0,0,1,1],[0,1,0,0],[0,1,0,1],[0,1,1,0],[0,1,1,1],[1,0,0,0],[1,0,0,1],[1,0,1,0],[1,0,1,1],[1,1,0,0],[1,1,0,1],[1,1,1,0],[1,1,1,1]]

"""step-1"""
input_white()
print_cipher(cipher)

"""starting rounds"""
for i in range(1,r+1):
    sBoxLayer()
    pLayer()
    updateKey(i)
    setKey()
    addRoundKey()
    print_cipher(cipher)
print('Encrypted text')
print_cipher(cipher)
"""last round"""
print('Decryption starts here----------')

for i in range(r,0,-1):
    key = [0]*size
    master_key = [0]*80
    generate_round_key(i)
    setKey()
    #print_cipher(key)
    addRoundKey()
    pLayer_inv()
    sBoxLayer_inv()
    #print_cipher(cipher)
key = [0]*size   
addRoundKey()    
print('Deceypted text')
print_cipher(cipher)


"""Testing done"""

"""3(b) Linear Cryptanalysis"""
print('Linear Cryptanalysis for number of rounds = 10')
#i
n = 2
size =n*4
plain = [0]*size
cipher = [0]*size
key = [0]*size
master_key = [0]*80

"""3(b)"""
#ii N = 10 and rounds = 10
N=10
S = 100*N
count =0
count_store = [0]*int(math.pow(2,size))
rounds = 10
for k in range(S):
    print('round: ',k)
    in_mask = random_plain(size)
    out_mask = random_plain(size)
    for i in range(N):    
        pl = random_plain(size)
        mask_pl = np.bitwise_and(in_mask,pl)
        #pl = [0]*size
        #print('plaintext:') 
        #print_cipher(pl)
        
        plain = pl
        cipher = [0]*size
        key = [0]*size
        master_key = [0]*80
        #ci = encrypt(rounds-1,size,pl)
        input_white()
        #print_cipher()    
        """starting rounds"""
        for j in range(1,10):  #generating upto 9 rounds
            sBoxLayer()
            pLayer()
            updateKey(j)
            setKey()
            addRoundKey()
            #print_cipher()
       # print_cipher(cipher)
        addRoundKey() #to un-xor the last xor 
        mask_ci = np.bitwise_and(out_mask,cipher)
    #    val1,val2 = 0,0
    #    for j in range(size):
    #        val1 = mask_ci[j] ^ val1 
    #        val1 = 0
    #    for j in range(size):
    #        val2 = mask_pl[j] ^ val2
        abc = np.bitwise_xor(mask_pl,mask_ci)
        abc_dec = abc[0]*1+abc[1]*2+abc[2]*4+abc[3]*8+abc[4]*16+abc[5]*32+abc[6]*64+abc[7]*128
        """for j in range(size):
            if abc[j] ==0:
                j=-1
                break;"""
        #print(abc_dec)
        count_store[abc_dec] = count_store[abc_dec] + 1 
print(count_store)
dist = np.divide(count_store,S)
print('Mean of calculated distribution',np.mean(dist))
print('Actual Mean',N/int(math.pow(2,size)))
xx = [i for i in range(N)]
yy = dist[0:N]
plt.plot(xx,yy)
plt.xlabel('N')
plt.ylabel('count_i/S')
plt.title('Linear Cryptanalysis N=10')
plt.show()

"""3(b) end"""

"""3(c) Differential Cryptanalysis"""
#selecting delX and delY
N=20;print('Differential Cryptanalysis for number of rounds',N)
S = 100*N
count =0
count_store = [0]*int(math.pow(2,size))
rounds = 10
for k in range(S):
    print('round: ',k)
    x1 = random_plain(size)
    x2 = random_plain(size)
    del_x = np.bitwise_xor(x1,x2)
    for m in [x1,x2]:
        plain = m
        cipher = [0]*size
        key = [0]*size
        master_key = [0]*80            
        input_white()   
        """starting rounds"""
        for j in range(1,10):  #generating upto 9 rounds
            sBoxLayer()
            pLayer()
            updateKey(j)
            setKey()
            addRoundKey()   
        addRoundKey() #to un-xor the last xor 
        if m==x1:
            y1=cipher
        else:
            y2=cipher
    del_y = np.bitwise_xor(y1,y2)
    for i in range(N):    
        p1 = random_plain(size)
        p2 = np.bitwise_xor(p1,del_x)

        for mm in range(2):
            if mm==1: 
                plain = p1
            else:
                plain = p2
            cipher = [0]*size
            key = [0]*size
            master_key = [0]*80            
            input_white()   
            """starting rounds"""
            for j in range(1,10):  #generating upto 9 rounds
                sBoxLayer()
                pLayer()
                updateKey(j)
                setKey()
                addRoundKey()   
            addRoundKey() #to un-xor the last xor 
            if mm==1:
                c1=cipher
            else:
                c2=cipher
        del_c = np.bitwise_xor(c1,c2)
        abc = np.bitwise_and(del_c,del_y)
        abc_dec = abc[0]*1+abc[1]*2+abc[2]*4+abc[3]*8+abc[4]*16+abc[5]*32+abc[6]*64+abc[7]*128
        if abc_dec ==0:
            del_y_val = del_y[0]*1+del_y[1]*2+del_y[2]*4+del_y[3]*8+del_y[4]*16+del_y[5]*32+del_y[6]*64+del_y[7]*128
            count_store[del_y_val] = count_store[del_y_val] + 1 
print(count_store)
dist = np.divide(count_store,S)
print('Mean of calculated distribution',np.mean(dist[0:N]))
print('Actual Mean',N/int(math.pow(2,size)))
xx = [i for i in range(N)]
yy = dist[0:N]
plt.plot(xx,yy)
plt.xlabel('N')
plt.ylabel('count_i/S')
plt.title('Differential Cryptanalysis N=20') #change N as taken by user
plt.show()
"""3(c) end"""
