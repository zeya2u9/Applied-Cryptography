#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
void byte_to_hex(int *buf,int n){
	int i;
	const char * hex = "0123456789ABCDEF";
	char str[100], * pout = str;
	str[0]='\0';
    for(i=0; i < n; ++i){
    	//printf("%d ",*buf);
        *pout++ = hex[(*buf>>4)&0xF];
        *pout++ = hex[(*buf++)&0xF];
        //*pout++ = ':';
	}
	str[n*2]='\0';
	printf("%s \n",str);
}
int getNum(char ch)
{
    int num=0;
    if(ch>='0' && ch<='9')
    {
        num=ch-0x30;
    }
    else
    {
        switch(ch)
        {
            case 'A': case 'a': num=10; break;
            case 'B': case 'b': num=11; break;
            case 'C': case 'c': num=12; break;
            case 'D': case 'd': num=13; break;
            case 'E': case 'e': num=14; break;
            case 'F': case 'f': num=15; break;
            default: num=0;
        }
    }
    return num;
}
int hex2int(char hex[])
{
    int x=0;
    x=(getNum(hex[0]))+(getNum(hex[1]))*16;
    
    return x;
}

int main()
{
	int i,j,l,kk,s[256],k[320],t[320],kstr,rev[200];
	int len,temp,ct[200],pt[200]={0},lent;
	char str[80],ch[2];
	int num[320];
	fflush(stdin);
	
	printf("Enter key(in hex format):: 0x");
	gets(str);
	//procesing input hex key
	j=(strlen(str)/2) -1;
	//j=0;
	printf("%s",str[strlen(str)]);
	for(i=strlen(str)-1;i>0;i-=2){
		ch[0]=str[i];
		ch[1]=str[i-1];		
		num[j]=hex2int(ch);	
		j--;
	}
	
	//done
	printf("\nEnter length of the plaintext((text is all zeros)):: ");
	//gets(pt);
	scanf("%d",&lent);
	printf("\n");
	
	//len = strlen(str)/2;
	len = strlen(str)/2;
	//initialize stream and key
	for(i=0;i<256;i++){
		s[i] = i;
		t[i] = num[i%len];
		//printf("%d ",t[i]);
	}
	printf("\n");
	//KEYGEN
	j=0;
	for(i=0;i<256;i++){
		j = (j+s[i]+t[i]) % 256;
		temp=s[i];
		s[i]=s[j];
		s[j]=temp;
	}
	
	//PseudoRandomGeneration
	len = strlen(pt);
	i=0;
	j=0;
	for(l=0;l<lent;l++){
		i = (i+1) % 256;
		j = (j+s[i]) % 256;
		temp=s[i];
		s[i]=s[j];
		s[j]=temp;
		kk = (s[i]+s[j]) % 256;
		ct[l] = pt[l] ^ s[kk];
		//printf("%c",ct[l]);
		
		//decrypting for verification purpose
		rev[l] = s[kk];		
	}
	//encrypted text
	printf("\nEncrypted Text(In HEX):: 0x");
	byte_to_hex(ct,lent);
	
	for(i=0;i<l;i++){
		//printf("%d ",ct[i]);
		//byte_to_hex(ct[i]);
		//printf("%c",byte_to_hex(ct[i])) ;
	}
	
	printf("\nDecrypted Text:: ");
	//decrypted text
	for(i=0;i<l;i++){
		printf("%d",(ct[i]^rev[i]) );
	}
	
	
	
	return 0;
}

