
#pragma once
#include"Heap.h"
#include<stdio.h>
/*
向下调整
array 数组的开始位置
size 数组的长度
root 要调整的结点的下标
*/

void AdjustDown222(int array[], int size, int root);
void AdjustDown(int array[], int size, int root)
{
	//判断 root 是否是叶子结点
	//因为 堆是完全二叉树，所以没有左孩子一定没有右孩子
	//又因为堆是顺序存储的
	//所以，找到左孩子的下标，如果左孩子的下标越界了，则没有左孩子
	while (1)
	{
		int left = 2 * root + 1;
		if (left >= size){
			//越界了，就是叶子结点
			return;
		}

		//走完上面一定有左孩子，判读是否有右孩子
		//找到左右孩子最小的一个
		int right = 2 * root +2;
		int min = left;//最开始就认为最小的值为左孩子
		if (right < size && array[right] < array[left]){
			//没有越界,就有右孩子，如果右孩子的值小于左孩子的值
			min = right;
		}

		//比较array[min]  array[root]
		if (array[root] <= array[min]){
			return;
		}

		//调整,交换值
		int t = array[root];
		array[root] = array[min];
		array[min] = t;

		//需要继续向下调整，以min作为结点
		root = min;
	}
}

//建堆
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

//精确的是O(n)
//粗略的看成O(nlog n)
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