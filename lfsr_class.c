
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print(int *a,int n){
	int i;
	for (i = 0;i < n;i++) {
		printf("%d", a[i]);
	}
	printf("\t");
}

int main()
{
	int arr[32] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int out_bit, in_bit;  //array initialised as all 1's
	//int arr[4] = {1,1,1,1};    //testing
	int x = 1,i,j,n=32,bitss;

	printf("---------Linear Feedback Shift Register----------\n Given polynomial p(X) = X^{32} + X^{22} + X^{2} + X^{1} +  1 for 32-bit LFSR\n it will repeat after ((2^32) - 1)=4294967295 states.\n");
	
	printf("\nEnter number of states to be produced:: ");
	scanf("%d",&bitss);
	
	//printf("x xor 1 = %d\n", (x ^ 1)^1); //testing
	//printf("x xor 0 = %d\n", x ^ 0); //testing
	printf("\nInitial state is starting from all 1's  :: ");
	print(arr,n);
	printf("\n");
	printf("\nPrinting all 32-bits at a time");
	for (i = 0;i < 32*bitss;i++) {
		//printf("Iteration Number = %d\t",i);
		if(i%32 == 0) printf("\nState number- %d :: ",i/32);
		in_bit = (((arr[0] ^ arr[1]) ^ arr[2]) ^ arr[22]);
		//in_bit = (arr[3] ^ arr[2]);
		//printf("In_bit = %d\t",in_bit);

		//shifting process
		out_bit = arr[0];
		for (j = 0;j < n-1;j++) {
			arr[j] = arr[j + 1];
		}
		arr[n-1] = in_bit;

		//print(arr,n);
		printf("%d ", out_bit);
		

	}
	return 0;
}


