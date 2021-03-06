
#pragma once
#include<stdio.h>


typedef struct Stack{
	int array[100];
	int top;
} Stack;

//��ʼ��
void StackInit(Stack *stack){
	stack->top = 0;
}
//ѹջ(˳�����β��)
void StackPush(Stack *stack, int value){
	stack->array[stack->top] = value;
	stack->top++;
}
//��ջ,����
void StackPop(Stack *stack){
	stack->top--;
}
//����ջ��Ԫ��
int StackTop(const Stack *stack){
	return stack->array[stack->top - 1];
}
//�ж��Ƿ�Ϊ��
int StackEmpty(const Stack *stack){
	return stack->top == 0 ? 1 : 0; 
}
//��ȡsize
int StackSize(const Stack *stack){
	return stack->top;
}

void StackDestroy( Stack*stack)
{
	stack->top = 0;
}
#if 0
//1. ����ƥ��
bool isValid(char * s){
	Stack stack;
	StackInit(&stack);

	while (*s != '\0'){
		switch (*s)
		{
		case'{':
		case'[':
		case'(':
			StackPush(&stack, (int)*s);
			break;
		case'}':
		case']':
		case')':
			if (StackEmpty(&stack)){
				return false;
			}
			char left = (char)StackTop(&stack);
			StackPop(&stack);
			if (!(left == '('&&*s == ')'
				|| left == '['&&*s == ']'
				|| left == '{'&&*s == '}')){
				return false;
			}
			break;
		default:
			;
			break;
		}
		s++;
	}
	if (!StackEmpty(&stack)){
		return false;
	}

	return true;
}
#endif