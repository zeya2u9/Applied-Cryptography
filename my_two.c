/****
The code is not true representation of twofish as in theory. Because round keys have been generated randomly and mds function is not complete.

All functions except round keys and mds(i.e., sBox, PHT, right/left rotation of subparts of intermediate ciphertexts) have been coded properly. 
****/
#include<stdio.h>
#include<conio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define print(a) printf("%d ",a);
char stream[1000];
int row=0,col=0,key[4][4]={0},plain[4][4]={0},key_copy[4][4]={0},s0[4]={0},s1[4]={0};
int r0[4] ={0},r1[4] ={0},r2[4] ={0},r3[4] ={0},r0_copy[4]={0},r1_copy[4]={0},k11[4],k22[4];
static const uint8_t p_0[256] = {  // p0
          0xA9,  0x67,  0xB3,  0xE8,
          0x04,  0xFD,  0xA3,  0x76,
          0x9A,  0x92,  0x80,  0x78,
          0xE4,  0xDD,  0xD1,  0x38,
          0x0D,  0xC6,  0x35,  0x98,
          0x18,  0xF7,  0xEC,  0x6C,
          0x43,  0x75,  0x37,  0x26,
          0xFA,  0x13,  0x94,  0x48,
          0xF2,  0xD0,  0x8B,  0x30,
          0x84,  0x54,  0xDF,  0x23,
          0x19,  0x5B,  0x3D,  0x59,
          0xF3,  0xAE,  0xA2,  0x82,
          0x63,  0x01,  0x83,  0x2E,
          0xD9,  0x51,  0x9B,  0x7C,
          0xA6,  0xEB,  0xA5,  0xBE,
          0x16,  0x0C,  0xE3,  0x61,
          0xC0,  0x8C,  0x3A,  0xF5,
          0x73,  0x2C,  0x25,  0x0B,
          0xBB,  0x4E,  0x89,  0x6B,
          0x53,  0x6A,  0xB4,  0xF1,
          0xE1,  0xE6,  0xBD,  0x45,
          0xE2,  0xF4,  0xB6,  0x66,
          0xCC,  0x95,  0x03,  0x56,
          0xD4,  0x1C,  0x1E,  0xD7,
          0xFB,  0xC3,  0x8E,  0xB5,
          0xE9,  0xCF,  0xBF,  0xBA,
          0xEA,  0x77,  0x39,  0xAF,
          0x33,  0xC9,  0x62,  0x71,
          0x81,  0x79,  0x09,  0xAD,
          0x24,  0xCD,  0xF9,  0xD8,
          0xE5,  0xC5,  0xB9,  0x4D,
          0x44,  0x08,  0x86,  0xE7,
          0xA1,  0x1D,  0xAA,  0xED,
          0x06,  0x70,  0xB2,  0xD2,
          0x41,  0x7B,  0xA0,  0x11,
          0x31,  0xC2,  0x27,  0x90,
          0x20,  0xF6,  0x60,  0xFF,
          0x96,  0x5C,  0xB1,  0xAB,
          0x9E,  0x9C,  0x52,  0x1B,
          0x5F,  0x93,  0x0A,  0xEF,
          0x91,  0x85,  0x49,  0xEE,
          0x2D,  0x4F,  0x8F,  0x3B,
          0x47,  0x87,  0x6D,  0x46,
          0xD6,  0x3E,  0x69,  0x64,
          0x2A,  0xCE,  0xCB,  0x2F,
          0xFC,  0x97,  0x05,  0x7A,
          0xAC,  0x7F,  0xD5,  0x1A,
          0x4B,  0x0E,  0xA7,  0x5A,
          0x28,  0x14,  0x3F,  0x29,
          0x88,  0x3C,  0x4C,  0x02,
          0xB8,  0xDA,  0xB0,  0x17,
          0x55,  0x1F,  0x8A,  0x7D,
          0x57,  0xC7,  0x8D,  0x74,
          0xB7,  0xC4,  0x9F,  0x72,
          0x7E,  0x15,  0x22,  0x12,
          0x58,  0x07,  0x99,  0x34,
          0x6E,  0x50,  0xDE,  0x68,
          0x65,  0xBC,  0xDB,  0xF8,
          0xC8,  0xA8,  0x2B,  0x40,
          0xDC,  0xFE,  0x32,  0xA4,
          0xCA,  0x10,  0x21,  0xF0,
          0xD3,  0x5D,  0x0F,  0x00,
          0x6F,  0x9D,  0x36,  0x42,
          0x4A,  0x5E,  0xC1,  0xE0};
