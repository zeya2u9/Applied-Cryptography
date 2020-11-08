/***
Input key and plaintext in main
***/
#include<stdio.h>
#include<stdint.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define print(a) printf("%d ",a);
char stream[1000];
int row=0,col=0,key[4][4]={0},plain[4][4]={0},key_copy[4][4]={0};
static const uint8_t Rcon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
static const int mds[4][4] = {{2,3,1,1},{1,2,3,1},{1,1,2,3},{3,1,1,2}};
static const int in_mds[4][4] = {{2,3,1,1},{1,2,3,1},{1,1,2,3},{3,1,1,2}};
static const uint8_t sbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };
static const uint8_t rsbox[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };
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
void set_roundKey( int r ){ //gives key from round[1-10]key for round-0 is already in main
	int i,j,k_temp[4]={0};
	
	//rotword last column
	k_temp[0] = key[1][3]; k_temp[1] = key[2][3];k_temp[2] = key[3][3];k_temp[3] = key[0][3];
	
	//sub-bytes from s-box
	for(i=0;i<4;i++){
		set_row_col(k_temp[i]);	//print(k_temp[i]);
		k_temp[i] = sbox[row*16 + col];
	}	
	//get each column
	key[0][0]= key[0][0] ^ k_temp[0] ^ Rcon[r-1]; //print(key[0][0]);
	key[1][0]= key[1][0] ^ k_temp[1] ^ 0;
	key[2][0]= key[2][0] ^ k_temp[2] ^ 0;
	key[3][0]= key[3][0] ^ k_temp[3] ^ 0;
	for(i=1;i<4;i++){
		for(j=0;j<4;j++){
			key[j][i] = key[j][i] ^ key[j][i-1];
		}	
	}
}
void inv_set_roundKey(int r){
	int i,j;
	//first setting key to key-0 via key_copy
	//printf("\n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			key[i][j] = key_copy[i][j];
			//printf("%d ",key_copy[i][j]);			
		}	//printf("\n");
	}
	//print_key();
	for(i=1;i<=r;i++ ){ 
		set_roundKey(i); 
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
void add_roundKey(){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			plain[i][j]=plain[i][j] ^ key[i][j];
		//printf("\n");
	}
}
void sub_bytes(){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			set_row_col(plain[i][j]);	
			plain[i][j] = sbox[row*16 + col];
		}
	}	
}
void in_sub_bytes(){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			set_row_col(plain[i][j]);	
			plain[i][j] = rsbox[row*16 + col];
		}
	}	
}
void inverse_shift_rows(){
	int i,j,k;
	i=plain[1][3];
	plain[1][3] = plain[1][2];  plain[1][2] = plain[1][1];  plain[1][1] = plain[1][0]; plain[1][0] = i;
	i=plain[2][3]; 
	j=plain[2][2];
	plain[2][3] = plain[2][1];  plain[2][2] = plain[2][0];  plain[2][1] = i; plain[2][0] = j;
	i=plain[3][3]; 
	j=plain[3][2];
	k=plain[3][1];
	plain[3][3] = plain[3][0];  plain[3][2] = i;  plain[3][1] = j; plain[3][0] = k;
}
void shift_rows(){
	int i,j,k;
	i=plain[1][0];
	plain[1][0] = plain[1][1];  plain[1][1] = plain[1][2];  plain[1][2] = plain[1][3]; plain[1][3] = i;
	i=plain[2][0]; 
	j=plain[2][1];
	plain[2][0] = plain[2][2];  plain[2][1] = plain[2][3];  plain[2][2] = i; plain[2][3] = j;
	i=plain[3][0]; 
	j=plain[3][1];
	k=plain[3][2];
	plain[3][0] = plain[3][3];  plain[3][1] = i;  plain[3][2] = j; plain[3][3] = k;
}
void mix_column(){
	int i,j,k,mult=0,sum=0;
	int temp[4][4]={0};
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			mult=0;
			for(k=0;k<4;k++){
				if(mds[i][k] > 2){ 
					sum = plain[k][j]*2 ; 
					if(sum>255) sum =sum ^ 283;
					sum = sum ^ plain[k][j]; 
				}
				else{ sum = plain[k][j]*mds[i][k];	
					if(sum>255) sum =sum ^ 283;
				}
				mult = sum ^ mult;
			}
			temp[i][j] = mult;
		}
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){	
			plain[i][j] = temp[i][j];
		}
	}		
}
int main()
{
	//int k[16]={'T','E','A','M','S','C','O','R','P','I','A','N','1','2','3','4'};
	int k[16]={'T','h','a','t','s',' ','m','y',' ','K','u','n','g',' ','F','u'};
	//int k[16]={0x2b, 0x7e, 0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	//int k[16]={0x0f, 0x15, 0x71,0xc9,0x47,0xd9,0xe8,0x59,0x0c,0xb7,0xad,0xd6,0xaf,0x7f,0x67,0x98};
	//int p[16]={0x01, 0x23, 0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	int p[16]={'T','w','o',' ','O','n','e',' ','N','i','n','e',' ','T','w','o'};
	int c[16];
	char str[16];
	int i,j,kk,value=0;
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
	//Initial round 1-round done
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			plain[i][j]=plain[i][j] ^ key[i][j];
		//printf("\n");
	}
	//print_plain();
	
	//main rounds   
	for(i=1;i<10;i++){
		//printf("\nRound = %d",i);
		set_roundKey(i); 
		sub_bytes(); //Sub-bytes
		//print_plain();
		shift_rows();//Shift Rows
		//print_plain();
		mix_column();//Mix columns
		//print_plain();
		add_roundKey();	//Add round key
		//print_plain();
	}
	//last round
	set_roundKey(10);
	//print_plain();
	sub_bytes(); //Sub-bytes
	//print_plain();
	shift_rows();//Shift Rows
	//print_plain();
	add_roundKey();	//Add round key
	printf("\nEncrypted text::\n");
	print_plain();
	//Encryption Ends Here
	
	//-----------Decryption starts here--------------------------//
	add_roundKey(); //print_plain(); //same
	
	for(i=9;i>0;i--){
		inv_set_roundKey(i); //print_key();
		inverse_shift_rows(); //print_plain();
		in_sub_bytes(); //print_plain();				
		add_roundKey(); //print_plain();
		for(j=0;j<3;j++) mix_column(); //M4 = I so M3 = M(inverse)
		//print_plain();
	}
	inv_set_roundKey(0);
	inverse_shift_rows(); //print_plain();
	in_sub_bytes(); //print_plain();
	add_roundKey(); 
	printf("\nDecrypted Text::\n");
	print_plain();
	//Decryption Ends here
	/*for(i=1;i<2;i++){
		printf("Round = %d",i);
		inv_set_roundKey(i); 
		print_key();
	}*/
	return 0;
}
