#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
char stream[1000];
void print(int *arr){
	int i;
	for(i=0;i<288;i++)
		printf("%d",arr[i]);
	printf("\n");
}
void hex_to_bin(char *st, int *keyy, int m){
	int i,j,num,a,b,c,d;
	int k = 79;
	int flag=0;
	for(i=0;i<strlen(st);i++){
		if(st[i]>='0' && st[i]<='9'){
	        num=st[i]-0x30;
	        if(num==0)  {a=0;b=0;c=0;d=0;} if(num==2)  {a=0;b=0;c=1;d=0;} if(num==4)  {a=0;b=1;c=0;d=0;} if(num==6)  {a=0;b=1;c=1;d=0;}
	        if(num==1)  {a=0;b=0;c=0;d=1;} if(num==3)  {a=0;b=0;c=1;d=1;} if(num==5)  {a=0;b=1;c=0;d=1;} if(num==7)  {a=0;b=1;c=1;d=1;}
	        if(num==8)  {a=1;b=0;c=0;d=0;} if(num==9)  {a=1;b=0;c=0;d=1;}	        
		}
	    else{
	        switch(st[i]){
	            case 'A': num=10; a=1;b=0;c=1;d=0;
						break;
	            case 'B': num=11; a=1;b=0;c=1;d=1; 
						break;
	            case 'C': num=12;  a=1;b=1;c=0;d=0;
						break;
	            case 'D': num=13;  a=1;b=1;c=0;d=1;
						break;
	            case 'E': num=14;  a=1;b=1;c=1;d=0;
						break;
	            case 'F': num=15;  a=1;b=1;c=1;d=1;
						break;
	            default: num=0;
	        }
	    }
	    //printf("%d ",num);
	    if(flag==0){ 
	    	keyy[k-7]= a; keyy[k-6]=b;keyy[k-5]= c;keyy[k-4]= d;
	    	flag=1;
	    }
	    else{
	    	keyy[k-3]= a; keyy[k-2]=b;keyy[k-1]= c;keyy[k]= d;
	    	flag=0;
	    	k= k-8;
		}
	}
	/*printf("\nPrinting keyy :: ");
	for(i=0;i<80;i++)
	{
		printf("%d",keyy[i]);
	}*/
	printf("\n");
}
void bin_to_hex(int *buff, int n){
	int i,j,k,val,num,stream_i,flag=0;
	char ch;
	//for(i=0;i<n;i++)	printf("%d",buff[i]);
	printf("\nIn HEX FORMAT\n");
	stream_i=n/4 -1;
	for(i=0;i<n;i+=4){
		val = buff[i]*8 + buff[i+1]*4 + buff[i+2]*2 + buff[i+3];
	    if(val>9)
	    {
	        switch(val)
	        {
	            case 10: ch = 'A'; break;
	            case 11: ch = 'B';break;
	            case 12: ch = 'C';break;
	            case 13: ch = 'D';break;
	            case 14: ch = 'E';break;
	            case 15: ch = 'F';break;
	            default: ch = 'z';
	        }
	    }
	    else
	    	ch = 48+val;
	    //printf("%c",ch);
	    if(flag==0){
	    	stream[stream_i-1]=ch;
	    	flag=1;
		}
		else{
			stream[stream_i]=ch;
			stream_i -= 2;
			flag=0;
		}
	}
	for(i=0;i<n/4;i++){
		printf("%c",stream[i]);
	}
	
}
int main()
{
	int s[288],iv[80]={0},key[80]={0};
	int i, j,t1,t2,t3,z[2048]={0},N,z_rev[2048];
	int buff[8];
	char str[80];
	fflush(stdin);
	printf("Enter stream length N for an input text containing all 0's\n");
	scanf("%d",&N);
	//input iv and key 
	printf("IV = 0x00000000000000000000\n");
	printf("Enter key in hex format:: 0x");
	scanf("%s",str);
	//printf("%s",str);
	hex_to_bin(str,key,80);

	//state initialization 
	//(st1; : : : ; st93) := (k1; : : : ; k80; 0; : : : ; 0)
	//(st94; : : : ; st177) : = (iv1; : : : ; iv80; 0; 0; 0; 0)
	//(st178; : : : ; st288) : = (0; : : : ; 0; 0; 1; 1; 1) :
	for (i = 0;i < 80;i++)		s[i] = key[i];
	for (i = 80;i < 93;i++)		s[i] = 0;
	for (i = 93;i < 173;i++)	s[i] = iv[i-93];
	s[173] = 0;
	s[174] = 0;
	s[175] = 0;
	s[176] = 0;
	for (i = 177;i < 285;i++)	s[i] = 0;
	s[285] = 1;
	s[286] = 1;
	s[287] = 1;
	
	//print(s);
	//testing
	//t1 = 0 ^ (0 & 1) ^ 1 ^ 1;
	//printf("%d ", t1);

	//Init phase
	for (i = 0;i < (4*288);i++) {
		t1 = (s[65] ^ (s[90] & s[91]) )^ (s[92] ^ s[170]);
		t2 = (s[161] ^ (s[174] & s[175]) )^ (s[176] ^ s[263]);
		t3 = (s[242] ^ (s[285] & s[286]) )^ (s[287] ^ s[68]) ;
		
		//printf("t1:%d t2:%d t3:%d\t",t1,t2,t3);
		
		for(j=92;j>0;j--)	
			s[j] = s[j-1];
		s[0]=t3;
		for(j=176;j>93;j--)	
			s[j] = s[j-1];
		s[93]=t1;
		for(j=287;j>177;j--)	
			s[j] = s[j-1];
		s[177]=t2;		
		
		//print(s);
		//getch();
	}
	//print(s);
	
	printf("\n\n");
	//GetBits
	for(i=0;i<N;i++){
		t1 = s[65] ^ s[92];
		t2 = s[161] ^ s[176];
		t3 = s[242] ^ s[287];
		
		z[i] = ((t1 ^ t2 ) ^ t3);
		printf("%d",z[i]);
		
		t1 = (t1 ^ (s[90] & s[91]) )^ s[170];
		t2 = (t2 ^ (s[174] & s[175]) )^ s[263];
		t3 = (t3 ^ (s[285] & s[286]) )^ s[68];
		
		for(j=92;j>0;j--)	s[j] = s[j-1];
		s[0]=t3;
		for(j=176;j>93;j--)	s[j] = s[j-1];
		s[93]=t1;
		for(j=287;j>177;j--)	s[j] = s[j-1];
		s[177]=t2;
	}
	printf("\n");
	j=0;
	for(i=N-1;i>=0;i--){
		z_rev[j]=z[i];
		//printf("%d",z_rev[j]);
		j++;
	}
	//binary to hex
	printf("%d-bit stream\n",N);
	bin_to_hex(z_rev,N);
	
	return 0;
}
