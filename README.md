# Applied-Cryptography
Homework, Quizzez and Assignments

Assignment-1
1.	Implement a 32-bit LFSR. Use 
p(X) = X^{32} + X^{22} + X^{2} + X^{1} +  1
as the corresponding connecting polynomial.           
Sol: 1.LFSR
Input:: Number of states to be produced
Polynomial is already given.
Output:: printing all 32 bits of a state
Code:  initial array has been taken as all 1’s
                            	
2.	Implement TRIVIUM. Use the test vectors given here.    
Sol: Input:: Stream length for an input containing all 0’s
Key:: take from user in hex format
IV :: all 0’s
Output:: Code will print the encrypted text(stream) in hex format which can be verified from below test vectors for Trivium
https://github.com/cantora/avr-crypto-lib/blob/master/testvectors/trivium-80.80.test-vectors
                               
3.	Implement RC4. Your program should work for any l-byte key, where 10 <= l <= 40. Use your implementation to verify Mantin's second output byte bias.
Sol: Input:: all 0’s
Key:: take from user in hex format(for any byte length)
Output:: Code will print the encrypted text in hex format which can be verified from below test vectors for RC4 provided by IETF
https://tools.ietf.org/html/rfc6229


Assignment-2
1. Twofish - my_two.c

2. AES  - AES.c

3. small scale variant of the SPN Present from - Small Scale Variants Of The Block Cipher-PRESENT.pdf

  (a) Implementation - smallPresent.py
  
  (b) Linear cryptanalysis 
  
  (c) Differential Cryptanalysis