static const uint8_t p_1[256] = {  // p1
          0x75,  0xF3,  0xC6,  0xF4,
          0xDB,  0x7B,  0xFB,  0xC8,
          0x4A,  0xD3,  0xE6,  0x6B,
          0x45,  0x7D,  0xE8,  0x4B,
          0xD6,  0x32,  0xD8,  0xFD,
          0x37,  0x71,  0xF1,  0xE1,
          0x30,  0x0F,  0xF8,  0x1B,
          0x87,  0xFA,  0x06,  0x3F,
          0x5E,  0xBA,  0xAE,  0x5B,
          0x8A,  0x00,  0xBC,  0x9D,
          0x6D,  0xC1,  0xB1,  0x0E,
          0x80,  0x5D,  0xD2,  0xD5,
          0xA0,  0x84,  0x07,  0x14,
          0xB5,  0x90,  0x2C,  0xA3,
          0xB2,  0x73,  0x4C,  0x54,
          0x92,  0x74,  0x36,  0x51,
          0x38,  0xB0,  0xBD,  0x5A,
          0xFC,  0x60,  0x62,  0x96,
          0x6C,  0x42,  0xF7,  0x10,
          0x7C,  0x28,  0x27,  0x8C,
          0x13,  0x95,  0x9C,  0xC7,
          0x24,  0x46,  0x3B,  0x70,
          0xCA,  0xE3,  0x85,  0xCB,
          0x11,  0xD0,  0x93,  0xB8,
          0xA6,  0x83,  0x20,  0xFF,
          0x9F,  0x77,  0xC3,  0xCC,
          0x03,  0x6F,  0x08,  0xBF,
          0x40,  0xE7,  0x2B,  0xE2,
          0x79,  0x0C,  0xAA,  0x82,
          0x41,  0x3A,  0xEA,  0xB9,
          0xE4,  0x9A,  0xA4,  0x97,
          0x7E,  0xDA,  0x7A,  0x17,
          0x66,  0x94,  0xA1,  0x1D,
          0x3D,  0xF0,  0xDE,  0xB3,
          0x0B,  0x72,  0xA7,  0x1C,
          0xEF,  0xD1,  0x53,  0x3E,
          0x8F,  0x33,  0x26,  0x5F,
          0xEC,  0x76,  0x2A,  0x49,
          0x81,  0x88,  0xEE,  0x21,
          0xC4,  0x1A,  0xEB,  0xD9,
          0xC5,  0x39,  0x99,  0xCD,
          0xAD,  0x31,  0x8B,  0x01,
          0x18,  0x23,  0xDD,  0x1F,
          0x4E,  0x2D,  0xF9,  0x48,
          0x4F,  0xF2,  0x65,  0x8E,
          0x78,  0x5C,  0x58,  0x19,
          0x8D,  0xE5,  0x98,  0x57,
          0x67,  0x7F,  0x05,  0x64,
          0xAF,  0x63,  0xB6,  0xFE,
          0xF5,  0xB7,  0x3C,  0xA5,
          0xCE,  0xE9,  0x68,  0x44,
          0xE0,  0x4D,  0x43,  0x69,
          0x29,  0x2E,  0xAC,  0x15,
          0x59,  0xA8,  0x0A,  0x9E,
          0x6E,  0x47,  0xDF,  0x34,
          0x35,  0x6A,  0xCF,  0xDC,
          0x22,  0xC9,  0xC0,  0x9B,
          0x89,  0xD4,  0xED,  0xAB,
          0x12,  0xA2,  0x0D,  0x52,
          0xBB,  0x02,  0x2F,  0xA9,
          0xD7,  0x61,  0x1E,  0xB4,
          0x50,  0x04,  0xF6,  0xC2,
          0x16,  0x25,  0x86,  0x56,
          0x55,  0x09,  0xBE,  0x91};
