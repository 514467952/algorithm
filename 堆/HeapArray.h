
#pragma once
#include"Heap.h"
#include<stdio.h>
/*
���µ���
array ����Ŀ�ʼλ��
size ����ĳ���
root Ҫ�����Ľ����±�
*/

void AdjustDown222(int array[], int size, int root);
void AdjustDown(int array[], int size, int root)
{
	//�ж� root �Ƿ���Ҷ�ӽ��
	//��Ϊ ������ȫ������������û������һ��û���Һ���
	//����Ϊ����˳��洢��
	//���ԣ��ҵ����ӵ��±꣬������ӵ��±�Խ���ˣ���û������
	while (1)
	{
		int left = 2 * root + 1;
		if (left >= size){
			//Խ���ˣ�����Ҷ�ӽ��
			return;
		}

		//��������һ�������ӣ��ж��Ƿ����Һ���
		//�ҵ����Һ�����С��һ��
		int right = 2 * root +2;
		int min = left;//�ʼ����Ϊ��С��ֵΪ����
		if (right < size && array[right] < array[left]){
			//û��Խ��,�����Һ��ӣ�����Һ��ӵ�ֵС�����ӵ�ֵ
			min = right;
		}

		//�Ƚ�array[min]  array[root]
		if (array[root] <= array[min]){
			return;
		}

		//����,����ֵ
		int t = array[root];
		array[root] = array[min];
		array[min] = t;

		//��Ҫ�������µ�������min��Ϊ���
		root = min;
	}
}

//����
void CreateHeap(int array[], int size)
{
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustDown222(array, size, i);
	}
}


void PrintArray(int array[], int size)
{
	for (int i =0; i < size; ++i){
		printf("%  d", array[i]);
	}
	printf("\n");
}

//��ȷ����O(n)
//���ԵĿ���O(nlog n)
void TestAdjustDown()
{
	int array[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	int size = sizeof array / sizeof(int);
	PrintArray(array, size);

	AdjustDown(array, size, 0);
	PrintArray(array, size);
}

void TestCreateHeap(){
	int array[] = { 15, 37, 2, 45, 63, 9, 18, 7, 16, 13 };
	int size = sizeof(array) / sizeof(int);

	CreateHeap(array, size);
	PrintArray(array, size);
}