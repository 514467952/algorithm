#include<stdio.h>
#include<stdlib.h>
#define N 5
typedef struct node{
	int data;
	struct node *next;
}ElemSN;
int main(void){
	ElemSN * Createlink1(int a[]);
	void Printlink(ElemSN *h);
	ElemSN * Prelink(ElemSN * h);
	int a[N]={1,20,3,40,50},key;
	
	ElemSN *head=NULL,*Pkey;
	//���򴴽�����
//	printf("11");
	head=Createlink1(a);
	//�ƶ�����
//	printf("2");
	head=Prelink(head); 
//	printf("3");
	 
	//�����������
	Printlink(head); 
} 
ElemSN * Createlink1(int a[]){      //�������� 

	ElemSN *h,*tail,*p;
	//��������
	h=tail=(ElemSN *)malloc(sizeof(ElemSN));
	h->data=a[0];
	h->next=NULL;
	for(int i=1;i<N;i++){
		p=(ElemSN *)malloc(sizeof(ElemSN));
		p->data=a[i];
		p->next=NULL;
		tail->next=p;
		tail=p;
	} 
	return h;
}
ElemSN * Prelink(ElemSN * h){      //�ƶ����� 
  ElemSN * h1=NULL,*p,*q,*pk,*t;
  p=h;
 // printf("1\n"); 
  while(p){
  //	printf("1\n"); 
  	if(p->data%2){   //Ϊ���� ɾ������ż��  �������������ϵ���һ������ 
	 pk=p;      
	  if(p==h)       //���pΪͷ�ڵ� 
	  	h=p=h->next;   //h��pָ����һ���ڵ� 
	  else{         //pΪ�м�ڵ� 
	  	q->next=p->next;   //ǰ���ڵ����̽ڵ����� 
	  	p=q->next;     //q���� 
	  }
	  pk->next=h1;
	  h1=pk;
	//  printf("1\n"); 
  	}
	else{    // ���Ϊż������ָ������ 
	  	q=p;
		p=p->next;
	}
  
  }    //��ż����ͷ�ڵ���������β�ڵ����� ����ż����������
  if(h1!=NULL){          //�ж���û�������ݣ����û��h1ָ�գ�����ɳ��� 
	  for(t=h1;t->next;t=t->next);   //��tΪ������ͷ�ڵ㲢�Ƶ�β�ڵ� 
	  	t->next=h;
	  }
	else{
		h1=h;	
	} 
  return h1;    //����ͷ�ڵ� 
	
}

void Printlink(ElemSN *h){       //������� 
	ElemSN *p;
	for(p=h;p!=NULL;p=p->next)
	printf("  %d",p->data);
	
}