static const int mds[4][4] = {{0x1,0xef,0x5b,0x5b},{0x5b,0xef,0xef,0x1},{0xef,0x5b,0x1,0xef},{0xef,0x1,0xef,0x5b}};

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
	printf("\nPrinting keyy :: ");
	for(i=0;i<32;i++)
	{
		printf("%d",keyy[i]);
	}
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
void set_row_col(int num){  
	char map[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	int quotient = num,i;
	char hex[2]={'0','0'};
	int j = 0,r=0;
    while (quotient != 0)
    {
        r = quotient % 16;
        if (r < 10)
            hex[j++] = 48 + r;
        else
            hex[j++] = 55 + r;
        quotient = quotient / 16;
    }
    //printf("\n%c %c\n",hex[1],hex[0]);
    for(i=0;i<16;i++){
    	if(hex[0]==map[i]){ col = i; break; }
	}
	for(i=0;i<16;i++){
    	if(hex[1]==map[i]){ row = i; break; }
	}
    //printf("row = %d\n",row);
    //printf("column = %d\n",col);
}
void print_key(){
	int i,j;
	printf("\n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			printf("%d ",key[i][j]);
		printf("\n");
	}
}
void print_plain(){
	int i,j;
	printf("\n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			printf("%d ",plain[i][j]);
		printf("\n");
	}
}
void set_Rs(){
	int i;
	for(i=0;i<4;i++)	{ r0[i] = plain[i][0]; r0_copy[i] = plain[i][0];}
	for(i=0;i<4;i++)	{ r1[i] = plain[i][1]; r1_copy[i] = plain[i][1];}
	for(i=0;i<4;i++)	r2[i] = plain[i][2];
	for(i=0;i<4;i++)	r3[i] = plain[i][3];
}
void print_r(int a[]){
	int i;
	for(i=0;i<4;i++) printf("%d ",a[i]);
	printf("\n");
}
void rotate_right(int *r){
	int i,j,lsb[4]={0};
	for(i=0;i<4;i++)	lsb[i] = r[i] & 1;
	for(i=3;i>0;i--){
		r[i] = r[i] >> 1;
		if(lsb[i-1]==1) r[i] += 128;
	}
	r[0] = r[0] >> 1;
	if(lsb[3]==1) r[0] += 128;
}
void rotate_left(int *r,int rot){
	int i,j,msb[4]={0};
	for(j=0;j<rot;j++){
		for(i=0;i<4;i++)	msb[i] = (r[i]>>7) & 1;
		for(i=0;i<3;i++){
			r[i] = (r[i] << 1)&255;
			if(msb[i+1]==1) r[i] += 1;
		}
		r[3] = (r[3] << 1)&255;
		if(msb[0]==1) r[3] += 1;
	}
}
void swap(int a[],int b[],int c[],int d[]){
	int i,j;
	for(i=0;i<4;i++){
		r0[i] = c[i];
		r1[i] = d[i];
		r2[i] = a[i];
		r3[i] = b[i];
	}
}
void generate_skey(){
	int i,j,temp1[4]={0},temp2[4]={0};
	//take first two columns to produce S0
	for(i=0;i<4;i++){
		s0[i] = rand()%256;
		s1[i] = rand()%256;
	}	
}
void generate_rkey(){
	int i,j;
	//take first two columns to produce S0
	for(i=0;i<4;i++){
		k11[i] = rand()%256;
		k22[i] = rand()%256;
	}	
}
int main()
{
	//int k[16]={'T','E','A','M','S','C','O','R','P','I','A','N','1','2','3','4'};
	int k[16]={'T','h','a','t','s',' ','m','y',' ','K','u','n','g',' ','F','u'};
	int p[16]={'T','w','o',' ','O','n','e',' ','N','i','n','e',' ','T','w','o'};
	int c[16],temp_r[4]={0};
	char str[16];
	int i,j,kk,value=0,ro,temp,mult,sum,num;
	double val1,val2,val_0,val_1;
	fflush(stdin);
	//printf("Enter key in hex format:: 0x");
	//scanf("%s",str);
	j=0;kk=0;
	for(i=0;i<16;i++){
		if(i%4==0 && i!=0) {
			kk++;
			j=0;
		}
	    key[j][kk] = k[i];
	    key_copy[j][kk] = k[i];
	    plain[j][kk] = p[i];
		j++;
	}
	printf("Printing key(decimal):: \n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			printf("%d ",key[i][j]);
		printf("\n");
	}
	printf("Printing key_copy(decimal):: \n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			printf("%d ",key_copy[i][j]);
		printf("\n");
	}
	printf("Printing plain(decimal):: \n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			printf("%d ",plain[i][j]);
		printf("\n");
	}
	
	//------------------------------Encryption Starts from here--------------------------------
	//Initial whitening round
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			plain[i][j]=plain[i][j] ^ key[i][j];
		//printf("\n");
	}
	print_plain();
	//saving in R0,R1,R2 and R3
	set_Rs(); //print_r(r0);
	
	//16 rounds---Function F starts from here
	generate_skey(); //it will set S0 and S1
	for(ro=0;ro<16;ro++){
		rotate_left(r1,8);
		//Function F starts from here
		//s-box 
		r0[0] = p_0[r0[0]]^s0[0]; 
		r0[0] = p_0[r0[0]]^s1[0];
		r0[0] = p_1[r0[0]];
		r1[0] = p_0[r1[0]]^s0[0]; 
		r1[0] = p_0[r1[0]]^s1[0];
		r1[0] = p_1[r1[0]];
		
		r0[1] = p_1[r0[1]]^s0[0]; 
		r0[1] = p_0[r0[1]]^s1[0];
		r0[1] = p_0[r0[1]];
		r1[1] = p_1[r1[1]]^s0[0]; 
		r1[1] = p_0[r1[1]]^s1[0];
		r1[1] = p_0[r1[1]];
		
		r0[2] = p_0[r0[2]]^s0[0]; 
		r0[2] = p_1[r0[2]]^s1[0];
		r0[2] = p_1[r0[2]];
		r1[2] = p_0[r1[2]]^s0[0]; 
		r1[2] = p_1[r1[2]]^s1[0];
		r1[2] = p_1[r1[2]];
		
		r0[3] = p_1[r0[3]]^s0[0]; 
		r0[3] = p_1[r0[3]]^s1[0];
		r0[3] = p_0[r0[3]];
		r1[3] = p_1[r1[3]]^s0[0]; 
		r1[3] = p_1[r1[3]]^s1[0];
		r1[3] = p_0[r1[3]];
		
		//mds
		for(i=0;i<4;i++){
			sum = 0;
			for(j=0;j<4;j++){
				sum=sum+r0[j]*mds[i][j];
			}
			temp_r[i] = sum%256;
		}
		
		//pht
		val1 = r0[0]*1 + r0[1]*16 + r0[2]*256 + r0[3]*4096;
		val2 = r1[0]*1 + r1[1]*16 + r1[2]*256 + r1[3]*4096 ;	
		val_0 = fmod((val1+val2), pow(2,32));		
		val_1 = fmod((val2+val_0), pow(2,32));
		//round keys k11 k22
		generate_rkey();
		val1 = k11[0]*1 + k11[1]*16 + k11[2]*256 + k11[3]*4096;
		val2 = k22[0]*1 + k22[1]*16 + k22[2]*256 + k22[3]*4096 ;	
		val_0 = fmod((val_0+val1), pow(2,32));		
		val_1 = fmod((val_1+val2), pow(2,32));
		
		//xor r0 and r2
		for(i=0;i<4;i++) r2[i] = r0[i] ^ r2[i];
		rotate_right(r2);
		rotate_left(r3,1);
		for(i=0;i<4;i++) r3[i] = r1[i] ^ r3[i];
		//print_r(r0_copy);print_r(r1_copy);print_r(r2);print_r(r3);
		//swap (r0,r1) with (r2,r3)
		if(ro<15)
			swap(r0_copy,r1_copy,r2,r3);
		//print_r(r0);print_r(r1);print_r(r2);print_r(r3);
	}
	printf("\nEncrypted Text:: \n");
	print_r(r0);print_r(r1);print_r(r2);print_r(r3);
	return 0;
}
