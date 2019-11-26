#include<stdio.h>
int add1(int n){
	if(n==0)
	return 0;
	else
	return add1(n/10)+n%10;
}    
int main(void){
	int n,s;
	printf("ÇëÊäÈënµÄÖµ\n");
	scanf("%d",&n);
	s=add1(n);
	printf("s=%d",s);
	
} 
