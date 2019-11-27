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
	//正向创建链表
//	printf("11");
	head=Createlink1(a);
	//移动函数
//	printf("2");
	head=Prelink(head); 
//	printf("3");
	 
	//输出单向链表
	Printlink(head); 
} 
ElemSN * Createlink1(int a[]){      //创建函数 

	ElemSN *h,*tail,*p;
	//创建链表
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
ElemSN * Prelink(ElemSN * h){      //移动函数 
  ElemSN * h1=NULL,*p,*q,*pk,*t;
  p=h;
 // printf("1\n"); 
  while(p){
  //	printf("1\n"); 
  	if(p->data%2){   //为奇数 删奇数留偶数  奇数存入名义上的另一个链表 
	 pk=p;      
	  if(p==h)       //如果p为头节点 
	  	h=p=h->next;   //h，p指到下一个节点 
	  else{         //p为中间节点 
	  	q->next=p->next;   //前驱节点与后继节点相连 
	  	p=q->next;     //q后移 
	  }
	  pk->next=h1;
	  h1=pk;
	//  printf("1\n"); 
  	}
	else{    // 如果为偶数，两指针联动 
	  	q=p;
		p=p->next;
	}
  
  }    //将偶链表头节点与奇链表尾节点相连 将奇偶链表连起来
  if(h1!=NULL){          //判断有没有奇数据，如果没有h1指空，会造成出错 
	  for(t=h1;t->next;t=t->next);   //让t为奇链表头节点并移到尾节点 
	  	t->next=h;
	  }
	else{
		h1=h;	
	} 
  return h1;    //返回头节点 
	
}

void Printlink(ElemSN *h){       //输出函数 
	ElemSN *p;
	for(p=h;p!=NULL;p=p->next)
	printf("  %d",p->data);
	
}

